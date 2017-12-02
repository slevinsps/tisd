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

typedef struct avl_tree // структура для представления узлов дерева
{
	char *s;
	unsigned char height;
	unsigned int frequency;
	struct avl_tree *left;
    struct avl_tree *right; 
} avl_tree;


typedef struct hash_struct
{
    char *s;
    struct hash_struct *next;    
} hash_struct;


avl_tree* create_avl_node(char *s)
{
    avl_tree *node = malloc(sizeof(avl_tree));
    if (node)
    {
        node->s = s;
        node->height = 1;
		node->frequency = 1;
        node->left = NULL;
        node->right = NULL;
    }
    return node;        
}

unsigned char height_avl(avl_tree* node)
{
	if (node)
		return(node->height);
	else
		return 0;
}

int balans_factor(avl_tree* node)
{
	return height_avl(node->right)-height_avl(node->left);
}


void correct_height(avl_tree* node)
{
	unsigned char hl = height_avl(node->left);
	unsigned char hr = height_avl(node->right);
	node->height = (hl>hr?hl:hr)+1;
}

avl_tree* rotateright(avl_tree* node)
{
	avl_tree *tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	correct_height(node);
	correct_height(tmp);
	return tmp;
}


avl_tree* rotateleft(avl_tree* node)
{
	avl_tree *tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	correct_height(node);
	correct_height(tmp);
	return tmp;
}

