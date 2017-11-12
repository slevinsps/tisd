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
#define NOT_ALL_ARGUMENTS -5
#define M 1000


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
	int bool1;
	int Nk = 0;
	IA *begin = NULL;
    if (fscanf(f,"%d %d",n,m) == 2)
    {
        *A = malloc((*n)*(*m)*sizeof(double));
		if (!*A)
            return MEMORY_ERROR;
        *JA = malloc((*n)*(*m)*sizeof(int));
		if (!*JA)
            return MEMORY_ERROR;
        
		
		IA *tmp = malloc(sizeof(IA));
		tmp->Nk = Nk;
		tmp->number_row = 0;
		tmp->next = NULL;
		(*ia) = tmp;
		begin = (*ia);
		
        for (int i = 0; i < *n; i++ )
        {
			bool1 = 1;
			Nk = -1;
            for (int j = 0; j < *m; j++ )
            {
                if (fscanf(f,"%lf",&elem) != 1)
                {
                    return INVALID_NUMBER;
                }
				else
				{
					if (elem != 0)
					{
						(*A)[*counter_not_zero] = elem;
						(*JA)[*counter_not_zero] = j;
						if (bool1)
						{
							Nk = *counter_not_zero;
							bool1 = 0;
						}
						(*counter_not_zero)++;
					}
					counter_all++;
				}  
            }
			
			IA *tmp = malloc(sizeof(IA));
			tmp->Nk = *counter_not_zero;
			tmp->number_row = i+1;
			tmp->next = NULL;
			(*ia)->next = tmp;
			(*ia) = tmp;
        }
		*ia = begin;
    }
    else
    {
        return INVALID_SIZE;
    }
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

void get_column(int number, int n, double *A, int *JA, IA *elem_ia, double **A1, int **JA1, int *counter_not_zero)
{
	*A1 = malloc(n*sizeof(double));
	*JA1 = malloc(n*sizeof(int));
	double elem;
	*counter_not_zero = 0;
	for (int j = 0; j < n; j++)
	{
		elem = get_element(j, number, A, JA, elem_ia);
		if (elem != 0)
		{
			(*A1)[*counter_not_zero] = elem;
			(*JA1)[*counter_not_zero] = j;
			(*counter_not_zero)++;
		}
	}
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

void multiply_razr(double *A, int *JA, IA *ia, double *B, int *JB, IA *ib, int n1, int m1, int n2, double **res_matr)
{
	double res = 0;
	int *IP1 = calloc(n1,sizeof(int));
	double *A1;
	int *JA1;
	int counter_not_zero;
	for (int k = 0; k < n2; k++)
	{
		for (int j = 0; j < m1; j++)
		{
			get_column(j, n1, A, JA, ia, &A1, &JA1,&counter_not_zero);
			
			for (int i = 0; i < counter_not_zero; i++)
			{
				IP1[JA1[i]] = i+1;		
			}
			
			for (int i = ib->Nk; i < ib->next->Nk; i++)
			{
				if (IP1[JB[i]] != 0)
				{
					res += (A1[IP1[JB[i]]-1]*B[i]);
				}
			}
			for (int i = 0; i < counter_not_zero; i++)
			{
				IP1[JA1[i]] = 0;		
			}
			res_matr[k][j] = res;
			res = 0;
		}
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
    double **data = (double**)malloc(n * sizeof(double*));
    if (!data)
        return NULL;
    for (int i = 0;i < n;i++)
    {
        data[i] = (double*)malloc(m * sizeof(double));
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
    if (m1 != n2)
		return -2;
	
	double **res = allocate_matrix_row(n1, m2);
	if (!res)
		return MEMORY_ERROR;
	*matrix3 = res;
   
	for (int ii = 0; ii < n1; ii++)
	{
		for (int i = 0; i < m2; i++)
		{
			res[ii][i] = 0;
			for (int j = 0; j < n2; j++)
			{
				res[ii][i] += matrix1[ii][j] * matrix2[j][i];
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
	/* for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < m1; j++)
		{
			printf("%f ", (*mat1)[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < n2; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			printf("%f ", (*mat2)[i][j]);
		}
		printf("\n");
	} */
	
}
unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}


int main(void)
{
	unsigned long long tb, te;
    unsigned long long t_mid = 0;

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
	FILE *f1 = fopen("mat.txt","r");
	FILE *f2 = fopen("vect.txt","r");
	input_razr(f1, &A, &JA, &elem_ia, &counter_not_zero1, &n1, &m1);
	input_razr(f2, &B, &JB, &elem_ib, &counter_not_zero2, &n2, &m2);
	fclose(f1);
	fclose(f2);
	
	double **res = allocate_matrix_row(n2, n1);
	tb = tick();
	multiply_razr(A, JA, elem_ia, B, JB, elem_ib, n1, m1, n2, res);
	te = tick();
	printf("t1 = %I64d\n",te - tb);
	
	
	double **mat1;
	double **mat2;
	double **mat_res;
	
	razr_in_full(A, JA, elem_ia, B, JB, elem_ib, n1, m1, n2, &mat1, &mat2);    
	
	tb = tick();
	multiply_matrix(mat2, mat1, n2, n1, n1, m1, &mat_res);
	te = tick();
	printf("t2 = %I64d\n",te - tb);
	
	for (int i = 0; i < n2; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			printf("%f ",res[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
	for (int i = 0; i < n2; i++)
	{
		for (int j = 0; j < n1; j++)
		{
			printf("%f ",mat_res[i][j]);
		}
		printf("\n");
	} 
	//print_razr(stdout, A, JA, elem_ia, counter_not_zero1, n1, m1);
	//printf("\n");
	//print_razr(stdout, B, JB, elem_ib, counter_not_zero2, n2, m2);

	return 0;
}