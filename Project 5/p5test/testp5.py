from rpnTest1 import rpn_test1
from cacheTest import cache_test
from tqdm import tqdm
import random
import os
import time

os.popen("g++ -Wall -std=c++17 -o cache ./yxm/cache.cpp")
os.popen("g++ -Wall -std=c++17 -o rpn ./yxm/rpn.cpp")

os.popen("g++ -Wall -std=c++17 -o lbmcache ./lbm/cache.cpp")
os.popen("g++ -Wall -std=c++17 -o lbmrpn ./lbm/rpn.cpp")

# wait until compiled
time.sleep(2)

with open("cacheIn.txt", "w+") as f:
    mem_size = random.randint(10, 100)
    f.write(str(5) + " " + str(mem_size) + '\n')

for count in tqdm((range(1, 500))):
    a = random.randint(1, 5000)
    rpn_test1(a)
    cache_test(mem_size)
