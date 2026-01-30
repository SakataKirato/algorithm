#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define REPEAT 12

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

unsigned long long *Syracuse(size_t n) {
  unsigned long long *p =
      (unsigned long long *)malloc(n * sizeof(unsigned long long));
  for (size_t i = 0; i < n; i++) {
    unsigned long long odd = 2 * i + 1;
    p[i] = chainlength(odd);
    // printf("%llu %llu\n", odd, p[i]);
  }
  return p;
}

void swap(unsigned long long *a, unsigned long long *b) {
  unsigned long long tmp = *a;
  *a = *b;
  *b = tmp;
}

void print(unsigned long long *array, size_t size) {
  for (int i = 0; i < size; i++) {
    printf("%llu ", array[i]);
  }
  printf("\n");
}

void quick(unsigned long long *array, int left, int right) {
  if (left >= right) {
    return;
  }

  unsigned long long pivot = array[(left + right) / 2];
  int i = left;
  int j = right;
  do {
    while (array[i] < pivot) {
      i++;
    }
    while (array[j] > pivot) {
      j--;
    }
    if (i <= j) {
      swap(&array[i], &array[j]);
      i++;
      j--;
    }
  } while (i <= j);
  quick(array, left, j);
  quick(array, i, right);
}

void quick_sort(unsigned long long *array, size_t size) {
  quick(array, 0, size - 1);
}

void insertion_sort(unsigned long long *array, size_t size) {
  for (size_t i = 1; i < size; i++) {
    for (int j = i - 1; j >= 0; j--) {
      if (array[j] <= array[j + 1])
        break;
      swap(&array[j], &array[j + 1]);
    }
  }
}

int main(int argc, char *argv[]) {
  const int N = 1 << strtol(argv[1], NULL, 10);
  unsigned long long *p = Syracuse(N);
  printf("Before: ");
  print(p, N);
  double time_q[REPEAT];
  double time_i[REPEAT];
  unsigned long long *q =
      (unsigned long long *)malloc(N * sizeof(unsigned long long));
  unsigned long long *i =
      (unsigned long long *)malloc(N * sizeof(unsigned long long));
  for (int r = 0; r < REPEAT; r++) {
    memcpy(q, p, N * sizeof(unsigned long long));
    double start_clock_q = (double)clock();
    quick_sort(q, N); // Quick Sort
    double end_clock_q = (double)clock();
    time_q[r] = (end_clock_q - start_clock_q) / CLOCKS_PER_SEC;

    memcpy(i, p, N * sizeof(unsigned long long));
    double start_clock_i = (double)clock();
    insertion_sort(i, N); // Insertion Sort
    double end_clock_i = (double)clock();
    time_i[r] = (end_clock_i - start_clock_i) / CLOCKS_PER_SEC;
  }
  double sum_q = 0.0;
  double sum_i = 0.0;
  double max_q = time_q[0];
  double max_i = time_i[0];
  double min_q = time_q[0];
  double min_i = time_i[0];
  for (int r = 0; r < REPEAT; r++) {
    sum_q += time_q[r];
    sum_i += time_i[r];
    if (time_q[r] > max_q)
      max_q = time_q[r];
    if (time_i[r] > max_i)
      max_i = time_i[r];
    if (time_q[r] < min_q)
      min_q = time_q[r];
    if (time_i[r] < min_i)
      min_i = time_i[r];
  }
  double avg_q = (sum_q - max_q - min_q) / (REPEAT - 2);
  double avg_i = (sum_i - max_i - min_i) / (REPEAT - 2);
  printf("After Quick Sort: ");
  print(q, N);
  printf("After Insertion Sort: ");
  print(i, N);
  printf("N = %d\n", N);
  printf("Quick Sort Time  : %.8lf s\n", avg_q);
  printf("Insertion Sort Time  : %.8lf s\n", avg_i);
  free(p);
  free(q);
  free(i);
  return 0;
}