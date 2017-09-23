#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define INCORRECT_NUMBER -1
#define INVALID_DEL_ARGUMENT -2
#define SIZE 30

typedef struct Car {
    char mark[SIZE];
    char country[SIZE];
    int price;
    char color[SIZE];
	int used;
	union {
		struct {
			int warranty;
		} new_car;

		struct {
			int year;
			int mileage;
			int repairs;
		} used_car;
	} united;
} Car;


typedef struct Car_table{
    int number;
    int price;
} Car_table;

void new_struct_table(Car *cars,Car_table **cars_tabl,int *size)
{
	Car_table *cars_tabl2 = (Car_table*)malloc((*size)*sizeof(Car_table));
	for (int j = 0;j<*size;j++)
	{
		cars_tabl2[j].number = j;		
		cars_tabl2[j].price = cars[j].price;		
	}
	*cars_tabl = cars_tabl2;
}

int read_struct(FILE *f, Car *cars,int size)
{
	for (int i = 0;i<size;i++)
	{	
		if (fscanf(f,"%s", cars[i].mark)!=1)
		{
			printf("Некорректно введена марка\n");
			return -1;
		}
		if (fscanf(f,"%s", cars[i].country)!=1)
		{
			printf("Некорректно введена страна\n");
			return -1;
		}
		if (fscanf(f,"%d", &cars[i].price)!=1)
		{
			printf("Некорректно введена цена\n");
			return -1;
		}
		if (fscanf(f,"%s", cars[i].color)!=1)
		{
			printf("Некорректно введен цвет\n");
			return -1;
		}
		if (fscanf(f,"%d", &cars[i].used)!=1)
		{
			printf("Некорректно введено состояние\n");
			return -1;
		}
		if (cars[i].used == 1)
		{
			
			
			if (fscanf(f,"%d", &cars[i].united.used_car.year)!=1)
			{
				printf("Некорректно введен год\n");
				return -1;
			}
			if (fscanf(f,"%d", &cars[i].united.used_car.mileage)!=1)
			{
				printf("Некорректно введен пробег\n");
				return -1;
			}
			if (fscanf(f,"%d", &cars[i].united.used_car.repairs)!=1)
			{
				printf("Некорректно введено количество ремонтов\n");
				return -1;
			}
		}
		else
		{
			if (fscanf(f,"%d", &cars[i].united.new_car.warranty)!=1)
			{
				printf("Некорректно введена гарантия\n");
				return -1;
			}
		}		 
	}
	fclose(f);
	return OK;
} 

void rewrite_file(FILE *f, Car *cars,int size)
{
	//int err = OK;
	fprintf(f,"%d\n",size);
	for (int i = 0;i<size;i++)
	{
		fprintf(f,"%s %s %d %s %d ",cars[i].mark,cars[i].country,cars[i].price,cars[i].color,cars[i].used);
		if (cars[i].used == 1)
			fprintf(f,"%d %d %d\n",cars[i].united.used_car.year,cars[i].united.used_car.mileage,cars[i].united.used_car.repairs);
		else
			fprintf(f,"%d\n",cars[i].united.new_car.warranty);
	}	
} 

void print_struct(FILE *f, Car *cars,int size)
{
	//int err = OK;
	printf("№     Марка           Страна        Цена       Цвет     Состояние      Год/      Пробег    Ремонты\n");
	printf("                                                                     Гарантия\n");
	for (int i = 0;i<size;i++)
	{
		fprintf(f,"%d %15s %10s %12d %10s %10d ",i+1,cars[i].mark,cars[i].country,cars[i].price,cars[i].color,cars[i].used);
		if (cars[i].used == 1)
			fprintf(f,"%10d %10d %10d\n",cars[i].united.used_car.year,cars[i].united.used_car.mileage,cars[i].united.used_car.repairs);
		else
			fprintf(f,"%10d\n",cars[i].united.new_car.warranty);
	}		
} 