avl_tree* balance(avl_tree* p)
{
	correct_height(p);
	if( balans_factor(p)==2 )
	{
		if( balans_factor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( balans_factor(p)==-2 )
	{
		if( balans_factor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}


avl_tree* insert_avl(avl_tree* node, avl_tree *node_ins) 
{
	if(!node) 
		return  node_ins;
	
	int cmp = strcmp(node_ins->s, node->s);
    
    if (cmp < 0)
		node->left = insert_avl(node->left, node_ins);
	else if (cmp > 0)
		node->right = insert_avl(node->right, node_ins);
	else
        node->frequency++;
	return balance(node);
}

avl_tree* findmin(avl_tree* node)
{
	if (node->left)
		return findmin(node->left);
	else
		return node;
}

avl_tree* removemin(avl_tree* p) 
{
	if(!p->left)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

avl_tree* remove_avl(avl_tree* node, char *s) // удаление ключа k из дерева p
{
	if(!node) 
		return  NULL;
	
	int cmp = strcmp(s, node->s);
    
    if (cmp < 0)
		node->left = remove_avl(node->left, s);
	else if (cmp > 0)
		node->right = remove_avl(node->right, s);

	else 
	{
		node->frequency--;
		if (node->frequency == 0)
        {
			avl_tree* q = node->left;
			avl_tree* r = node->right;
			free(node);
			if(!r) 
				return q;
			avl_tree* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
	}
	return balance(node);
}

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

char* min_current( tree_node *tree)
{
    while (tree->left)
    {
        tree = tree->left;
    }
    return tree->s;
}

void apply_in(tree_node *tree)
{
    if (tree == NULL)
        return;

    // pre-order
    // f(tree, arg);
    
    apply_in(tree->left);
    // in-order
    printf("%s ",tree->s);
    apply_in(tree->right);
    // post-order
    // f(tree, arg);
}


void apply_in_avl(avl_tree *tree)
{
    if (tree == NULL)
        return;

    // pre-order
    // f(tree, arg);
    
    apply_in_avl(tree->left);
    // in-order
    printf("%s ",tree->s);
    apply_in_avl(tree->right);
    // post-order
    // f(tree, arg);
}


void apply_pre_ord(tree_node *tree)
{
    if (tree == NULL)
        return;

    // pre-order
    // f(tree, arg);
    printf("%s ",tree->s);
    apply_pre_ord(tree->left);
    // in-order
    
    apply_pre_ord(tree->right);
    // post-order
    // f(tree, arg);
}

void apply_pre_ord_avl(avl_tree *tree)
{
    if (tree == NULL)
        return;

    // pre-order
    // f(tree, arg);
    printf("%s ",tree->s);
    apply_pre_ord_avl(tree->left);
    // in-order
    
    apply_pre_ord_avl(tree->right);
    // post-order
    // f(tree, arg);
}

void apply_post(tree_node *tree)
{
    if (tree == NULL)
        return;

    // pre-order
    // f(tree, arg);
    
    apply_post(tree->left);
    // in-order
    
    apply_post(tree->right);
    printf("%s ",tree->s);
    // post-order
    // f(tree, arg);
}

void apply_post_avl(avl_tree *tree)
{
    if (tree == NULL)
        return;

    // pre-order
    // f(tree, arg);
    
    apply_post_avl(tree->left);
    // in-order
    
    apply_post_avl(tree->right);
    printf("%s ",tree->s);
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

avl_tree* search_avl(avl_tree *tree, char *s)
{
    int cmp;

    if (tree == NULL)
        return NULL;

    cmp = strcmp(s, tree->s);
    if (cmp == 0)
        return tree;
    else if (cmp < 0)
        return search_avl(tree->left, s);
    else
        return search_avl(tree->right, s);
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

    
    apply_pre(tree->left, f, arg);
    f(tree, arg);
    apply_pre(tree->right, f, arg);
}

void apply_pre_avl(avl_tree *tree, void (*f)(avl_tree*, void*), void *arg)
{
    if (tree == NULL)
        return;

    
    apply_pre_avl(tree->left, f, arg);
    f(tree, arg);
    apply_pre_avl(tree->right, f, arg);
}

void to_dot(tree_node *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->s, tree->left->s);

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->s, tree->right->s);
}

void to_dot_avl(avl_tree *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->s, tree->left->s);

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->s, tree->right->s);
}

void export_to_dot(FILE *f, const char *tree_name, tree_node *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);
    fprintf(f, "node [shape=\"circle\", style=\"filled\", fillcolor=\"white\", fontcolor=\"black\", margin=\"0.01\"];\n");
    apply_pre(tree, to_dot, f);

    fprintf(f, "}\n");
}

void export_to_dot_avl(FILE *f, const char *tree_name, avl_tree *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);
    fprintf(f, "node [shape=\"circle\", style=\"filled\", fillcolor=\"white\", fontcolor=\"black\", margin=\"0.01\"];\n");
    apply_pre_avl(tree, to_dot_avl, f);

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


int find_high_avl(avl_tree *tree)
{
    if(tree == 0)
        return 0;
    int left, right;
    if (tree->left != NULL)
    {
        left = find_high_avl(tree->left);
    }
    else 
        left = -1;
    if (tree->right != NULL) 
    {
        right = find_high_avl(tree->right);
    }
    else 
        right = -1;
    int max = left > right ? left : right;
    return max+1;
}



int strcmp1(const char* s1, const char* s2)   // функция сравнения элементов массива
{
    int cmp;
    cmp = strcmp(s1, s2);
    return cmp;              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}


int hash_key(char *s)
{
	unsigned int key = 0;
	int len = strlen(s);
	int size;
	for (int i = 0; i < len; i++)
	{
		size = (unsigned char)s[i];
		/* if ((unsigned char)s[i] % 2 == 0)
			key += (((unsigned char)s[i]  - 47)) ^ (i + 1);
		else
			key += ((((unsigned char)s[i] - 47)) ^ (i + 1)); */
		//key += ((((unsigned char)s[i] ) << 2) + (i + 1)) >> 1;
		//key += (size ^ (i + 1) + (size % 10) * (size - len)  ); 
		if (size < 100)
			//key += (size ^ (i + 1) + (size % 10) * (size - len)  ); // крутая штука 
			key += ((size - 47) * (i + 1));
		else
			key += (size / 10) * (size % 10) + (i + 1) ; // для русских букв
			 
	}
	return key;
}

int add_in_hash_array(hash_struct ***hash_array, char *s, int *size_hash_array, int *memory)
{
	int key = hash_key(s);
	hash_struct **tmp = NULL;
	hash_struct *tmp2 = NULL;
	if (key >= *size_hash_array)
	{
		
		tmp = realloc(*hash_array, (key+1)*sizeof(hash_struct));
		if (tmp)
		{
			for(int i = *size_hash_array; i < key+1; i++)
			{
				tmp[i] = NULL;
			}
			*hash_array = tmp;
			*size_hash_array = key+1;
		}
		else 
		{
			return 0;
		}
	}
	if (!(*hash_array)[key])
	{
		(*hash_array)[key] = malloc(sizeof(hash_struct));
		*memory += sizeof(hash_struct);
		(*hash_array)[key]->s = s;
		(*hash_array)[key]->next = NULL;
	}
	else
	{
		tmp2 = (*hash_array)[key];
		if (strcmp(tmp2->s, s) == 0)
			return 1;
		while (tmp2->next)
		{
			if (strcmp(tmp2->s, s) == 0)
				return 1;
			tmp2 = tmp2->next;
		}
		if (strcmp(tmp2->s, s) == 0)
			return 1;
		tmp2->next = malloc(sizeof(hash_struct));
		*memory += sizeof(hash_struct);
		tmp2->next->s = s;
		tmp2->next->next = NULL;	
	}
	return 1;
}

int del_in_hash_array(hash_struct **hash_array, char *s, int *size_hash_array)
{
	int res = hash_key(s);
	hash_struct *tmp = NULL;
	hash_struct *tmp2 = NULL;
	if (hash_array[res])
	{
		if (strcmp(hash_array[res]->s, s) == 0)
		{
			tmp = hash_array[res];
			hash_array[res] = hash_array[res]->next;
			free(tmp);
			return 1;
		}
		tmp2 = hash_array[res];
		while (tmp2->next)
		{
			if (strcmp(tmp2->next->s, s) == 0)
			{
				tmp = tmp2->next;
				tmp2->next = tmp->next;
				free(tmp);
				return 1;
			}
			tmp2 = tmp2->next;
		}
		if (strcmp(hash_array[res]->s, s) == 0)
		{
			tmp = hash_array[res];
			hash_array[res] = NULL;
			free(tmp);
			return 1;
		}
	}
	return 0;
}

void printf_hash_table(hash_struct **hash_array, int size_hash_array, int *max_coll)
{
	int count = -1;
	int k = 1;
	for (int i = 0; i < size_hash_array ; i++)
    {
		if (hash_array[i])
		{
			k = 0;
			hash_struct *tmp = hash_array[i];
			count = -1;
			while(tmp)
			{
				count++;
				printf("%s -> ", tmp->s);
				tmp = tmp->next;
			}
			printf("\n");
			if (*max_coll < count)
				*max_coll = count;
		}
	}
	if (k)
		printf("Таблица пуста!\n");
}

void max_compare(hash_struct **hash_array, int size_hash_array, int *max_coll)
{
	int count = -1;
	for (int i = 0; i < size_hash_array ; i++)
    {
		if (hash_array[i])
		{
			count = -1;
			hash_struct *tmp = hash_array[i];
			while(tmp)
			{
				count++;
				tmp = tmp->next;
			}
			if (*max_coll < count)
				*max_coll = count;
		}
	}
}

char * find_in_hash(hash_struct **hash_array, char *s, int size_hash_array)
{
	unsigned int res = hash_key(s);
	if (res > size_hash_array || res < 0)
		return NULL;
	while (hash_array[res])
	{
		if (strcmp(hash_array[res]->s, s) == 0)
			return (hash_array[res]->s);
		hash_array[res] = hash_array[res]->next;
	}
	return NULL;
}




void test_time(void)
{
	printf("Эффективность поиска:\n");
	printf("|кол-во эл-ов| дерево| avl дерево| hash таблица| массив|\n");
    srand(time(NULL));
    tree_node *root = NULL;
    tree_node *node;
	
	avl_tree *root_avl = NULL;
    avl_tree *node_avl = NULL;
	
	int size_hash_array = 20;
    hash_struct **hash_array = calloc(size_hash_array,sizeof(hash_struct));
	int memory = 0;
	
    unsigned long long tb, te, t_mid = 0, t_mid_avl = 0, t_mid_hash = 0, t_mid_arr = 0;
    char **words = NULL;
    int n = 4096;
    int num;
    char *string;
    words = realloc(words,n*sizeof(char *));
    
    tree_node *sear;
    avl_tree *sear_avl;
    char *sear1;
    
    for (int i = 2; i <= n; i *= 2)
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
    
					
			add_in_hash_array(&hash_array, string, &size_hash_array, &memory);
					
			node_avl = create_avl_node(string);
			root_avl = insert_avl(root_avl, node_avl);
	
	
            string = malloc(6);
        }
		char *search_str = "50";
		//char *search_str = "mamamammamamamam";
		int m = 100;
		t_mid = 0;
        t_mid_hash = 0;
        t_mid_arr = 0;
        t_mid_avl = 0;
		for (int w = 0; w < m; w++ )
		{
			tb = tick();
			sear = search(root, search_str);
			te = tick();
			t_mid += (te - tb);
			
			tb = tick();
			sear_avl = search_avl(root_avl, search_str);
			te = tick();
			t_mid_avl += (te - tb);
			
			char *ss;
			tb = tick();
			ss = find_in_hash(hash_array, search_str, size_hash_array);
			te = tick();
			t_mid_hash += (te - tb);
			
			tb = tick();
			for(int j = 0; j < i; j++)
			{
				if (strcmp(words[j],search_str) == 0)
				{
					sear1 = words[j];
				}
			}
			te = tick();
			t_mid_arr += (te - tb);
		}
        t_mid = t_mid / m;
        t_mid_hash = t_mid_hash / m;
        t_mid_arr = t_mid_arr / m;
        t_mid_avl = t_mid_avl / m;
		
        printf("%8d       %4I64d      %4I64d       %5I64d       %6I64d\n", i, t_mid, t_mid_avl, t_mid_hash, t_mid_arr);
        while(root)
        {
            root = delete(root, root->s);
        }
        root = NULL;
		while(root_avl)
        {
            root_avl = remove_avl(root_avl, root_avl->s);
        }
        root_avl = NULL;
		free(hash_array);
		size_hash_array = 20;
		hash_array = calloc(size_hash_array,sizeof(hash_struct));    
	}
	printf("Эффективность по пямяти(байты):\n");
	printf("|кол-во эл-ов|   дерево  |  avl дерево| hash таблица| массив|\n");
	memory = 0;
	for (int i = 2; i <= n; i *= 2)
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
    
					
			add_in_hash_array(&hash_array, string, &size_hash_array, &memory);
					
			node_avl = create_avl_node(string);
			root_avl = insert_avl(root_avl, node_avl);
	
	
            string = malloc(6);
        }
		int max_coll = -1;
		max_compare(hash_array, size_hash_array, &max_coll);
		
		printf("%8d       %7I64d      %7I64d       %5I64d       %6I64d   h = %d    us= %d  avl=  %d\n", i, i*sizeof(tree_node), i*sizeof(avl_tree), memory, i*sizeof(char *), max_coll+1, find_high(root)+1, find_high(root_avl)+1);
	}	
}


