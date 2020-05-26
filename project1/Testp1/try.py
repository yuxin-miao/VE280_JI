import os
from subprocess import Popen, PIPE

os.popen("g++ -Wall -std=c++11 -o yxm yxm.cpp")
os.popen("g++ -Wall -std=c++11 -o lbm lbm.cpp")
p_yxm = Popen(['./yxm'], shell=True, stdout=PIPE, stdin=PIPE)
p_lbm = Popen(['./lbm'], shell=True, stdout=PIPE, stdin=PIPE)

for i in range(1, 4):
    for j in range(1, 1000000):

        input_content = str(j) + ' ' + str(i) + '\n'
        # p_yxm.stdin.write(bytes(input_content, 'UTF-8'))
        yxm_stdout = p_yxm.communicate(input=bytes(input_content, 'UTF-8'))[0]
        res_yxm = yxm_stdout.decode()
        # p_yxm.stdin.flush()

        # p_lbm.stdin.write(bytes(input_content, 'UTF-8'))
        lbm_stdout = p_lbm.communicate(input=bytes(input_content, 'UTF-8'))[0]
        res_lbm = lbm_stdout.decode()
        # p_lbm.stdin.flush()

        if res_yxm != res_lbm:
            print(input_content)

        '''if p_yxm.stdout.readline().strip() != p_lbm.stdout.readline().strip():
            print(input_content)
        else:
            print('pass')
        p_yxm.stdout.flush()
        p_lbm.stdout.flush()'''
        if i == 4 & j == 999999:
            print('Pass')
