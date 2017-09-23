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


void read_struct(FILE *f, Car *cars,int size)
{
	//int err = OK;
	for (int i = 0;i<size;i++)
	{	
		fscanf(f,"%s %s %s %s %s %s %s", cars[i].mark,cars[i].country,cars[i].price,cars[i].color,cars[i].state,cars[i].mileage,cars[i].repairs);
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


/* typedef struct Car {
    char mark[30];
    char country[30];
    char price[30];
    char color[30];
    char state[30];
    char mileage[30];
    char repairs[30];
} Car; */


void bubble_sort(Car **cars,int size)
{
	int k1,k2;
	char tmp[30];
	for (int i = 0;i<size-1;i++)
	{
		for (int j = i;j<size;j++)
		{
			//printf("%s    %s\n",(*cars)[i].price,(*cars)[j].price);
			k1 = atoi((*cars)[i].price);
			k2 = atoi((*cars)[j].price);
			if (k1>k2)
			{		
				
				replace_array((*cars)[i].mark,(*cars)[j].mark,30);
				replace_array((*cars)[i].country,(*cars)[j].country,30);
				replace_array((*cars)[i].price,(*cars)[j].price,30);
				replace_array((*cars)[i].color,(*cars)[j].color,30);
				replace_array((*cars)[i].state,(*cars)[j].state,30);
				replace_array((*cars)[i].mileage,(*cars)[j].mileage,30);
				replace_array((*cars)[i].repairs,(*cars)[j].repairs,30);			
			}
		}
	}
	print_struct(stdout, *cars, size);
}




int menu(Car **cars,int *size)
{
	FILE *f1;
	int choice;
	int err = OK;
	printf("МЕНЮ\n");
	printf("1 - Показать список\n");
	printf("2 - Добавить запись\n");
	printf("3 - Удалить запись\n");
	printf("4 - Отсортировать\n");
	printf("5 - Записать изменения в файл\n\n");
	
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
		add_record(cars,size);
		printf("Запись добавлена!\n");
	}
	if (choice == 3)
	{
		print_struct(stdout, *cars, *size);
		printf("Введите номер машины:\n");
		err = del_record(cars,size);
		if (err == INVALID_DEL_ARGUMENT)
		{
			printf("Введен неверный аргумент\n");
		}
		else
		{
			printf("Запись удалена!\n");
		}
	}
	
	if (choice == 4)
	{
		bubble_sort(cars,*size);
	}
	
	
	if (choice == 5)
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
	setbuf(stdout,NULL);
	f1 = fopen("table.txt","r");
	if (fscanf(f1,"%d",&size) == 1)
	{		
		cars = (Car*)malloc(size*sizeof(Car));
		read_struct(f1, cars, size);
		fclose(f1);
		while(exit)
		{
			exit = menu(&cars, &size);
		}
	}
	else
	{
		printf("Error");
	}
	return 0;
}
