#include "klib.h"

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t len = 0;
  while((*s++) != '\0') {
    len++;
  }
  return len;
}

char *strcpy(char* dst, const char* src) {
  return strncpy(dst, src, strlen(src));
}

char* strncpy(char* dst, const char* src, size_t n) {
  if(n > strlen(src)) {
    n = strlen(src);
  }
  char *res = dst;
  while(n && (*dst++ = *src++)) {
    n--;
  }
  return res;
}

char* strcat(char* dst, const char* src) {
  char *tmp = dst;
  while(*dst) {
    dst++;
  }
  while((*dst++ = *src++) != 0);
  return tmp; 
}

int strcmp(const char* s1, const char* s2) {
  int t = 0;
  while((t = (*s1 - *s2)) == 0 && *s1 && *s2) {
    s1++;
    s2++;
  }
  return t;
}

int strncmp(const char* s1, const char* s2, size_t n) {
  while(n-- && *s1 && *s2) {
    if(*s1 == 0 || *s1 != *s2) {
      return *s1 - *s2;
    }
    s1++;
    s2++;
  }
  return 0;
}

void* memset(void* v, int c, size_t n) {
  for(size_t i = 0; i < n; i++) {
    ((int8_t*)v)[i] = c;
  }
  return v;
}

void* memcpy(void* out, const void* in, size_t n) {
  char *tmp = (char*)(out);
  const char *pin = (const char*)(in);
  if(tmp > pin && tmp < pin + n) {
    tmp = tmp + n - 1;
    pin = pin + n - 1;
    while(n--) {
      *tmp-- = *pin--;
    }
  }
  else {
    while(n--) {
      *tmp++ = *pin++;
    }
  }
  return tmp;
}

int memcmp(const void* s1, const void* s2, size_t n){
  const unsigned char *tmp1, *tmp2;
  int cnt = 0;
  for(tmp1 = s1, tmp2 = s2; n > 0; ++tmp1, ++tmp2, n--) {
    if((cnt = *tmp1 - *tmp2) != 0) {
      break;
    }
  }
  return cnt;
}

#endif
