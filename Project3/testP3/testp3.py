import os  # operation system, provides a portable way of using operating system dependent functionality
from tqdm import tqdm
from random import randint
import difflib

# os.path: used for common path manipulation
result_folder = "result"

if not os.path.exists(result_folder):
    os.mkdir(result_folder)

count = 0  # used for count the different cases

for a in tqdm(range(1, 10001)):
    b = randint(1, 10000)

    # read the number just written and output the result
    yxm = os.popen("./yxm {} {} simple".format(a, b)).read()
    lbm = os.popen("./lbm {} {} simple".format(a, b)).read()
    yxm2 = os.popen("./yxm {} {} counting".format(a, b)).read()
    lbm2 = os.popen("./lbm {} {} counting".format(a, b)).read()

    if yxm != lbm:  # compare result for this number
        count += 1
        filename = str(count) + ".diff"  # output the difference into file
        with open(os.path.join(result_folder, filename), 'w+') as f:
            f.write(str(a) + " " + str(b) + "simple" + '\n')
            diff = list(difflib.context_diff(yxm.splitlines(), lbm.splitlines(), lineterm=''))
            for item in diff:
                f.write(item + '\n')

        with open(os.path.join(result_folder, "yxm"), 'w+') as f:
            f.write(str(a) + " " + str(b) + "simple" + '\n')
            f.write('*' * 10 + 'yxm' + '=' + yxm + '\n')

        with open(os.path.join(result_folder, "lbm"), 'w+') as f:
            f.write(str(a) + " " + str(b) + "simple" + '\n')
            f.write('*' * 10 + 'lbm' + '=' + lbm + '\n')
        exit(-1)

    if yxm2 != lbm2:  # compare result for this number
        count += 1
        filename = str(count) + ".diff"  # output the difference into file
        with open(os.path.join(result_folder, filename), 'w+') as f:
            f.write(str(a) + " " + str(b) + "counting" + '\n')
            diff = list(difflib.context_diff(yxm.splitlines(), lbm.splitlines(), lineterm=''))
            for item in diff:
                f.write(item + '\n')

        with open(os.path.join(result_folder, "yxm"), 'w+') as f:
            f.write(str(a) + " " + str(b) + "counting" + '\n')
            f.write('*' * 10 + 'yxm' + '=' + yxm + '\n')

        with open(os.path.join(result_folder, "lbm"), 'w+') as f:
            f.write(str(a) + " " + str(b) + "counting" + '\n')
            f.write('*' * 10 + 'lbm' + '=' + lbm + '\n')
        exit(-1)
