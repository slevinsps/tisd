#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define OK 0
#define STACK_OVERFOW -1
#define STACK_UNDERFLOW -2
#define MEMORY_ERROR -3

#define MAX_SIZE_STACK 5
#define MIN_SIZE_STACK 5
#define MULTIPLY 2

typedef struct Stack {
    char *AUB;
    char *PS;
    char *ALB;
    int L;
} Stack;

typedef struct Stack_spisok{
    char value;
    struct Stack_spisok *next;
} Stack_spisok;


void print_stack(Stack *stack_arr)
{
    for (int i = 0; i <= stack_arr->PS - stack_arr->AUB; i++)
    {
        printf("%c ",*(stack_arr->PS-i));
    }
}

void print_stack_list(Stack_spisok *head)
{
    while (head != NULL)
    {
        printf("%c ", head->value);
        head = head->next;
    }
}

void print_sost(Stack_spisok *head)
{
    while (head != NULL)
    {
        printf("%p       %c\n", head,head->value);
        head = head->next;
    }
}

int push_static_array(Stack *stack_arr, char data)
{
    int err = OK;
    stack_arr->PS += stack_arr->L;
    if (stack_arr->PS > stack_arr->ALB-1)
        err = STACK_OVERFOW;
    
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

int push_dynamic_array(Stack *stack_arr, char data)
{
    int err = OK;
    int size;
    stack_arr->PS += stack_arr->L;

    if (stack_arr->PS > stack_arr->ALB-1)
    {
        size = stack_arr->ALB - stack_arr->AUB;
        stack_arr->AUB = realloc(stack_arr->AUB, size * MULTIPLY * sizeof(char));
        stack_arr->PS = stack_arr->AUB + size;
        stack_arr->ALB = stack_arr->AUB + size * MULTIPLY;
    }
    if (stack_arr->PS - stack_arr->AUB + 1> MAX_SIZE_STACK)
        err = STACK_OVERFOW;

    *(stack_arr->PS) = data;

    return err;    
}

int push_list(Stack_spisok **head, char value) 
{
    int err = OK;
    Stack_spisok *tmp = malloc(sizeof(Stack_spisok));
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

int pop_list(Stack_spisok **head,char *value) 
{
    Stack_spisok *last;
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

int  palindrom_array(Stack *stack_arr, char *s)
{
    int k = 1;
    int err = OK;
    char value;  
    for (int i = 0; i < strlen(s);i++)
    {
        err = pop_array(stack_arr, &value);
        if (value != s[i])
            k = 0;                
    }
    if (k)        
           printf("\nСтрока является палиндромом\n");
    else
        printf("\nСтрока не является палиндромом\n");
    return err;
}

int palindrom_list(Stack_spisok *head, char *s)
{
    int k = 1;
    int err = OK;
    char value;
    
    for (int i = 0; i < strlen(s);i++)
    {
        err = pop_list(&head,&value);
        if (value != s[i])
            k = 0;                
    }
    pop_list(&head,&value);
    if (k)        
           printf("\nСтрока является палиндромом\n");
    else
        printf("\nСтрока не является палиндромом\n");
    return err;
}

int menu_array(Stack *stack_arr, char *s)
{
    int choice;
    char value; 
    int err = OK;
    printf("\n-----------------------------------------------------\n");
    printf("ПОДМЕНЮ \n");
    printf("1 - Добавить элемент в стэк\n");
    printf("2 - Удалить последний элемент из стэка\n");
    printf("3 - Очистить стэк\n");    
    printf("4 - Проверить на палиндромность\n");
    printf("5 - Печать элементов стэка\n\n");
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
            err = push_static_array(stack_arr, c[0]);
            if (err == STACK_OVERFOW)
            {
                printf("Стэк переполнен\n");
                return 0;
            }
        }
        if (choice == 2)
        {
            err = pop_array(stack_arr,&value);
            s[strlen(s)-1] = 0;
            if(err == STACK_UNDERFLOW)
            {
                printf("Стэк пуст!\n");
            }
        }
        if (choice == 3)
        {
            while (pop_array(stack_arr,&value)  == OK)
            {    
                s[strlen(s)-1] = 0;
            }
            s[strlen(s)-1] = 0;
            printf("Стэк очищен!\n");
        }

        if (choice == 4)
        {
            palindrom_array(stack_arr, s);
            for (int i = 0; i < strlen(s);i++)
            {
                err = push_static_array(stack_arr, s[i]);
                if (err == STACK_OVERFOW)
                {
                    printf("Стэк переполнен\n");
                    return STACK_OVERFOW;
                }
            }
        }
        if (choice == 5)
        {
            printf("Содержимое стэка\n");
            if (stack_arr->PS < stack_arr->AUB)
                printf("Стэк пуст!\n");
            else
                print_stack(stack_arr);
            //printf("\n%s\n",s);
        }
        if (choice == 0)
            return 0;
    }
    return 1;
}

int menu_list(Stack_spisok **head, char *s)
{
    int choice;
    char value; 
    int err = OK;
    printf("\n-----------------------------------------------------\n");
    printf("ПОДМЕНЮ \n");
    printf("1 - Добавить элемент в стэк\n");
    printf("2 - Удалить последний элемент из стэка\n");
    printf("3 - Очистить стэк\n");    
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
            print_stack_list(*head);
            if (err == STACK_OVERFOW)
            {
                printf("Стэк переполнен\n");
                return 0;
            }
        }
        if (choice == 2)
        {
            err = pop_list(head,&value);
            s[strlen(s)-1] = 0;
            if(err == STACK_UNDERFLOW)
            {
                printf("Стэк пуст!\n");
            }
        }
        if (choice == 3)
        {
            while (pop_list(head,&value) == OK)
            {    
                s[strlen(s)-1] = 0;
            }
            s[strlen(s)-1] = 0;
            printf("Стэк очищен!\n");
        }

        if (choice == 4)
        {
            palindrom_list(*head, s);
            
            *head = NULL;
            for (int i = 0; i < strlen(s);i++)
            {
                push_list(head, s[i]);                
            }    
        }
        if (choice == 5)
        {            
            printf("Адреса элементов |  Элементы\n");
            if (*head == NULL) 
                printf("Стэк пуст!\n");
            else
                print_sost(*head);
        }
        if (choice == 0)
            return 0;
    }
    return 1;
}

