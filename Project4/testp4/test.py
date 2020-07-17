import os  # operation system, provides a portable way of using operating system dependent functionality
from tqdm import tqdm
from random import randint
import difflib
import random


count = 0  # used for count the different cases
strLetter = "qwertyuiopasdfghjklzxcvbnm "

for a in tqdm(range(1, 10001)):

    for b in range(1, 10):  # write the file used for compress
        with open("text.txt", "a") as f:
            f.write("\n")
            f.write("".join(random.sample(strLetter, b)) + "\n")

    tree = os.popen("./compress -tree text.txt").read()
    binary = os.popen("./compress text.txt").read()

    with open("tree.txt", "w+") as f:
        f.write(tree)
    with open("binary.txt", "w+") as f:
        f.write(binary)

    result = os.popen("./decompress tree.txt binary.txt").read()

    with open("text.txt", 'r') as f:
        txt = f.read()

    if txt != result:  # compare result for this number
        count += 1
        filename = str(count) + ".diff"  # output the difference into file
        with open(filename, 'w+') as f:
            diff = list(difflib.context_diff(txt.splitlines(), result.splitlines(), lineterm=''))
            for item in diff:
                f.write(item + '\n')
        with open("result.txt", 'w+') as f:
            f.write(result)
        exit(-1)