void print_struct_with_key(FILE *f, Car *cars,Car_table *cars_tabl,int size)
{
	int i;
	for (int j = 0;j<size;j++)
	{
		i = cars_tabl[j].number;
		fprintf(f,"%d %15s %10s %12d %10s %10d ",i+1,cars[i].mark,cars[i].country,cars[i].price,cars[i].color,cars[i].used);
		if (cars[i].used == 1)
			fprintf(f,"%10d %10d %10d\n",cars[i].united.used_car.year,cars[i].united.used_car.mileage,cars[i].united.used_car.repairs);
		else
			fprintf(f,"%10d\n",cars[i].united.new_car.warranty);
	}
	
}

int add_record(Car **cars,int *size)
{
	printf("Марка | Страна | Цена |  Цвет | Состояние |   Год/     | Пробег | Ремонты\n");
	printf("                                            Гарантия\n");
	Car *cars2;
	//*size += 1;
	cars2 = (Car*)malloc((*size+1)*sizeof(Car));
	
	for (int i=0;i<*size;i++)
	{
		cars2[i] = (*cars)[i];
	}
	int i = *size;
	
	if (scanf("%s", cars2[i].mark)!=1)
	{
		printf("Некорректно введена марка\n");
		return -1;
	}
	if (scanf("%s", cars2[i].country)!=1)
	{
		printf("Некорректно введена страна\n");
		return -1;
	}
	if (scanf("%d", &cars2[i].price)!=1)
	{
		printf("Некорректно введена цена\n");
		return -1;
	}
	if (scanf("%s", cars2[i].color)!=1)
	{
		printf("Некорректно введен цве\n");
		return -1;
	}
	if (scanf("%d", &cars2[i].used)!=1)
	{
		printf("Некорректно введено состояние\n");
		return -1;
	}
	if (cars2[i].used == 1)
	{
		if (scanf("%d", &cars2[i].united.used_car.year)!=1)
		{
			printf("Некорректно введен год\n");
			return -1;
		}
		if (scanf("%d", &cars2[i].united.used_car.mileage)!=1)
		{
			printf("Некорректно введен пробег\n");
			return -1;
		}
		if (scanf("%d", &cars2[i].united.used_car.repairs)!=1)
		{
			printf("Некорректно введено количество ремонтов\n");
			return -1;
		}
	}
	else
	{
		if (scanf("%d", &cars2[i].united.new_car.warranty)!=1)
		{
			printf("Некорректно введена гарантия\n");
			return -1;
		}
	}
	*size += 1;
	*cars = cars2;
	return OK;
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
	int tmp;
	for (int i = 0;i<size-1;i++)
	{
		for (int j = i;j<size;j++)
		{
			if (cars[i].price>cars[j].price)
			{		
				replace_array(cars[i].mark,cars[j].mark,SIZE);
				replace_array(cars[i].country,cars[j].country,SIZE);
	
				tmp = cars[i].price;
				cars[i].price = cars[j].price;
				cars[j].price = tmp;
				replace_array(cars[i].color,cars[j].color,30);
				tmp = cars[i].used;
				cars[i].used = cars[j].used;
				cars[j].used = tmp;
				if (cars[i].used == 1)
				{
					tmp = cars[i].united.used_car.year;
					cars[i].united.used_car.year = cars[j].united.used_car.year;
					cars[j].united.used_car.year = tmp;

					tmp = cars[i].united.used_car.mileage;
					cars[i].united.used_car.mileage = cars[j].united.used_car.mileage;
					cars[j].united.used_car.mileage = tmp;
					
					tmp = cars[i].united.used_car.repairs;
					cars[i].united.used_car.repairs = cars[j].united.used_car.repairs;
					cars[j].united.used_car.repairs = tmp;
				}
				else
				{
					tmp = cars[i].united.new_car.warranty;
					cars[i].united.new_car.warranty = cars[j].united.new_car.warranty;
					cars[j].united.new_car.warranty = tmp;
					
				}	
				if (cars[j].used == 1)
				{
					tmp = cars[i].united.used_car.year;
					cars[i].united.used_car.year = cars[j].united.used_car.year;
					cars[j].united.used_car.year = tmp;
	
					tmp = cars[i].united.used_car.mileage;
					cars[i].united.used_car.mileage = cars[j].united.used_car.mileage;
					cars[j].united.used_car.mileage = tmp;
					
					tmp = cars[i].united.used_car.repairs;
					cars[i].united.used_car.repairs = cars[j].united.used_car.repairs;
					cars[j].united.used_car.repairs = tmp;
				}
				else
				{
					tmp = cars[i].united.new_car.warranty;
					cars[i].united.new_car.warranty = cars[j].united.new_car.warranty;
					cars[j].united.new_car.warranty = tmp;
				
				}
			}
		}
	}
}


