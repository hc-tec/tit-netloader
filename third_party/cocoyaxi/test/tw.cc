#include "test.h"
#include "co/def.h"
#include "co/cout.h"
#include "co/str.h"
#include "co/fastream.h"
#include "co/time.h"
#include <algorithm>

#ifndef _WIN32
#define max std::max
#endif

int64 QS(const char* s, int64 n, const char* x, int64 m) {
    if (n < m) return -1;

    typedef unsigned char u8;
    int64 tbl[256] = { 0 };
    for (int64 i = 0; i < m; ++i) tbl[(const u8)x[i]] = m - i;

    int64 j = 0;
    while (j <= n - m) {
        if (memcmp(x, s + j, m) == 0) return j;
        int64 x = tbl[(int)s[j + m]];
        if (x == 0) x = m + 1;
        j += x;
    }
    return -1;
}

inline int64 QS(const char* s, const char* x) {
    return QS(s, strlen(s), x, strlen(x));
}

int64 RQS(const char* str, int64 n, const char* sub, int64 m) {
    if (n < m) return -1;

    const unsigned char* s = (const unsigned char*) str;
    const unsigned char* p = (const unsigned char*) sub;

    int64 tbl[256] = { 0 };
    for (int64 i = m; i > 0; --i) tbl[p[i - 1]] = i;

    for (int64 j = n - m;;) {
        if (memcmp(p, s + j, m) == 0) return j;
        if (j == 0) return -1;

        int64 x = tbl[s[j - 1]];
        if (x == 0) x = m + 1;
        if (j < x) return -1;
        j -= x;
    }

    return -1;
}

inline int64 RQS(const char* s, const char* x) {
    return RQS(s, strlen(s), x, strlen(x));
}

// Two-Way algorithm
//   search substring x in string s
//   @n: length of @s
//   @m: length of @x
void  tw_init(const char* x, int64 m, int64* p, int64* q);
int64 tw_find(const char* s, int64 n, const char* x, int64 m, int64 p, int64 q);

// Two-Way reverse search
void  tw_rinit(const char* x, int64 m, int64* p, int64* q);
int64 tw_rfind(const char* s, int64 n, const char* x, int64 m, int64 p, int64 q);

inline int64 tw_find(const char* s, int64 n, const char* x, int64 m) {
    int64 p, q;
    tw_init(x, m, &p, &q);
    return tw_find(s, n, x, m, p, q);
}

inline int64 tw_find(const char* s, const char* x) {
    return tw_find(s, strlen(s), x, strlen(x));
}

inline int64 tw_rfind(const char* s, int64 n, const char* x, int64 m) {
    int64 p, q;
    tw_rinit(x, m, &p, &q);
    return tw_rfind(s, n, x, m, p, q);
}

inline int64 tw_rfind(const char* s, const char* x) {
    return tw_rfind(s, strlen(s), x, strlen(x));
}

void  tw_init(const char* x, int64 m, int64* p, int64* q) {
    char a, b;
    int64 s1 = -1, s2 = -1, p1 = 1, p2 = 1, j, k;

    // computing of the maximal suffix for <= 
    j = 0, k = 1;
    while (j + k < m) {
        a = x[j + k];
        b = x[s1 + k];

        if (a < b) {
            j += k;
            k = 1;
            p1 = j - s1;
        } else if (a == b) {
            k != p1 ? ++k : (j += p1, k = 1);
        } else { /* a > b */
            s1 = j;
            j = s1 + 1;
            k = p1 = 1;
        }
    }

    // computing of the maximal suffix for >= 
    j = 0, k = 1;
    while (j + k < m) {
        a = x[j + k];
        b = x[s2 + k];

        if (a > b) {
            j += k;
            k = 1;
            p2 = j - s2;
        } else if (a == b) {
            k != p2 ? ++k : (j += p2, k = 1);
        } else { /* a < b */
            s2 = j;
            j = s2 + 1;
            k = p2 = 1;
        }
    }

    if (s1 > s2) {
        *p = s1, *q = p1;
    } else {
        *p = s2, *q = p2;
    }
}

inline int64 tw_max(int64 x, int64 y) {
    return x < y ? y : x;
}

