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
    for b in range(1, 10001):

        # read the number just written and output the result
        yxm = os.popen("./yxm {} {} simple".format(a, b)).read()
        ncj = os.popen("./ncj {} {} simple".format(a, b)).read()
        yxm2 = os.popen("./yxm {} {} counting".format(a, b)).read()
        ncj2 = os.popen("./ncj {} {} counting".format(a, b)).read()

        if yxm != ncj:  # compare result for this number
            count += 1
            filename = str(count) + ".diff"  # output the difference into file
            with open(os.path.join(result_folder, filename), 'w+') as f:
                f.write(str(a) + " " + str(b) + "simple" + '\n')
                diff = list(difflib.context_diff(yxm.splitlines(), ncj.splitlines(), lineterm=''))
                for item in diff:
                    f.write(item + '\n')

            with open(os.path.join(result_folder, "yxm"), 'w+') as f:
                f.write(str(a) + " " + str(b) + "simple" + '\n')
                f.write('*' * 10 + 'yxm' + '=' + yxm + '\n')

            with open(os.path.join(result_folder, "ncj"), 'w+') as f:
                f.write(str(a) + " " + str(b) + "simple" + '\n')
                f.write('*' * 10 + 'ncj' + '=' + ncj + '\n')
            exit(-1)

        if yxm2 != ncj2:  # compare result for this number
            count += 1
            filename = str(count) + ".diff"  # output the difference into file
            with open(os.path.join(result_folder, filename), 'w+') as f:
                f.write(str(a) + " " + str(b) + "counting" + '\n')
                diff = list(difflib.context_diff(yxm.splitlines(), ncj.splitlines(), lineterm=''))
                for item in diff:
                    f.write(item + '\n')

            with open(os.path.join(result_folder, "yxm"), 'w+') as f:
                f.write(str(a) + " " + str(b) + "counting" + '\n')
                f.write('*' * 10 + 'yxm' + '=' + yxm + '\n')

            with open(os.path.join(result_folder, "ncj"), 'w+') as f:
                f.write(str(a) + " " + str(b) + "counting" + '\n')
                f.write('*' * 10 + 'ncj' + '=' + ncj + '\n')
            exit(-1)

