#ifndef _WIN32

#include "co/fs.h"
#include "co/mem.h"
#include "./co/hook.h"
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace fs {

bool exists(const char* path) {
    struct stat attr;
    return ::lstat(path, &attr) == 0;
}

bool isdir(const char* path) {
    struct stat attr;
    return ::lstat(path, &attr) == 0 && S_ISDIR(attr.st_mode);
}

int64 mtime(const char* path) {
    struct stat attr;
    return ::lstat(path, &attr) == 0 ? attr.st_mtime : -1;
}

int64 fsize(const char* path) {
    struct stat attr;
    return ::lstat(path, &attr) == 0 ? attr.st_size : -1;
}

// p = false  ->  mkdir
// p = true   ->  mkdir -p
bool mkdir(const char* path, bool p) {
    if (!p) return ::mkdir(path, 0755) == 0;

    const char* s = strrchr(path, '/');
    if (s == 0 || s == path) return ::mkdir(path, 0755) == 0;

    fastring parent(path, s - path);
    
    if (fs::exists(parent.c_str())) {
        return ::mkdir(path, 0755) == 0;
    } else {
        return fs::mkdir(parent.c_str(), true) && ::mkdir(path, 0755) == 0;
    }
}

bool mkdir(char* path, bool p) {
    if (!p) return ::mkdir(path, 0755) == 0;

    char* s = (char*) strrchr(path, '/');
    if (s == 0 || s == path) return ::mkdir(path, 0755) == 0;

    *s = '\0';
    if (fs::exists(path)) {
        *s = '/';
        return ::mkdir(path, 0755) == 0;
    } else {
        bool x = fs::mkdir(path, true);
        *s = '/';
        return x ? ::mkdir(path, 0755) == 0 : false;
    }
}

// rf = false  ->  rm or rmdir
// rf = true   ->  rm -rf
bool remove(const char* path, bool rf) {
    if (!fs::exists(path)) return true;

    if (!rf) {
        if (fs::isdir(path)) return ::rmdir(path) == 0;
        return ::unlink(path) == 0;
    } else {
        fastring cmd(strlen(path) + 9);
        cmd.append("rm -rf \"").append(path).append('"');
        FILE* f = popen(cmd.c_str(), "w");
        if (f == NULL) return false;
        return pclose(f) != -1;
    }
}

bool rename(const char* from, const char* to) {
    return ::rename(from, to) == 0;
}

bool symlink(const char* dst, const char* lnk) {
    fs::remove(lnk);
    return ::symlink(dst, lnk) == 0;
}

#define nullfd -1

namespace xx {
int open(const char* path, char mode) {
    if (mode == 'r') {
        return ::open(path, O_RDONLY);
    } else if (mode == 'a') {
        return ::open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    } else if (mode == 'w') {
        return ::open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    } else if (mode == 'm') {
        return ::open(path, O_WRONLY | O_CREAT, 0644);
    } else {
        return nullfd;
    }
}
} // xx

struct fctx {
    uint32 n;
    int fd;
};

file::file(size_t n) : _p(0) {
    const size_t x = n + sizeof(fctx) + 1;
    _p = co::alloc(x); assert(_p);
    fctx* p = (fctx*)_p;
    p->n = (uint32)x;
    p->fd = nullfd;
    *(char*)(p + 1) = '\0';
}

file::~file() {
    if (_p) {
        this->close();
        co::free(_p, ((fctx*)_p)->n);
        _p = 0;
    }
}

file::operator bool() const {
    fctx* p = (fctx*)_p;
    return p && p->fd != nullfd;
}

const char* file::path() const {
    return _p ? ((char*)_p + sizeof(fctx)) : "";
}

bool file::open(const char* path, char mode) {
    // make sure CO_RAW_API(close, read, write) are not NULL
    static bool kx = []() {
        if (CO_RAW_API(close) == 0) ::close(-1);
        if (CO_RAW_API(read) == 0)  { auto r = ::read(-1, 0, 0);  (void)r; }
        if (CO_RAW_API(write) == 0) { auto r = ::write(-1, 0, 0); (void)r; }
        return true;
    }();
    (void) kx;

    this->close();
    if (!path || !*path) return false;

    const uint32 n = (uint32)strlen(path) + 1;
    const uint32 x = n + sizeof(fctx);
    fctx* p = (fctx*)_p;

    if (!p || p->n < x) {
        _p = co::realloc(_p, p ? p->n : 0, x); assert(_p);
        p = (fctx*)_p;
        memcpy(p + 1, path, n);
        p->n = x;
    } else {
        memcpy(p + 1, path, n);
    }

    p->fd = xx::open(path, mode);
    return p->fd != nullfd;
}

void file::close() {
    fctx* p = (fctx*)_p;
    if (p && p->fd != nullfd) {
        while (CO_RAW_API(close)(p->fd) != 0 && errno == EINTR);
        p->fd = nullfd;
    }
}

void file::seek(int64 off, int whence) {
    static int seekfrom[3] = { SEEK_SET, SEEK_CUR, SEEK_END };
    fctx* p = (fctx*)_p;
    if (p && p->fd != nullfd) {
        whence = seekfrom[whence];
        ::lseek(p->fd, off, whence);
    }
}

size_t file::read(void* s, size_t n) {
    fctx* p = (fctx*)_p;
    if (!p || p->fd == nullfd) return 0;

    char* c = (char*)s;
    size_t remain = n;
    const size_t N = 1u << 30; // 1G

    while (true) {
        size_t toread = (remain < N ? remain : N);
        auto r = CO_RAW_API(read)(p->fd, c, toread);
        if (r > 0) {
            remain -= (size_t)r;
            if (remain == 0) return n;
            c += (size_t)r;
        } else if (r == 0) { /* end of file */
            return n - remain;
        } else {
            if (errno != EINTR) return n - remain;
        }
    }
}

fastring file::read(size_t n) {
    fastring s(n + 1);
    s.resize(this->read((void*)s.data(), n));
    return s;
}

size_t file::write(const void* s, size_t n) {
    fctx* p = (fctx*)_p;
    if (!p || p->fd == nullfd) return 0;

    const char* c = (const char*)s;
    size_t remain = n;
    const size_t N = 1u << 30; // 1G

    while (true) {
        size_t towrite = (remain < N ? remain : N);
        auto r = CO_RAW_API(write)(p->fd, c, towrite);
        if (r >= 0) {
            remain -= (size_t)r;
            if (remain == 0) return n;
            c += (size_t)r;
        } else {
            if (errno != EINTR) return n - remain;
        }
    }
}

#undef nullfd

} // namespace fs

#endif
