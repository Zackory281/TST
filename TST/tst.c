#include <stdio.h>
#include <stdlib.h>
#include "tst.h"

void restructure(struct TSTnode** tree);
void print(struct TSTnode* tree);
/* ############### TST FUNCTIONS #################
 These comprise the public interface for our TST
 ################################################ */

/* insert_tst is an idempotent function.
 * returns 1 if str was inserted into tree successfully,
 otherwise returns 0.
 * invokes _insert to insert word into internal tree. */
int insert_tst(struct TSTnode** tree, const char* str) {
    return _insert(tree, str, 0);
}

/* search_tst returns 1 if word is in tree, otherwise 0. */
int search_tst(struct TSTnode* tree, const char* str) {
    if (!tree)
        return 0;
    if (*str < tree->self)
        return search_tst(tree->left, str);
    else if (*str > tree->self)
        return search_tst(tree->right, str);
    else if (*(str+1))
        return search_tst(tree->sub, str+1);
    else {
        return tree->word != NULL;
    }
}

/* delete_tst returns 1 if str was deleted from tree successfully,
 returns 0 if encounter any error, such as str does not exist.
 * should invoke _delete to delete str from internal tree. */
int delete_tst(struct TSTnode** tree, const char* str) {
    if (search_tst(*tree, str)) {
        return _delete(tree, str);
    }
    return 0;
}

/* prefix_tst returns 1 if pre exists in tree, 0 otherwise */
int prefix_tst(struct TSTnode* tree, const char* pre) {
    if (!tree)
        return 0;
    if (*pre < tree->self)
        return prefix_tst(tree->left, pre);
    else if (*pre > tree->self)
        return prefix_tst(tree->right, pre);
    else if (*(pre+1))
        return prefix_tst(tree->sub, pre+1);
    else
        return 1;
}

/* clear_tst frees entire tree
 * Remember to set old TSTnode pointer to NULL */
void clear_tst(struct TSTnode** tree) {
    // TODO: TST #4
    if ((*tree)->left)
        clear_tst(&((*tree)->left));
    if ((*tree)->sub)
        clear_tst(&((*tree)->sub));
    if ((*tree)->right)
        clear_tst(&((*tree)->right));
    else
    {
        free(*tree);
        *tree = 0;
    }
}


/* ############### TRIE NODE FUNCTIONS #################
 These functions internally implement TST's public interface
 ##################################################### */

/* new_node returns a new node with provided character */
struct TSTnode* new_tst_node(char self) {
    // TODO: TST #1
    struct TSTnode* newNode = (struct TSTnode*) calloc(1,sizeof(struct TSTnode));
    newNode->self=self;
    return newNode;
}

/* _insert inserts the string str (starting from character at $position into
 tst node @tree. A leaf TSTnode should have a copy of the inserted str
 * Returns 1 if the insertion was successful, otherwise returns 0. */
int _insert(struct TSTnode** tree, const char* str, int position) {
    // TODO: TST #2
    // Hint: to copy a string, use strcpy
    if(*tree)    printf("the current self (we are inside insert) is: %c,position is %d\n",(*tree)->self,position);
    else
        fprintf(stderr,"there is no self, the tree was a lai\n");
    if (!str[position])
        return 1;
    else if (!(*tree))
    {
        *tree = new_tst_node(str[position]);
        return _insert(tree,str,position);
    }
    else if ((*tree)->self == str[position])
    {
        if (!str[position+1]){
            (*tree)->word = str;
            printf("inside insert inserting the word: %s\n",str);
            return 1;
        }
        return _insert(&((*tree)->sub),str,position+1);
    }
    else if ((*tree)->self > str[position])
        return _insert(&((*tree)->left),str,position);
    else if ((*tree)->self < str[position])
        return _insert(&((*tree)->right),str,position);
    else
        return 0;
}

/* _delete deletes the string str from tst tree
 * Return 1 if the deletion was successful,
 * otherwise returns 0. */
