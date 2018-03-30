#!/usr/bin/python3

import time
from sys import argv, getsizeof

def do_operations(C):
    len_c = len(C)
    num_operations = len_c * 10
    #performing a number of operations that is a order of magnitude larger than the size of C
    
    jj = 0
    for ii in range(num_operations):
        C[jj] = C[jj] + C[len_c - jj - 1] + C[len_c // 2] + C[jj // 2] % 200

        jj= (jj + 1) % len_c

modifiers = [.01, .5, .6, .7, .8, .9, .95, .99, 1, 1.01, 1.1, 1.5, 2, 5, 10, 50]

if __name__ == '__main__':
    org_M = int(argv[1]) * 1024**3

    times = []

    print("Using active memory size of {} bytes".format(org_M))

    #we have to modify M so that C will actually be the number of bytes we expect
    int_size = getsizeof(200)
    M = org_M // int_size

    for mod in modifiers:
        this_m = int(mod * M)
        #use a max size of 200 to keep the data about the same size
        C = [i % 200 for i in range(this_m)]
        assert(len(C) == this_m)

        print("Running opearations on C of size {}, ".format(mod), end='')
        
        start = time.time()
        do_operations(C)
        end = time.time()

        print("took {} seconds".format(end - start))

        times.append( (int(org_M * mod), end - start))
        

    print("\n\n#bytes        time")
    for time in times:
        print("{}            {}".format(time[0], time[1]))

