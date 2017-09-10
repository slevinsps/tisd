#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h> 

#define MAX_STRING_LENGTH1 39 //1+30+1+1+5(+)1
#define MAX_STRING_LENGTH2 32

void division(int *x, int *y, int n1, int n2,int *k)
{
    int count1 = 1;
    int count2 = 1;
    *k = -1;
    while ((count1 == 1) || (count2 == 1))
    {
        *k += 1;
        /* for (int j = n1-1;j>=0;j--)
        {
            printf("%d",x[j]);
        }
        printf("\n"); */
        for (int i=0;i<n1;i++)
        {
            if (i <= n2-1)
            {
                if (x[i]<y[i])
                {
                    count1 = 0;
                    count2 = 0;
                    for (int j = i+1;j<n2;j++)
                    {
                        if (x[j] >= y[j])
                        {
                            count1 = 1;    

                        }                            
                    }
                    for (int j = n2;j<n1;j++)
                    {
                        if (x[j] != 0)
                        {
                            count2 = 1;    
                        }                            
                    }
                    if (count1 == 0 && count2 == 0)
                    {
                        break;
                    }
                    if (x[i] == -1)
                    {
                        x[i] = 9-y[i];
                        x[i+1] -= 1;
                    }
                    else
                    {
                        x[i] = x[i]+10-y[i];
                        x[i+1] -= 1;
                    }
                }
                else
                {
                    x[i] = x[i]-y[i];
                }
            }
            else
            {
                if (x[i] == -1)
                {
                    x[i] = 9; 
                    x[i+1] -= 1;
                }
            }
        }
    }    
}

void round_string(char *s,int *len)
{
    int r = 1,n;
    if (s[30] < '5')
    {
        *len = 30; 
    }
    else
    {
        *len = 30;
        for (int i = 29;i>=0;i--)
        {
            n = s[i] - '0';
            if (n+r>9)
            {
                if (i == 0)
                {
                    s[i] = '1';
                    *len += 1;
                    for (int j = *len;j>=2;j--)
                    {
                        s[j] = s[j-1];
                    }
                    s[1] = '0';
                    break;
                }
                else
                {
                    n = n+r - 10;
                    s[i] = '0'+n;
                }
            }
            else
            {
                n = n+r;
                s[i] = '0'+n;
                break;
            }
        }    
    }
}

int read_first_number(int *len1,char *s1,char *s1_new)
{
    int counter1 = 0,counter3 = 0,add_por = 0,bool1 = 0,bool2 = 0,bool3 = 0, por_new = 0;
    
    while (s1[counter1] != 'E' && s1[counter1] != '\0')
    {
        
        if (isdigit(s1[counter1])) 
        {
            s1_new[*len1] = s1[counter1];
            *len1 += 1;    
            if (bool1)
            {
                add_por += 1;
            }
        }
        if (s1[counter1] == '.')
        {
            bool1 = 1;
        }
        counter1 += 1;
        if (s1[counter1] == 'E')
        {
            bool3 = 1;
        }
    }
    if (bool3)
    {
        counter1 +=1;
        if (s1[counter1] == '-')
        {
            bool2 = 1;
        }
        while (s1[counter1] != '\0')
        {
            if (isdigit(s1[counter1]) && counter3 <= 7) 
            {
                por_new = por_new*10+(s1[counter1]-'0');
                counter3 += 1;    
            }
            counter1 += 1;
        }
        if (bool2)
        {
            por_new *= -1;
        }
    }
    return por_new;
    
}


void compare_strings(int *len1,int *len2,int *por_new,char* s1_new,char* s2)
{
    if (*len1>*len2)
    {
        for (int i= *len2;i<*len1;i++)
        {
            s2[i] = '0';
            *por_new +=1;
        }
        *len2 = *len1;
    }
    if (*len1<*len2)
    {
        for (int i= *len1;i<*len2;i++)
        {
            s1_new[i] = '0';
            *por_new -=1;
        }
        *len1 = *len2;
    }
    
    if (strcmp(s1_new,s2) < 0)
    {
        s1_new[*len1] = '0';
        *len1 += 1;
        *por_new -= 1;
    }
    
}


int main() 
{

    char s1[MAX_STRING_LENGTH1];
    char s2[MAX_STRING_LENGTH2];
    char s1_new[MAX_STRING_LENGTH2];
    int por_new;
    
    char s3[MAX_STRING_LENGTH2];
    int a1[MAX_STRING_LENGTH2];
    int a2[MAX_STRING_LENGTH2];
    int chastnoe;
    int len1 = 0,len2,len3, add_por = 0, zn1 = 1, zn2 = 1;
    setbuf(stdout,NULL);

    printf("Enter first number:  ");
    fgets(s1, MAX_STRING_LENGTH1, stdin);
    s1[strlen(s1)-1] = '\0';
    
    printf("\nEnter second number:  ");
    fgets(s2, MAX_STRING_LENGTH2, stdin);
    s2[strlen(s2)-1] = '\0';
    len2 = strlen(s2);
    
    
    if (s2[0] == '-')
        zn2 = 0;
    
    if (s1[0] == '-')
        zn1 = 0;
    
    if ((s2[0] == '+') || (s2[0] == '-'))
    {
        for (int i=0;i<len2-1;i++)
        {
            s2[i] = s2[i+1];
        }
        len2 -= 1;
    }
    
    por_new = read_first_number(&len1,s1,s1_new);
    por_new = por_new - add_por;
    
    if (por_new>99999)
    {
        por_new = 99999;    
    }

    compare_strings(&len1,&len2,&por_new,s1_new,s2);
    
    if (len1>30)
    {
        round_string(s1_new,&len1);
    }
    
    if (len2>30)
    {
        round_string(s2,&len2);
    }
    
    
    for (int i = len1-1;i>=0;i--)
    {
        a1[len1-1-i] = s1_new[i]-'0';
    }
    for (int i = len2-1;i>=0;i--)
    {
        a2[len2-1-i] = s2[i]-'0';
    } 
    
    
    division(a1, a2,len1,len2,&chastnoe);
    
    s3[0] = chastnoe + '0';
    s3[1] = '.';

    
    for (int i = 2;i<=30;i++)
    {
        for (int j = len1;j>0;j--)
        {
            a1[j] = a1[j-1];
        } 
        a1[0] = 0;
        division(a1, a2,len1+1,len2,&chastnoe);
        s3[i] = chastnoe + '0';
    }
    len3 = 31;
    for (int i=30;i>=0;i--)
    {
        if (s3[i] == '0')
        {
            len3 -= 1;
        }
        else
            break;    
    }
    
    s3[len3]='E';
    
    if ((zn1 && !zn2) || (!zn1 && zn2))
    {
        printf("-");
    }
    
    for (int i = 0;i<=len3;i++)
    {
        printf("%c",s3[i]);
    } 
    printf("%d",por_new);
    
}