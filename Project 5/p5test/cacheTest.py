import os  # operation system, provides a portable way of using operating system dependent functionality
from tqdm import tqdm
from random import randint
import difflib
import random
from valgrindTest import valgrind_check


def generate_case(mem_size):
    with open("cacheIn.txt", "a") as f:
        for i in range(0, 5):
            # legal cases
            f.write("READ " + str(random.randint(0, mem_size)) + '\n')
            f.write("WRITE " + str(random.randint(0, mem_size)) + " " + str(random.randint(0, 200000)) + '\n')
            if i == 3:
                f.write("PRINTCACHE" + '\n')
                f.write("PRINTMEM" + '\n')
            # exceptions
            f.write("READ " + '\n')
            f.write("WRITE " + str(random.randint(0, mem_size)) + '\n')
            f.write("WRITE " + '\n')
            f.write("READ " + str(random.randint(0, mem_size)) + " " + str(random.randint(0, 200000)) + '\n')
            f.write("WRITE " + str(random.randint(0, mem_size)) + " " + str(random.randint(0, 200000)) + " " + str(random.randint(0, 200000)) + '\n')
            f.write("WRITE " + str(random.randint(-300, 900)) + " " + str(random.randint(0, 200000)) + '\n')


def cache_test(mem_size):
    generate_case(mem_size)

    yxm = os.popen("./cache < cacheIn.txt").read()
    lbm = os.popen("./lbmcache < cacheIn.txt").read()

    if yxm != lbm:
        with open("yxmcache.txt", "w+") as f:
            f.write(yxm)
        with open("lbmcache.txt", "w+") as f:
            f.write(lbm)

        with open("cachediff.txt", "w+") as f:
            diff = list(difflib.context_diff(yxm.splitlines(), lbm.splitlines(), lineterm=''))
            for item in diff:
                f.write(item + '\n')
        exit(-1)

    if not valgrind_check('./cache', "cacheIn.txt", "yxmValgrind") or not valgrind_check('./lbmcache', "cacheIn.txt", "lbmValgrind"):
        exit(-1)
