#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define OK 0 
#define INVALID_NUMBER -1
#define INVALID_SIZE -2
#define INVALID_FILE -3
#define MEMORY_ERROR -4


typedef struct IA
{
    int Nk; 
    int number_row;
    struct IA *next;
} IA;


int input_razr(FILE *f, double **A, int **JA, IA **ia,int *counter_not_zero, int *n, int *m)
{
    double elem;
    *counter_not_zero = 0;
    int counter_all = 0;
    IA *begin = NULL;
    
    *A = malloc((*n)*(*m)*sizeof(double));
    if (!*A)
        return MEMORY_ERROR;
    *JA = malloc((*n)*(*m)*sizeof(int));
    if (!*JA)
        return MEMORY_ERROR;

    IA *tmp = malloc(sizeof(IA));
    if (!tmp)
    {
        free(*A);
        free(*JA);
        return MEMORY_ERROR;
    }
    tmp->Nk = 0;
    tmp->number_row = 0;
    tmp->next = NULL;
    (*ia) = tmp;
    begin = (*ia);
    
    for (int i = 0; i < *n; i++ )
    {
        for (int j = 0; j < *m; j++ )
        {
            if (fscanf(f,"%lf",&elem) != 1)
            {
                free(*A);
                free(*JA);
                return INVALID_NUMBER;
            }
            else
            {
                if (elem != 0)
                {
                    (*A)[*counter_not_zero] = elem;
                    (*JA)[*counter_not_zero] = j;
                    (*counter_not_zero)++;
                }
                counter_all++;
            }  
        }
        
        IA *tmp = malloc(sizeof(IA));
        if (!tmp)
        {
            free(*A);
            free(*JA);                
            return MEMORY_ERROR;
        }
        tmp->Nk = *counter_not_zero;
        tmp->number_row = i+1;
        tmp->next = NULL;
        (*ia)->next = tmp;
        (*ia) = tmp;
    }
    *ia = begin;
    

    return OK;
}

int matr_to_razr(double **m1, double **A, int **JA, IA **ia, int *counter_not_zero, int *n, int *m)
{
    *counter_not_zero = 0;
    int counter_all = 0;
    IA *begin = NULL;
    
    *A = malloc((*n)*(*m)*sizeof(double));
    if (!*A)
        return MEMORY_ERROR;
    *JA = malloc((*n)*(*m)*sizeof(int));
    if (!*JA)
        return MEMORY_ERROR;

    IA *tmp = malloc(sizeof(IA));
    if (!tmp)
    {
        free(*A);
        free(*JA);
        return MEMORY_ERROR;
    }
    tmp->Nk = 0;
    tmp->number_row = 0;
    tmp->next = NULL;
    (*ia) = tmp;
    begin = (*ia);
    
    for (int i = 0; i < *n; i++ )
    {
        for (int j = 0; j < *m; j++ )
        {

            if (m1[i][j] != 0)
            {
                (*A)[*counter_not_zero] = m1[i][j];
                (*JA)[*counter_not_zero] = j;
                (*counter_not_zero)++;
            }
            counter_all++;
             
        }
        
        IA *tmp = malloc(sizeof(IA));
        if (!tmp)
        {
            free(*A);
            free(*JA);                
            return MEMORY_ERROR;
        }
        tmp->Nk = *counter_not_zero;
        tmp->number_row = i+1;
        tmp->next = NULL;
        (*ia)->next = tmp;
        (*ia) = tmp;
    }
    *ia = begin;
    return OK;
}

double get_element(int i,int j, double *A, int *JA, IA *ia)
{
    double AA = 0; // значение искомого элемента
    while (ia->number_row != i)
        ia = ia->next;
    int N1=ia->Nk;
    int N2=ia->next->Nk;
    for(int k = N1; k < N2; k++)
    {
        if (JA[k] == j)
        {
            AA = A[k];
            break;
        }
    }
    return AA;
}

