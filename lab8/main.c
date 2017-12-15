# include <stdio.h>
# include <stdlib.h>

void free_matrix_rows(int **data, int n)
{
    for (int i = 0;i < n; i++)
    {
        free((data)[i]);        
    }
    free(data);    
}
  
// Выделение памяти  
int **allocate_matrix_row(int n, int m)
{
    int **data = (int**)calloc(n, sizeof(int*));
    if (!data)
        return NULL;
    for (int i = 0; i < n; i++)
    {
        data[i] = (int*)calloc(m, sizeof(int));
        if (!data[i])
        {
            free_matrix_rows(data, n);
            return NULL;
        } 
    }
    return data;
}


int load_matrix(FILE *f, int **matrix, int n)
{
	int var;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (fscanf(f, "%d", &var) != 1)
				return -1;
			if ((i == j && var != 0) || (i != j && var == 0))
				return -1;
			if (var < -1)
				return -1;
			matrix[i][j] = var;
		}
	}
	return 0;
}

void printf_matrix(FILE *f, int **matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fprintf(f, "%d ", matrix[i][j]);
		}
		fprintf(f, "\n");
	}	
}

int min_my(int a, int b)
{
	return a < b && a != -1?a:b;
}

void floid_uorshel_max(int **matrix, int n)
{
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (matrix[i][k] >= 0 && matrix[k][j] >= 0)
					matrix[i][j] = min_my(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
		}
	}
}

void print_dot_graf(int **matrix, int n)
{
	FILE *f = fopen("graf.dot","w");
	fprintf(f, "digraph test_tree_avl {\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] > 0)
			{
				fprintf(f, "%d -> %d[label=""%d"";];\n", i+1, j+1, matrix[i][j]);
			}
		}
	}
	fprintf(f, "}\n");
}

void print_res(int **matrix, int n)
{
	printf("Самые короткие пути между всеми парами городов:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] > 0)
			{
				printf("%d -> %d = %d\n", i+1, j+1, matrix[i][j]);
			}
		}
	}
}

int read_matrix(int **matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j)
				matrix[i][j] = -1;
		}
	}
	printf("Вводите данные в следующем формате через пробел(с единицы):\n");	
	printf("первый город _ второй город _ длина пути\n");	
	printf("например: 1 5 4\n");
	printf("таким образом заполните только города, между которыми есть дороги\n");
	printf("чтобы закончить введите с новой строки: -1\n");
	int i = 0, j = 0, len = 0;
	while (1)
	{
		if (scanf("%d",&i) != 1 || i < -1 || i > n)	
			return -1;
		if (i == -1)
			break;
		if (scanf("%d %d",&j, &len) != 2  || j < 0 || j > n  || len < 1)	
			return -1;
		if (i == j)
			return -1;
		matrix[i-1][j-1] = len;
	}
	return 0;
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}


int main(void)
{
	unsigned long long t1, t2;
	
	FILE *f = fopen("in.txt", "r");
	if (!f)
	{
		printf("Такого файла нет\n");
		return -1;
	}
	printf("Для каждой пары городов найти длину кратчайшего пути между ними\n");
	int n;
	int **matrix;
	int ch = 0;
	setbuf(stdout,NULL); 
	while (1)
	{
		printf("Меню\n");
		printf("1 - ввести граф вручную\n");
		printf("2 - загрузить матрицу смежности из файла\n\n");
		printf("0 - выйти\n");
		printf("Ваш выбор: \n");
		if (scanf("%d", &ch) != 1 || ch > 2 || ch < 0)
		{
			printf("Неверный пункт меню\n");
			fflush(stdin);
			
		}
		else
		{
			if (ch == 0)
				return -1;
			break;
		}
			
		
	}
	if (ch == 1)
	{
		printf("Введите количество городов: ");
		if (scanf("%d", &n) != 1 || n < 1)
		{
			printf("Некорректное количество городов\n");
			return -1;
		}	
		matrix = allocate_matrix_row(n, n);
		if (!matrix)
		{
			printf("Memory error\n");
			return -1;
		}
		int err = read_matrix(matrix, n);
		if (err == -1)
		{
			printf("Некорректные данные\n");
			return -1;
		}	
	}
	else
	{
		if (fscanf(f, "%d", &n) != 1 || n < 1)
		{
			printf("Некорректное количество городов\n");
			return -1;
		}
		matrix = allocate_matrix_row(n, n);
		if (!matrix)
		{
			printf("Memory error\n");
			return -1;
		}
		int err = load_matrix(f, matrix, n);
		if (err == -1)
		{
			printf("Некорректные данные\n");
			return -1;
		}
	}
	printf("Матрица смежности взвешенного графа:\n");
	printf_matrix(stdout, matrix, n);
	print_dot_graf(matrix, n);
	
	t1 = tick();
	floid_uorshel_max(matrix, n);
	t2 = tick();
	
	printf("\n");	
	print_res(matrix, n);
	
	printf("Время выполнения алгоритма Флойда — Уоршелла = %I64d\n", t2-t1);
	printf("\nИсходный граф записан в файле graf.dot\n");
	
}
