#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define OK 0
#define QUEUE_OVERFOW -1
#define QUEUE_UNDERFLOW -2
#define MEMORY_ERROR -3

#define MAX_SIZE_STACK 1000
#define MIN_SIZE_STACK 5
#define MULTIPLY 2


typedef struct Time_q {
    double time_come;
    double time_work;
    double time_wait;
} Time_q;

typedef struct Arr_q {
    Time_q *Pin;
    Time_q *Pout;
    Time_q *end;
} Arr_q;

typedef struct List_q {
    Time_q time1;  
    struct List_q *next;
} List_q;

typedef struct Queue_list {
    List_q *Pin;
    List_q *Pout;
} Queue_list;


int push_Queue_arr(Arr_q *arr, double t_work, double t_come)
{
	arr->Pin->time_come = t_come;
	arr->Pin->time_work = t_work;
	arr->Pin += 1;
	if (arr->Pin > arr->end)
		return -1;
	return 0;
}

int pop_Queue_arr(Arr_q *arr)
{
	int len = arr->Pin - arr->Pout;
	for (int i = 1; i <= len; i++)
	{
		*(arr->Pout+i-1) = *(arr->Pout+i);
	}
	arr->Pin -= 1;
	if (arr->Pout >= arr->Pin)
		return -1;
	return 0;
}

int push_Queue_list(Queue_list *list, double t_work, double t_come) 
{
    int err = OK;
    List_q *tmp = malloc(sizeof(List_q));
    if (tmp == NULL) 
        err = MEMORY_ERROR;
    else
    {
		tmp->time1.time_come = t_come;
		tmp->time1.time_work = t_work;
		tmp->next = NULL;
		
		if (list->Pout == NULL)
		{
			list->Pout = tmp;			
		}
		
		if (list->Pin == NULL)
		{
			list->Pin = tmp;			
		}
		else
		{
			list->Pin->next = tmp;
			list->Pin = list->Pin->next;
		}
    }
    return err;
}

int pop_list(Queue_list *list) 
{
	int err = OK;
	if (!list->Pout)
		err = QUEUE_UNDERFLOW;
	else
	{
		List_q *tmp = list->Pout;
		list->Pout = list->Pout->next;
		free(tmp);
	}
    return err;
}


void create_time(double *time_come,double *time_work, double t1, double t2, double t3, double t4)
{
	//t1 + (t2 - t1) * (double)rand() / (double)40
	double tmp;
	tmp = *time_come;
	*time_come = t1 + (t2 - t1) * (double)rand() / (double)RAND_MAX;
	*time_come += tmp;
	*time_work = t3 + (t4 - t3) * (double)rand() / (double)RAND_MAX;
}


double min_d(double n1, double n2)
{
	if (n1 > n2)
		return n2;
	else
		return n1;	
}