int print_razr(FILE *f, double *A, int *JA, IA *elem_ia,int counter_not_zero, int n, int m)
{    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fprintf(f,"%f ", get_element(i, j, A, JA, elem_ia));
        }
        fprintf(f,"\n");
        elem_ia = elem_ia->next;
    }
    return 0;
}

void get_column(int number, int n, double *A, int *JA, IA *elem_ia, int counter_not_zero1,double **A1, int **JA1, int *counter_not_zero)
{

    *counter_not_zero = 0;
    
    for (int j = 0; j < counter_not_zero1; j++)
    {
        if (JA[j] == number)
        {
            (*A1)[*counter_not_zero] = A[j];
            while(j >= elem_ia->Nk)
                elem_ia = elem_ia->next;
            //printf("#%d  %d#",j,elem_ia->Nk);
            (*JA1)[*counter_not_zero] = elem_ia->number_row-1;
            (*counter_not_zero)++;
        }
    }
}

void multiply_razr(double *A, int *JA, IA *ia, double *B, int *JB, IA *ib, double **res_matr)
{
    int k = 0;
    IA *ia_copy = ia;
    while(ib->next)
    {
        for (int i = ib->Nk; i < ib->next->Nk; i++)
        {
            while(JB[i] != ia->number_row)
                ia = ia->next;
            for (int j = ia->Nk; j < ia->next->Nk; j++)
            {
                res_matr[k][JA[j]] += A[j] * B[i];
            }
        }
        k++;
        ia = ia_copy;
        ib = ib->next;
    }    
}

void free_matrix_rows(double **data, int n)
{
    for (int i = 0;i < n; i++)
    {
        free((data)[i]);        
    }
    free(data);    
}
  
// Выделение памяти  
double **allocate_matrix_row(int n, int m)
{
    double **data = (double**)calloc(n,sizeof(double*));
    if (!data)
        return NULL;
    for (int i = 0;i < n;i++)
    {
        data[i] = (double*)calloc(m,sizeof(double));
        if (!data[i])
        {
            free_matrix_rows(data, n);
            return NULL;
        } 
    }
    return data;
}


int multiply_matrix(double **matrix1, double **matrix2, int n1, int m1, int n2, int m2, double ***matrix3)
{  
    for (int ii = 0; ii < n1; ii++)
    {
        for (int i = 0; i < m2; i++)
        {
            //(*matrix3)[ii][i] = 0;
            for (int j = 0; j < n2; j++)
            {
                (*matrix3)[ii][i] += matrix1[ii][j] * matrix2[j][i];
            }
        }        
    }  
    return OK;
}

void razr_in_full(double *A, int *JA, IA *ia, double *B, int *JB, IA *ib, int n1, int m1, int n2, double ***mat1, double ***mat2)
{
    *mat1 = allocate_matrix_row(n1, m1);
    *mat2 = allocate_matrix_row(n2, n1);
    double elem;
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m1; j++)
        {
            elem = get_element(i, j, A, JA, ia);
            (*mat1)[i][j] = elem;
        }
    }
    for (int i = 0; i < n2; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            elem = get_element(i, j, B, JB, ib);
            (*mat2)[i][j] = elem;
        }
    }
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

void print_matrix(double **matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%f ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");    
}


