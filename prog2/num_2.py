
import random
import time


n_vals = [15, 64, 256, 1024, 4096, 16384]
m_vals = [100, 1677721600, 13421772800]


def generate_triples(num_vals, max):
    M = []
    for _ in range(num_vals):
        M.append(
            (random.randint(0, max - 1),
             random.randint(0, max - 1),
             random.randint(0, max - 1)))
    return M

def generate_square_matrix(n):
    N = []
    for ii in range(n):
        N.append([])
        for jj in range(n):
            N[ii].append(random.randint(0, n - 1))
    return N

def add_triples(N, triples):
    for triple in triples:
        N[triple[0]][triple[1]] += triple[2]
    return N


if __name__ == '__main__':
    for m in m_vals:
        for n in n_vals:
            print("running triple algorithm for n = {}, m = {}".format(n, m))
            M = []
            N = []


            M = generate_triples(m, n)
            N = generate_square_matrix(n)


            start = time.time()
            add_triples(N, M)
            end = time.time()

            print("Time to multiply add m triples into our matrix was {} seconds".format(end - start))


