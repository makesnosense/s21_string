#include <math.h>
#include <stdio.h>

int cat_nam(long double input_num);

void scale_input_and_calculate_exponent(long double* input_num);

int main() { printf("%d", cat_nam(549.45)); }

int cat_nam(long double input_num) {
  scale_input_and_calculate_exponent(&input_num);

  input_num = roundl(input_num);

  return (int)input_num;
}

void scale_input_and_calculate_exponent(long double* input_num) {
  while (*input_num >= 10.0 || *input_num < 1.0) {
    if (*input_num >= 10.0) {
      *input_num /= 10.0;
    } else {
      *input_num *= 10.0;
    }
  }
}