void print_time_size(void)
{
    unsigned long long tb, te;
    unsigned long long t_mid1 = 0;
    unsigned long long t_mid2 = 0;
    FILE *f1;
    FILE *f2;
    int w;
    int nn = 900;
    int k;
    double **mat1;
    double **mat2;
    double **mat_res;
    int size_matrix = nn*nn;
    double *A = NULL;
    int *JA = NULL;
    IA *elem_ia = NULL;
    int counter_not_zero1;
    int n1,m1;
    
    double *B = NULL;
    int *JB = NULL;
    IA *elem_ib = NULL;
    int counter_not_zero2;
    int n2,m2;
    int pr = 0;
    int pam_razr = 0;
	double **res = allocate_matrix_row(nn, nn);
    printf("Матрица %dx%d\n",nn,nn);
    printf("  Процент         разреженная     классическая  отношение    разреженная     классическая    отношение \n");
    printf("заполнения          (время)          (время)                   (память)       (память)\n");
    for (int e = size_matrix/10; e <= size_matrix; e+=(size_matrix/10))
    {
        pr+=10;
        f1 = fopen("v.txt","w");
        f2 = fopen("m.txt","w");
        
        fprintf(f1,"%d\n",nn);
        k = 0;
        for (int i = 0; i < nn; i++)
        {
            if (k < e/nn)
                fprintf(f1,"%f ",1.0);
            else 
                fprintf(f1,"%f ",0.0);
            k++;
        }
        
        k = 0;
        fprintf(f2,"%d %d\n",nn,nn);
        for (int i = 0; i < nn; i++)
        {
            for (int j = 0; j < nn; j++)
            {
                
                if (k < e)
                    fprintf(f2,"%f ",1.0);
                else 
                    fprintf(f2,"%f ",0.0);
                k++;
            }
            fprintf(f2,"\n");
        }
        fclose(f1);
        fclose(f2);
        
        f1 = fopen("v.txt","r");
        f2 = fopen("m.txt","r");
		fscanf(f1,"%d",&m2);
		n2 = 1;
        fscanf(f2,"%d %d",&n1, &m1);

        
        input_razr(f2, &A, &JA, &elem_ia, &counter_not_zero1, &n1, &m1);
        input_razr(f1, &B, &JB, &elem_ib, &counter_not_zero2, &n2, &m2);
        
        
        w = 100;
        t_mid1 = 0;
        for (int k = 0; k < w; k++)
        {
            tb = tick();
            multiply_razr(A, JA, elem_ia, B, JB, elem_ib, res);
            te = tick();
            if (te > tb )
                t_mid1 += ( te - tb );
            else
                w--;
        }
        t_mid1 = t_mid1/w;
        printf("%3d%%                %7I64d        ",pr,t_mid1);
        
        
        razr_in_full(A, JA, elem_ia, B, JB, elem_ib, n1, m1, n2, &mat1, &mat2);    
        t_mid2 = 0;
        w = 100;
        mat_res = allocate_matrix_row(n2, n1);
        for (int k = 0; k < w; k++)
        {
            tb = tick();
            multiply_matrix(mat2, mat1, n2, n1, n1, m1, &mat_res);
            te = tick();
            if (te > tb )
                t_mid2 += ( te - tb );
            else
               w--;
        }
        t_mid2 = t_mid2/w;
        printf("%7I64d  ",t_mid2);
        printf("  %8.3f  ",(float)t_mid2/t_mid1);
        
        pam_razr = (sizeof(int)+sizeof(double))*(counter_not_zero1+counter_not_zero2);
        pam_razr += (sizeof(IA)*(n1+1));
        IA *copy;
        while (elem_ia)
        {
            copy = elem_ia;
            elem_ia = elem_ia->next;
            free(copy);
        }
        while (elem_ib)
        {
            copy = elem_ib;
            elem_ib = elem_ib->next;
            free(copy);
        }
        printf("      %7d   ",pam_razr);
        
        printf("       %7I64d",sizeof(double)*size_matrix);
        printf("    %8.3f\n",(sizeof(double)*size_matrix)/(float)pam_razr);
        
        free(A);
        free(JA);
        free(B);
        free(JB);
        
        //free_matrix_rows(res, n2);
        //free_matrix_rows(mat_res, n2);
        fclose(f1);
        fclose(f2);    
    }
}


