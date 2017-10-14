#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define OK 0
#define STACK_OVERFOW -1
#define STACK_UNDERFLOW -2
#define MEMORY_ERROR -3

#define MAX_SIZE_STACK 50
#define MIN_SIZE_STACK 5
#define MULTIPLY 2

typedef struct Stack {
    char *AUB;
    char *PS;
    char *ALB;
    int L;
} Stack;

typedef struct Stack_list{
    char value;
    struct Stack_list *next;
} Stack_list;


void print_stack(Stack *stack_arr)
{
    for (int i = 0; i <= stack_arr->PS - stack_arr->AUB; i++)
    {
        printf("%c ",*(stack_arr->PS-i));
    }
}

void print_sost(Stack_list *head,Stack_list **empty_area,int k)
{
    if (head == NULL) 
        printf("стек пуст!\n");
    else
    {
        printf("Адреса элементов |  Элементы\n");
        while (head != NULL)
        {
            printf("%p       %c\n", head,head->value);
            head = head->next;
        }
    }
    printf("Адреса свободных областей:\n");
    for(int i = 0; i < k; i++)
    {
        printf("%p\n", empty_area[i]);    
    }
}

int push_static_array(Stack *stack_arr, char data)
{
    int err = OK;
    stack_arr->PS += stack_arr->L;
    if (stack_arr->PS > stack_arr->ALB-1)
    {
        err = STACK_OVERFOW;
        stack_arr->PS -= stack_arr->L;
    }
    else        
        *(stack_arr->PS) = data;

    return err;    
}

int pop_array(Stack *stack_arr, char *value)
{
    int err = OK;
    *value = *(stack_arr->PS);
    stack_arr->PS -= stack_arr->L;
    if (stack_arr->PS < stack_arr->AUB)
        err = STACK_UNDERFLOW;
    return err;    
}

int push_dynamic_array(Stack *stack_arr, char data, int *size_array)
{
    int err = OK;
    stack_arr->PS += stack_arr->L;
    
    if (stack_arr->PS > stack_arr->ALB-1)
    {
        
        *size_array = stack_arr->ALB - stack_arr->AUB;
        stack_arr->AUB = realloc(stack_arr->AUB, *size_array * MULTIPLY * sizeof(char));
        if (stack_arr->AUB)
        {
            stack_arr->PS = stack_arr->AUB + *size_array;
            stack_arr->ALB = stack_arr->AUB + *size_array * MULTIPLY;
            *size_array *= MULTIPLY;    
        }
        else
            return MEMORY_ERROR;
    }
    if (stack_arr->PS - stack_arr->AUB + 2> MAX_SIZE_STACK)
    {
        stack_arr->PS -= stack_arr->L;
        err = STACK_OVERFOW;
    }
    else
    {
        *(stack_arr->PS) = data;
    }
    return err;    
}



int pop_dynamic_array(Stack *stack_arr,  char *value, int *size_array)
{

    *value = *(stack_arr->PS);
    stack_arr->PS -= stack_arr->L;
    if (stack_arr->PS < stack_arr->AUB)
    {
        return STACK_UNDERFLOW; 
    }
    int size = stack_arr->PS - stack_arr->AUB+1;
    if (*size_array/size == 2 && *size_array%size == 0)
    {
        *size_array = size;
        stack_arr->AUB = realloc(stack_arr->AUB,*size_array * sizeof(char));
        if (stack_arr->AUB)
        {
            stack_arr->PS = stack_arr->AUB + *size_array-1;
            stack_arr->ALB = stack_arr->AUB + *size_array;
        }
        else
            return MEMORY_ERROR;
    }
    return OK;    
}


int push_list(Stack_list **head, char value) 
{
    int err = OK;
    Stack_list *tmp = malloc(sizeof(Stack_list));
    if (tmp == NULL) 
        err = MEMORY_ERROR;
    else
    {
        tmp->next = *head;
        tmp->value = value;
        *head = tmp;
    }
    return err;
}

int pop_list(Stack_list **head,char *value) 
{
    Stack_list *last;
    int err = OK;
    if (*head == NULL) 
    {
        err = STACK_UNDERFLOW;    
    }
    else
    {
        last = *head;
        *head = (*head)->next;
        *value = last->value;
        free(last);
    }
    return err;
}