int main(void)
{
    tree_node *root = NULL;
    avl_tree *root_avl = NULL;
    avl_tree *node_avl = NULL;
	avl_tree *tmp_avl = NULL;
    tree_node *tmpp = NULL;
	int memory = 0;
    tree_node *node;
	
	int size_hash_array = 20;
    hash_struct **hash_array = calloc(size_hash_array,sizeof(hash_struct));
	
	
	
    unsigned long long tb, te, t_mid;
    
    char *string = malloc(SIZE_BUF);
    
    int n = 0;
    char **words = NULL;
    int ind = 0;
    
    setbuf(stdout,NULL); 
    while(1)
    {
        printf("\nПрограмма ищет количество слов в файле, начинающихся на определенную букву\n");
        printf("Меню:\n");
        printf("1 - заполнить хэш-таблицу, обычное и avl-дерево из файла\n");
        printf("2 - добавить элемент в структуры(хэш-таблица обычное и avl дерево)\n");
        printf("3 - удалить элемент из всех структур\n");
        printf("4 - вывести элементы обычного дерева и avl дерева\n");
        printf("5 - вывести hash таблицу\n");
        printf("6 - очистить данные из всех структур(хэш-таблица обычное и avl дерево)\n");
        printf("7 - поиск по слову\n");
        printf("8 - вывести эффективность\n\n");
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
					
					add_in_hash_array(&hash_array, words[i], &size_hash_array, &memory);
					
					node_avl = create_avl_node(words[i]);
					root_avl = insert_avl(root_avl, node_avl);
                }
				fclose(f);
                printf("Структуры заполнены!\n");
				printf("Максимальное количество сравнений:\n");
				printf("Обычное дерево = %d \n", find_high(root)+1);
				printf("Avl дерево = %d \n", find_high_avl(root_avl)+1);
				
				int max_coll = 0;
				max_compare(hash_array, size_hash_array, &max_coll);
				printf("hash таблица = %d\n", max_coll+1);
				

            }            
            else if (choose == 2)
            {
                char *str = malloc(SIZE_BUF);
                printf("Введите слово: ");
                scanf("%s",str);
                fflush(stdin);
				
                node = create_node(str);
                root = insert(root, node);
                
				add_in_hash_array(&hash_array, str, &size_hash_array, &memory);
					
				node_avl = create_avl_node(str);
				root_avl = insert_avl(root_avl, node_avl);
				
                printf("Элемент добавлен!\n");
            }
            else if (choose == 3)
            {
                if (!root)
                {
                    printf("Структуры пусты!\n");
                    continue;
                }
                char *str_del = malloc(SIZE_BUF);
                printf("Введите слово: ");
                scanf("%s",str_del);
                fflush(stdin);
                
                tree_node* search_node = search(root, str_del); // удаление
                avl_tree* search_node_avl = search_avl(root_avl, str_del); // удаление
                if (!search_node)
                {
                    printf("Такого слова в нет!\n");
                    break;
                }
                while (search_node)    
                {
                    root = delete(root, str_del);
                    search_node = search(root, str_del);
                }
				while (search_node_avl)    
                {
                    root_avl = remove_avl(root_avl, str_del);
                    search_node_avl = search_avl(root_avl, str_del);
                }
				del_in_hash_array(hash_array, str_del, &size_hash_array);
				
				
                if (!root)
                    printf("Структуры пусты!\n");
                else
                    printf("Элемент удален!\n");
            }
            else if (choose == 4)
            {
                if (!root)
                {
                    printf("Деревья пусты!\n");
                }
                else
                {
                    printf("Элементы обычного дерева:\n");
                    printf("pre order:\n");
                    apply_pre_ord(root);
                    printf("\n");
                    printf("in order:\n");
                    apply_in(root);
                    printf("\n");
                    printf("post order:\n");
                    apply_post(root);
                    printf("\n\n");
					
					printf("Элементы avl дерева:\n");
                    printf("pre order:\n");
                    apply_pre_ord_avl(root_avl);
                    printf("\n");
                    printf("in order:\n");
                    apply_in_avl(root_avl);
                    printf("\n");
                    printf("post order:\n");
                    apply_post_avl(root_avl);
                    printf("\n");					
                    {
						FILE *f = fopen("res.gv", "w");
						FILE *f2 = fopen("res_avl.gv", "w");
						assert(f);
				
						export_to_dot(f, "test_tree", root);
						export_to_dot_avl(f2, "test_tree_avl", root_avl);
						
						fclose(f);
						fclose(f2);
					} 
                    printf("\nВ файле res.gv записано дерево на языке DOT\n");
                    printf("В файле res_avl.gv записано avl дерево на языке DOT\n");
                }
            }
			else if (choose == 5)
            {
				
				int max_coll = -1;
				printf_hash_table(hash_array, size_hash_array, &max_coll); 
				memory += size_hash_array*sizeof(hash_array);
				printf("words = %d  collisions = %d array_size = %d memory = %d\n",n, max_coll, size_hash_array, memory);
			}
            else if (choose == 6)
            {
                while(root)
                {
                    root = delete(root, root->s);
                }
				while(root_avl)
                {
                    root_avl = remove_avl(root_avl, root_avl->s);
                }
				size_hash_array = 3000;
				free(hash_array);
				hash_array = calloc(size_hash_array,sizeof(hash_struct));
				
                printf("Структуры очищены!\n");
            }
			else if (choose == 7)
            {
                char *str1 = malloc(SIZE_BUF);
                printf("Введите слово: ");
                scanf("%s",str1);
                fflush(stdin);
				
				char *ss;
				int kol = 100;
				t_mid = 0;
				for(int i = 0; i < kol; i++)
				{
					tb = tick();
					ss = find_in_hash(hash_array, str1, size_hash_array);
					te = tick();
					t_mid += (te - tb);
				}
				if (ss)
					printf("[Хэш таблица] слово: %s время: %I64d\n",ss, t_mid/kol );
				else
					printf("Такого слова нет в таблице\n");
				t_mid = 0;
				for(int i = 0; i < kol; i++)
				{
					tb = tick();
					tmpp = search(root, str1);
					te = tick();
					t_mid += (te - tb);
				}
				if (tmpp)
				{
					ss = tmpp->s;
					printf("[Обычное дерево] слово: %s время: %I64d\n", ss, t_mid/kol );
				}
				else
					printf("Такого слова нет в обычном дереве\n");
				t_mid = 0;
				for(int i = 0; i < kol; i++)
				{
					tb = tick();
					tmp_avl = search_avl(root_avl, str1);
					te = tick();
					t_mid += (te - tb);
				}
				if (tmp_avl)
				{
					ss = tmp_avl->s;
					printf("[Avl дерево] слово: %s время: %I64d\n", ss, t_mid/kol );
				}
				else
					printf("Такого слова нет в avl дереве\n");
				
            }
            else if (choose == 8)
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
