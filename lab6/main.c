#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define OK 0 
#define INVALID_NUMBER -1
#define INVALID_SIZE -2
#define INVALID_FILE -3
#define MEMORY_ERROR -4
#define NOT_ALL_ARGUMENTS -5

# define SEP "\"., ?!\n" 
# define SIZE_BUF 300

typedef struct tree_node
{
	char *s;
	unsigned int frequency;
	struct tree_node *left;
	struct tree_node *right;	
} tree_node;

tree_node* create_node(char *s)
{
    tree_node *node = malloc(sizeof(tree_node));
    if (node)
    {
        node->s = s;
        node->frequency = 1;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

tree_node* insert(tree_node *tree, tree_node *node)
{
	
    int cmp;
    if (tree == NULL)
	{
        return node;
	}
    cmp = strcmp(node->s, tree->s);
	
    if (cmp < 0)
        tree->left = insert(tree->left, node);
    else if (cmp > 0)
        tree->right = insert(tree->right, node);
	else
		tree->frequency++;
    return tree;
}

int dist(tree_node *tree)
{
	if(tree == 0)
        return 0;
    int left, right;
    if (tree->left != NULL)
	{
        left = dist(tree->left);
    }
	else 
        left = -1;
    if (tree->right != NULL) 
	{
        right = dist(tree->right);
    }
	else 
        right = -1;
    int min;
	if (left > right)
	{
		if (right != -1)
			min = right;
		else
			min = left;
	}
	else
	{
		if (left != -1)
			min = left;
		else
			min = right;		
	}
    return min+1;
}

tree_node* insert_left_tree(tree_node *tree, tree_node *node)
{
	int cmp;
	tree_node *tmp;
	if (tree == NULL) 
	{
		return node;
	}
	if (node == NULL) 
		return tree;
	
	cmp = strcmp(node->s, tree->s);
	if (cmp == 0)
		return tree;

	if (cmp < 0)
	{
		
		tmp = tree;
		tree = node;
		node = tmp;
	}
	//  100 150 250 350
	tree->right = insert_left_tree(tree->right, node);
	
	if ((tree->left == NULL && tree->right != NULL) || dist(tree->right) > dist(tree->left))
	{
		
		tmp = tree->right;
		tree->right = tree->left;
		tree->left = tmp;
	}
	//dist(x) = min(dist(x.left), dist(x.right)) + 1 // пересчитаем расстояние до ближайшей свободной позиции
	return tree;
}

char* min_current( tree_node *tree)
{
	while (tree->left)
	{
		tree = tree->left;
	}
	return tree->s;
}

void apply(tree_node *tree)
{
    if (tree == NULL)
        return;

    // pre-order
    // f(tree, arg);
	
    apply(tree->left);
    // in-order
    printf("%s ",tree->s);
    apply(tree->right);
    // post-order
    // f(tree, arg);
}

tree_node* search(tree_node *tree, char *s)
{
    int cmp;

    if (tree == NULL)
        return NULL;

    cmp = strcmp(s, tree->s);
    if (cmp == 0)
        return tree;
    else if (cmp < 0)
        return search(tree->left, s);
    else
        return search(tree->right, s);
}


tree_node* delete(tree_node *tree, char* s)
{
	tree_node *tmp;
    int cmp;
    if (tree == NULL)
        return tree;
	
    cmp = strcmp(tree->s, s);
	
    if (cmp > 0)
	{
		
        tree->left = delete(tree->left, s);
	}
    else if (cmp < 0)
	{
		//printf("!! %s  %s  %d \n",tree->s,s,cmp);
        tree->right = delete(tree->right, s);
	}
	else 
	{
		
		if (tree->left != NULL && tree->right != NULL)
		{
			tree->s = min_current(tree->right);
			tree->right = delete(tree->right, tree->s);
		}
		else
		{
			if (tree->left != NULL)
			{
				tree->frequency--;
				if (tree->frequency == 0)
				{
					tmp = tree;
					tree = tree->left;
					free(tmp);
				}
				
			}
			else
			{
				tree->frequency--;
				if (tree->frequency == 0)
				{
					tmp = tree;
					tree = tree->right;
					free(tmp);
				}
			}
		}
		
	}
    return tree;
}

const char *strchr1(const char *str, char symbol)
{
    const char *c = NULL;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] == symbol)
        {
            c = &(str[i]);
            break;
        }
    }
    return c;
}

int count_words(const char *str)
{
    int n = 0;
    int len = strlen(str);
    for (int i = 0;i < len;i++)
    {
        if (!strchr1(SEP, str[i]) && (i == 0 || strchr1(SEP, str[i-1])))
            n++;
    }
    return n;
}

