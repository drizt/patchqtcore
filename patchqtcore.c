#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRF "qt_prfxpath="

/*
 * https://stackoverflow.com/a/2188951
 *
 * The memmem() function finds the start of the first occurrence of the
 * substring 'needle' of length 'nlen' in the memory area 'haystack' of
 * length 'hlen'.
 *
 * The return value is a pointer to the beginning of the sub-string, or
 * NULL if the substring is not found.
 */
void *memmem(const void *haystack, size_t hlen, const void *needle, size_t nlen)
{
    int needle_first;
    const void *p = haystack;
    size_t plen = hlen;

    if (!nlen) {
        return NULL;
    }

    needle_first = *(unsigned char*)needle;

    while (plen >= nlen && (p = memchr(p, needle_first, plen - nlen + 1))) {
        if (!memcmp(p, needle, nlen)) {
            return (void*)p;
        }

        p++;
        plen = hlen - (p - haystack);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s Qt5Core.dll\n", argv[0]);
        return 0;
    }

    FILE *f = fopen(argv[1], "rb+");
    fseek(f, 0L, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0L, SEEK_SET);

    char *buf = (char*)malloc(sz);
    if (!buf) {
        printf("Not enough memory\n");
        fclose(f);
        free(buf);
        return 1;
    }

    if (fread(buf, 1, sz, f) != sz) {
        printf("Can't read file\n");
        fclose(f);
        free(buf);
        return 1;
    }

    char *prf = memmem(buf, sz, PRF, sizeof(PRF) - 1);

    if (!prf) {
        printf("Can't find \"%s\"\n", PRF);
        fclose(f);
        free(buf);
        return 1;
    }

    prf += sizeof(PRF) - 1;
    char *prf_end = strchr(prf, '\0');
    if (!prf_end) {
        printf("Can't find end of \"%s\"\n", PRF);
        fclose(f);
        free(buf);
        return 1;
    }

    fseek(f, prf - buf, SEEK_SET);
    fputc('.', f);
    for (int i = 1; i < prf_end - prf; ++i) {
        fputc('\0', f);
    }

    fclose(f);
    free(buf);
    return 0;
}
