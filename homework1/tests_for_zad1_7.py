import zad1_7 as zad
import sys


def Tests():
    k = 0
    
    # 1 тест
    a = [[2,3,-1],
         [-4,8,2],
         [3,4,6]]
    n = 3
    zad.main()
    """
    k+=1
    if  poboch == [[2, 0, 0], [-4, 3, 0], [3, 8, -1], [0, 4, 2], [0, 0, 6]]:
        print("Test %d in TestsOpredPoboch passed" % k)
    else:
        print("Test %d in TestsOpredPoboch failed" % k)
    """

sys.stdin = open("in.txt")     
sys.stdout = open("out.txt", "w")
Tests()
sys.stdout.close()
