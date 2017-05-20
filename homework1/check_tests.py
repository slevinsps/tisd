import zad1_7 as zad

def TestsOpredPoboch():
    k = 0;
    # 1 тест
    a = [[2,3,-1],
         [-4,8,2],
         [3,4,6]]
    n = 3
    poboch = zad.OpredPoboch(a,n)
    k+=1
    if [[2, 0, 0], [-4, 3, 0], [3, 8, -1], [0, 4, 2], [0, 0, 6]] == poboch:
        print("Test %d in TestsOpredPoboch passed" % k)
    else:
        print("Test %d in TestsOpredPoboch failed" % k)
        
    # 2 тест
    a = [[2,3,],
         [-4,8]]
    n = 2
    poboch = zad.OpredPoboch(a,n)
    k+=1
    if [[2, 0], [-4, 3], [0, 8]] == poboch:
        print("Test %d in TestsOpredPoboch passed" % k)
    else:
        print("Test %d in TestsOpredPoboch failed" % k)

def TestsOpredGlav():
    k = 0;
    # 1 тест
    a = [[2,3,-1],
         [-4,8,2],
         [3,4,6]]
    n = 3
    glav = zad.OpredGlav(a,n)
    k+=1
    if [[3, 0, 0], [-4, 4, 0], [2, 8, 6], [0, 3, 2], [0, 0, -1]] == glav:
        print("Test %d in TestsOpredGlav passed" % k)
    else:
        print("Test %d in TestsOpredGlav failed" % k)
        
    # 2 тест
    a = [[2,3,],
         [-4,8]]
    n = 2
    glav = zad.OpredGlav(a,n)
    k+=1
    if [[-4, 0], [2, 8], [0, 3]] == glav:
        print("Test %d in TestsOpredGlav passed" % k)
    else:
        print("Test %d in TestsOpredGlav failed" % k)
    


def TestsProizvOtr():
    k = 0;
    # 1 тест
    poboch = [[6,0,0],
              [0,-1,0],
              [1,0,6],
              [0,-2,0],
              [0,0,3]]
    n = 3
    pr = zad.ProizvOtr(poboch,n)
    k+=1
    if [0,-1,0,-2,0] == pr:
        print("Test %d in TestsProizvOtr passed" % k)
    else:
        print("Test %d in TestsProizvOtr failed" % k)    
    

TestsOpredPoboch()    
TestsOpredGlav()
TestsProizvOtr()
