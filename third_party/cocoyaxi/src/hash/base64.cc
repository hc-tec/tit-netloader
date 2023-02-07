#include "co/hash/base64.h"

fastring base64_encode(const void* p, size_t n) {
    const size_t k = n / 3;
    const int r = (int) (n - k * 3); // r = n % 3

    fastring v;
    v.resize((k + !!r) * 4);   // size: 4k or 4k + 4
    char* x = (char*) v.data();

    unsigned char a, b, c;
    const unsigned char* s = (const unsigned char*) p;
    const unsigned char* e = s + n - r;
    static const char* entab = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    for (; s < e; s += 3, x += 4) {
        a = s[0];
        b = s[1];
        c = s[2];
        x[0] = entab[a >> 2];
        x[1] = entab[((a << 4) | (b >> 4)) & 0x3f];
        x[2] = entab[((b << 2) | (c >> 6)) & 0x3f];
        x[3] = entab[c & 0x3f];
    }

    if (r == 1) {
        c = s[0];
        x[0] = entab[c >> 2];
        x[1] = entab[(c & 0x03) << 4];
        x[2] = '=';
        x[3] = '=';
    } else if (r == 2) {
        a = s[0];
        b = s[1];
        x[0] = entab[a >> 2];
        x[1] = entab[((a & 0x03) << 4) | (b >> 4)];
        x[2] = entab[(b & 0x0f) << 2];
        x[3] = '=';
    }

    return v;
}

fastring base64_decode(const void* p, size_t n) {
    fastring v(n * 3 >> 2); // size <= n * 3/4
    char* x = (char*) v.data();

    int m = 0, a, b, c, d;
    const unsigned char* s = (const unsigned char*) p;
    const unsigned char* e = s + n;
    static const int8 detab[256] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
        -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
        -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    };

    while (s + 8 <= e) {
        a = detab[s[0]] << 18;
        b = detab[s[1]] << 12;
        c = detab[s[2]] << 6;
        d = detab[s[3]];
        m = (a | b | c | d);
        if (unlikely(m < 0)) goto err;

        x[0] = (char) ((m & 0x00ff0000) >> 16);
        x[1] = (char) ((m & 0x0000ff00) >> 8);
        x[2] = (char) (m & 0x000000ff);
        s += 4, x += 3;

        if (*s == '\r' || *s == '\n') {
            ++s;
            if (*s == '\n' || *s == '\r') ++s;
        }
    }

    if (s == e) return v;
    if (e < s + 4) goto err;

    if (unlikely(e[-1] == '\n' || e[-1] == '\r')) {
        --e;
        if (e[-1] == '\r' || e[-1] == '\n') --e;
    }

    if (unlikely(e != s + 4)) goto err;

    do {
        a = detab[s[0]] << 18;
        b = detab[s[1]] << 12;
        m = (a | b);
        if (unlikely(m < 0)) goto err;
        *x++ = (char) ((m & 0x00ff0000) >> 16);

        if (s[2] == '=') {
            if (s[3] == '=') break;
            goto err;
        }

        m |= (detab[s[2]] << 6);
        if (unlikely(m < 0)) goto err;
        *x++ = (char) ((m & 0x0000ff00) >> 8);

        if (s[3] != '=') {
            m |= detab[s[3]];
            if (unlikely(m < 0)) goto err;
            *x++ = (char) (m & 0x000000ff);
        }
    } while (0);

    v.resize(x - v.data());
    return v;

  err:
    return fastring();
}
