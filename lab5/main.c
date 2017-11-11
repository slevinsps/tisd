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
	struct IA *next;
} IA;


int input_razr(FILE *f, double **A, int **JA, IA **ia,int *counter_not_zero, int *n, int *m)
{
	double elem;
	*counter_not_zero = 0;
	int counter_all = 0;
	int bool1;
	int Nk;
	IA *begin = NULL;
    if (fscanf(f,"%d %d",n,m) == 2)
    {
		
        *A = malloc(100);
		if (!*A)
            return MEMORY_ERROR;
        *JA = malloc(100);
		if (!*JA)
            return MEMORY_ERROR;
        
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
			tmp->Nk = Nk;
			tmp->next = NULL;
			if (!(*ia))
			{
				(*ia) = tmp;
			}
			else
			{
				(*ia)->next = tmp;
				if (!begin)
					begin = (*ia);
				(*ia) = tmp;
			}
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

int print_razr(FILE *f, double *A, int *JA, IA *ia,int counter_not_zero, int n, int m)
{
	int k1 = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (ia->Nk == -1)
				fprintf(f,"%f ",0.0);
			else
			{
				if (j == JA[k1])
				{
					fprintf(f,"%f ",A[k1]);
					k1++;
				}
				else
					fprintf(f,"%f ",0.0);
			}
		}
		fprintf(f,"\n");
		ia = ia->next;
	}
return 0;
}
int main(void)
{
	double *A = NULL;
	int *JA = NULL;
	IA *elem_ia = NULL;
	int counter_not_zero;
	int n,m;
	FILE *f = fopen("mat.txt","r");
	input_razr(f, &A, &JA, &elem_ia, &counter_not_zero, &n, &m);
	fclose(f);
	/* printf("%f\n",A[0]);
	printf("%f\n",A[1]);
	printf("%f\n",A[2]);
	printf("%f\n",A[3]);
	printf("%f\n",A[4]);
	printf("%f\n",A[5]);
	printf("%d\n",counter_not_zero); */
	print_razr(stdout, A, JA, elem_ia, counter_not_zero, n, m);
	/* for (int i = 0; i < counter_not_zero; i++)
	{
		printf("%f ",A[i]);
	}
	printf("\n");
	for (int i = 0; i < counter_not_zero; i++)
	{
		printf("%d ",JA[i]);
	}
	printf("\n");
	while (elem_ia)
	{
		printf("%d ",elem_ia->Nk);
		elem_ia = elem_ia->next;
	} */
	return 0;
}