void split_words(char *str, char **words, int ind)
{
    int len = strlen(str);
    for (int i = 0;i < len;i++)
    {
        if (!strchr1(SEP, str[i])) 
        {
            if (i == 0 || str[i-1] == 0)
            {
                words[ind] = &(str[i]);
                ind++;
            }
        }
        else
            str[i] = 0;
    }    
} 

int find_words_literal_tree(tree_node *tree, char liter)
{
	int count_words = 0;
	if (tree == NULL)
		return 0;
	if (liter < tree->s[0])
	{
		count_words += find_words_literal_tree(tree->left, liter);
	}
	else if (liter > tree->s[0]) 
	{
		count_words += find_words_literal_tree(tree->right, liter);
	}
	else
	{
		count_words += tree->frequency;
		count_words += find_words_literal_tree(tree->left, liter);
		count_words += find_words_literal_tree(tree->right, liter);
	}	
	return count_words;
}


int find_words_literal_arr(char **words, int n, char liter)
{
	int count_words = 0;
	for (int i = 0; i < n; i++)
	{
		if (words[i][0] == liter)
		{
			count_words++;
		}
	}
	return count_words;
}


void print_color_words(tree_node *tree, char literal, FILE *f)
{
	if (tree == NULL)
		return;
	if (literal < tree->s[0])
	{
		print_color_words(tree->left, literal, f);
	}
	else if (literal > tree->s[0]) 
	{
		print_color_words(tree->right, literal, f);
	}
	else
	{
		fprintf(f,"%s [fillcolor=\"yellow\"];\n",tree->s);
		print_color_words(tree->left, literal, f);
		print_color_words(tree->right, literal, f);
	}	
	
}


void apply_pre(tree_node *tree, void (*f)(tree_node*, void*), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    apply_pre(tree->left, f, arg);
    apply_pre(tree->right, f, arg);
}

void to_dot(tree_node *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->s, tree->left->s);

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->s, tree->right->s);
}

void export_to_dot(FILE *f, const char *tree_name, tree_node *tree, char literal)
{
    fprintf(f, "digraph %s {\n", tree_name);
    fprintf(f, "node [shape=\"circle\", style=\"filled\", fillcolor=\"white\", fontcolor=\"black\", margin=\"0.01\"];\n");
	print_color_words(tree, literal, f);
    apply_pre(tree, to_dot, f);

    fprintf(f, "}\n");
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}


int find_high(tree_node *tree)
{
	if(tree == 0)
        return 0;
    int left, right;
    if (tree->left != NULL)
	{
        left = find_high(tree->left);
    }
	else 
        left = -1;
    if (tree->right != NULL) 
	{
        right = find_high(tree->right);
    }
	else 
        right = -1;
    int max = left > right ? left : right;
    return max+1;
}

void bubble_sort(char **words, int k)
{
	int cmp;
	char *tmp;
	for (int i = 0; i < k - 1; i++)
	{
		for (int j = i; j < k; j++)
		{
			cmp = strcmp(words[i], words[j]);
			if (cmp > 0)
			{
				tmp = words[j];
				words[j] = words[i];
				words[i] = tmp;
			}
		}
	}
}