void bubble_sort_key(Car_table *cars_tabl,int size)
{
	int tmp;
	for (int i = 0;i<size-1;i++)
	{
		for (int j = i;j<size;j++)
		{
			if (cars_tabl[i].price>cars_tabl[j].price)
			{		
				tmp = cars_tabl[i].price;
				cars_tabl[i].price = cars_tabl[j].price;
				cars_tabl[j].price = tmp;
				
				tmp = cars_tabl[i].number;
				cars_tabl[i].number = cars_tabl[j].number;
				cars_tabl[j].number = tmp;
			}
		}
	}
}

void quicksort_all(Car *cars,int l,int r)
{
	int tmp;
	int i = l;
	int j = r;
	int x = cars[(l+r)/2].price;
	while(1)
	{
		while(cars[i].price<x)
			i++;
		while(cars[j].price>x)
			j--;
		if (i<=j)
		{
			replace_array(cars[i].mark,cars[j].mark,SIZE);
			replace_array(cars[i].country,cars[j].country,SIZE);
	
			tmp = cars[i].price;
			cars[i].price = cars[j].price;
			cars[j].price = tmp;
			replace_array(cars[i].color,cars[j].color,30);
			tmp = cars[i].used;
			cars[i].used = cars[j].used;
			cars[j].used = tmp;
			if (cars[i].used == 1)
			{
				tmp = cars[i].united.used_car.year;
				cars[i].united.used_car.year = cars[j].united.used_car.year;
				cars[j].united.used_car.year = tmp;

				tmp = cars[i].united.used_car.mileage;
				cars[i].united.used_car.mileage = cars[j].united.used_car.mileage;
				cars[j].united.used_car.mileage = tmp;
				
				tmp = cars[i].united.used_car.repairs;
				cars[i].united.used_car.repairs = cars[j].united.used_car.repairs;
				cars[j].united.used_car.repairs = tmp;
			}
			else
			{
				tmp = cars[i].united.new_car.warranty;
				cars[i].united.new_car.warranty = cars[j].united.new_car.warranty;
				cars[j].united.new_car.warranty = tmp;
				
			}
			if (cars[j].used == 1)
			{
				tmp = cars[i].united.used_car.year;
				cars[i].united.used_car.year = cars[j].united.used_car.year;
				cars[j].united.used_car.year = tmp;

				tmp = cars[i].united.used_car.mileage;
				cars[i].united.used_car.mileage = cars[j].united.used_car.mileage;
				cars[j].united.used_car.mileage = tmp;
				
				tmp = cars[i].united.used_car.repairs;
				cars[i].united.used_car.repairs = cars[j].united.used_car.repairs;
				cars[j].united.used_car.repairs = tmp;
			}
			else
			{
				tmp = cars[i].united.new_car.warranty;
				cars[i].united.new_car.warranty = cars[j].united.new_car.warranty;
				cars[j].united.new_car.warranty = tmp;
				
			}
			
			i++;
			j--;
		}
		if (i>j)
			break;
	}
	if (l<j)
        quicksort_all(cars,l,j);
    if (r>i)
        quicksort_all(cars,i,r);
}

void quicksort_key(Car_table *cars_tabl,int l,int r)
{
	int tmp;
	int i = l;
	int j = r;
	int x = cars_tabl[(l+r)/2].price;
	while(1)
	{
		while(cars_tabl[i].price<x)
			i++;
		while(cars_tabl[j].price>x)
			j--;
		if (i<=j)
		{
			tmp = cars_tabl[i].price;
			cars_tabl[i].price = cars_tabl[j].price;
			cars_tabl[j].price = tmp;
			
			tmp = cars_tabl[i].number;
			cars_tabl[i].number = cars_tabl[j].number;
			cars_tabl[j].number = tmp;
			i++;
			j--;
		}
		if (i>j)
			break;
	}
	if (l<j)
        quicksort_key(cars_tabl,l,j);
    if (r>i)
        quicksort_key(cars_tabl,i,r);
}


