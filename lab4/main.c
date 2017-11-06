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

#define MAX_SIZE_QUEUE 1000
#define MIN_SIZE_QUEUE 5
#define MULTIPLY 2


typedef struct Time_q {
    double time_come;
    double time_work;
} Time_q;

typedef struct Arr_q {
    Time_q *Pin;
    Time_q *Pout;
    Time_q *end;
    int size;
} Arr_q;

typedef struct List_q {
    Time_q time1;  
    struct List_q *next;
} List_q;        

typedef struct Queue_list {
    List_q *Pin;
    List_q *Pout;
    int size;
} Queue_list;

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

int push_Queue_arr(Arr_q *arr, double t_work, double t_come)
{
    arr->Pin->time_come = t_come;
    arr->Pin->time_work = t_work;
    arr->Pin += 1;
	arr->size += 1;
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
		list->size += 1;
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


int filling_empty_area(List_q ***empty_area, Queue_list *head, int *k, int *size)
{
    int err = OK;
    if (*k >= *size)
    {
        *empty_area = realloc(*empty_area, *size * 2 * sizeof(List_q *));    
        *size *= MULTIPLY;
    }
    if (*empty_area)
    {
        (*empty_area)[*k] = head->Pout;
        (*k)++;
    }
    else
    {
        err = MEMORY_ERROR;
    }

    return err; 
}

void delete_empty_area(List_q ***empty_area, Queue_list *head, int *k, int *h)
{
    int n = -1;
    for (int i = 0;i < *k; i++)
    {
        if ((*empty_area)[i] == head->Pin)
        {
            n = i;
            break;
        }
    }
    if (n != -1)
    {   
        for (int i = n;i < *k-1; i++)
        {
            (*empty_area)[i] = (*empty_area)[i+1];
        }
        (*k)--;
    }
    else
        if (*k > 0)
            *h += 1;
}

void print_sost(Queue_list *q1,Queue_list *q2,List_q **empty_area,int k)
{
    if (q1 == NULL)
    {
        printf("очередь 1 пуста!\n");
    }
    if (q2 == NULL) 
    {
        printf("очередь 2 пуста!\n");
    }
    printf("Занятые адреса\n");
    while(q1->Pout)
    {
        printf("%p\n",q1->Pout);
        q1->Pout = q1->Pout->next;
    }
    while(q2->Pout)
    {
        printf("%p\n",q2->Pout);
        q2->Pout = q2->Pout->next;
    }
    printf("Адреса свободных областей:\n");
    for(int i = 0; i < k; i++)
    {
        printf("%p\n", empty_area[i]);    
    }
    printf("Количество свободных областей = %d\n",k);
}


int modelling_system_list(Queue_list *queue_1, Queue_list *queue_2, List_q ***empty_area, int *k, int *size_emty_area, int *t_all1, int *t_all2)
{
    int counter_loop = 0;
    double time_come1 = 0;
    double time_come2 = 0;
    double time_work1 = 0;
    double time_work2 = 0;

    double real_time = -1;
    double time_prost1 = 0;
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
    int h = 0;
    int sr_time_in_queue1 = 0;
    int sr_time_in_queue2 = 0;
    int counter_loop_2 = 0;
    while (counter_loop < 1000)
    {
        if (real_time < 0)
        {
            create_time(&time_come1,&time_work1, t_all1[0], t_all1[1], t_all1[2], t_all1[3]);    
            time_obrab1 += time_work1;
            push_Queue_list(queue_1, time_work1, time_come1);
            delete_empty_area(empty_area, queue_1, k, &h);
            count_queue1++;
            create_time(&time_come2,&time_work2, t_all2[0], t_all2[1], t_all2[2], t_all2[3]);
            push_Queue_list(queue_2, time_work2, time_come2);
            delete_empty_area(empty_area, queue_2, k, &h);
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
                    create_time(&time_come2,&time_work2, t_all2[0], t_all2[1], t_all2[2], t_all2[3]);
                    push_Queue_list(queue_2, time_work2, time_come2);
                    delete_empty_area(empty_area, queue_2, k, &h);
                    time_obrab2 += time_work2;
                    count_applications_enter2++;                    
                    real_time = (queue_2->Pout->time1.time_work + queue_2->Pout->time1.time_come);
                    filling_empty_area(empty_area, queue_2, k, size_emty_area);
                    pop_list(queue_2);    
                    
                    count_applications_exit2++;                    
                }
                else
                {
                    create_time(&time_come1,&time_work1, t_all1[0], t_all1[1], t_all1[2], t_all1[3]);
                    push_Queue_list(queue_1, time_work1, time_come1);
                    delete_empty_area(empty_area, queue_1, k, &h);
                    time_obrab1 += time_work1;
                    count_applications_enter1++;
                    real_time = (queue_1->Pout->time1.time_work + queue_1->Pout->time1.time_come);
                    filling_empty_area(empty_area, queue_1, k, size_emty_area);
                    pop_list(queue_1);
                    
                    counter_loop++;
                    counter_loop_2 = 1;
                    count_queue1_sr += count_queue1;
                    count_queue2_sr += count_queue2;
                    count_applications_exit1++;
                }
            }    
            else if (real_time < queue_1->Pout->time1.time_come && real_time > queue_2->Pout->time1.time_come)
            {
                sr_time_in_queue2 += (real_time - queue_2->Pout->time1.time_come);
                while (time_come2 <= real_time)
                {
                    create_time(&time_come2,&time_work2, t_all2[0], t_all2[1], t_all2[2], t_all2[3]);
                    push_Queue_list(queue_2, time_work2, time_come2);
                    delete_empty_area(empty_area, queue_2, k, &h);
                    count_queue2++;
                    time_obrab2 += time_work2;
                    count_applications_enter2++;
                }
                    
                if (real_time < (queue_2->Pout->time1.time_work + queue_2->Pout->time1.time_come))
                    real_time = (queue_2->Pout->time1.time_work + queue_2->Pout->time1.time_come);
                filling_empty_area(empty_area, queue_2, k, size_emty_area);
                pop_list(queue_2);
                
                count_queue2--;                
                count_applications_exit2++;            
            }
            else if (real_time > queue_1->Pout->time1.time_come && real_time < queue_2->Pout->time1.time_come)
            {
                sr_time_in_queue1 += (real_time - queue_1->Pout->time1.time_come);
                while (time_come1 <= real_time)
                {
                    create_time(&time_come1,&time_work1, t_all1[0], t_all1[1], t_all1[2], t_all1[3]);
                    push_Queue_list(queue_1, time_work1, time_come1);
                    delete_empty_area(empty_area, queue_1, k, &h);
                    count_queue1++;    
                    time_obrab1 += time_work1;
                    count_applications_enter1++;
                }
                    
                if (real_time < (queue_1->Pout->time1.time_work + queue_1->Pout->time1.time_come))
                    real_time = (queue_1->Pout->time1.time_work + queue_1->Pout->time1.time_come);
                filling_empty_area(empty_area, queue_1, k, size_emty_area);
                pop_list(queue_1);
                
                
                count_queue1--;                    
                counter_loop++;
                counter_loop_2 = 1;
                count_queue1_sr += count_queue1;
                count_queue2_sr += count_queue2;
                count_applications_exit1++;            
            }
            else if (real_time >= queue_1->Pout->time1.time_come && real_time >= queue_2->Pout->time1.time_come)
            {
                sr_time_in_queue1 += (real_time - queue_1->Pout->time1.time_come);
                sr_time_in_queue2 += (real_time - queue_2->Pout->time1.time_come);
                while (time_come1 <= real_time)
                {
                    create_time(&time_come1,&time_work1, t_all1[0], t_all1[1], t_all1[2], t_all1[3]);
                    push_Queue_list(queue_1, time_work1, time_come1);
                    delete_empty_area(empty_area, queue_1, k, &h);
                    count_queue1++;    
                    time_obrab1 += time_work1;
                    count_applications_enter1++;
                }
                while (time_come2 <= real_time)
                {
                    create_time(&time_come2,&time_work2, t_all2[0], t_all2[1], t_all2[2], t_all2[3]);
                    push_Queue_list(queue_2, time_work2, time_come2);
                    delete_empty_area(empty_area, queue_2, k, &h);
                    count_queue2++;    
                    time_obrab2 += time_work2;
                    count_applications_enter2++;
                }
                
                
                if (real_time < (queue_1->Pout->time1.time_work + queue_1->Pout->time1.time_come))
                    real_time = (queue_1->Pout->time1.time_work + queue_1->Pout->time1.time_come);
                filling_empty_area(empty_area, queue_1, k, size_emty_area);
                pop_list(queue_1);
                            
                count_queue1--;    
                counter_loop++;
                counter_loop_2 = 1;
                count_queue1_sr += count_queue1;
                count_queue2_sr += count_queue2;
                count_applications_exit1++;
            }   
            
            if (counter_loop % 100 == 0 && counter_loop != 0 && counter_loop_2 == 1)
            {
                counter_loop_2 = 0;
                printf("%d --------------------------------\n",counter_loop);
                printf("Длина первой очереди = %d\n",count_queue1);
                printf("Длина второй очереди = %d\n",count_queue2);
                printf("Средняя длина первой очереди = %f\n",(double)count_queue1_sr/counter_loop);
                printf("Средняя длина второй очереди = %f\n",(double)count_queue2_sr/counter_loop);
                printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter1, count_applications_exit1);
                printf("Количество вошедших и вышедших заявок во второй очереди: %d; %d\n",count_applications_enter2, count_applications_exit2);
				if (count_applications_exit1 > 0)
					printf("Среднее время пребывания в первой очереди = %f\n",(double)sr_time_in_queue1/count_applications_exit1);
				if (count_applications_exit2 > 0)
					printf("Среднее время пребывания во второй очереди = %f\n",(double)sr_time_in_queue2/count_applications_exit2);
            }    
        }
    }
    time_prost1 = real_time - (time_obrab1 + time_obrab2);
    printf("\nВремя моделирования = %f\n",real_time);
    printf("Время простоя OA = %f\n",time_prost1);
    printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter1, count_applications_exit1);
    printf("Количество вошедших и вышедших заявок во второй очереди: %d; %d\n",count_applications_enter2, count_applications_exit2);
    printf("Аппарат сработал: %d раз\n",count_applications_exit1 + count_applications_exit2);
    printf("Время работы ОА для первой очереди составило: %f\n",(double)count_applications_exit1*(((double)t_all1[2]+(double)t_all1[3])/2));
    printf("Время работы ОА для второй очереди составило: %f\n",(double)count_applications_exit2*(((double)t_all2[2]+(double)t_all2[3])/2));
    double zayav = real_time / ((t_all1[0]+t_all1[1])/2);
    printf("Погрешность =  %f%%\n",100*(fabs(zayav - count_applications_enter1)/zayav));
    int choose;
    while (1)
    {
        printf("Подменю:\n");
        printf("1 - вывести список адресов\n\n");
        printf("0 - выход\n");
        printf("Введите пункт меню: ");
        if (scanf("%d",&choose) == 1)
        {
            if (choose == 1)
            {
                print_sost(queue_1,queue_2,*empty_area,*k);
                if (h != 0)
                    printf("Присутствует фрагментация\n");
                else
                    printf("Отсутствует фрагментация\n");
                break;
            }
            else if (choose == 0)
                break;
            else
                printf("Такого пункта меню нет\n");
        }
        else
		{
            printf("Некорректный пункт меню\n");
			fflush(stdin);
		}
    } 
    
    return 0;
} 





 
int modelling_system_arr(Arr_q *queue_1, Arr_q *queue_2, int *t_all1, int *t_all2)
{
    int counter_loop = 0;
    double time_come1 = 0;
    double time_come2 = 0;
    double time_work1 = 0;
    double time_work2 = 0;

    double real_time = -1;
    double time_prost1 = 0;
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
    int counter_loop_2 = 0;
	int bool1 = 1;
    while (counter_loop < 1000)
    {
        if (real_time < 0)
        {
            create_time(&time_come1,&time_work1, t_all1[0], t_all1[1], t_all1[2], t_all1[3]);    
            time_obrab1 += time_work1;
            push_Queue_arr(queue_1, time_work1, time_come1);
            count_queue1++;
            create_time(&time_come2,&time_work2, t_all2[0], t_all2[1], t_all2[2], t_all2[3]);
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
                    create_time(&time_come2,&time_work2, t_all2[0], t_all2[1], t_all2[2], t_all2[3]);
                    push_Queue_arr(queue_2, time_work2, time_come2);
                
                    time_obrab2 += time_work2;
                    count_applications_enter2++;                    
                    real_time = (queue_2->Pout->time_work + queue_2->Pout->time_come);
                    pop_Queue_arr(queue_2);    
            
                    count_applications_exit2++;                    
                }
                else
                {
                    create_time(&time_come1,&time_work1, t_all1[0], t_all1[1], t_all1[2], t_all1[3]);
                    push_Queue_arr(queue_1, time_work1, time_come1);
                    time_obrab1 += time_work1;
                    count_applications_enter1++;
                    real_time = (queue_1->Pout->time_work + queue_1->Pout->time_come);
                    pop_Queue_arr(queue_1);
                    counter_loop++;
                    counter_loop_2 = 1;
                    count_queue1_sr += count_queue1;
                    count_queue2_sr += count_queue2;
                    count_applications_exit1++;
                }
            }
            else if (real_time < queue_1->Pout->time_come && real_time > queue_2->Pout->time_come)
            {
                sr_time_in_queue2 += (real_time - queue_2->Pout->time_come);
                while (time_come2 <= real_time)
                {
                    create_time(&time_come2,&time_work2, t_all2[0], t_all2[1], t_all2[2], t_all2[3]);
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
            else if (real_time > queue_1->Pout->time_come && real_time < queue_2->Pout->time_come)
            {
                sr_time_in_queue1 += (real_time - queue_1->Pout->time_come);
                while (time_come1 <= real_time)
                {
                    create_time(&time_come1,&time_work1, t_all1[0], t_all1[1], t_all1[2], t_all1[3]);
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
                counter_loop_2 = 1;
                count_queue1_sr += count_queue1;
                count_queue2_sr += count_queue2;
                count_applications_exit1++;            
            }
            else if (real_time >= queue_1->Pout->time_come && real_time >= queue_2->Pout->time_come)
            {
                sr_time_in_queue1 += (real_time - queue_1->Pout->time_come);
                sr_time_in_queue2 += (real_time - queue_2->Pout->time_come);
                while (time_come1 <= real_time)
                {
                    create_time(&time_come1,&time_work1, t_all1[0], t_all1[1], t_all1[2], t_all1[3]);
                    push_Queue_arr(queue_1, time_work1, time_come1);
                    count_queue1++;    
                    time_obrab1 += time_work1;
                    count_applications_enter1++;
                }
                while (time_come2 <= real_time)
                {
                    create_time(&time_come2,&time_work2, t_all2[0], t_all2[1], t_all2[2], t_all2[3]);
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
                counter_loop_2 = 1;
                count_queue1_sr += count_queue1;
                count_queue2_sr += count_queue2;
                count_applications_exit1++;
            }   
            
            if (count_queue1 > 1000 || count_queue2 > 1000)
			{
				printf("Переполнение массива\n");
				bool1 = 0;
				break;
			}
            if (counter_loop % 100 == 0 && counter_loop != 0 && counter_loop_2 == 1)
            {
                counter_loop_2 = 0;
                printf("%d --------------------------------\n",counter_loop);
                printf("Длина первой очереди = %d\n",count_queue1);
                printf("Длина второй очереди = %d\n",count_queue2);
                printf("Средняя длина первой очереди = %f\n",(double)count_queue1_sr/counter_loop);
                printf("Средняя длина второй очереди = %f\n",(double)count_queue2_sr/counter_loop);
                printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter1, count_applications_exit1);
                printf("Количество вошедших и вышедших заявок во второй очереди: %d; %d\n",count_applications_enter2, count_applications_exit2);
                if (count_applications_exit1 > 0)
					printf("Среднее время пребывания в первой очереди = %f\n",(double)sr_time_in_queue1/count_applications_exit1);
				if (count_applications_exit2 > 0)
					printf("Среднее время пребывания во второй очереди = %f\n",(double)sr_time_in_queue2/count_applications_exit2);
            }
        }
    }
	if (bool1)
	{
		time_prost1 = real_time - (time_obrab1 + time_obrab2);
		printf("\nВремя моделирования = %f\n",real_time);
		printf("Время простоя OA = %f\n",time_prost1);
		printf("Количество вошедших и вышедших заявок в первой очереди: %d; %d\n",count_applications_enter1, count_applications_exit1);
		printf("Количество вошедших и вышедших заявок во второй очереди: %d; %d\n",count_applications_enter2, count_applications_exit2);
		printf("Аппарат сработал: %d раз\n",count_applications_exit1 + count_applications_exit2);
		printf("Время работы ОА для первой очереди составило: %f\n",(double)count_applications_exit1*(((double)t_all1[2]+(double)t_all1[3])/2));
		printf("Время работы ОА для второй очереди составило: %f\n",(double)count_applications_exit2*(((double)t_all2[2]+(double)t_all2[3])/2));
		double zayav = real_time / ((t_all1[0]+t_all1[1])/2);
		printf("Погрешность =  %f%%\n",100*(fabs(zayav - count_applications_enter1)/zayav));
	}
    return 0;
} 




void add1(int k)
{
    unsigned long long tb, te;
    unsigned long long t_mid = 0;
    unsigned long long t_mid1;
    unsigned long long t_mid2;
    int n;
    
    Queue_list q_list_1;
    q_list_1.Pin = NULL;
    q_list_1.Pout = NULL;
    
    Arr_q q_arr_1;
    Time_q q_arr_11[MAX_SIZE_QUEUE];
    q_arr_1.Pin = q_arr_11;
    q_arr_1.Pout = q_arr_11;
    q_arr_1.end = q_arr_11 + MAX_SIZE_QUEUE-1;
    
    
    n = k;
    
    for (int i = 0; i < n; i++)
    {
        tb = tick();
        push_Queue_list(&q_list_1, 1, 2);
        te = tick();
        if (te >= tb)
            t_mid += (te - tb);
        else
            n--;        
    }
    
    printf("Время добавления %d элементов к очереди, реализованной списком: %f\n",k,(float)t_mid);
    printf("Время добавления одного элемента к очереди, реализованной списком: %f\n",(float)t_mid/n);
    t_mid1 = (float)t_mid/n;
    t_mid = 0;
    n = k;
    for (int i = 0; i < n; i++)
    {
        tb = tick();
        push_Queue_arr(&q_arr_1, 1, 2);
        te = tick();
        if (te >= tb)
            t_mid += (te - tb);
        else
            n--;        
    }    
    printf("Время добавления %d элементов к очереди, реализованной массивом: %f\n",k,(float)t_mid);
    printf("Время добавления одного элемента к очереди, реализованному массивом: %f\n",(float)t_mid/n);
    t_mid2 = (float)t_mid/n;
    printf("Очередь реализованная массивом быстрее списка на %f %%\n",100-(float)((float)t_mid2/(float)t_mid1)*100);
    printf("-----------------------------------------------------\n"); 

}


void pop_all(int k)
{
    
    unsigned long long tb, te;
    unsigned long long t_mid = 0;
    unsigned long long t_mid1;
    unsigned long long t_mid2;
    int n;
    Queue_list q_list_1;
    q_list_1.Pin = NULL;
    q_list_1.Pout = NULL;
    
    Arr_q q_arr_1;
    Time_q q_arr_11[MAX_SIZE_QUEUE];
    q_arr_1.Pin = q_arr_11;
    q_arr_1.Pout = q_arr_11;
    q_arr_1.end = q_arr_11 + MAX_SIZE_QUEUE-1;
    
    n = k;
    for (int i = 0; i < n; i++)
    {
        push_Queue_list(&q_list_1, 1, 2);      
    }
    
    tb = tick();      
    while (q_list_1.Pout != NULL)
    {    
        pop_list(&q_list_1);
    }
    te = tick();
    t_mid = te-tb;
    printf("Время очистки очереди, реализованного списком: %f\n",(float)t_mid);
    t_mid1 = t_mid;
    
    
    for (int i = 0; i < n; i++)
    {
        push_Queue_arr(&q_arr_1, 1, 2);
    }  
    
    tb = tick(); 
    q_arr_1.Pin = q_arr_11;
    q_arr_1.Pout = q_arr_11;
    te = tick();
    t_mid = te-tb;
    printf("Время очистки очереди, реализованного массивом: %f\n",(float)t_mid);
    t_mid2 = t_mid;

    printf("Очередь реализованная массивом быстрее списка на %f %%\n",100-((float)(t_mid2)/(float)t_mid1)*100);
    printf("-----------------------------------------------------\n"); 
    
}

void time_memory(void)
{ 
    int k = 20;
    for (int i = 0;i<3;i++)
    {
        printf("Количество элементов = %d\n",k);
        add1(k);
        pop_all(k);        
        printf("Объем памяти, которое занимает %d элементов очереди реализованной списком: %I64d\n", k, sizeof(List_q)*k);
        printf("Объем памяти, которое занимает %d элементов очереди реализованного массивом: %I64d\n", k, sizeof(Arr_q)*k);
        printf("Очередь реализованная списком меньше массива на %f %%\n",100-((float)sizeof(List_q)*k/((float)sizeof(Arr_q)*k))*100);
        k += 20;
        printf("\n\n################################\n");         
    }
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
    
    Time_q q_arr_11[MAX_SIZE_QUEUE];
    q_arr_1.Pin = q_arr_11;
    q_arr_1.Pout = q_arr_11;
    q_arr_1.end = q_arr_11 + MAX_SIZE_QUEUE-1;
    
    Time_q q_arr_22[MAX_SIZE_QUEUE];
    q_arr_2.Pin = q_arr_22;
    q_arr_2.Pout = q_arr_22;
    q_arr_2.end = q_arr_22 + MAX_SIZE_QUEUE-1;
    
    setbuf(stdout, NULL);
    int choose;
    
    int t1[4];
    int t2[4];
    printf("Введите границы интервала времени прихода и работы первой очереди:\n");
    printf("tc11 tc12 tw11 tw12 = ");
    if (scanf("%d %d %d %d",&t1[0], &t1[1], &t1[2], &t1[3]) != 4 || t1[1]-t1[0] <= 0 || t1[3]-t1[2] <= 0)
    {
        printf("Некорректные границы");
        return -1;
    }
    printf("tc21 tc22 tw21 tw22 = ");
    if (scanf("%d %d %d %d",&t2[0], &t2[1], &t2[2], &t2[3]) != 4 || t2[1]-t2[0] <= 0 || t2[3]-t2[2] <= 0)
    {
        printf("Некорректные границы");
        return -1;
    }
    
    while (1)
    {
        printf("Меню:\n");
        printf("1 - смоделировать очередь списком\n");
        printf("2 - смоделировать очередь массивом\n");
        printf("3 - вывести информацию о времени и памяти\n\n");
        printf("0 - выход\n");
        printf("Введите пункт меню: ");
        if (scanf("%d",&choose) == 1)
		{
			if (choose == 1)
			{
				int k = 0;
				int size_emty_area = 5;
				List_q **empty_area = malloc(size_emty_area*sizeof(Queue_list *));
	
				modelling_system_list(&q_list_1, &q_list_2, &empty_area, &k, &size_emty_area, t1, t2);
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
				modelling_system_arr(&q_arr_1, &q_arr_2, t1, t2);
				q_arr_1.Pin = q_arr_11;
				q_arr_1.Pout = q_arr_11;
				q_arr_1.end = q_arr_11 + MAX_SIZE_QUEUE-1;
				q_arr_2.Pin = q_arr_22;
				q_arr_2.Pout = q_arr_22;
				q_arr_2.end = q_arr_22 + MAX_SIZE_QUEUE-1;
			}
			else if (choose == 3)
			{
				time_memory();
			}
			else if (choose == 0)
				break;
			else
				printf("Такого пункта меню нет\n");
		}
		else
		{
			printf("Некорректный пункт меню\n");
			fflush(stdin);
		}
    }

}
