#include <arm_neon.h>
#include <stdio.h>
#include <time.h>

float compute_pi_f(int iterations) {
    float32x4_t a_vec, b_vec, step_vec, reci_vec, acc_vec;

    float32_t a[] = {1.0f, -1.0f, 1.0f, -1.0f};
    float32_t b[] = {1.0f, 3.0f, 5.0f, 7.0f};

    // load vector registers
    a_vec = vld1q_f32(a);
    b_vec = vld1q_f32(b);
    acc_vec = vdupq_n_f32(0.0f);
    step_vec = vdupq_n_f32(8.0f);

    for (int i = 0; i < iterations; i++) {
        reci_vec = vdivq_f32(a_vec, b_vec);
        acc_vec = vaddq_f32(acc_vec, reci_vec);
        b_vec = vaddq_f32(b_vec, step_vec);
    }

    float32_t pi_4 = vgetq_lane_f32(acc_vec, 0);
    pi_4 += vgetq_lane_f32(acc_vec, 1);
    pi_4 += vgetq_lane_f32(acc_vec, 2);
    pi_4 += vgetq_lane_f32(acc_vec, 3);
    
    return pi_4 * 4.0f;
}

double compute_pi(int iterations) {
    float64x2_t a_vec, b_vec, step_vec, reci_vec, acc_vec;

    float64_t a[] = {1.0, -1.0};
    float64_t b[] = {1.0, 3.0};

    // load vector registers
    a_vec = vld1q_f64(a);
    b_vec = vld1q_f64(b);
    acc_vec = vdupq_n_f64(0.0);
    step_vec = vdupq_n_f64(4.0f);

    for (int i = 0; i < iterations; i++) {
        reci_vec = vdivq_f64(a_vec, b_vec);
        acc_vec = vaddq_f64(acc_vec, reci_vec);
        b_vec = vaddq_f64(b_vec, step_vec);
    }

    float64_t pi_4 = vgetq_lane_f64(acc_vec, 0) + vgetq_lane_f64(acc_vec, 1);

    return pi_4 * 4.0;
}

int main(void) {
    clock_t begin = clock();
    float comp_pi = compute_pi(100000000);
    clock_t end = clock();

    printf("%.15f\n", comp_pi);
    printf("time elapsed: %.3f\n", (double)(end - begin) / CLOCKS_PER_SEC);

    return 0;
}
