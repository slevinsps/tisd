def ReadMatrix(n):
    try:
        if n > 100:
            raise Exception("Превышена размерность матрицы")
        elif n < 1:
            raise Exception("Некорректный размер матрицы")
        print("Введите матрицу:")
        a = [[]]*n
        for i in range(n):
            s = input()
            x = s.split()
            if len(x) != n:
                raise Exception("Матрица введена некорректно")
            for j in range(len(x)):
                x[j] = int(x[j])
            a[i] = x
    except (TypeError, ValueError):
            return -1,a
    return 0,a

def OpredPoboch(a,n):
    poboch = [0] * (2*n-1) 
    for i in range(2*n-1): 
        poboch[i] = [0] * n
    for i in range(n):
        for j in range(n):
            poboch[i+j][j] = a[i][j]         
    return poboch


def OpredGlav(a,n):
    glav = [0] * (2*n-1) 
    for i in range(2*n-1): 
        glav[i] = [0] * n
    for i in range(n):
        for j in range(n):
            glav[j-i+n-1][j] = a[i][j]         
    return glav

def ProizvOtr(poboch,n):
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
    return mini

def Max(summa,n):
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
    return maxi

def form_diag(arr,ind,n):
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
    if min_index < 0:
        print("Невозможно найти диагональ, параллельную побочной имеющую минимальное\
произведение отрицательных элементов, так как их нет в матрице")
    else:
        poboch_ans = form_diag(poboch_diagonali,min_index,n)
        for i in range(len(poboch_ans)):
            print(poboch_ans[i],end=' ')    
        print(" - диагональ, параллельная побочной имеющая минимальное произведение отрицательных элементов")
        
def print_glav_giagonal(max_index,glav_diagonali,n):
    if max_index < 0:
        print("Невозможно найти диагональ, параллельную главной имеющую максимальную\
сумму положительных элементов, так как их нет в матрице")
    else:
        glav_ans = form_diag(glav_diagonali,max_index,n)
        for i in range(len(glav_ans)):
            print(glav_ans[i],end=' ')
        print(" - диагональ, параллельная главной имеющая максимальную сумму положительных элементов ")
    
def main():
    try:

        n = int(input("Введите размер матрицы: "))  
        
        k,a = ReadMatrix(n)
        if k == -1:
           raise Exception("Матрица введена некорректно")

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
    except Exception as e:
        print(e)

main()
