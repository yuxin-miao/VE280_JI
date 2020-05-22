import os  # operation system, provides a portable way of using operating system dependent functionality
from tqdm import tqdm  # for the progress bar
import random
import time

test_2_folder = "test_2"
# os.path: used for common path manipulation
result_folder = "result"
if not os.path.exists(test_2_folder):
    os.mkdir(test_2_folder)

if not os.path.exists(result_folder):
    os.mkdir(result_folder)

test_2_input = os.path.join(test_2_folder, "test.txt")  # join one or more path components, get "/test_2/test_2_in"
count = 0  # used for count the different cases

# Used to: open a pipe to/from command.
# Return: an open file object connected to the pipe, can be read/write
# default: 'r' read mode.
os.popen("g++ -Wall -std=c++11 -o ./test/lbq lbq.cpp")
os.popen("g++ -Wall -std=c++11 -o ./test/yxm yxm.cpp")

time.sleep(2)  # wait until compiled
# find it really useful and necessary, or the program could not find the executable file when began test

for i in range(1, 5):
    print("Testing Number" + str(i))

    for k in tqdm(range(9999000, 10000001)):
        # generate invalid case randomly, 100 times for test
        for time in range(0, 100):
            invalid = random.randint(-20000000, 20000000)
            if 0 < invalid < 10000000:
                continue
            with open(test_2_input, 'w+') as f:
                f.write(str(invalid) + ' ' + str(i) + '\n')

        # Generate the valid test cases, write into the file test_input
        with open(test_2_input, 'w+') as f:  # when open a file object, using "with" - do not need to close
            f.write(str(k) + ' ' + str(i) + '\n')
        # read the number just written and output the result
        lbq = os.popen("./test/lbq < ./test/test.txt").read()
        yxm = os.popen("./test/yxm < ./test/test.txt").read()

        if yxm != lbq:  # compare result for this number
            with open(test_2_input, 'r') as f:
                input_num = f.read()  # find out which input number
            count += 1
            filename = str(count) + ".diff"  # output the difference into file
            with open(os.path.join(result_folder, filename), 'w+') as f:
                f.write(input_num + '\n')
                f.write('*' * 10 + 'lbq' + '=' + lbq + '\n')
                f.write('*' * 10 + 'yxm' + '=' + yxm + '\n')