int modelling_system_list(Queue_list *queue_1, Queue_list *queue_2)
{
	int counter_loop = 0;
	double time_come1 = 0;
	double time_come2 = 0;
	double time_work1 = 0;
	double time_work2 = 0;

	double real_time = -1;
	double time_prost1 = 0;
	double time_prost2 = 0;
	double time_obrab1 = 0;
	double time_obrab2 = 0;
	int count_applications_enter1 = 0;
	int count_applications_enter2 = 0;
	int count_applications_exit1 = 0;
	int count_applications_exit2 = 0;
	int count_queue1_sr = 0;
	int count_queue1 = 0;
	int count_queue2_sr = 0;
	int count_queue2 = 0;
	
	int sr_time_in_queue1 = 0;
	int sr_time_in_queue2 = 0;
	
	while (counter_loop < 1000)
	{
		if (real_time < 0)
		{
			create_time(&time_come1,&time_work1, 1, 5, 0, 4);	
			time_obrab1 += time_work1;
			push_Queue_list(queue_1, time_work1, time_come1);
			count_queue1++;
			create_time(&time_come2,&time_work2, 0, 3, 0, 1);
			push_Queue_list(queue_2, time_work2, time_come2);
			count_queue2++;
			time_obrab2 += time_work2;
			count_applications_enter1++;
			count_applications_enter2++;
			real_time = 0;
		}
		else
		{ 	
			if (real_time < queue_1->Pout->time1.time_come && real_time < queue_2->Pout->time1.time_come)
			{
				if (queue_1->Pout->time1.time_come > queue_2->Pout->time1.time_come)
				{
					create_time(&time_come2,&time_work2, 0, 3, 0, 1);
			        push_Queue_list(queue_2, time_work2, time_come2);
				
			        time_obrab2 += time_work2;
					count_applications_enter2++;					
					real_time = (queue_2->Pout->time1.time_work + queue_2->Pout->time1.time_come);
					pop_list(queue_2);	
			
					count_applications_exit2++;					
				}
				else
				{
					create_time(&time_come1,&time_work1, 1, 5, 0, 4);
			        push_Queue_list(queue_1, time_work1, time_come1);
					time_obrab1 += time_work1;
					count_applications_enter1++;
					real_time = (queue_1->Pout->time1.time_work + queue_1->Pout->time1.time_come);
					pop_list(queue_1);
					counter_loop++;
					count_queue1_sr += count_queue1;
					count_queue2_sr += count_queue2;
					count_applications_exit1++;
				}
			}
			
			if (real_time < queue_1->Pout->time1.time_come && real_time > queue_2->Pout->time1.time_come)
			{
				sr_time_in_queue2 += (real_time - queue_2->Pout->time1.time_come);
				while (time_come2 <= real_time)
				{
					create_time(&time_come2,&time_work2, 0, 3, 0, 1);
			        push_Queue_list(queue_2, time_work2, time_come2);
					count_queue2++;
					time_obrab2 += time_work2;
					count_applications_enter2++;
				}
					
				if (real_time < (queue_2->Pout->time1.time_work + queue_2->Pout->time1.time_come))
					real_time = (queue_2->Pout->time1.time_work + queue_2->Pout->time1.time_come);
				pop_list(queue_2);
				count_queue2--;				
				count_applications_exit2++;			
			}
			
			if (real_time > queue_1->Pout->time1.time_come && real_time < queue_2->Pout->time1.time_come)
			{
				sr_time_in_queue1 += (real_time - queue_1->Pout->time1.time_come);
				while (time_come1 <= real_time)
				{
					create_time(&time_come1,&time_work1, 1, 5, 0, 4);
			        push_Queue_list(queue_1, time_work1, time_come1);
					count_queue1++;	
					time_obrab1 += time_work1;
					count_applications_enter1++;
				}
					
				if (real_time < (queue_1->Pout->time1.time_work + queue_1->Pout->time1.time_come))
					real_time = (queue_1->Pout->time1.time_work + queue_1->Pout->time1.time_come);
				pop_list(queue_1);
				count_queue1--;					
				counter_loop++;
				count_queue1_sr += count_queue1;
				count_queue2_sr += count_queue2;
				count_applications_exit1++;			
			}
			
			if (real_time >= queue_1->Pout->time1.time_come && real_time >= queue_2->Pout->time1.time_come)
			{
				sr_time_in_queue1 += (real_time - queue_1->Pout->time1.time_come);
				sr_time_in_queue2 += (real_time - queue_2->Pout->time1.time_come);
				while (time_come1 <= real_time)
				{
					create_time(&time_come1,&time_work1, 1, 5, 0, 4);
			        push_Queue_list(queue_1, time_work1, time_come1);
					count_queue1++;	
					time_obrab1 += time_work1;
					count_applications_enter1++;
				}
				while (time_come2 <= real_time)
				{
					create_time(&time_come2,&time_work2, 0, 3, 0, 1);
			        push_Queue_list(queue_2, time_work2, time_come2);
					count_queue2++;	
					time_obrab2 += time_work2;
					count_applications_enter2++;
				}
				
				
				if (real_time < (queue_1->Pout->time1.time_work + queue_1->Pout->time1.time_come))
					real_time = (queue_1->Pout->time1.time_work + queue_1->Pout->time1.time_come);
				pop_list(queue_1);	
				count_queue1--;	
				counter_loop++;
				count_queue1_sr += count_queue1;
				count_queue2_sr += count_queue2;
			    count_applications_exit1++;
			}   
			
			
			if (counter_loop % 100 == 0 && counter_loop != 0)
			{
			    printf("%d --------------------------------\n",counter_loop);
				printf("Длина первой очереди = %d\n",count_queue1);
				printf("Длина второй очереди = %d\n",count_queue2);
				printf("Средняя длина первой очереди = %f\n",(float)count_queue1_sr/counter_loop);
				printf("Средняя длина второй очереди = %f\n",(float)count_queue2_sr/counter_loop);
				printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter1, count_applications_exit1);
	            printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter2, count_applications_exit2);
	            printf("Среднее время пребывания в первой очереди = %f\n",(float)sr_time_in_queue1/count_applications_exit1);
	            printf("Среднее время пребывания во второй очереди = %f\n",(float)sr_time_in_queue2/count_applications_exit2);
			}
			
		}
	}
	time_prost1 = time_obrab1 - time_come1;
	time_prost2 = time_obrab2 - time_come2;
	printf("\nВремя моделирования = %f\n",real_time);
	printf("Время простоя первой очереди = %f\n",time_prost1);
	printf("Время простоя второй очереди = %f\n",time_prost2);
	printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter1, count_applications_exit1);
	printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter2, count_applications_exit2);
	printf("Аппарат сработал: %d раз\n",count_applications_enter1 + count_applications_enter2);
	printf("Время работы ОА для первой очереди составило: %f\n",(float)count_applications_enter1*(4/2));
	printf("Время работы ОА для второй очереди составило: %f\n",count_applications_enter2*(0.5));
	double zayav = real_time / ((1+5)/2);
	printf("Погрешность =  %f%%\n",100*(fabs(zayav - count_applications_enter1)/zayav));

	return 0;
} 





 
int modelling_system_arr(Arr_q *queue_1, Arr_q *queue_2)
{
	int counter_loop = 0;
	double time_come1 = 0;
	double time_come2 = 0;
	double time_work1 = 0;
	double time_work2 = 0;

	double real_time = -1;
	double time_prost1 = 0;
	double time_prost2 = 0;
	double time_obrab1 = 0;
	double time_obrab2 = 0;
	int count_applications_enter1 = 0;
	int count_applications_enter2 = 0;
	int count_applications_exit1 = 0;
	int count_applications_exit2 = 0;
	int count_queue1_sr = 0;
	int count_queue1 = 0;
	int count_queue2_sr = 0;
	int count_queue2 = 0;
	
	int sr_time_in_queue1 = 0;
	int sr_time_in_queue2 = 0;
	
	while (counter_loop < 1000)
	{
		if (real_time < 0)
		{
			create_time(&time_come1,&time_work1, 1, 5, 0, 4);	
			time_obrab1 += time_work1;
			push_Queue_arr(queue_1, time_work1, time_come1);
			count_queue1++;
			create_time(&time_come2,&time_work2, 0, 3, 0, 1);
			push_Queue_arr(queue_2, time_work2, time_come2);
			count_queue2++;
			time_obrab2 += time_work2;
			count_applications_enter1++;
			count_applications_enter2++;
			real_time = 0;
		}
		else
		{ 	
			if (real_time < queue_1->Pout->time_come && real_time < queue_2->Pout->time_come)
			{
				if (queue_1->Pout->time_come > queue_2->Pout->time_come)
				{
					create_time(&time_come2,&time_work2, 0, 3, 0, 1);
			        push_Queue_arr(queue_2, time_work2, time_come2);
				
			        time_obrab2 += time_work2;
					count_applications_enter2++;					
					real_time = (queue_2->Pout->time_work + queue_2->Pout->time_come);
					pop_Queue_arr(queue_2);	
			
					count_applications_exit2++;					
				}
				else
				{
					create_time(&time_come1,&time_work1, 1, 5, 0, 4);
			        push_Queue_arr(queue_1, time_work1, time_come1);
					time_obrab1 += time_work1;
					count_applications_enter1++;
					real_time = (queue_1->Pout->time_work + queue_1->Pout->time_come);
					pop_Queue_arr(queue_1);
					counter_loop++;
					count_queue1_sr += count_queue1;
					count_queue2_sr += count_queue2;
					count_applications_exit1++;
				}
			}
			
			if (real_time < queue_1->Pout->time_come && real_time > queue_2->Pout->time_come)
			{
				sr_time_in_queue2 += (real_time - queue_2->Pout->time_come);
				while (time_come2 <= real_time)
				{
					create_time(&time_come2,&time_work2, 0, 3, 0, 1);
			        push_Queue_arr(queue_2, time_work2, time_come2);
					count_queue2++;
					time_obrab2 += time_work2;
					count_applications_enter2++;
				}
					
				if (real_time < (queue_2->Pout->time_work + queue_2->Pout->time_come))
					real_time = (queue_2->Pout->time_work + queue_2->Pout->time_come);
				pop_Queue_arr(queue_2);
				count_queue2--;				
				count_applications_exit2++;			
			}
			
			if (real_time > queue_1->Pout->time_come && real_time < queue_2->Pout->time_come)
			{
				sr_time_in_queue1 += (real_time - queue_1->Pout->time_come);
				while (time_come1 <= real_time)
				{
					create_time(&time_come1,&time_work1, 1, 5, 0, 4);
			        push_Queue_arr(queue_1, time_work1, time_come1);
					count_queue1++;	
					time_obrab1 += time_work1;
					count_applications_enter1++;
				}
					
				if (real_time < (queue_1->Pout->time_work + queue_1->Pout->time_come))
					real_time = (queue_1->Pout->time_work + queue_1->Pout->time_come);
				pop_Queue_arr(queue_1);
				count_queue1--;					
				counter_loop++;
				count_queue1_sr += count_queue1;
				count_queue2_sr += count_queue2;
				count_applications_exit1++;			
			}
			
			if (real_time >= queue_1->Pout->time_come && real_time >= queue_2->Pout->time_come)
			{
				sr_time_in_queue1 += (real_time - queue_1->Pout->time_come);
				sr_time_in_queue2 += (real_time - queue_2->Pout->time_come);
				while (time_come1 <= real_time)
				{
					create_time(&time_come1,&time_work1, 1, 5, 0, 4);
			        push_Queue_arr(queue_1, time_work1, time_come1);
					count_queue1++;	
					time_obrab1 += time_work1;
					count_applications_enter1++;
				}
				while (time_come2 <= real_time)
				{
					create_time(&time_come2,&time_work2, 0, 3, 0, 1);
			        push_Queue_arr(queue_2, time_work2, time_come2);
					count_queue2++;	
					time_obrab2 += time_work2;
					count_applications_enter2++;
				}
				
				
				if (real_time < (queue_1->Pout->time_work + queue_1->Pout->time_come))
					real_time = (queue_1->Pout->time_work + queue_1->Pout->time_come);
				pop_Queue_arr(queue_1);	
				count_queue1--;	
				counter_loop++;
				count_queue1_sr += count_queue1;
				count_queue2_sr += count_queue2;
			    count_applications_exit1++;
			}   
			
			
			if (counter_loop % 100 == 0 && counter_loop != 0)
			{
			    printf("%d --------------------------------\n",counter_loop);
				printf("Длина первой очереди = %d\n",count_queue1);
				printf("Длина второй очереди = %d\n",count_queue2);
				printf("Средняя длина первой очереди = %f\n",(float)count_queue1_sr/counter_loop);
				printf("Средняя длина второй очереди = %f\n",(float)count_queue2_sr/counter_loop);
				printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter1, count_applications_exit1);
	            printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter2, count_applications_exit2);
	            printf("Среднее время пребывания в первой очереди = %f\n",(float)sr_time_in_queue1/count_applications_exit1);
	            printf("Среднее время пребывания во второй очереди = %f\n",(float)sr_time_in_queue2/count_applications_exit2);
			}
			
		}
	}
	time_prost1 = time_obrab1 - time_come1;
	time_prost2 = time_obrab2 - time_come2;
	printf("\nВремя моделирования = %f\n",real_time);
	printf("Время простоя первой очереди = %f\n",time_prost1);
	printf("Время простоя второй очереди = %f\n",time_prost2);
	printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter1, count_applications_exit1);
	printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter2, count_applications_exit2);
	printf("Аппарат сработал: %d раз\n",count_applications_enter1 + count_applications_enter2);
	printf("Время работы ОА для первой очереди составило: %f\n",(float)count_applications_enter1*(4/2));
	printf("Время работы ОА для второй очереди составило: %f\n",count_applications_enter2*(0.5));
	double zayav = real_time / ((1+5)/2);
	printf("Погрешность =  %f%%\n",100*(fabs(zayav - count_applications_enter1)/zayav));

	return 0;
} 

