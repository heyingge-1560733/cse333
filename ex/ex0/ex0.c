#include <stdio.h>
#include <stdlib.h>

// This program can estimate pi using Nilakantha's accelerated series
// of n (given number) terms in 20 digits procession
// Yingge He, 1560733, heyingge@uw.edu

double calc_pi(int degree) {
    if (degree == 0) {
       return 3;
    } else {
       double term = 4.0/((2 * degree) * (2 * degree + 1) * (2 * degree + 2));
       if (degree % 2 == 0) {
          return calc_pi(degree - 1) - term;
       } else {
          return calc_pi(degree - 1) + term;
       }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
       printf("Invalid input\n");
       exit(1);
    }
    
    char* degree_in_string = argv[argc - 1];
    while (*degree_in_string != '\0'){
       if (!(*degree_in_string >= '0' && *degree_in_string <= '9')) {
          printf("Invalid number\n");
          exit(1);
       }
       degree_in_string++;
    }

    int degree = atoi(argv[argc - 1]);
    double pi = calc_pi(degree);
    printf("Our estimate of Pi is %.20lf\n", pi);
    return 0;    
}
