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
						//printf("# %d\n",(*JA)[*counter_not_zero]);
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
	int k;
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
		//printf("%f\n",elem);
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
	int k1 = 0;
	
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

double multiply(double *A, int *JA, IA *ia, double *B, int *JB, IA *ib, int n, int m)
{
	double res = 0;
	int *IP1 = calloc(n,sizeof(int));
	double *A1;
	int *JA1;
	int counter_not_zero;
	for (int j = 0; j < m; j++)
	{
		get_column(j, n, A, JA, ia, &A1, &JA1,&counter_not_zero);
		for (int i = 0; i < counter_not_zero; i++)
		{
			IP1[JA1[i]] = i+1;		
		}
		for (int i = 0; i < ib->next->Nk; i++)
		{
			if (IP1[JB[i]] != 0)
			{
				res += (A1[IP1[JB[i]]-1]*B[i]);
				IP1[JB[i]] = 0;
			}		
		}
		printf("%f ",res);
		res = 0;
	}
	printf("\n");
	
	/*for (int i = 0; i < n; i++)
	{
		printf("%d ",IP1[i]);
	}
	printf("\n");
	for (int i = 0; i < counter_not_zero; i++)
	{
		printf("%d ",JA1[i]);
	} */
	return 0;	
}
int main(void)
{
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
	
	
	FILE *f1 = fopen("mat.txt","r");
	FILE *f2 = fopen("vect.txt","r");
	input_razr(f1, &A, &JA, &elem_ia, &counter_not_zero1, &n1, &m1);
	input_razr(f2, &B, &JB, &elem_ib, &counter_not_zero2, &n2, &m2);
	fclose(f1);
	fclose(f2);
	multiply(A, JA, elem_ia, B, JB, elem_ib, n1, m1);
	//print_razr(stdout, A, JA, elem_ia, counter_not_zero1, n1, m1);
	//printf("\n");
	//print_razr(stdout, B, JB, elem_ib, counter_not_zero2, n2, m2);
	
	//printf("%f\n",get_element(5, 3, A, JA, elem_ia));
	
	/* for (int i = 0; i < counter_not_zero1; i++)
	{
		printf("%f ",A[i]);
	}
	printf("\n");
	for (int i = 0; i < counter_not_zero1; i++)
	{
		printf("%d ",JA[i]);
	}
	printf("\n");

	while (elem_ib)
	{
		printf("%d ",elem_ib->Nk);
		elem_ib = elem_ib->next;
	} */
	return 0;
}