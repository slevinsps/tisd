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


typedef struct tree_node
{
	char *s;
	struct tree_node *left;
	struct tree_node *right;	
} tree_node;

tree_node* create_node(char *s)
{
    tree_node *node = malloc(sizeof(tree_node));
    if (node)
    {
        node->s = s;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

tree_node* insert(tree_node *tree, tree_node *node)
{
    int cmp;
    if (tree == NULL)
        return node;

    cmp = strcmp(node->s, tree->s);
	
    if (cmp < 0)
        tree->left = insert(tree->left, node);
    else if (cmp >= 0)
        tree->right = insert(tree->right, node);

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

void apply(struct tree_node *tree)
{
    if (tree == NULL)
        return;

    // pre-order
    // f(tree, arg);
	printf("%s ",tree->s);
    apply(tree->left);
    // in-order
    
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
				tree = tree->left;
			}
			else
			{
				tree = tree->right;
			}
		}
		
	}
    return tree;
}




void apply_pre(struct tree_node *tree, void (*f)(struct tree_node*, void*), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    apply_pre(tree->left, f, arg);
    apply_pre(tree->right, f, arg);
}

void to_dot(struct tree_node *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->s, tree->left->s);

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->s, tree->right->s);
}

void export_to_dot(FILE *f, const char *tree_name, struct tree_node *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    apply_pre(tree, to_dot, f);

    fprintf(f, "}\n");
}

int main(void)
{
	tree_node *root = NULL;
	tree_node *node;
	node = create_node("hello");
	root = insert(root, node);
	node = create_node("fuck");
	root = insert(root, node);
	node = create_node("everyone");
	root = insert(root, node);
	node = create_node("only");
	root = insert(root, node);
	node = create_node("somebody");
	root = insert(root, node);
	
	node = create_node("fuck");
	root = insert(root, node);
	node = create_node("fuck");
	root = insert(root, node);
	node = create_node("fuck");
	root = insert(root, node);
	node = create_node("fzck");
	root = insert(root, node);
	{
        FILE *f = fopen("test1.gv", "w");

        assert(f);

        export_to_dot(f, "test_tree", root);

        fclose(f);
    }
	tree_node* search_node = search(root, "fuck");
	while (search_node)	
	{
		root = delete(root, "fuck");
		search_node = search(root, "fuck");
	}
	
	apply(root);
	{
        FILE *f = fopen("test.gv", "w");

        assert(f);

        export_to_dot(f, "test_tree", root);

        fclose(f);
    }

	
}
