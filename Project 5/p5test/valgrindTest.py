import random
import os


def valgrind_check(exe_name, input_file, output_file):
    cmd = 'valgrind --leak-check=full --log-file={} {} < {} > tmp'.format(output_file, exe_name, input_file)
    suc_msg = 'no leaks are possible'
    os.system(cmd)

    with open(output_file, 'r') as f:
        content = f.read()
        if content.find(suc_msg) == -1:
            return False
        return True
