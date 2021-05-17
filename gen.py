import numpy as np
import sys

n, k, m = 4000, 4000, 4000


a = np.random.randint(100, size=(n, k))
b = np.random.randint(100, size=(k, m))


sys.stdout = open('aa.txt', 'w')

print(f'row={n} col={k}')
for i in range(n):
    for j in range(k):
        print(a[i][j], end='\t')
    print()

sys.stdout = open('bb.txt', 'w')

print(f'row={k} col={m}')

for i in range(k):
    for j in range(m):
        print(b[i][j], end='\t')
    print()
