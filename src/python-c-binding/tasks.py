import invoke

@invoke.task()
def build_lib(c, path=None):
    """Build the shared library for the sample C code"""
    # Moving this type hint into signature causes an error (???)
    c: invoke.Context
    print("Building C Library")
    cmd = "gcc -c -Wall -Werror -fpic -o lib/pi.o lib/pi.c -I /usr/include/python3.7"
    invoke.run(cmd)
    invoke.run("gcc -shared -o lib/libcpi.so lib/pi.o")
