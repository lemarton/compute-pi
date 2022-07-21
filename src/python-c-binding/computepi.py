import ctypes
import pathlib
import time

def print_duration(func):
    def wrapper(*args, **kwargs):
        t0 = time.time()
        ret = func(*args, **kwargs)
        t1 = time.time()
        print(f'time elapsed: {t1 - t0:.3f}')
        return ret
    return wrapper

@print_duration
def compute_pi(iterations: int):    
    pi_4 = 0.0
    divisor = 1
    
    for _ in range(iterations):
        pi_4 += 1 / divisor
        divisor += 2
        pi_4 -= 1 / divisor
        divisor += 2

    return pi_4 * 4.0

if __name__ == "__main__":
    libname = pathlib.Path().absolute() / "lib/libcpi.so"
    c_lib = ctypes.CDLL(libname)

    c_lib.compute_pi.argtypes = [ctypes.c_int]
    c_lib.compute_pi.restype = ctypes.c_double

    c_compute_pi = print_duration(c_lib.compute_pi)

    # compute with native Python 
    print('computing with Python')
    pi = compute_pi(10_000_000)
    print(pi)
    
    print('----')

    # compute with C lib
    print('computing with C library')
    pi = c_compute_pi(100_000_000)
    print(pi)
    