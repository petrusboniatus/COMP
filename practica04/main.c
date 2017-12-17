#include <stdio.h> 
#include <sys/time.h>
aqui

double res[N];
int main() {


  struct timeval inicio, final;
  double tiempo;

  for(int i = 0; i < N; i++)
    res[i] = 0;

  gettimeofday(&inicio,NULL);
  int i;
  double x;
  for (i = 0; i < N; i++)
    res[i] = 0.0005 * i;
  for (i = 0; i < N; i++) {
    x = res[i];
    if (x < 10.0e6) x = x * x + 0.0005;
    else x = x - 1000;
    res[i] += x;
  }
  gettimeofday(&final,NULL);

  tiempo = (final.tv_sec-inicio.tv_sec+(final.tv_usec-inicio.tv_usec)/1.e6);
  printf("resultado= %e tiempo: %lf \n", res[N - 1], tiempo);
  return 0;
}
