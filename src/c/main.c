#include <stdio.h>
#include <time.h>

double compute_pi(int iterations) {
    double pi_4 = 0.0;
    double div = 1.0;

    for (int i = 0; i < iterations; i++) {
        pi_4 += 1.0 / div;
        div += 2.0;
        pi_4 -= 1.0 / div;
        div += 2.0;
    }

    return pi_4 * 4.0;
}

int main(void) {
    clock_t begin = clock();
    double comp_pi = compute_pi(100000000);
    clock_t end = clock();

    printf("%.15f\n", comp_pi);
    printf("time elapsed: %.3f\n", (double)(end - begin) / CLOCKS_PER_SEC);

    return 0;
}