int main(void)        
{
	srand(time(NULL));
	Queue_list q_list_1;
	Queue_list q_list_2;
	Arr_q q_arr_1;
	Arr_q q_arr_2;
	
	q_list_1.Pin = NULL;
	q_list_1.Pout = NULL;
	
	q_list_2.Pin = NULL;
	q_list_2.Pout = NULL;
	
	Time_q q_arr_11[MAX_SIZE_STACK];
	q_arr_1.Pin = q_arr_11;
	q_arr_1.Pout = q_arr_11;
	q_arr_1.end = q_arr_11 + MAX_SIZE_STACK-1;
	
	Time_q q_arr_22[MAX_SIZE_STACK];
	q_arr_2.Pin = q_arr_22;
	q_arr_2.Pout = q_arr_22;
	q_arr_2.end = q_arr_22 + MAX_SIZE_STACK-1;
	
	setbuf(stdout, NULL);
	int choose;
	
	
	/* push_Queue_arr(&q_arr_1, 1, 1);
	push_Queue_arr(&q_arr_1, 1, 2);
	push_Queue_arr(&q_arr_1, 1, 3);
	push_Queue_arr(&q_arr_1, 1, 4);
	pop_Queue_arr(&q_arr_1);
	pop_Queue_arr(&q_arr_1);
	push_Queue_arr(&q_arr_1, 1, 4);
	
	while(q_arr_1.Pout < q_arr_1.Pin)
	{
		printf("%f\n",q_arr_1.Pout->time_come);
		q_arr_1.Pout += 1;
	} */ 
	
	while (1)
	{
		printf("Меню:\n");
		printf("1 - смоделировать очередь списком\n");
		printf("2 - смоделировать очередь массивом\n\n");
		printf("0 - выход\n");
		printf("Введите пункт меню: ");
		scanf("%d",&choose);
		if (choose == 1)
		{
			modelling_system_list(&q_list_1, &q_list_2);
			while (pop_list(&q_list_1) == OK)
			{
			}
			while (pop_list(&q_list_1) == OK)
			{
			}
			q_list_1.Pin = NULL;
			q_list_1.Pout = NULL;
			
			q_list_2.Pin = NULL;
			q_list_2.Pout = NULL;
		}
		else if (choose == 2)
		{
			modelling_system_arr(&q_arr_1, &q_arr_2);
			q_arr_1.Pin = q_arr_11;
			q_arr_1.Pout = q_arr_11;
			q_arr_1.end = q_arr_11 + MAX_SIZE_STACK-1;
			q_arr_2.Pin = q_arr_22;
			q_arr_2.Pout = q_arr_22;
			q_arr_2.end = q_arr_22 + MAX_SIZE_STACK-1;
		}
		else if (choose == 0)
			break;
		else
			printf("Такого пункта меню нет\n");
	}

}
