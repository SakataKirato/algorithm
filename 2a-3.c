#include "gmp_stdio.h"
#include <stdlib.h>
#include <string.h>

void chainlength(mpz_t n, mpz_t length) {
  mpz_t t;
  mpz_init_set(t, n);    // t = n
  mpz_set_ui(length, 0); // length = 0

  while (1) {
    if (mpz_cmp_ui(t, 1) != 0) {
      gmp_printf("%Zd,", t); // print t
    } else {
      gmp_printf("%Zd\n", t); // print t
    }
    mpz_add_ui(length, length, 1); // length++

    if (mpz_cmp_ui(t, 1) == 0) // if (t == 1)
      break;

    mpz_mul_ui(t, t, 3); // t = 3*t
    mpz_add_ui(t, t, 1); // t = t+1

    while (mpz_even_p(t)) {     // while even
      mpz_divexact_ui(t, t, 2); // t /= 2
    }
  }

  mpz_clear(t);
}

void make_target(mpz_t n, unsigned long long m) {
  mpz_ui_pow_ui(n, 2, m);   // n = 2^m
  mpz_sub_ui(n, n, 1);      // n = 2^m - 1
  mpz_divexact_ui(n, n, 3); // n /= 3
}

int main(int argc, char *argv[]) {
  unsigned long long m = strtol(argv[1], NULL, 10);

  FILE *fp = fopen("output.txt", "w");
  if (!fp) {
    perror("fopen");
    return 1;
  }

  mpz_t n, length;
  mpz_init(n);
  mpz_init(length);

  make_target(n, m);

  chainlength(n, length);
  gmp_fprintf(fp, "%Zd\n", n);               // fprint n
  gmp_printf("chainlength = %Zd\n", length); // print length

  mpf_t ratio, f_n;
  mpf_init2(ratio, 20000);
  mpf_init2(f_n, 20000);

  mpf_set_z(ratio, length);     // ratio = length
  mpf_set_z(f_n, n);            // f_n = n
  mpf_div(ratio, ratio, f_n);   // ratio /= f_n
  gmp_printf("%.3Fe\n", ratio); // print ratio

  mpf_clear(ratio);
  mpf_clear(f_n);
  mpz_clear(n);
  mpz_clear(length);
  fclose(fp);
  return 0;
}

// brew install gmp
// brew reinstall gmp
// gcc 2a-3.c -I/opt/homebrew/include -L/opt/homebrew/lib -lgmp