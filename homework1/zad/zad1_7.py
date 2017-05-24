## @mainpage Программа, находящая диагонали в матрице
# @section intro_sec Описание программы
#
# Программа находит диагональ матрицы, параллельную главной,
# имеющую максимальную сумму положительных элементов, и диагональ матрицы, параллельную
# побочной, имеющую минимальное произведение отрицательных

## Считывает размер матрицы и саму матрицу
#
# @return a - матрица размера n*n
# @return n - размер матрицы
# @throw DIMENSION_EXCEEDED Превышена размерность матрицы
# @throw INVALID_SIZE Некорректный размер матрицы
# @throw ERR_NUMBER_IN_LINE Количество элементов матрицы в строке не соответствует размеру матрицы
# @throw INVALID_ELEMENTS Элементы матрицы введены некорректно
def ReadMatrix():
    n = int(input("Введите размер матрицы: "))  
    try:
        if n > 100:
            return (DIMENSION_EXCEEDED,None,-1)  # Превышена размерность матрицы
        elif n < 1:
            return (INVALID_SIZE,None,-1)  # Некорректный размер матрицы  
        print("Введите матрицу:")
        a = [[]]*n
        for i in range(n):
            s = input()
            x = s.split()      
            if len(x) != n:
                return (ERR_NUMBER_IN_LINE,None,-1)  # Количество элементов матрицы в строке не соответствует размеру матрицы
            for j in range(len(x)):
                x[j] = int(x[j])
            a[i] = x
    except (TypeError, ValueError):
            return (INVALID_ELEMENTS,None,-1)  # Элементы матрицы введены некорректно
    return (0,a,n)

