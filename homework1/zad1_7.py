# Спасенов Иван ИУ7-23 Вариант 7
#---------------------------------------------------------------------------------#
# Дана квадратная целочисленная матрица. Найти диагональ, параллельную главной,   #
# имеющую максимальную сумму положительных элементов, и диагональ, параллельную   #
# побочной, имеющую минимальное произведение отрицательных (при поиске минимума и #
# максимума главная и побочная диагонали также учитываются).                      #
#---------------------------------------------------------------------------------#

def ReadMatrix():
    n = int(input("Введите размер матрицы: "))  
    try:
        if n > 100:
            return (-1,-1,-1)  # Превышена размерность матрицы
        elif n < 1:
            return (-2,-2,-2)  # Некорректный размер матрицы
        print("Введите матрицу:")
        a = [[]]*n
        for i in range(n):
            s = input()
            x = s.split()
            if len(x) != n:
                return (-3,-3,-3)  # Матрица введена некорректно
            for j in range(len(x)):
                x[j] = int(x[j])
            a[i] = x
    except (TypeError, ValueError):
            return (-3,-3,-3)  # Матрица введена некорректно
    return (0,a,n)

def OpredPoboch(a,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    poboch = [0] * (2*n-1) 
    for i in range(2*n-1): 
        poboch[i] = [0] * n
    for i in range(n):
        for j in range(n):
            poboch[i+j][j] = a[i][j]         
    return poboch


def OpredGlav(a,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    glav = [0] * (2*n-1) 
    for i in range(2*n-1): 
        glav[i] = [0] * n
    for i in range(n):
        for j in range(n):
            glav[j-i+n-1][j] = a[i][j]         
    return glav

def ProizvOtr(poboch,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    pr = [1]*(2*n-1)
    for i in range(2*n-1):
        bool = False
        for j in range(n):
            if poboch[i][j] < 0:
                pr[i] *= poboch[i][j]
                bool = True
        if not bool:
            pr[i] = 0
    return(pr)
                
def SumPoloj(glav,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    summa = [0]*(2*n-1)
    for i in range(2*n-1):
        bool = False
        for j in range(n):
            if glav[i][j] > 0:
                summa[i] += glav[i][j]
                bool = True
        if not bool:
            summa[i] = -1
    return(summa)            

def Min(pr,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    min_pr = 0
    mini = -1
    for i in range(2*n-1):
        if pr[i] != 0:
            if min_pr != 0:
                if pr[i] < min_pr:
                    min_pr = pr[i]
                    mini = i
            else:
                min_pr = pr[i]
                mini = i
    assert (-1 <= mini < 2*n-1),"Некорректный индекс минимального элемента"
    return mini

def Max(summa,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    max_summa = -1
    maxi = -1
    for i in range(2*n-1):
        if summa[i] != -1:
            if max_summa != -1:
                if summa[i] > max_summa:
                    max_summa = summa[i]
                    maxi = i
            else:
                max_summa = summa[i]
                maxi = i
    assert (-1 <= maxi < 2*n-1),"Некорректный индекс максимального элемента"
    return maxi

def form_diag(arr,ind,n):
    assert (0 <= ind < 2*n-1),"Некорректный индекс элемента"
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    if ind <= (2*n-1)//2:
        ans = [0]*(ind+1)
        for i in range(ind+1):
            ans[i] = arr[ind][i]
    else:
        ans = [0]*(2*n-ind-1)
        k = 0
        for i in range(ind-(2*n-1)//2,n):
            ans[k] = arr[ind][i]
            k += 1    
    return ans

def print_poboch_giagonal(min_index,poboch_diagonali,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    assert (-1 <= min_index < 2*n-1),"Некорректный индекс минимального элемента"
    if min_index < 0:
        print("Невозможно найти диагональ, параллельную побочной имеющую минимальное\
               произведение отрицательных элементов, так как их нет в матрице")
    else:
        poboch_ans = form_diag(poboch_diagonali,min_index,n)
        for i in range(len(poboch_ans)):
            print(poboch_ans[i],end=' ')    
        print(" - диагональ, параллельная побочной имеющая минимальное произведение отрицательных элементов")
        
def print_glav_giagonal(max_index,glav_diagonali,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    assert (-1 <= max_index < 2*n-1),"Некорректный индекс максимального элемента"
    if max_index < 0:
        print("Невозможно найти диагональ, параллельную главной имеющую максимальную\
              сумму положительных элементов, так как их нет в матрице")
    else:
        glav_ans = form_diag(glav_diagonali,max_index,n)
        for i in range(len(glav_ans)):
            print(glav_ans[i],end=' ')
        print(" - диагональ, параллельная главной имеющая максимальную сумму положительных элементов ")

def error_print(k):
    if k == -1:
        print("Превышена размерность матрицы")
    elif k == -2:
        print("Некорректный размер матрицы")
    elif k == -3:
        print("Матрица введена некорректно")

def main():
    try:
        error,a,n = ReadMatrix()
        if error != 0:
            error_print(error)
            return error
        
        poboch_diagonali = OpredPoboch(a,n)
        proizvedenie_diag = ProizvOtr(poboch_diagonali,n)
        min_index = Min(proizvedenie_diag,n)
        print_poboch_giagonal(min_index,poboch_diagonali,n)

        glav_diagonali = OpredGlav(a,n)
        summa_diag = SumPoloj(glav_diagonali,n)
        max_index = Max(summa_diag,n)
        print_glav_giagonal(max_index,glav_diagonali,n)
        
    except (TypeError, ValueError):
        print("Некорректный размер матрицы")

main()
