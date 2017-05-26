import zad1_7 as zad

def TestsOpredPoboch():
    k = 0;
    # 1 тест
    a = [[2,3,-1],
         [-4,8,2],
         [3,4,6]]
    n = 3
    expected = [[2, 0, 0], [-4, 3, 0], [3, 8, -1], [0, 4, 2], [0, 0, 6]]
    actual = zad.OpredPoboch(a,n)
    k+=1
    if  actual == expected:
        print("Test %d in TestsOpredPoboch passed" % k)
    else:
        print("Test %d in TestsOpredPoboch failed" % k)
        
    # 2 тест - тест на граничное значение размера матрицы
    a = [[1]]
    n = 1
    expected = [[1]]
    actual = zad.OpredPoboch(a,n)
    k+=1
    if  actual == expected:
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
    expected = [[3, 0, 0], [-4, 4, 0], [2, 8, 6], [0, 3, 2], [0, 0, -1]]
    actual = zad.OpredGlav(a,n)
    k+=1
    if  expected == actual:
        print("Test %d in TestsOpredGlav passed" % k)
    else:
        print("Test %d in TestsOpredGlav failed" % k)
        
    # 2 тест - тест на граничное значение размера матрицы
    a = [[-4]]
    n = 1
    expected = [[-4]]
    actual = zad.OpredGlav(a,n)
    k+=1
    if  actual == expected:
        print("Test %d in TestsOpredGlav passed" % k)
    else:
        print("Test %d in TestsOpredGlav failed" % k)
    print()
    
def TestsProizvOtr():
    k = 0;
    # 1 тест
    a = [[6,0,0],
         [0,-1,0],
         [1,0,6],
         [0,-2,-2],
         [0,0,0]]
    n = 3
    expexted = [0,-1,0,4,0]
    actual = zad.ProizvOtr(a,n)
    k+=1
    if  actual == expexted:
        print("Test %d in TestsProizvOtr passed" % k)
    else:
        print("Test %d in TestsProizvOtr failed" % k)
            
def TestsSumPoloj():
    k = 0;
    # 1 тест
    a = [[6,0,0],
         [-5,-1,-2],
         [1,0,6],
         [0,-2,0],
         [0,0,0]]
    n = 3
    expected = [6,-1,7,0,0]
    actual = zad.SumPoloj(a,n)
    k+=1
    if  actual == expected:
        print("Test %d in TestsSumPoloj passed" % k)
    else:
        print("Test %d in TestsSumPoloj failed" % k)
    print()
	
def TestsMin():
    k = 0;
    # 1 тест - одно минимальное значение
    a = [-6,0,7,0,-3]
    n = 3
    actual = zad.Min(a,n)
    expected = 0
    k+=1
    if actual == expected:
        print("Test %d in TestsMin passed" % k)
    else:
        print("Test %d in TestsMin failed" % k)

    # 2 тест - одинаковые минимальные значения
    a = [8,0,6,6,0]
    n = 3
    actual = zad.Min(a,n)
    expected = 2
    k+=1
    if actual == expected:
        print("Test %d in TestsMin passed" % k)
    else:
        print("Test %d in TestsMin failed" % k)

    # 3 тест - все нули обозначающие, что в диагонали нет отрицательных элементов
    a = [0,0,0,0,0]
    n = 3
    actual = zad.Min(a,n)
    expected = -1
    k+=1
    if actual == expected:
        print("Test %d in TestsMin passed" % k)
    else:
        print("Test %d in TestsMin failed" % k)    
    print()

def TestsMax():
    k = 0;
    # 1 тест - одно максимальное значение
    a = [6,0,0,7,3]
    n = 3
    actual = zad.Max(a,n)
    expected = 3
    k+=1
    if actual == expected:
        print("Test %d in TestsMax passed" % k)
    else:
        print("Test %d in TestsMax failed" % k)

    # 2 тест - одинаковые максимальные значения
    a = [2,-1,6,6,-1]
    n = 3
    actual = zad.Max(a,n)
    expected = 2
    k+=1
    if actual == expected:
        print("Test %d in TestsMax passed" % k)
    else:
        print("Test %d in TestsMax failed" % k)
        
    # 3 тест - все -1,обозначающие, что в диагонали нет положительных элементов
    a = [-1,-1,-1,-1,-1]
    n = 3
    actual = zad.Max(a,n)
    expected = -1
    k+=1
    if actual == expected:
        print("Test %d in TestsMax passed" % k)
    else:
        print("Test %d in TestsMax failed" % k)
        
    print()
    
def TestsForm_diag():
    k = 0;
    # 1 тест
    arr = [2, 0, 0]
    ind = 0
    n = 3
    actual = zad.form_diag(arr,ind,n)
    excepted = [2]
    k+=1
    if actual == excepted:
        print("Test %d in TestsForm_diag passed" % k)
    else:
        print("Test %d in TestsForm_diag failed" % k)
        
    # 2 тест
    arr = [-4, 3, 0]
    ind = 1
    n = 3
    actual = zad.form_diag(arr,ind,n)
    excepted = [-4, 3]
    k+=1
    if actual == excepted:
        print("Test %d in TestsForm_diag passed" % k)
    else:
        print("Test %d in TestsForm_diag failed" % k)

    # 3 тест
    arr = [3, 8, -1]
    ind = 2
    n = 3
    actual = zad.form_diag(arr,ind,n)
    excepted = [3, 8, -1]
    k+=1
    if actual == excepted:
        print("Test %d in TestsForm_diag passed" % k)
    else:
        print("Test %d in TestsForm_diag failed" % k)

    
    # 4 тест
    arr = [0, 4, 2]
    ind = 3
    n = 3
    actual = zad.form_diag(arr,ind,n)
    excepted = [4, 2]
    k+=1
    if actual == excepted:
        print("Test %d in TestsForm_diag passed" % k)
    else:
        print("Test %d in TestsForm_diag failed" % k)
        

    # 5 тест
    arr = [0, 0, 6]
    ind = 4
    n = 3
    actual = zad.form_diag(arr,ind,n)
    excepted = [6]
    k+=1
    if actual == excepted:
        print("Test %d in TestsForm_diag passed" % k)
    else:
        print("Test %d in TestsForm_diag failed" % k)
    
def main():    
    TestsOpredPoboch()    
    TestsOpredGlav()
    TestsProizvOtr()
    TestsSumPoloj()
    TestsMin()
    TestsMax()
    TestsForm_diag()
main()
