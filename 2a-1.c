#include <stdio.h>
#include <stdlib.h>
#define N 200000

unsigned long long chainlength(unsigned long long n) {
  unsigned long long length = 0;
  while (1) {
    length++;
    if (n == 1)
      break;
    n = 3 * n + 1;
    while (n % 2 == 0)
      n /= 2;
  }
  return length;
}

void Syracuse(size_t n) {
  unsigned long long *p =
      (unsigned long long *)malloc(n * sizeof(unsigned long long));
  for (size_t i = 0; i < n; i++) {
    unsigned long long odd = 2 * i + 1;
    p[i] = chainlength(odd);
    printf("%llu %llu\n", odd, p[i]);
  }
}

int main(int argc, char *argv[]) {
  Syracuse(strtol(argv[1], NULL, 10));
  return 0;
}