int main(void)
{
    unsigned long long tb, te;

    double *A = NULL;
    int *JA = NULL;
    IA *elem_ia = NULL;
    int counter_not_zero1;
    int n1,m1;
    
    double *B = NULL;
    int *JB = NULL;
    IA *elem_ib = NULL;
    int counter_not_zero2;
    int n2,m2;
    
    srand(time(NULL));
    FILE *f1;
    FILE *f2;
    
    
    setbuf(stdout,NULL);
    int err = OK;
    printf("%I64d\n",sizeof(IA));
    while(1)
    {
        int choose;
        printf("Умножение вектора на матрицу:\n");
        printf("Вводимые данные - вещественные и целые числа\n");
        printf("Меню:\n");
        printf("1 - Ввести данные вручную\n");
        printf("2 - Ввести данные из файла\n");
        printf("3 - Вывести сравнительную характеристику\n\n");
        printf("0 - Выход\n\n");
        printf("Ваш выбор: ");
        int ch1;
        int ch2;
        int ii, jj;
        double zn;
        if (scanf("%d",&choose) == 1)
        {
            if (choose == 1)
            {
                printf("1 - ввести элементы по индексам\n");
                printf("2 - ввести все элементы\n");
                printf("Выбор: ");
                scanf("%d", &ch1);
                if (ch1 == 1)
                {
                    
                    printf("Введите размер вектора:\n");
                    if (scanf("%d",&m2) != 1)
                    {
                        printf("Некорректный размер");
                        return INVALID_SIZE;
                    }
                    n2 = 1;
                    double **vector = allocate_matrix_row(n2,m2);                
                    while(1)
                    {
                        printf("1 - Ввести очередной элемент вектора\n");
                        printf("0 - Завершить\n");
                        scanf("%d", &ch2);
                        
                        if (ch2 == 1)
                        {
                            printf("Введите номер элемента вектора(с 0): ");
                            if (scanf("%d", &ii) != 1 || (ii >= m2 || ii < 0))
                            {
                                printf("Некорректный индекс\n");
                                return INVALID_SIZE;
                            }
                            printf("\na[%d] = ",ii);
                            if (scanf("%lf", &zn) != 1)
                            {                        
                                printf("Некорректный элемент\n");
                                return INVALID_NUMBER;
                            }
                            vector[0][ii] = zn;
                        }
                        if (ch2 == 0)
                        {
                            break;
                        }
                    }
                    matr_to_razr(vector, &B,  &JB, &elem_ib, &counter_not_zero2, &n2, &m2);
                    printf("Введите размер матрицы через пробел:\n");
                    if (scanf("%d %d",&n1, &m1) != 2)
                    {
                        printf("Некорректный размер");
                        return INVALID_SIZE;
                    }
                    if (m2 != n1)
                    {
                        printf("Количество столбцов вектора не равно количеству строк матрицы!\n");
                        return -5;
                    }
                    double **matrix = allocate_matrix_row(n1,m1);
                    while(1)
                    {
                        printf("1 - Ввести очередной элемент матрицы\n");
                        printf("0 - Завершить\n");
                        scanf("%d", &ch2);
                        
                        if (ch2 == 1)
                        {
                            printf("Введите индексы элемента матрицы(с 0): ");
                            if (scanf("%d %d", &ii, &jj) != 2 || (ii >= n1 || ii < 0 || jj >= m1 || jj < 0))
                            {
                                printf("Некорректный индекс\n");
                                return INVALID_SIZE;
                            }
                            printf("\na[%d][%d] = ", ii, jj);
                            if (scanf("%lf", &zn) != 1)
                            {                        
                                printf("Некорректный элемент\n");
                                return INVALID_NUMBER;
                            }
                            matrix[ii][jj] = zn;
                        }
                        if (ch2 == 0)
                        {
                            break;
                        }
                    }
                    matr_to_razr(matrix, &A,  &JA, &elem_ia, &counter_not_zero1, &n1, &m1);
                    
                    
                    printf("Вектор:\n");
                    print_razr(stdout, B, JB, elem_ib, counter_not_zero2, n2, m2);
                    printf("\n");
                    printf("Матрица:\n");
                    print_razr(stdout, A, JA, elem_ia, counter_not_zero1, n1, m1);
                    printf("\n");
                    
                    double **res = allocate_matrix_row(n2, m1);
                    tb = tick();
                    multiply_razr(A, JA, elem_ia, B, JB, elem_ib, res);
                    te = tick();
                    printf("Время выполнения умножения разреженных матриц = %I64d\n",te - tb);
                    
                    
                    double **mat1;
                    double **mat2;
                    double **mat_res = allocate_matrix_row(n2, m1);
                    
                    razr_in_full(A, JA, elem_ia, B, JB, elem_ib, n1, m1, n2, &mat1, &mat2);
  
                    tb = tick();
                    multiply_matrix(mat2, mat1, n2, m2, n1, m1, &mat_res);
                    te = tick();
                    printf("Время выполнения стандартного умножения %I64d\n",te - tb);
                    
                    
                    
                    printf("Результат умножения разреженных матриц:\n");
                    //print_matrix(res, n2, m1);
					
                    printf("Результат умножения обычных матриц:\n");
                    print_matrix(mat_res, n2, m1);
                    free(A);
                    free(JA);
                    free(B);
                    free(JB);
                    IA *copy;
                    while (elem_ia)
                    {
                        copy = elem_ia;
                        elem_ia = elem_ia->next;
                        free(copy);
                    }
                    while (elem_ib)
                    {
                        copy = elem_ib;
                        elem_ib = elem_ib->next;
                        free(copy);
                    }
                    free_matrix_rows(mat_res, n2);
                    free_matrix_rows(res, n2);
                    
                    
                }
                if (ch1 == 2)
                {
                    printf("Введите размер и элементы вектора:\n");
                    if (scanf("%d",&m2) != 1)
                    {
                        printf("Некорректный размер");
                        return INVALID_SIZE;
                    }
                    n2 = 1;
                    err = input_razr(stdin, &B, &JB, &elem_ib, &counter_not_zero2, &n2, &m2);
                    if (err == INVALID_NUMBER)
                    {
                        printf("Некорректный элемент вектора\n");
                        return err;
                    }
                    if (err == MEMORY_ERROR)
                    {
                        printf("Ошибка памяти\n");
                        return err;
                    }
                    printf("Введите размер и элементы матрицы:\n");
                    if (scanf("%d %d",&n1, &m1) != 2)
                    {
                        printf("Некорректный размер");
                        return INVALID_SIZE;
                    }
                    if (m2 != n1)
                    {
                        printf("Количество столбцов вектора не равно количеству строк матрицы!\n");
                        return -5;
                    }
                    err = input_razr(stdin, &A, &JA, &elem_ia, &counter_not_zero1, &n1, &m1);
                    if (err == INVALID_NUMBER)
                    {
                        printf("Некорректный элемент матрицы\n");
                        return err;
                    }
                    if (err == MEMORY_ERROR)
                    {
                        printf("Ошибка памяти\n");
                        return err;
                    }
        
                    printf("Вектор:\n");
                    print_razr(stdout, B, JB, elem_ib, counter_not_zero2, n2, m2);
                    printf("\n");
                    printf("Матрица:\n");
                    print_razr(stdout, A, JA, elem_ia, counter_not_zero1, n1, m1);
                    printf("\n");
                    
                    double **res = allocate_matrix_row(n2, m1);
                    tb = tick();
                    multiply_razr(A, JA, elem_ia, B, JB, elem_ib, res);
                    te = tick();
                    printf("Время выполнения умножения разреженных матриц = %I64d\n",te - tb);
                    
                    
                    double **mat1;
                    double **mat2;
                    double **mat_res = allocate_matrix_row(n2, m1);
                    
                    razr_in_full(A, JA, elem_ia, B, JB, elem_ib, n1, m1, n2, &mat1, &mat2);                   
                    
                    tb = tick();
                    multiply_matrix(mat2, mat1, n2, m2, n1, m1, &mat_res);
                    te = tick();
                    printf("Время выполнения стандартного умножения %I64d\n",te - tb);
                    
                    
                    
                    printf("Результат умножения разреженных матриц:\n");
                    print_matrix(res, n2, m1);
                    printf("Результат умножения обычных матриц:\n");
                    print_matrix(mat_res, n2, m1);
                    free(A);
                    free(JA);
                    free(B);
                    free(JB);
                    IA *copy;
                    while (elem_ia)
                    {
                        copy = elem_ia;
                        elem_ia = elem_ia->next;
                        free(copy);
                    }
                    while (elem_ib)
                    {
                        copy = elem_ib;
                        elem_ib = elem_ib->next;
                        free(copy);
                    }
                    free_matrix_rows(mat_res, n2);
                    free_matrix_rows(res, n2);
                    
                }
                
            }
            else if (choose == 2)
            {
                f1 = fopen("mat.txt","r");
                f2 = fopen("vect.txt","r");
                
                
                if (fscanf(f2,"%d",&m2) != 1)
                {
                    printf("Некорректный размер");
                    return INVALID_SIZE;
                }
                n2 = 1;
                err = input_razr(f2, &B, &JB, &elem_ib, &counter_not_zero2, &n2, &m2);
                if (err == INVALID_NUMBER)
                {
                    printf("Некорректный элемент вектора\n");
                    return err;
                }
                if (err == MEMORY_ERROR)
                {
                    printf("Ошибка памяти\n");
                    return err;
                }
                if (fscanf(f1,"%d %d",&n1, &m1) != 2)
                {
                    printf("Некорректный размер");
                    return INVALID_SIZE;
                }
                if (m2 != n1)
                {
                    printf("Количество столбцов вектора не равно количеству строк матрицы!\n");
                    return -5;
                }
                err = input_razr(f1, &A, &JA, &elem_ia, &counter_not_zero1, &n1, &m1);

                if (err == INVALID_NUMBER)
                {
                    printf("Некорректный элемент матрицы\n");
                    return err;
                }
                if (err == MEMORY_ERROR)
                {
                    printf("Ошибка памяти\n");
                    return err;
                }
                fclose(f1);
                fclose(f2);
                
                if (n1 < 20 && m1 < 20)
                {
                    printf("Вектор:\n");
                    print_razr(stdout, B, JB, elem_ib, counter_not_zero2, n2, m2);
                    printf("\n");
                    printf("Матрица:\n");
                    print_razr(stdout, A, JA, elem_ia, counter_not_zero1, n1, m1);
                    printf("\n");
                }
                double **res = allocate_matrix_row(n2, m1);
                tb = tick();
                multiply_razr(A, JA, elem_ia, B, JB, elem_ib, res);
                te = tick();
                printf("Время выполнения умножения разреженных матриц = %I64d\n",te - tb);
                
                double **mat1;
                double **mat2;
                double **mat_res = allocate_matrix_row(n2, m1);
                
                razr_in_full(A, JA, elem_ia, B, JB, elem_ib, n1, m1, n2, &mat1, &mat2);    
                
                tb = tick();
                multiply_matrix(mat2, mat1, n2, m2, n1, m1, &mat_res);
                te = tick();
                printf("Время выполнения стандартного умножения %I64d\n",te - tb);
                
                printf("Результат умножения разреженных матриц:\n");
                print_matrix(res, n2, m1);
                printf("Результат умножения обычных матриц:\n");
                print_matrix(mat_res, n2, m1);
                free(A);
                free(JA);
                free(B);
                free(JB);        
                IA *copy;
                while (elem_ia)
                {
                    copy = elem_ia;
                    elem_ia = elem_ia->next;
                    free(copy);
                }
                while (elem_ib)
                {
                    copy = elem_ib;
                    elem_ib = elem_ib->next;
                    free(copy);
                }
                free_matrix_rows(mat_res, n2);
                free_matrix_rows(res, n2);
                
                
            }
            else if (choose == 3)
            {
                print_time_size();    
            }
            else if (choose == 0)
                break;
            else
            {
                printf("Такого пункта меню нет!\n");
                fflush(stdin);
            }
        }
        else
        {
            printf("Такого пункта меню нет!\n");
            fflush(stdin);
        }    
    }
    return 0;
}