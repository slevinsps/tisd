#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define INCORRECT_NUMBER -1
#define INVALID_DEL_ARGUMENT -2

typedef struct Car {
    char mark[30];
    char country[30];
    char price[30];
    char color[30];
    char state[30];
    char mileage[30];
    char repairs[30];
} Car;

typedef struct Car_table{
    int number;
    char price[30];
} Car_table;

void new_struct_table(Car *cars,Car_table **cars_tabl,int *size)
{
	Car_table *cars_tabl2 = (Car_table*)malloc((*size)*sizeof(Car_table));
	for (int j = 0;j<*size;j++)
	{
		cars_tabl2[j].number = j;
		for (int i = 0; i < 30;i++)
		{
			cars_tabl2[j].price[i] = cars[j].price[i];		
		}
	}
	*cars_tabl = cars_tabl2;
}

void read_struct(FILE *f, Car *cars,Car_table *cars_tabl,int size)
{
	//int err = OK;
	for (int i = 0;i<size;i++)
	{	
		fscanf(f,"%s %s %s %s %s %s %s", cars[i].mark,cars[i].country,cars[i].price,cars[i].color,cars[i].state,cars[i].mileage,cars[i].repairs);
		cars_tabl[i].number = i;
		for (int j = 0;j<30;j++)
		{
			cars_tabl[i].price[j] = cars[i].price[j];		
		}			
	}	
} 

void rewrite_file(FILE *f, Car *cars,int size)
{
	//int err = OK;
	fprintf(f,"%d\n",size);
	for (int i = 0;i<size;i++)
	{
		fprintf(f,"%s %s %s %s %s %s %s\n",cars[i].mark,cars[i].country,cars[i].price,cars[i].color,cars[i].state,cars[i].mileage,cars[i].repairs);
	}	
} 


void print_struct(FILE *f, Car *cars,int size)
{
	//int err = OK;
	printf("№     Марка     Страна        Цена       Цвет   Состояние      П-г      Ремонты\n");
	for (int i = 0;i<size;i++)
	{
		fprintf(f,"%d %10s %10s %10s %10s %10s %10s %8s\n",i+1,cars[i].mark,cars[i].country,cars[i].price,cars[i].color,cars[i].state,cars[i].mileage,cars[i].repairs);
	}	
} 


void print_struct_table(FILE *f, Car_table *cars_tabl,int size)
{
	//int err = OK;
	//printf("№     Марка     Страна        Цена       Цвет   Состояние      П-г      Ремонты\n");
	for (int i = 0;i<size;i++)
	{
		fprintf(f,"%d %10s\n",cars_tabl[i].number,cars_tabl[i].price);
	}	
} 

void add_record(Car **cars,int *size)
{
	Car *cars2;
	*size += 1;
	cars2 = (Car*)malloc((*size)*sizeof(Car));
	
	for (int i=0;i<*size-1;i++)
	{
		cars2[i] = (*cars)[i];
	}
	int i = *size-1;
	scanf("%s %s %s %s %s %s %s", cars2[i].mark,cars2[i].country,cars2[i].price,cars2[i].color,cars2[i].state,cars2[i].mileage,cars2[i].repairs);

	*cars = cars2;
}

int del_record(Car **cars,int *size)
{
	Car *cars2;
	int number;
	int err = OK;
	if (scanf("%d",&number) == 1 && number<=*size && number>0)
	{
		*size -= 1;
		cars2 = (Car*)malloc((*size)*sizeof(Car));
		int k = 0;
		for (int i=0;i<*size+1;i++)
		{
			if (i+1!=number)
			{
				cars2[k] = (*cars)[i];
				k++;
			}
		}		
		*cars = cars2;
	}
	else
	{
		err = INVALID_DEL_ARGUMENT;
	}
	return err;
}

void replace_array(char *s1,char *s2,int size)
{
	char tmp[size];
	for (int i = 0;i < size; i++)
	{
		tmp[i] = s1[i];
	}
	for (int i = 0;i < size; i++)
	{
		s1[i] = s2[i];
	}
	for (int i = 0;i < size; i++)
	{
		s2[i] = tmp[i];
	}
	
}