## Выделяет из массива диагонали параллельные побочной
#
# @param a - матрица размера n*n
# @param n - размер матрицы
# @return poboch - двумерный массив диагоналей, параллельных побочной, размера 2*n-1 на n 
def OpredPoboch(a,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    assert (a != None),"Матрица не инициализирована"
    kolvo_diag = 2*n-1
    poboch = [0] * (kolvo_diag) 
    for i in range(kolvo_diag): 
        poboch[i] = [0] * n
    for i in range(n):
        for j in range(n):
            poboch[i+j][j] = a[i][j]         
    return poboch

## Выделяет из массива диагонали параллельные главной
#
# @param a - матрица размера n*n
# @param n - размер матрицы
# @return glav - двумерный массив диагоналей, параллельных главной, размера 2*n-1 на n
def OpredGlav(a,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    assert (a != None),"Матрица не инициализирована"
    kolvo_diag = 2*n-1
    glav = [0] * (kolvo_diag) 
    for i in range(kolvo_diag): 
        glav[i] = [0] * n
    for i in range(n):
        for j in range(n):
            glav[j-i+n-1][j] = a[i][j]         
    return glav

## Перемножает отрицательные элементы массива
#
# @param poboch - двумерный массив размера 2*n-1 на n
# @param n - размер матрицы
# @return pr - массив размера 2*n-1 произведений отрицательных элементов
def ProizvOtr(poboch,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    assert (poboch != None),"Массив не инициализирован"
    kolvo_diag = 2*n-1
    pr = [1]*(kolvo_diag)
    for i in range(kolvo_diag):
        bool = False
        for j in range(n):
            if poboch[i][j] < 0:
                pr[i] *= poboch[i][j]
                bool = True
        if not bool:
            pr[i] = 0
    return(pr)

## Суммирует положительные элементы массива
#
# @param glav - двумерный массив размера 2*n-1 на n
# @param n - размер матрицы
# @return summa - массив размера 2*n-1 сумм положительных элементов	
def SumPoloj(glav,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    assert (glav != None),"Массив не инициализирован"
    kolvo_diag = 2*n-1
    summa = [0]*(kolvo_diag)
    for i in range(kolvo_diag):
        bool = False
        for j in range(n):
            if glav[i][j] > 0:
                summa[i] += glav[i][j]
                bool = True
        if not bool:
            summa[i] = -1
    return(summa)
	
## Находит идекс минимального элемента
#
# @param pr - массив размера 2*n-1
# @param n - размер матрицы
# @return mini - индекс минимального элемента массива		
def Min(pr,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    assert (pr != None),"Массив не инициализирован"
    kolvo_diag = 2*n-1
    min_pr = 0
    mini = -1
    for i in range(kolvo_diag):
        if pr[i] != 0:
            if min_pr != 0:
                if pr[i] < min_pr:
                    min_pr = pr[i]
                    mini = i
            else:
                min_pr = pr[i]
                mini = i
    assert (-1 <= mini < kolvo_diag),"Некорректный индекс минимального элемента"
    return mini

## Находит идекс максимального элемента
#
# @param summa - массив размера 2*n-1
# @param n - размер матрицы
# @return maxi - индекс максимального элемента массива	
def Max(summa,n):
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    assert (summa != None),"Массив не инициализирован"
    kolvo_diag = 2*n-1
    max_summa = -1
    maxi = -1
    for i in range(kolvo_diag):
        if summa[i] != -1:
            if max_summa != -1:
                if summa[i] > max_summa:
                    max_summa = summa[i]
                    maxi = i
            else:
                max_summa = summa[i]
                maxi = i
    assert (-1 <= maxi < kolvo_diag),"Некорректный индекс максимального элемента"
    return maxi
	
## Формирует диагональ матрицы, убирая лишние элементы
#
# @param arr - двумерный массив диагоналей размера 2*n-1 на n
# @param ind - индекс диагонали
# @param n - размер матрицы
# @return ans - диагональ матрицы	
def form_diag(arr,ind,n):
    kolvo_diag = 2*n-1
    assert (0 <= ind < kolvo_diag),"Некорректный индекс элемента"
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    assert (arr != None),"Массив не инициализирован"
    if ind <= (2*n-1)//2:
        ans = [0]*(ind+1)
        for i in range(ind+1):
            ans[i] = arr[ind][i]
    else:
        ans = [0]*(2*n-ind-1)
        k = 0
        for i in range(ind-(kolvo_diag)//2,n):
            ans[k] = arr[ind][i]
            k += 1    
    return ans

## Печатает диагональ параллельную побочной
#
# @param min_index - индекс диагонали
# @param poboch_diagonali - двумерный массив диагоналей размера 2*n-1 на n
# @param n - размер матрицы
def print_poboch_giagonal(min_index,poboch_diagonali,n):
    kolvo_diag = 2*n-1
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    assert (-1 <= min_index < kolvo_diag),"Некорректный индекс минимального элемента"
    assert (poboch_diagonali != None),"Массив не инициализирован"
    if min_index < 0:
        print("Невозможно найти диагональ, параллельную побочной имеющую минимальное \
произведение отрицательных элементов, так как их нет в матрице")
    else:
        poboch_ans = form_diag(poboch_diagonali,min_index,n)
        for i in range(len(poboch_ans)):
            print(poboch_ans[i],end=' ')    
        print(" - диагональ, параллельная побочной имеющая минимальное произведение отрицательных элементов")

## Печатает диагональ параллельную главной
#
# @param max_index - индекс диагонали
# @param glav_diagonali - двумерный массив диагоналей размера 2*n-1 на n
# @param n - размер матрицы        
def print_glav_giagonal(max_index,glav_diagonali,n):
    kolvo_diag = 2*n-1
    assert (1 <= n <= 100),"Некорректный размер матрицы"
    assert (-1 <= max_index < kolvo_diag),"Некорректный индекс максимального элемента"
    assert (glav_diagonali != None),"Массив не инициализирован"
    if max_index < 0:
        print("Невозможно найти диагональ, параллельную главной имеющую максимальную сумму \
положительных элементов, так как их нет в матрице")
    else:
        glav_ans = form_diag(glav_diagonali,max_index,n)
        for i in range(len(glav_ans)):
            print(glav_ans[i],end=' ')
        print(" - диагональ, параллельная главной имеющая максимальную сумму положительных элементов ")

## Печатает ошибку, возникшую в программе
#
# @param k - номер ошибки		
def error_print(k):
    assert (k != None),"Код ошибки не инициализирован"
    if k == DIMENSION_EXCEEDED:
        print("Превышена размерность матрицы")
    elif k == INVALID_SIZE:
        print("Некорректный размер матрицы")
    elif k == ERR_NUMBER_IN_LINE:
        print("Количество элементов матрицы в строке не соответствует размеру матрицы")
    elif k == INVALID_ELEMENTS:
        print("Элементы матрицы введены некорректно")
		
## Точка входа в программу
#
# @throw INVALID_SIZE Некорректный размера матрицы
def main():
    DIMENSION_EXCEEDED = -1
    INVALID_SIZE = -2
    ERR_NUMBER_IN_LINE = -3
    INVALID_ELEMENTS = -4
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
    

if __name__ == "__main__":
    main()
