import puzzle15 as p15
#import numpy as np;
import time

def print_instance(instance):
    for i, j in enumerate(instance):
        if j == 0:
            print(f'   ', end='')
        else:
            print(f'{j:02} ', end='')
        if i % 4 == 3:
            print()


def main():
    #instance = [x+1 for x in np.random.permutation(15)]+[0]
    #while not p15.isSolvable(instance):
    #    instance = [x+1 for x in np.random.permutation(15)]+[0]
    instance = [3,1,4,12,10,5,13,0,9,2,8,15,7,14,11,6]
    if not p15.isSolvable(instance):
        print("not solvable")
        return
    print_instance(instance)
    print("1")
    start = time.time()
    a, sol1 = p15.solveInvertDistance(instance)
    print(len(sol1))
    print(a)
    print(f'took {time.time()-start}s')
    for s in sol1:
        print_instance(s)
        print()
    print("2")
    start = time.time()
    a, sol2 = p15.solveManhattan(instance)
    print(len(sol2))
    print(a)
    print(f'took {time.time()-start}s')
    for s in sol2:
        print_instance(s)
        print()

if __name__ == '__main__':
    main()
