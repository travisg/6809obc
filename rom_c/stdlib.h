#pragma once

#include <stddef.h>
#include <stdint.h>

void putchar(char c);
void puts(const char *str);
int getchar(void);
void *memcpy(void *dest, const void *src, size_t count);
void *memset(void *dest, int c, size_t count);