int _delete(struct TSTnode** tree, const char* str) {
    int flag = 0;
    if (!tree)
        flag = 0;
    if (*str < (*tree)->self)
        flag = _delete(&(*tree)->left, str);
    else if (*str > (*tree)->self)
        flag = _delete(&(*tree)->right, str);
    else if (*(str+1))
        flag = _delete(&(*tree)->sub, str+1);
    else {
        printf("horray we are at the end of a word and the word is: %s\n",(*tree)->word);
        flag = 2;
    }
    struct TSTnode* right = (*tree)->right;
    struct TSTnode* left = (*tree)->left;
    struct TSTnode* sub = (*tree)->sub;
    //restructure:always called can modifying the tree without obstructing existing words
    if(!(*tree)->word && !sub){
        if(right && left){
            //TODO-perform difficult algorithmic restructring function
        }else if(right && !left){
            //TODO-replace tree with right
        }else if(!right && left){
            //TODO-replace tree with left
        }
    }
    //deletion: only called when flag is 2
    if(flag == 2){
        if(!(*tree)->word && !sub && (*tree)->self == *str && !right && !left){
            //TODO-delete this(tree) node
        }else{
            flag = 1;
        }
    }
    return flag;
}

void restructure(struct TSTnode** tree)
{
    struct TSTnode** newNode;
    if ((*tree)->left)
    {
        newNode = &((*tree)->left);
        if (! ((*newNode)->right))
        {
            (*newNode)->right = (*tree)->right;
            free(*tree);
            **tree = **newNode;
        }
        else
        {
            while ((*newNode)->right)
                newNode = &((*newNode)->right);
            (*newNode)->right = (*tree)->right;
            if (! ((*newNode)->left) )
            {
                (*newNode)->left = (*tree)->left;
                free(*tree);
                **tree = **newNode;
                *newNode = 0;
            }
            else
            {
                struct TSTnode* newerNode = &(*((*newNode)->left));
                (*newNode)->left = (*tree)->left;
                **tree = **newNode;
                //free(*tree);
                *tree = NULL;
                *newNode = newerNode;
            }
        }
    }
    else
    {
        newNode = &((*tree)->right);
        if (! ((*tree)->right) )
        {
            free(*tree);
            **tree = **newNode;
        }
        else if (! ((*newNode)->left))
        {
            (*newNode)->left = (*tree)->left;
            free(*tree);
            **tree = **newNode;
        }
        else
        {
            while ((*newNode)->left)
                newNode = &((*newNode)->left);
            (*newNode)->left = (*tree)->left;
            if (! ((*newNode)->sub) )
            {
                (*newNode)->sub = (*tree)->right;
                free(*tree);
                **tree = **newNode;
                *newNode = 0;
            }
            else if (! ((*newNode)->right) )
            {
                (*newNode)->right = (*tree)->right;
                free(*tree);
                **tree = **newNode;
                *newNode = 0;
            }
            else
            {
                struct TSTnode* newerNode = &(*((*newNode)->right));
                (*newNode)->right = (*tree)->right;
                free(*tree);
                **tree = **newNode;
                *newNode = newerNode;
            }
        }
    }
}
void _clear(struct TSTnode* node) {
    // TODO: TST #4helper
    // You may or may not need to use this function.
    
    
}

/* ############### HELPER FUNCTIONS ####################
 These functions you may find useful for helping to
 implement other functions.
 ##################################################### */

/* allocation_failed gets invoked when memroy allocation fails */
int allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    return 0;
}

void print(struct TSTnode* tree)
{
    if (!tree)
        return;
    printf("the current self is: %c\n",(tree)->self);
    return;
    fprintf(stderr,"node %c {",tree->self);
    if (tree->left)
    {
        fprintf(stderr, " left: ");
        print(tree->left);
    }
    else
        fprintf(stderr," left: 0");
    if (tree->sub)
    {
        fprintf(stderr, " sub: ");
        print(tree->sub);
    }
    else
        fprintf(stderr," sub: 0");
    if (tree->right)
    {
        fprintf(stderr, " right: ");
        print(tree->right);
        fprintf(stderr, "} ");
    }
    else
        fprintf(stderr," right: 0}");
}