void bubble_sort_all(Car *cars,int size)
{
	int k1,k2;
	for (int i = 0;i<size-1;i++)
	{
		for (int j = i;j<size;j++)
		{
			k1 = atoi(cars[i].price);
			k2 = atoi(cars[j].price);
			if (k1>k2)
			{		
				replace_array(cars[i].mark,cars[j].mark,30);
				replace_array(cars[i].country,cars[j].country,30);
				replace_array(cars[i].price,cars[j].price,30);
				replace_array(cars[i].color,cars[j].color,30);
				replace_array(cars[i].state,cars[j].state,30);
				replace_array(cars[i].mileage,cars[j].mileage,30);
				replace_array(cars[i].repairs,cars[j].repairs,30);			
			}
		}
	}
}


void bubble_sort_key(Car_table *cars_tabl,int size)
{
	int k1,k2;
	int tmp;
	for (int i = 0;i<size-1;i++)
	{
		for (int j = i;j<size;j++)
		{
			k1 = atoi(cars_tabl[i].price);
			k2 = atoi(cars_tabl[j].price);
			if (k1>k2)
			{		
				replace_array(cars_tabl[i].price,cars_tabl[j].price,30);
				tmp = cars_tabl[i].number;
				cars_tabl[i].number = cars_tabl[j].number;
				cars_tabl[j].number = tmp;
			}
		}
	}
}



int menu(Car **cars,Car_table **cars_tabl,int *size)
{
	FILE *f1;
	int choice;
	int err = OK;
	printf("МЕНЮ\n");
	printf("1 - Показать список\n");
	printf("2 - Добавить запись\n");
	printf("3 - Удалить запись\n");
	printf("4 - Отсортировать исходную таблцу по цене\n");
	printf("5 - Отсортировать таблцу по цене используя таблицу ключей\n");
	printf("6 - Записать изменения в файл\n\n");
	
	printf("0 - Выйти\n");
	printf("Выбор: ");
	scanf("%d",&choice);
	if (choice == 1)
	{
		printf("Список:\n");
		print_struct(stdout, *cars, *size);	
	}
	if (choice == 2)
	{
		printf("Введите запись:\n");
		add_record(cars, size);
		printf("Запись добавлена!\n");
		new_struct_table(*cars,cars_tabl,size);
		
	}
	if (choice == 3)
	{
		print_struct(stdout, *cars, *size);
		printf("Введите номер машины:\n");
		err = del_record(cars, size);
		if (err == INVALID_DEL_ARGUMENT)
		{
			printf("Введен неверный аргумент\n");
		}
		else
		{
			printf("Запись удалена!\n");
		}
		new_struct_table(*cars,cars_tabl,size);
	}
	
	if (choice == 4)
	{
		bubble_sort_all(*cars,*size);
		print_struct(stdout, *cars, *size);
		new_struct_table(*cars,cars_tabl,size);
	}
	if (choice == 5)
	{
		bubble_sort_key(*cars_tabl,*size);
		for (int j = 0;j<*size;j++)
		{
			int i = (*cars_tabl)[j].number;
			printf("%d %10s %10s %10s %10s %10s %10s %8s\n",i+1,(*cars)[i].mark,(*cars)[i].country,(*cars)[i].price,(*cars)[i].color,(*cars)[i].state,(*cars)[i].mileage,(*cars)[i].repairs);
		}
	}
	
	if (choice == 6)
	{
		f1 = fopen("table.txt","w");
		rewrite_file(f1, *cars, *size);
		fclose(f1);
		printf("Файл перезаписан!\n");
	}
	if (choice == 0)
	{
		return 0;
	}
	return 1;
}


int main(void)
{
	int exit = 1;
	FILE *f1;
	int size;
	Car *cars;
	Car_table *cars_tabl;
	setbuf(stdout,NULL);
	f1 = fopen("table.txt","r");
	if (fscanf(f1,"%d",&size) == 1)
	{		
		cars = (Car*)malloc(size*sizeof(Car));
		cars_tabl = (Car_table*)malloc(size*sizeof(Car_table));
		read_struct(f1, cars, cars_tabl, size);
		fclose(f1);
		while(exit)
		{
			exit = menu(&cars,&cars_tabl,&size);
		}
	}
	else
	{
		printf("Error");
	}
	return 0;
}