int palindrom_array(Stack *stack_arr, char *s)
{
    int k = 1;
    char value;  
    for (int i = 0; i < strlen(s);i++)
    {
        pop_array(stack_arr, &value);
        if (value != s[i])
            k = 0;                
    }
    if (k)        
        return 1;
    else
        return 0;
}

int palindrom_list(Stack_list *head, char *s)
{
    int k = 1;
    char value;
    
    for (int i = 0; i < strlen(s);i++)
    {
        pop_list(&head,&value);
        if (value != s[i])
            k = 0;                
    }
    pop_list(&head,&value);
    if (k)        
        return 1;
    else
        return 0;
    
}



int menu_array(Stack *stack_arr, char *s,int r, int *size_array)
{
    //printf("@@@@@@@@@@@@@@  %I64d    %d\n",stack_arr->ALB - stack_arr->AUB,*size_array);
    int choice;
    char value; 
    int err = OK;
    printf("\n-----------------------------------------------------\n");
    printf("ПОДМЕНЮ \n");
    printf("1 - Добавить элемент в стек\n");
    printf("2 - Удалить последний элемент из стека\n");
    printf("3 - Очистить стек\n");    
    printf("4 - Проверить на палиндромность\n");
    printf("5 - Печать элементов стека\n\n");
    printf("0 - Выйти в главное меню\n");
    printf("Выбор: ");
    if (scanf("%d",&choice) != 1 || choice > 5 || choice < 0)
    {
        printf("Неверный аргумент подменю!");
        fflush(stdin);
    }
    else
    {
        if (choice == 1)
        {
            fflush(stdin);
            char c[1];
            printf("Введите символ: ");
            scanf("%c",c);
            
            if (r == 1)
                err = push_static_array(stack_arr, c[0]);
            else
                err = push_dynamic_array(stack_arr, c[0],size_array);
            if (err == STACK_OVERFOW)
            {
                printf("стек переполнен\n");
            }
            if (err == MEMORY_ERROR)
            {
                printf("ошибка выделения памяти\n");
                return 0;
            }
            if (err == OK)
                s[strlen(s)] = c[0];
        }
        if (choice == 2)
        {
            if (r == 1)
                err = pop_array(stack_arr,&value);
            else
                pop_dynamic_array(stack_arr,&value,size_array);
            s[strlen(s)-1] = 0;
            //printf("$$ %s \n",s);
            //printf("$$ %s \n",stack_arr->PS);
            if(err == STACK_UNDERFLOW)
            {
                printf("стек пуст!\n");
            }
        }
        if (choice == 3)
        {
            if (r == 1)
                stack_arr->PS = stack_arr->AUB - 1;
            else
            {
                free(stack_arr->AUB);
                stack_arr->AUB = malloc(MIN_SIZE_STACK*sizeof(char));
                stack_arr->PS = stack_arr->AUB-1;
                stack_arr->ALB = stack_arr->AUB + MIN_SIZE_STACK;
                size_array    = 0;            
            }
            int len = strlen(s);
            for (int i = 0;i < len;i++)
            {    
                s[i] = 0;
            }
            printf("стек очищен!\n");
        }

        if (choice == 4)
        {    
            int tmp = palindrom_array(stack_arr, s);
            if (tmp)
                printf("Строка является палиндромом\n");
            else
                printf("Строка не является палиндромом\n");
            for (int i = 0; i < strlen(s);i++)
            {
                if (r == 1)
                    err = push_static_array(stack_arr, s[i]);
                else
                    err = push_dynamic_array(stack_arr, s[i],size_array);
            }
        }
        if (choice == 5)
        {
            printf("Содержимое стека\n");
            if (stack_arr->PS < stack_arr->AUB)
                printf("стек пуст!\n");
            else
                print_stack(stack_arr);
        }
        if (choice == 0)
            return 0;
    }
    return 1;
}