int64 tw_find(const char* s, int64 n, const char* x, int64 m, int64 ell, int64 per) {
    int64 i, j, memory;

    if (memcmp(x, x + per, ell + 1) == 0) {
        j = 0, memory = -1;
        while (j <= n - m) {
            i = tw_max(ell, memory) + 1;
            while (i < m && x[i] == s[i + j]) ++i;
            if (i >= m) {
                i = ell;
                while (i > memory && x[i] == s[i + j]) --i;
                if (i <= memory) return j;
                j += per;
                memory = m - per - 1;
            } else {
                j += (i - ell);
                memory = -1;
            }
        }

    } else {
        per = tw_max(ell + 1, m - ell - 1) + 1;
        j = 0;
        while (j <= n - m) {
            i = ell + 1;
            while (i < m && x[i] == s[i + j]) ++i;
            if (i >= m) {
                i = ell;
                while (i >= 0 && x[i] == s[i + j]) --i;
                if (i < 0) return j;
                j += per;
            } else {
                j += (i - ell);
            }
        }
    }

    return -1;
}

void  tw_rinit(const char* x, int64 m, int64* p, int64* q) {
    char a, b;
    int64 mm = m - 1, s1 = -1, s2 = -1, p1 = 1, p2 = 1, j, k;

    j = 0, k = 1;
    while (j + k < m) {
        a = x[mm - (j + k)];
        b = x[mm - (s1 + k)];

        if (a < b) {
            j += k;
            k = 1;
            p1 = j - s1;
        } else if (a == b) {
            k != p1 ? ++k : (j += p1, k = 1);
        } else { /* a > b */
            s1 = j;
            j = s1 + 1;
            k = p1 = 1;
        }
    }

    j = 0, k = 1;
    while (j + k < m) {
        a = x[mm - (j + k)];
        b = x[mm - (s2 + k)];

        if (a > b) {
            j += k;
            k = 1;
            p2 = j - s2;
        } else if (a == b) {
            k != p2 ? ++k : (j += p2, k = 1);
        } else { /* a < b */
            s2 = j;
            j = s2 + 1;
            k = p2 = 1;
        }
    }

    if (s1 > s2) {
        *p = s1, *q = p1;
    } else {
        *p = s2, *q = p2;
    }
}

int64 tw_rfind(const char* s, int64 n, const char* x, int64 m, int64 ell, int64 per) {
    if (unlikely(n < m)) return -1;

    int64 i, j, memory;
    int64 nn = n - 1, mm = m - 1, ee = ell + 1;

    const char* ex = x + mm - ee;
    if (memcmp(ex, ex - per, ee) == 0) {
        j = nn, memory = -1;
        while (j >= mm) {
            i = tw_max(ell, memory) + 1;
            while (i < m && x[mm - i] == s[j - i]) ++i;
            if (i >= m) {
                i = ell;
                while (i > memory && x[mm - i] == s[j - i]) --i;
                if (i <= memory) return j - mm;
                j -= per;
                memory = mm - per;
            } else {
                j -= (i - ell);
                memory = -1;
            }
        }

    } else {
        per = tw_max(ee, m - ee) + 1;
        j = nn;
        while (j >= mm) {
            i = ee;
            while (i < m && x[mm - i] == s[j - i]) ++i;
            if (i >= m) {
                i = ell;
                while (i >= 0 && x[mm - i] == s[j - i]) --i;
                if (i < 0) return j - mm;
                j -= per;
            } else {
                j -= (i - ell);
            }
        }
    }

    return -1;
}

inline int64 tw(const char* s, const char* x) {
    return tw_find(s, x);
}

inline int64 rtw(const char* s, const char* x) {
    return tw_rfind(s, x);
}

int main(int argc, char** argv) {
    CLOG << "hello world";

    def_test(100000);
    std::string ss = "hello world" + std::string(256, 'x');
    const char* s = ss.c_str();
    const char* p = "llo";

    CLOG << QS(s, "llo");
    CLOG << QS(s, "world");
    CLOG << QS(s, "xxxxx");
    CLOG << RQS(s, "llo");
    CLOG << RQS(s, "world");
    CLOG << RQS(s, "xxxxx");

    CLOG << tw(s, "llo");
    CLOG << tw(s, "world");
    CLOG << tw(s, "xxxxx");
    CLOG << rtw(s, "llo");
    CLOG << rtw(s, "world");
    CLOG << rtw(s, "xxxxx");
    CLOG << ss.rfind("xxxxx");

    int64 v;
    size_t r;
    const char* t;
    (void)v;

    def_case(v = QS(s, p));
    def_case(v = tw(s, p));
    def_case(r = ss.find(p));
    def_case(t = strstr(s, p));
    def_case(v = RQS(s, p));
    def_case(v = rtw(s, p));
    def_case(r = ss.rfind(p));

    int64 x, y, ls = strlen(s), lp = strlen(p);
    tw_rinit(p, strlen(p), &x, &y);
    def_case(v = tw_rfind(s, ls, p, lp, x, y));

    return 0;
}
