#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define P 5
#define N 23
#define EPS 1e-5

void calc_cov(double data[N][P], double A[P][P]) {
  double mean[P] = {0};
  for (int j = 0; j < P; j++) {
    for (int i = 0; i < N; i++) {
      mean[j] += data[i][j];
    }
    mean[j] /= N;
  }

  for (int k = 0; k < P; k++) {
    for (int l = 0; l < P; l++) {
      A[k][l] = 0.0;
      for (int i = 0; i < N; i++) {
        A[k][l] += (data[i][k] - mean[k]) * (data[i][l] - mean[l]);
      }
      A[k][l] /= N;
    }
  }
  return;
}

void print_vec(double x[]) {
  for (int i = 0; i < P; i++) {
    printf("%6.3f ", x[i]);
  }
  printf("\n");
}

void multi_mat_vec(double y[], double A[][P], double x[]) {
  for (int i = 0; i < P; i++) {
    y[i] = 0.0;
    for (int j = 0; j < P; j++) {
      y[i] += A[i][j] * x[j];
    }
  }
}

double inner_prod(double x[], double y[]) {
  double prod = 0.0;
  for (int i = 0; i < P; i++) {
    prod += x[i] * y[i];
  }
  return prod;
}

void normalize_vec(double y[], double x[]) {
  double length = sqrt(inner_prod(y, y));
  for (int i = 0; i < P; i++) {
    x[i] = y[i] / length;
  }
}

void poweigen(double A[][P], double *x, double *eigen_value) {
  double y[P];
  double l = 0.0, old_l = 1.0;

  while (fabs(l-old_l) > EPS*fabs(l)) {
    old_l = l;
    multi_mat_vec(y, A, x);
    l = inner_prod(x, y);
    normalize_vec(y, x);
  }
  *eigen_value = l;
}

int main(int argc, char *argv[]) {
  double lambda;
  double data[][P] = {
    {55, 84, 29, 33, 79},
    {72, 97, 71, 68, 64},
    {79, 100, 74, 91, 76},
    {58, 85, 52, 56, 60},
    {96, 98, 77, 92, 88},
    {66, 88, 60, 85, 66},
    {73, 95, 81, 91, 63},
    {72, 92, 61, 84, 78},
    {81, 96, 70, 75, 67},
    {73, 92, 53, 70, 51},
    {96, 97, 69, 64, 57},
    {90, 100, 87, 89, 85},
    {96, 98, 83, 75, 81},
    {67, 86, 76, 61, 57},
    {78, 97, 87, 82, 82},
    {78, 94, 77, 80, 70},
    {45, 96, 38, 43, 12},
    {78, 95, 67, 73, 67},
    {80, 100, 83, 77, 67},
    {56, 95, 47, 61, 21},
    {88, 96, 70, 62, 51},
    {63, 92, 81, 51, 66},
    {36, 84, 51, 16, 48}
  };
  double A[P][P];
  double x[P] = {};
  x[0] = 1;

  calc_cov(data, A);

  poweigen(A, x, &lambda);
  printf("第１主成分 : ");
  print_vec(x);

  for (int i = 0; i < P; i++) {
    for (int j = 0; j < P; j++) {
      A[i][j] -= lambda * x[i] * x[j];
    }
  }

  for (int i = 0; i < P; i++)
    x[i] = 0;
  x[0] = 1;
  poweigen(A, x, &lambda);
  printf("第２主成分 : ");
  print_vec(x);

  return 0;
}
