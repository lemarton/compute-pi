#include <arm_neon.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#define MAX_THREADS 4

typedef struct {
    long start;
    long iterations;
    double pi;
} thread_data;

void *compute_pi(void *arg) {
    thread_data *tdata = (thread_data *)arg;

    double pi_4 = 0.0;
    double div = (double)(tdata->start * 4 + 1);

    for (long i = 0; i < tdata->iterations; i++) {
        pi_4 += 1.0 / div;
        div += 2.0;
        pi_4 -= 1.0 / div;
        div += 2.0;
    }

    tdata->pi = pi_4 * 4.0;
    pthread_exit(NULL);
}

void *compute_pi_vec(void *arg) {
    thread_data *tdata = (thread_data *)arg;
    
    float64x2_t a_vec, b_vec, step_vec, reci_vec, acc_vec;

    float64_t a[] = {1.0, -1.0};
    float64_t b[] = {(double)(tdata->start * 4 + 1),
                     (double)(tdata->start * 4 + 3)};

    // load vector registers
    a_vec = vld1q_f64(a);
    b_vec = vld1q_f64(b);
    acc_vec = vdupq_n_f64(0.0);
    step_vec = vdupq_n_f64(4.0f);

    for (int i = 0; i < tdata->iterations; i++) {
        // reci = a / b
        reci_vec = vdivq_f64(a_vec, b_vec);
        // acc += reci
        acc_vec = vaddq_f64(acc_vec, reci_vec);
        // b += {4.0, 4.0}
        b_vec = vaddq_f64(b_vec, step_vec);
    }

    float64_t pi_4 = vgetq_lane_f64(acc_vec, 0) + vgetq_lane_f64(acc_vec, 1);
    tdata->pi = pi_4 * 4.0;

    pthread_exit(NULL);
}

int main(void) {
    struct timespec begin, end;
    clock_gettime(CLOCK_MONOTONIC, &begin);

    pthread_t pth[MAX_THREADS];
    thread_data tdata[MAX_THREADS];

    long stride = 2500000;

    for (int i = 0; i < MAX_THREADS; i++) {
        tdata[i].start = i * stride;
        tdata[i].iterations = stride;
        // pthread_create(&pth[i], NULL, compute_pi, &tdata[i]);
        pthread_create(&pth[i], NULL, compute_pi_vec, &tdata[i]);
    }

    double pi = 0.0;
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(pth[i], NULL);
        pi += tdata[i].pi;
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("pi: %.15f\n", pi);

    double elapsed = (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
    printf("time elapsed: %.3f\n", elapsed);

    return 0;
}