int menu(char *s)
{
    int err = OK;
    int choice;
    int exit = 1;
    Stack stack_arr;
    printf("\n-----------------------------------------------------\n");
    printf("МЕНЮ\n");
    printf("Вы можете проверить на палиндромность разными способами\n");
    printf("в зависимости от того, как вы зададите стэк\n");
    printf("1 - Задать стэк с помощью статического массива\n");
    printf("2 - Задать стэк с помощью динамического массива\n");
    printf("3 - Задать стэк с помощью односвязного списка\n");
      
    printf("0 - Выйти\n");
    printf("Выбор: ");
    if (scanf("%d",&choice) != 1 || choice>3 || choice<0)
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
                    printf("Стэк переполнен\n");
                    return STACK_OVERFOW;
                }
            }
            while(exit)
            {
                exit = menu_array(&stack_arr,s);
            }    
        }
        if (choice == 2)
        {            
            stack_arr.AUB = malloc(5*sizeof(char));
            stack_arr.PS = stack_arr.AUB-1;
            stack_arr.ALB = stack_arr.AUB + MIN_SIZE_STACK;
            stack_arr.L = 1;
            
            for (int i = 0; i < strlen(s);i++)
            {
                err = push_static_array(&stack_arr, s[i]);
                if (err == STACK_OVERFOW)
                {
                    printf("Стэк переполнен\n");
                    return STACK_OVERFOW;
                }
            }
            while(exit)
            {
                exit = menu_array(&stack_arr,s);
            }           
        }
        if (choice == 3)
        {
            Stack_spisok *head = NULL;
            for (int i = 0; i < strlen(s);i++)
            {
                push_list(&head, s[i]);                
            }
            while(exit)
            {
                exit = menu_list(&head, s);
            }            
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
    printf("Проверка на палиндрость\n");
    printf("Введите строку: ");
    scanf("%s",s);        
    while(exit)
        exit = menu(s);    
    return err;
}
