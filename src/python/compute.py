import math
import time

def compute_pi(iterations: int):
    t0 = time.time();
    
    pi_4 = 0
    dividend = 1
    divisor = 1
    
    for _ in range(iterations):
        pi_4 += dividend / divisor
        divisor += 2
        pi_4 -= dividend / divisor
        divisor += 2

    print(pi_4 * 4)
    print(math.pi)
    print(pi_4 * 4 - math.pi)

    t1 = time.time();
    print(f'{t1 - t0}')


if __name__ == '__main__':
    compute_pi(100_000_000)

