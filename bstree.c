#include "bstree.h"
#include <assert.h>


// TODO: Implement
typedef struct node node;
typedef struct bstree bstree;

struct node{
    int value;
    node* leftNode;
    node* rightNode;
};


struct bstree{
    node* root;
    size_t size;
};



/**
 * Creates and returns a new binary tree.
 * Must be deallocated by bstree_destroy.
 */
bstree* bstree_create(){
    bstree* tree = malloc(sizeof(bstree));
    tree->root = NULL;
    tree->size = 0;
    return tree;
};

static bool find_node(node* n,int d){
    if(n == NULL){
        return false;
    }
    if(n->value == d){
        return true;
    }
    return(find_node(n->leftNode,d) || find_node(n->rightNode,d) );
}

/**
 * Returns true if the given tree 't' contains 'd', false otherwise.
 */
bool bstree_contains(const bstree* t, int d){
    if(t->root == NULL){
        return false;
    }
    return(find_node(t->root,d));

}



static void free_node(node* n){
    if(n->leftNode != NULL){
        free_node(n->leftNode);
    }
    if(n->rightNode != NULL){
        free_node(n->rightNode);
    }
    free(n);
}

/**
 * Destroys and deallocates all memory for the given tree 't'
 */
void bstree_destroy(bstree* t){
    node* root = t->root;
    free_node(root);
    free(t);    
};

void insert_node(node* n,int d){
    if(n->value == d){
        return;
    }
    if(n->value > d){
        if(n->leftNode == NULL){
            node* new = malloc(sizeof(node));
            new->value = d;
            new->leftNode = NULL;
            new->rightNode = NULL;
            n->leftNode = new;
            return;
        }
        insert_node(n->leftNode,d);        
    }
    else
    {
        if(n->rightNode == NULL){
            node* new = malloc(sizeof(node));
            new->value = d;
            new->leftNode = NULL;
            new->rightNode = NULL;
            n->rightNode = new;
            return;
        }
        insert_node(n->rightNode,d);  
    }    
}

node* minimum_node(node* n){
    if(n->leftNode == NULL){
        return n;
    }
    return minimum_node(n->leftNode);
}

node* maximum_node(node* n){
    if(n->rightNode == NULL){
        return n;
    }
    return maximum_node(n->rightNode);
}

/**
 * Returns the smallest number in tree 't'.
 */
int bstree_minimum(const bstree* t){
    if(t->root == NULL){
        return 0;
    }
    node* minNode = minimum_node(t->root);
    return minNode->value;
}


/**
 * Returns the largest number in tree 't'.
 */
int bstree_maximum(const bstree* t){
    if(t->root == NULL){
        return 0;
    }
    node* maxNode = maximum_node(t->root);
    return maxNode->value;
}

/**
 * Returns the number of elements of the given bstree 't'.
 * NOTE: should complete in O(1) time.
 */
size_t bstree_size(const bstree* t){
    return t->size;
};

/**
 * Inserts the given number 'd' into tree 't'.
 * if the number is already in 't', no changes are made.
 */
void bstree_insert(bstree* t, int d){
    if(!bstree_contains(t,d)){
        t->size++;
        if(t->root == NULL){
            node* new = malloc(sizeof(node));
            new->value = d;
            new->leftNode = NULL;
            new->rightNode = NULL;
            t->root = new;
            return;
        }
        insert_node(t->root,d);
    }
};

static bool remove_node(node* p,int d){
    if(p == NULL){
        return false;
    }
    if(p->value > d){
        if(remove_node(p->leftNode,d)){
            free(p->leftNode);
            p->leftNode = NULL;
        }
        return false;
    }
    if(p->value < d){
        if(remove_node(p->rightNode,d)){
            free(p->rightNode);
            p->rightNode = NULL;
        }
        return false;
    }
    else{
        if(p->leftNode == NULL && p->rightNode == NULL){
            p = NULL;
            free(p);
            return true;
        }
        if(p->leftNode != NULL && p->rightNode != NULL){
            node* ersatz = maximum_node(p->leftNode);
            int newValue = ersatz->value;
            if(remove_node(p->leftNode,newValue)){
                free(p->leftNode);
                p->leftNode = NULL;
            }
            p->value = newValue;
            return false;
        }
        else
        {
            if(p->leftNode != NULL){
                p->value = p->leftNode->value;
                p->rightNode = p->leftNode->rightNode;
                node* leftn = p->leftNode;
                p->leftNode = p->leftNode->leftNode;
                free(leftn);
                return false;
            }
            else{
                p->value = p->rightNode->value;
                p->leftNode = p->rightNode->leftNode;
                node* rightn = p->rightNode;
                p->rightNode = p->rightNode->rightNode;
                free(rightn);
                return false;
            }
        }
        
    }
}
/**
 * Removes the given number 'd' from tree 't'.
 */
void bstree_remove(bstree* t, int d){
    if(bstree_contains(t,d)){
        t->size--;
        remove_node(t->root,d);
    }
}

static void print_node(FILE* out,node* n){
    if(n!= NULL){
        fprintf(out,"(");
        print_node(out,n->leftNode);
        fprintf(out," %d ",n->value);
        print_node(out,n->rightNode);
        fprintf(out,")");
    }
}

/**
 * Prints the given bstree 't' to the supplied output stream 'out'
 * output format: ([LEFT], VAL, [RIGHT]) : [SIZE]
 * example empty: ( NIL ) : 0
 * example 3,4,7 in a balanced tree: ((3), 4, (7)) : 3
 */
void bstree_print(const bstree* t, FILE* out){
    print_node(out,t->root);
    fprintf(out,"\n");
};



int main()
{
bstree* ta = bstree_create();

	assert(bstree_size(ta) == 0);
	assert(bstree_contains(ta, 4) == false);
	bstree_print(ta, stdout);

	bstree_insert(ta, 4);
	bstree_insert(ta, 7);
	bstree_insert(ta, 3);

	assert(bstree_size(ta) == 3);
	assert(bstree_contains(ta, 4) == true);
	assert(bstree_minimum(ta) == 3);
	assert(bstree_maximum(ta) == 7);
	bstree_print(ta, stdout);

	bstree_remove(ta, 4);

	assert(bstree_size(ta) == 2);
	assert(bstree_contains(ta, 4) == false);
	assert(bstree_minimum(ta) == 3);
	assert(bstree_maximum(ta) == 7);
	bstree_print(ta, stdout);

	bstree_insert(ta, 2);
	bstree_insert(ta, -3);
	bstree_insert(ta, 6);
	bstree_insert(ta, 9);

	assert(bstree_size(ta) == 6);
	bstree_print(ta, stdout);

	bstree_remove(ta, 6);

	assert(bstree_size(ta) == 5);
	assert(bstree_contains(ta, 6) == false);
	bstree_print(ta, stdout);

	bstree_insert(ta, 5);
	bstree_insert(ta, 5);

	assert(bstree_size(ta) == 6);
	assert(bstree_contains(ta, 5) == true);
	bstree_print(ta, stdout);

	bstree_insert(ta, 6);
	bstree_insert(ta, 4);
	bstree_remove(ta, 7);
	bstree_remove(ta, 7);

	assert(bstree_size(ta) == 7);
	assert(bstree_contains(ta, 7) == false);
	bstree_print(ta, stdout);

	bstree_destroy(ta);
}