int strcmp1(const char* s1, const char* s2)   // функция сравнения элементов массива
{
	int cmp;
	cmp = strcmp(s1, s2);
	return cmp;              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

void test_time(void)
{
	srand(time(NULL));
	tree_node *root = NULL;
	tree_node *node;
	unsigned long long tb, te, t_mid = 0;
	char **words = NULL;
	int n = 100;
	int num;
	char *string;
	words = realloc(words,n*sizeof(char *));
	printf("Эффективность сортировки:\n");
	for (int i = 10; i <= n; i += 10)
	{
		t_mid = 0;
		string = malloc(6);
		for (int j = 0; j < i; j++)
		{
			num = 100 + rand() % 800;
			itoa(num, string, 10);
			words[j] = string;
			node = create_node(string);
			tb = tick();
			root = insert(root, node);
			te = tick();
			t_mid += (te-tb);
			string = malloc(6);
		}
		
		
		tb = tick();
		bubble_sort(words, i);
		//qsort(words, i, sizeof(string), (int (*)(const void *,const  void *)) strcmp);
		te = tick();
		printf("количество элементов = %3d; высота = %d; время (дерево) = %I64d; время (пузырек) = %I64d; отношение = %f\n", i, find_high(root), t_mid, te - tb, (float)(te - tb)/t_mid);
		while(root)
		{
			root = delete(root, root->s);
		}
		root = NULL;
	}
	tree_node *sear;
	char *sear1;
	printf("Эффективность поиска:\n");
	for (int i = 10; i <= n; i += 10)
	{
		t_mid = 0;
		string = malloc(6);
		for (int j = 0; j < i; j++)
		{
			num = 100 + rand() % 800;
			itoa(num, string, 10);
			words[j] = string;
			node = create_node(string);
			root = insert(root, node);
			t_mid += (te-tb);
			string = malloc(6);
		}
		tb = tick();
		sear = search(root, "hello");
		te = tick();
		t_mid = te - tb;
		tb = tick();
		for(int j = 0; j < i; j++)
		{
			if (strcmp(words[j],"hello") == 0)
			{
				sear1 = words[j];
			}
		}
		te = tick();
		printf("количество элементов = %3d; высота = %d; время (дерево) = %I64d; время (файл) = %I64d; отношение = %f\n", i, find_high(root), t_mid, te - tb, (float)(te - tb)/t_mid);
		while(root)
		{
			root = delete(root, root->s);
		}
		root = NULL;
	}
	

	
}



int main(void)
{
	 tree_node *root = NULL;
	tree_node *node;
	unsigned long long tb, te;
	
	char *string = malloc(SIZE_BUF);
	
	int n = 0;
	char **words = NULL;
	int ind = 0;
	char literal;
	int count_words1;
	int count_words2;
	
	setbuf(stdout,NULL); 
	int r = 1;
	while(1)
	{
		printf("\nПрограмма ищет количество слов в файле, начинающихся на определенную букву\n");
		printf("Меню:\n");
		printf("1 - заполнить дерево из файла\n");
		printf("2 - добавить элемент в дерево\n");
		printf("3 - удалить элемент из дерева\n");
		printf("4 - вывести количество слов на указанную букву\n");
		printf("5 - вывести элементы дерева\n");
		printf("6 - вывести эффективность\n\n");
		printf("0 - выход\n");
		int choose;
		printf("Ваш выбор: ");
		if (scanf("%d",&choose) == 1)
		{
			if (choose == 1)
			{
				FILE *f = fopen("in.txt","r");
				while(fgets(string,SIZE_BUF - 2,f))
				{
					ind = n;
					n += count_words(string);
					words = realloc(words,n*2*sizeof(char *));
					split_words(string, words, ind);
					string = malloc(SIZE_BUF);
				}
			
				for (int i = 0; i < n ; i++)
				{
					node = create_node(words[i]);
					root = insert(root, node);
					//root = insert_left_tree(root, node);
				} 
				fclose(f);
				printf("Дерево заполнено!\n");
			}			
			else if (choose == 2)
			{
				r = 0;
				char *str = malloc(SIZE_BUF);
				printf("Введите слово: ");
				scanf("%s",str);
				fflush(stdin);
				node = create_node(str);
				root = insert(root, node);
				
				printf("Элемент добавлен!\n");
			}
			else if (choose == 3)
			{
				r = 0;
				if (!root)
				{
					printf("Дерево пусто!\n");
					break;
				}
				char *str_del = malloc(SIZE_BUF);
				printf("Введите слово: ");
				scanf("%s",str_del);
				fflush(stdin);
				
				tree_node* search_node = search(root, str_del); // удаление
				if (!search_node)
				{
					printf("Такого слова в дереве нет!\n");
					break;
				}
				while (search_node)	
				{
					root = delete(root, str_del);
					search_node = search(root, str_del);
				}
				if (!root)
					printf("Дерево пусто!\n");
				else
					printf("Элемент удален!\n");
			}
			else if (choose == 4)
			{
				fflush(stdin);
				printf("Введите букву: ");
				scanf("%c",&literal);
				
				tb = tick();
				count_words1 = find_words_literal_tree(root, literal);
				te = tick();
				printf("Время на подсчет с помощью дерева: %I64d\n",  te-tb);
				
				if (r)
				{
					tb = tick();
					count_words2 = find_words_literal_arr(words, n, literal);
					te = tick();
					printf("Время на подсчет из файла: %I64d\n",  te-tb);
				}
				
				printf("Количество слов на букву %c, посчитанных деревом = %d\n",literal, count_words1);
				if (r)
					printf("Количество слов на букву %c, посчитанных из файла = %d\n",literal, count_words2);
				{
					FILE *f = fopen("res.gv", "w");
					assert(f);
			
					export_to_dot(f, "test_tree", root, literal);
					
					fclose(f);
				} 
				printf("В файле res.gv записано дерево на языке DOT\n");
			
			}
			else if (choose == 5)
			{
				printf("Элементы дерева:\n");
				apply(root);
				printf("\n");
			}
			else if (choose == 6)
			{
				test_time();
			}
			else if (choose == 0)
				break;
			else
			{
				printf("Такого пункта меню нет!\n");
				fflush(stdin);
			}
        }
        else
        {
            printf("Такого пункта меню нет!\n");
            fflush(stdin);
        }   
	}
}
