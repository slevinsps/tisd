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
    if  poboch == [[2, 0, 0], [-4, 3, 0], [3, 8, -1], [0, 4, 2], [0, 0, 6]]:
        print("Test %d in TestsOpredPoboch passed" % k)
    else:
        print("Test %d in TestsOpredPoboch failed" % k)
        
    # 2 тест
    a = [[2,3,],
         [-4,8]]
    n = 2
    poboch = zad.OpredPoboch(a,n)
    k+=1
    if  poboch == [[2, 0], [-4, 3], [0, 8]]:
        print("Test %d in TestsOpredPoboch passed" % k)
    else:
        print("Test %d in TestsOpredPoboch failed" % k)
    print()

def TestsOpredGlav():
    k = 0;
    # 1 тест
    a = [[2,3,-1],
         [-4,8,2],
         [3,4,6]]
    n = 3
    glav = zad.OpredGlav(a,n)
    k+=1
    if  glav == [[3, 0, 0], [-4, 4, 0], [2, 8, 6], [0, 3, 2], [0, 0, -1]]:
        print("Test %d in TestsOpredGlav passed" % k)
    else:
        print("Test %d in TestsOpredGlav failed" % k)
        
    # 2 тест
    a = [[2,3,],
         [-4,8]]
    n = 2
    glav = zad.OpredGlav(a,n)
    k+=1
    if  glav == [[-4, 0], [2, 8], [0, 3]]:
        print("Test %d in TestsOpredGlav passed" % k)
    else:
        print("Test %d in TestsOpredGlav failed" % k)
    print()
    
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
    if  pr == [0,-1,0,-2,0]:
        print("Test %d in TestsProizvOtr passed" % k)
    else:
        print("Test %d in TestsProizvOtr failed" % k)
        
    # 2 тест
    poboch = [[6,0,0],
              [0,1,0],
              [1,0,6],
              [0,2,0],
              [1,0,3]]
    n = 3
    pr = zad.ProizvOtr(poboch,n)
    k+=1
    if  pr == [0,0,0,0,0]:
        print("Test %d in TestsProizvOtr passed" % k)
    else:
        print("Test %d in TestsProizvOtr failed" % k) 
    print()    

def TestsSumPoloj():
    k = 0;
    # 1 тест
    glav = [[6,0,0],
            [0,-1,0],
            [1,0,6],
            [0,-2,0],
            [0,0,3]]
    n = 3
    summa = zad.SumPoloj(glav,n)
    k+=1
    if  summa == [6,-1,7,-1,3]:
        print("Test %d in TestsSumPoloj passed" % k)
    else:
        print("Test %d in TestsSumPoloj failed" % k)
        
    # 2 тест
    glav = [[-6,0,0],
            [0,-1,0],
            [-1,0,-6],
            [0,-2,0],
            [-1,0,-3]]
    n = 3
    summa = zad.SumPoloj(glav,n)
    k+=1
    if  summa == [-1,-1,-1,-1,-1]:
        print("Test %d in TestsSumPoloj passed" % k)
    else:
        print("Test %d in TestsSumPoloj failed" % k)
    print()

def TestsMin():
    k = 0;
    # 1 тест
    pr = [-6,0,7,0,-3]
    n = 3
    mini = zad.Min(pr,n)
    k+=1
    if mini == 0:
        print("Test %d in TestsMin passed" % k)
    else:
        print("Test %d in TestsMin failed" % k)

    # 2 тест
    pr = [2,0,-6,-6,0]
    n = 3
    mini = zad.Min(pr,n)
    k+=1
    if mini == 2:
        print("Test %d in TestsMin passed" % k)
    else:
        print("Test %d in TestsMin failed" % k)

    # 3 тест
    pr = [0,0,0,0,0]
    n = 3
    mini = zad.Min(pr,n)
    k+=1
    if mini == -1:
        print("Test %d in TestsMin passed" % k)
    else:
        print("Test %d in TestsMin failed" % k)
    print()

def TestsMax():
    k = 0;
    # 1 тест
    summa = [6,0,0,7,3]
    n = 3
    maxi = zad.Max(summa,n)
    k+=1
    if maxi == 3:
        print("Test %d in TestsMax passed" % k)
    else:
        print("Test %d in TestsMax failed" % k)

    # 2 тест
    summa = [2,-1,6,6,-1]
    n = 3
    maxi = zad.Max(summa,n)
    k+=1
    if maxi == 2:
        print("Test %d in TestsMax passed" % k)
    else:
        print("Test %d in TestsMax failed" % k)

    # 3 тест
    summa = [-1,-1,-1,-1,-1]
    n = 3
    maxi = zad.Max(summa,n)
    k+=1
    if maxi == -1:
        print("Test %d in TestsMax passed" % k)
    else:
        print("Test %d in TestsMax failed" % k)
    print()

def TestsForm_diag():
    k = 0;
    # 1 тест
    arr = [[2, 0, 0], [-4, 3, 0], [3, 8, -1], [0, 4, 2], [0, 0, 6]]
    ind = 0
    n = 3
    ans = zad.form_diag(arr,ind,n)
    k+=1
    if ans == [2]:
        print("Test %d in TestsForm_diag passed" % k)
    else:
        print("Test %d in TestsForm_diag failed" % k)
        
    # 2 тест
    arr = [[2, 0, 0], [-4, 3, 0], [3, 8, -1], [0, 4, 2], [0, 0, 6]]
    ind = 1
    n = 3
    ans = zad.form_diag(arr,ind,n)
    k+=1
    if ans == [-4, 3]:
        print("Test %d in TestsForm_diag passed" % k)
    else:
        print("Test %d in TestsForm_diag failed" % k)

    # 3 тест
    arr = [[2, 0, 0], [-4, 3, 0], [3, 8, -1], [0, 4, 2], [0, 0, 6]]
    ind = 2
    n = 3
    ans = zad.form_diag(arr,ind,n)
    k+=1
    if ans == [3, 8, -1]:
        print("Test %d in TestsForm_diag passed" % k)
    else:
        print("Test %d in TestsForm_diag failed" % k)
    
    # 4 тест
    arr = [[2, 0, 0], [-4, 3, 0], [3, 8, -1], [0, 4, 2], [0, 0, 6]]
    ind = 3
    n = 3
    ans = zad.form_diag(arr,ind,n)
    k+=1
    if ans == [4, 2]:
        print("Test %d in TestsForm_diag passed" % k)
    else:
        print("Test %d in TestsForm_diag failed" % k)

    # 5 тест
    arr = [[2, 0, 0], [-4, 3, 0], [3, 8, -1], [0, 4, 2], [0, 0, 6]]
    ind = 4
    n = 3
    ans = zad.form_diag(arr,ind,n)
    k+=1
    if ans == [6]:
        print("Test %d in TestsForm_diag passed" % k)
    else:
        print("Test %d in TestsForm_diag failed" % k)
    print()

def main():    
    TestsOpredPoboch()    
    TestsOpredGlav()
    TestsProizvOtr()
    TestsSumPoloj()
    TestsMin()
    TestsMax()
    TestsForm_diag()

main()
