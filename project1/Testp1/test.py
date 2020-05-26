import os  # operation system, provides a portable way of using operating system dependent functionality
from tqdm import tqdm  # for the progress bar

test_2_folder = "test_2"
# os.path: used for common path manipulation
result_folder = "result"
if not os.path.exists(test_2_folder):
    os.mkdir(test_2_folder)

if not os.path.exists(result_folder):
    os.mkdir(result_folder)

test_2_input = os.path.join(test_2_folder, "test_2.txt")  # join one or more path components, get "/test_2/test_2_in"
count = 0  # used for count the different cases

# Used to: open a pipe to/from command.
# Return: an open file object connected to the pipe, can be read/write
# default: 'r' read mode.
os.popen("g++ -Wall -std=c++11 -o ./test_2/yxm yxm.cpp")
os.popen("g++ -Wall -std=c++11 -o ./test_2/lbq lbq.cpp")

for i in range(1, 5):
    print("Testing Number" + str(i))

    for k in tqdm(range(9999000, 10000001)):

        # Generate the test_2 cases, write into the file test_2_input
        with open(test_2_input, 'w+') as f:  # when open a file object, using "with" - do not need to close
            f.write(str(k) + ' ' + str(i) + '\n')
        # read the number just written and output the result
        yxm = os.popen("./test_2/yxm < ./test_2/test_2.txt").read()
        lbq = os.popen("./test_2/lbq < ./test_2/test_2.txt").read()

        if lbq != yxm:  # compare result for this number
            with open(test_2_input, 'r') as f:
                input_num = f.read()  # find out which input number
            count += 1
            filename = str(count) + ".diff"  # output the difference into file
            with open(os.path.join(result_folder, filename), 'w+') as f:
                f.write(input_num + '\n')
                f.write('*' * 10 + 'yxm' + '=' + yxm + '\n')
                f.write('*' * 10 + 'lbq' + '=' + lbq + '\n')
