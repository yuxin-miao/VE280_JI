import os  # operation system, provides a portable way of using operating system dependent functionality
from tqdm import tqdm
from random import randint
import difflib
import random
from valgrindTest import valgrind_check


def generate1(a):
    operators = "+-*/"
    with open("rpnInfix.txt", "w+") as f:
        f.write(str(random.randint(200, 10000)) + " " + random.choice(operators) + " " + str(a))  # a + b
        for b in range(1, 50):
            x = random.randint(1, 50)
            if x > 5:
                f.write(" " + random.choice(operators) + " " + "(" + " " + str(random.randint(0, 100)))
            if x > 20:
                for i in range(1, 5):
                    f.write(" " + random.choice(operators) + " " + "(" + " " + str(random.randint(0, 100)))
            f.write(" " + random.choice(operators) + " " + str(random.randint(0, 100000)))
            if x > 5:
                f.write(" " + ")" + " " + random.choice(operators) + " " + str(random.randint(0, 10000)))
            if x > 20:
                for i in range(1, 5):
                    f.write(" " + ")" + " " + random.choice(operators) + " " + str(random.randint(0, 10000)))


def generate2(a):
    operators = "+-*/"
    with open("rpnInfix.txt", "w+") as f:
        f.write(str(random.randint(200, 10000)) + " " + random.choice(operators) + " " + str(a))  # a + b
        for b in range(1, 5):
            x = random.randint(1, 200)
            f.write(" " + random.choice(operators) + " " + str(random.randint(0, 100000)))
            if b == 2 & 100 < x < 150:
                f.write(" " + random.choice(operators) + " " + "(" + " " + str(random.randint(0, 100)))
            if b == 1 & 150 < x < 200:
                f.write(" " + str(random.randint(0, 100000)))
            if 50 < x < 100:
                f.write(" " + random.choice(operators))


def rpn_test1(a):
    if a < 4000:  # exceptions
        generate2(a)
    else:
        generate1(a)  # normal, only divided by zero

    yxm = os.popen("./rpn < rpnInfix.txt").read()
    lbm = os.popen("./lbmrpn < rpnInfix.txt").read()

    if yxm != lbm:
        with open("yxmrpn.txt", "w+") as f:
            f.write(yxm)
        with open("lbmrpn.txt", "w+") as f:
            f.write(lbm)

        with open("rpndiff.txt", "w+") as f:
            diff = list(difflib.context_diff(yxm.splitlines(), lbm.splitlines(), lineterm=''))
            for item in diff:
                f.write(item + '\n')
        exit(-1)

    # if not valgrind_check('./rpn', "rpnInfix.txt", "yxmValgrind") or not valgrind_check('./lbmrpn', "rpnInfix.txt", "lbmValgrind"):
    #    exit(-1)
