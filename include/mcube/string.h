/**
 * @file include/mcube/string.h
 *
 * @author Hiroyuki Chishiro
 */
#ifndef __MCUBE_MCUBE_STRING_H__
#define __MCUBE_MCUBE_STRING_H__

#ifndef __ASSEMBLY__

#if !CONFIG_ARCH_SIM

void *memset(void *s, int c, size_t n);
void *memset32(void *dst, uint32_t val, uint64_t len);
void *memset64(void *dst, uint64_t val, uint64_t len);

int memcmp(const void *s1, const void *s2, size_t n);

void *memcpy(void *dst, const void *src, size_t n);
void *memcpy_nocheck(void *restrict dst, const void *restrict src, size_t len);
void *memcpy_forward(void *dst, const void *src, size_t len);
void *memcpy_forward_nocheck(void *dst, const void *src, size_t len);

void *memmove(void *dst, const void *src, size_t n);
size_t strlen(const char *s);
size_t strnlen(const char *str, int n);
int strcmp(const char *s, const char *t);
int strncmp(const char *s1, const char *s2, size_t n);
char *strcpy(char *s, const char *t);
char *strncpy(char *s, const char *t, size_t);
char *strcat(char *s, const char *t);
char *strncat(char *s, const char *t, size_t n);
char *strchr(const char *s, int c);
char *strtok(char *str, const char *delim);

#endif /* !CONFIG_ARCH_SIM */

#endif /* !__ASSEMBLY__ */

#endif /* __MCUBE_MCUBE_STRING_H__ */