int menu(Car **cars,Car_table **cars_tabl,int *size)
{
	FILE *f1;
	int choice;
	int err = OK;
	printf("\n----------------------------------------------------------------------------------------------\n");
	printf("МЕНЮ\n");
	printf("1 - Показать список\n");
	printf("2 - Добавить запись\n");
	printf("3 - Удалить запись\n");
	printf("4 - Отсортировать пузырьком исходную таблцу по цене обычным способом\n");
	printf("5 - Отсортировать пузырьком таблцу по цене используя таблицу ключей\n");
	printf("6 - Отсортировать быстрой сортировкой таблцу по цене обычным способом\n");
	printf("7 - Отсортировать быстрой сортировкой  таблцу по цене используя таблицу ключей\n");
	printf("8 - Записать изменения в файл\n");
	printf("9 - Вернуть исходый файл\n\n");
	printf("10 - Вывести таблицу в соответствии с фильтром\n\n");
	
	
	printf("0 - Выйти\n");
	printf("Выбор: ");
	scanf("%d",&choice);
	new_struct_table(*cars,cars_tabl,size);
	if (choice == 1)
	{
		printf("Список:\n");
		print_struct(stdout, *cars, *size);	
	}
	if (choice == 2)
	{
		
		err = add_record(cars, size);
		if (err == OK)
		{
			printf("Запись добавлена!\n");
			new_struct_table(*cars,cars_tabl,size);	
		}
		else
		{
			fflush(stdin);
		}
	}
	if (choice == 3)
	{
		print_struct(stdout, *cars, *size);
		printf("Введите номер машины:\n");
		err = del_record(cars, size);
		if (err == INVALID_DEL_ARGUMENT)
		{
			fflush(stdin);
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
		print_struct_with_key(stdout,*cars,*cars_tabl,*size);
		new_struct_table(*cars,cars_tabl,size);
	}
	if (choice == 6)
	{
		quicksort_all(*cars,0,*size-1);
		print_struct(stdout, *cars, *size);
		new_struct_table(*cars,cars_tabl,size);
	}
	if (choice == 7)
	{
		quicksort_key(*cars_tabl,0,*size-1);
		print_struct_with_key(stdout,*cars,*cars_tabl,*size);
		new_struct_table(*cars,cars_tabl,size);
	}
	
	
	if (choice == 8)
	{
		f1 = fopen("table.txt","w");
		rewrite_file(f1, *cars, *size);
		fclose(f1);
		printf("Файл перезаписан!\n");
	}
	if (choice == 9)
	{
		f1 = fopen("table.txt","r");
		fscanf(f1,"%d",size);
		err = read_struct(f1, *cars, *size);
		if (err == OK)
		{
			print_struct(stdout, *cars, *size);
			new_struct_table(*cars,cars_tabl,size);
			printf("Исходный массив возращен!\n");
		}
		else
		{
			fflush(stdin);
		}
		fclose(f1);	
	}
	
	if (choice == 10)
	{
		for (int i = 0;i<size;i++)
		{
			fprintf(f,"%d %15s %10s %12d %10s %10d ",i+1,cars[i].mark,cars[i].country,cars[i].price,cars[i].color,cars[i].used);
			if (cars[i].used == 1)
				fprintf(f,"%10d %10d %10d\n",cars[i].united.used_car.year,cars[i].united.used_car.mileage,cars[i].united.used_car.repairs);
			else
				fprintf(f,"%10d\n",cars[i].united.new_car.warranty);
		}	
	}
	
	
	if (choice == 0)
	{
		return 0;
	}
	return 1;
}


int main(void)
{
	int err = OK;
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
		err = read_struct(f1, cars, size);
		if (err == OK)
		{
			print_struct(stdout, cars, size);
			fclose(f1);
			while(exit)
			{
				exit = menu(&cars,&cars_tabl,&size);
			}
		}

		free(cars);
		free(cars_tabl); 
	}
	else
	{
		printf("Error");
	}
	return 0;
}
