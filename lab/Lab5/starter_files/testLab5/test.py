import os  # operation system, provides a portable way of using operating system dependent functionality
from tqdm import tqdm

test_folder = "test"
# os.path: used for common path manipulation
result_folder = "result"
if not os.path.exists(test_folder):
    os.mkdir(test_folder)

if not os.path.exists(result_folder):
    os.mkdir(result_folder)

test_input = os.path.join(test_folder, "test.txt")  # join one or more path components, get "/test/test_in"
count = 0  # used for count the different cases

for a in tqdm(range(-50, 20)):
    for b in range(1, 3):
        for c in (range(-5, 5)):

            # Generate the test cases, write into the file test_input
            with open(test_input, 'w+') as f:  # when open a file object, using "with" - do not need to close
                if a == 0:
                    a = a + 1

                f.write(str(a) + ' ' + str(b) + ' ' + str(c) + '\n')
                f.write(str(a) + '\n')
                f.write(str(c+50) + ' ' + str(a+50) + ' ' + str(b+50) + '\n')
            # read the number just written and output the result
            ex2 = os.popen("./ex2 < ./test/test.txt").read()
            ex3 = os.popen("./lbm/ex2 < ./test/test.txt").read()

            if ex2 != ex3:  # compare result for this number
                with open(test_input, 'r') as f:
                    input_num = f.read()  # find out which input number
                count += 1
                filename = str(count) + ".diff"  # output the difference into file
                with open(os.path.join(result_folder, filename), 'w+') as f:
                    f.write(input_num + '\n')
                    f.write('*' * 10 + 'ex2' + '=' + ex2 + '\n')
                    f.write('*' * 10 + 'ex3' + '=' + ex3 + '\n')
