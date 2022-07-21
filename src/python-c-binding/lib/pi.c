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