int filling_empty_area(Stack_list ***empty_area, Stack_list *head, int *k, int *size)
{
    int err = OK;
    if (*k >= *size)
    {
        *empty_area = realloc(*empty_area, *size * MULTIPLY * sizeof(Stack_list *));    
        *size *= MULTIPLY;
    }
    if (*empty_area)
    {
        (*empty_area)[*k] = head;
        (*k)++;
    }
    else
        err = MEMORY_ERROR;
    return err; 
}

void delete_empty_area(Stack_list ***empty_area, Stack_list *head, int *k)
{
    int n = -1;
    for (int i = 0;i < *k; i++)
    {
        if ((*empty_area)[i] == head)
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
}


int menu_list(Stack_list **head, char *s,Stack_list ***empty_area,int *k,int *size_emty_area)
{
    int choice;
    char value; 
    int err = OK;
    printf("\n-----------------------------------------------------\n");
    printf("ПОДМЕНЮ \n");
    printf("1 - Добавить элемент в стек\n");
    printf("2 - Удалить последний элемент из стека\n");
    printf("3 - Очистить стек\n");    
    printf("4 - Проверить на палиндромность\n");
    printf("5 - Печать текущего состояния стека\n\n");
    printf("0 - Выйти в главное меню\n");
    printf("Выбор: ");
    if (scanf("%d",&choice) != 1 || choice > 5 || choice<0)
    {
        printf("Неверный аргумент подменю!");
        fflush(stdin);
    }
    else
    {
        if (choice == 1)
        {
            fflush(stdin);        
            char c[1];
            printf("Введите символ: ");
            scanf("%c",c);
            s[strlen(s)] = c[0];
            err = push_list(head, c[0]); 
            if (err == STACK_OVERFOW)
            {
                printf("стек переполнен\n");
            }
            else
            {
                delete_empty_area(empty_area, *head, k);                    
            }
        }
        if (choice == 2)
        {
            Stack_list *tmp = *head;
            err = pop_list(head,&value);
            s[strlen(s)-1] = 0;
            if(err == STACK_UNDERFLOW)
            {
                printf("стек пуст!\n");
            }
            else
            {
                err = filling_empty_area(empty_area, tmp, k, size_emty_area);
                if (err == MEMORY_ERROR)
                {
                    printf("ошибка выделения памяти\n");
                    return 0;
                }
            }
        }
        if (choice == 3)
        {
            while (*head != NULL)
            {    
                err = filling_empty_area(empty_area, *head, k, size_emty_area);
                if (err == MEMORY_ERROR)
                {
                    printf("ошибка выделения памяти\n");
                    return 0;
                }
                else
                {
                    pop_list(head,&value);
                    s[strlen(s)-1] = 0;
                }    
            }
            printf("стек очищен!\n");
        }

        if (choice == 4)
        {
            int tmp;
            tmp = palindrom_list(*head, s);
            if (tmp)
                printf("Строка является палиндромом\n");
            else
                printf("Строка не является палиндромом\n");
            *head = NULL;
            for (int i = 0; i < strlen(s);i++)
            {
                push_list(head, s[i]);                
            }    
        }
        if (choice == 5)
        {            
            print_sost(*head,*empty_area,*k);
        }
        if (choice == 0)
            return 0;
    }
    return 1;
}


unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

void add1(int k)
{
    unsigned long long tb, te;
    unsigned long long t_mid;
    float t_mid1;
    float t_mid2;
    float t_mid3;
    int n = k;
    int size_array = MIN_SIZE_STACK;
    Stack_list *head = NULL;
    Stack stack_arr;
    Stack stack_arr2;
    for (int i = 0; i < n; i++)
    {
        tb = tick();
        push_list(&head, 'c');
        te = tick();
        if (te >= tb)
            t_mid = te-tb;
        else
            n--;        
    }
    printf("Время добавления одного элемента к стеку, реализованному списком: %f\n",(float)t_mid/n);
    t_mid1 = (float)t_mid/n;
    
    n = k;
    char arr1[MAX_SIZE_STACK];
    stack_arr.AUB = arr1;
    stack_arr.PS = arr1-1;
    stack_arr.ALB = arr1 + MAX_SIZE_STACK;
    stack_arr.L = 1;
    for (int i = 0; i < n; i++)
    {
        tb = tick();
        push_static_array(&stack_arr, 'c');
        te = tick();
        //printf("%I64d  %I64d\n",te,tb);
        if (te >= tb)
            t_mid = te-tb;
        else
            n--;        
    }    
    printf("Время добавления одного элемента к стеку, реализованному cтатическим массивом: %f\n",(float)t_mid/n);
    t_mid2 = (float)t_mid/n;
    
    n = k;
    stack_arr2.AUB = malloc(MIN_SIZE_STACK*sizeof(char));
    stack_arr2.PS = stack_arr2.AUB-1;
    stack_arr2.ALB = stack_arr2.AUB + MIN_SIZE_STACK;
    stack_arr2.L = 1;
    for (int i = 0; i < n; i++)
    {
        tb = tick();
        push_dynamic_array(&stack_arr2, 'c',&size_array);
        te = tick();
        //printf("%I64d  %I64d\n",te,tb);
        if (te >= tb)
            t_mid = te-tb;
        else
            n--;        
    } 
    printf("Время добавления одного элемента к стеку, реализованному динамическим массивом: %f\n",(float)t_mid/n);
    t_mid3 = (float)t_mid/n;
    printf("Стек реализованный массивом быстрее списка на %f %%\n",100-(t_mid2/t_mid1)*100);
    printf("-----------------------------------------------------\n"); 
    
    
    
    
    n = k;
    char s[n];
    for (int i = 0; i<n; i++)
        s[i] = 'c';

    for (int i = 0; i < n; i++)
    {
        tb = tick();
        palindrom_array(&stack_arr, s);
        te = tick();
        for (int i = 0; i < n; i++)
        {
            push_static_array(&stack_arr, 'c');     
        } 
        if (te >= tb)
            t_mid = te-tb;
        else
            n--;        
    } 
    printf("Время работы функции, стек, реализован статическим массивом: %f\n",(float)t_mid/n);
    t_mid1 = (float)t_mid/n;
    n = k;
    for (int i = 0; i < n; i++)
    {
        tb = tick();
        palindrom_array(&stack_arr2, s);
        te = tick();
        for (int i = 0; i < n; i++)
        {
            push_dynamic_array(&stack_arr2, 'c',&size_array);     
        } 
        if (te >= tb)
            t_mid = te-tb;
        else
            n--;        
    }
    printf("Время работы функции, стек, реализован динамическим массивом: %f\n",(float)t_mid/n);
    t_mid2 = (float)t_mid/n;
    n = k;
    for (int i = 0; i < n; i++)
    {
        tb = tick();
        palindrom_list(head, s);
        te = tick();
        head = NULL;
        for (int i = 0; i < n; i++)
        {
            push_list(&head, 'c');      
        }
        
        if (te >= tb)
            t_mid = te-tb;
        else
            n--;        
    } 
    t_mid3 = (float)t_mid/n;
    printf("Время работы функции, стек, реализован списком: %f\n",(float)t_mid/n);
    printf("Стек реализованный статическим массивом быстрее списка на %f %%\n",100-(t_mid1/t_mid3)*100);
    printf("Стек реализованный динамическим массивом быстрее списка на %f %%\n",100-(t_mid2/t_mid3)*100);
    printf("-----------------------------------------------------\n"); 

    /* n = k;
    head = NULL;
    tb = tick();
    for (int i = 0; i < n; i++)
    {
        push_list(&head, 'c');     
    }
    te = tick();
    t_mid = te-tb;
    printf("Время заполнения стека, реализованного списком: %f\n",(float)t_mid/n);
    
    n = k;
    char arr1[MAX_SIZE_STACK];
    stack_arr.AUB = arr1;
    stack_arr.PS = arr1-1;
    stack_arr.ALB = arr1 + MAX_SIZE_STACK;
    stack_arr.L = 1;
    tb = tick();
    for (int i = 0; i < n; i++)
    {
        push_static_array(&stack_arr, 'c');      
    }  
    te = tick();    
    printf("Время заполнения стека, реализованногоcтатическим массивом: %f\n",(float)t_mid/n);
    
    
    n = k;
    stack_arr2.AUB = malloc(MIN_SIZE_STACK*sizeof(char));
    stack_arr2.PS = stack_arr2.AUB-1;
    stack_arr2.ALB = stack_arr2.AUB + MIN_SIZE_STACK;
    stack_arr2.L = 1;
    tb = tick();
    for (int i = 0; i < n; i++)
    {        
        push_dynamic_array(&stack_arr2, 'c',&size_array);
      
    } 
    te = tick();
    printf("Время заполнения стека, реализованногодинамическим массивом: %f\n",(float)t_mid/n);
    
    printf("-----------------------------------------------------\n"); */
}


void pop_all(int k)
{
    unsigned long long tb, te;
    unsigned long long t_mid;
    unsigned long long t_mid1;
    unsigned long long t_mid2;
    unsigned long long t_mid3;
    int n = k;
    int size_array = MIN_SIZE_STACK;
    Stack_list *head = NULL;
    Stack stack_arr;
    Stack stack_arr2;
    
    char value;
    
    for (int i = 0; i < n; i++)
    {
        push_list(&head, 'c');    
    }
    tb = tick();      
    while (head != NULL)
    {    
        pop_list(&head,&value);  
    }
    te = tick();
    t_mid = te-tb;

    printf("Время очистки стека, реализованного списком: %f\n",(float)t_mid);
    t_mid1 = t_mid;
    
    char arr1[MAX_SIZE_STACK];
    stack_arr.AUB = arr1;
    stack_arr.PS = arr1-1;
    stack_arr.ALB = arr1 + MAX_SIZE_STACK;
    stack_arr.L = 1;
    for (int i = 0; i < n; i++)
    {
        push_static_array(&stack_arr, 'c');  
    }  
    
    tb = tick(); 
    stack_arr.PS = stack_arr.AUB - 1;
    te = tick();
    t_mid = te-tb;
    printf("Время очистки стека, реализованного статическим массивом: %f\n",(float)t_mid);
    t_mid2 = t_mid;

    stack_arr2.AUB = malloc(MIN_SIZE_STACK*sizeof(char));
    stack_arr2.PS = stack_arr2.AUB-1;
    stack_arr2.ALB = stack_arr2.AUB + MIN_SIZE_STACK;
    stack_arr2.L = 1;
    for (int i = 0; i < n; i++)
    {
        push_dynamic_array(&stack_arr2, 'c',&size_array);    
    } 
    
    tb = tick();
    free(stack_arr2.AUB);
    stack_arr2.AUB = malloc(MIN_SIZE_STACK*sizeof(char));
    stack_arr2.PS = stack_arr2.AUB-1;
    stack_arr2.ALB = stack_arr2.AUB + MIN_SIZE_STACK;        
    te = tick();
    t_mid = te-tb;
    printf("Время очистки стека, реализованного динамическим массивом: %f\n",(float)t_mid);
    t_mid3 = t_mid;
    free(stack_arr2.AUB);
    printf("Стек реализованный статическим массивом быстрее списка на %f %%\n",100-((float)(t_mid2)/(float)t_mid1)*100);
    printf("Стек реализованный динаммическим массивом быстрее списка на %f %%\n",100-((float)(t_mid3)/(float)t_mid1)*100);
    printf("-----------------------------------------------------\n"); 
    
}

void time_memory(void)
{
    Stack stack_arr2;      
    int k = 20;
    int size_array = MIN_SIZE_STACK;
    for (int i = 0;i<3;i++)
    {
        printf("Количество элементов = %d\n",k);
        add1(k);
        pop_all(k);        
        stack_arr2.AUB = malloc(MIN_SIZE_STACK*sizeof(char));
        stack_arr2.PS = stack_arr2.AUB-1;
        stack_arr2.ALB = stack_arr2.AUB + MIN_SIZE_STACK;
        stack_arr2.L = 1;
        for (int i = 0; i < k;i++)
        {
            push_dynamic_array(&stack_arr2, 'c',&size_array);
        }
        printf("Объем памяти, которое занимает %d элементов стека реализованного списком: %I64d\n", k, sizeof(Stack_list)*k);
        printf("Объем памяти, которое занимает %d элементов стека реализованного статическим массивом: %I64d\n", k, sizeof(Stack)*k);
        printf("Объем памяти, которое занимает %d элементов стека реализованного динамическим массивом: %I64d\n", k, sizeof(Stack)*(stack_arr2.ALB - stack_arr2.AUB));        
        printf("Стек реализованный спиком меньше статического массива на %f %%\n",100-((float)sizeof(Stack_list)*k/((float)sizeof(Stack)*k))*100);
        printf("Стек реализованный спиком меньше динамического массива на %f %%\n",100-(((float)sizeof(Stack_list)*k)/((float)sizeof(Stack)*(stack_arr2.ALB - stack_arr2.AUB))*100));
        k += 20;
        printf("\n\n################################\n");         
    }
}
int menu(char *s)
{
    int err = OK;
    int choice;
    int exit = 1;
    int size_array;
    Stack stack_arr;
    Stack_list *head = NULL;
    printf("\n-----------------------------------------------------\n");
    printf("МЕНЮ\n");
    printf("Вы можете проверить на палиндромность разными способами\n");
    printf("в зависимости от того, как вы зададите стек\n");
    printf("1 - Задать стек с помощью статического массива\n");
    printf("2 - Задать стек с помощью динамического массива\n");
    printf("3 - Задать стек с помощью односвязного списка\n");
    printf("4 - Вывести время работы и занимаемую память\n");
      
    printf("0 - Выйти\n");
    printf("Выбор: ");
    if (scanf("%d",&choice) != 1 || choice>4 || choice<0)
    {
        printf("Неверный аргумент меню!");
        fflush(stdin);
    }
    else
    {
        if (choice == 1)
        {            
            char arr1[MAX_SIZE_STACK];
            stack_arr.AUB = arr1;
            stack_arr.PS = arr1-1;
            stack_arr.ALB = arr1 + MAX_SIZE_STACK;
            stack_arr.L = 1;
            for (int i = 0; i < strlen(s);i++)
            {
                err = push_static_array(&stack_arr, s[i]);
                if (err == STACK_OVERFOW)
                {
                    printf("стек переполнен\n");
                    return 0;
                }
            }
            while(exit)
            {
                exit = menu_array(&stack_arr,s,1,&size_array);
            }    
        }
        if (choice == 2)
        {            
            stack_arr.AUB = malloc(MIN_SIZE_STACK*sizeof(char));
            stack_arr.PS = stack_arr.AUB-1;
            stack_arr.ALB = stack_arr.AUB + MIN_SIZE_STACK;
            stack_arr.L = 1;
            size_array = MIN_SIZE_STACK;
            for (int i = 0; i < strlen(s);i++)
            {
                err = push_dynamic_array(&stack_arr, s[i],&size_array);
                if (err == STACK_OVERFOW)
                {
                    printf("стек переполнен\n");
                    return 0;
                }
            }
            while(exit)
            {
                exit = menu_array(&stack_arr,s,2,&size_array);
            }           
        }
        if (choice == 3)
        {
            
            for (int i = 0; i < strlen(s);i++)
            {
                push_list(&head, s[i]);                
            }
            int k = 0;
            int size_emty_area = MIN_SIZE_STACK;
            Stack_list **empty_area = malloc(size_emty_area*sizeof(Stack_list *));
            while(exit)
            {
                exit = menu_list(&head, s,&empty_area,&k, &size_emty_area);
            }            
        }
        if (choice == 4)
        {            
            srand(time(NULL));
            time_memory();           
        }
        if (choice == 0)
            return 0;
    }
    return 1;
}

int main(void)        
{
    int exit = 1;
    int err = OK;  
    char s[MAX_SIZE_STACK*2];
    for (int i = 0;i<MAX_SIZE_STACK*2;i++)
        s[i] = 0;
    
    setbuf(stdout,NULL);
    printf("Проверка на палиндромность\n");
    printf("Введите строку(максимальная длина %d): ",MAX_SIZE_STACK);
    scanf("%s",s);        
    while(exit)
        exit = menu(s);    
    return err;
}
