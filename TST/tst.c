#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tst.h"

/* ############### TST FUNCTIONS #################
 These comprise the public interface for our TST
 ################################################ */

/* insert_tst is an idempotent function.
 * returns 1 if str was inserted into tree successfully,
 otherwise returns 0.
 * invokes _insert to insert word into internal tree. */
struct TSTnode** getRightMostNode(struct TSTnode** tree);
int restructNode(struct TSTnode** tree);

int insert_tst(struct TSTnode** tree, const char* str) {
    if(search_tst(*tree, str)){
        return 1;
    }
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
    if (search_tst(*tree, str) && str) {
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
    if(*tree != NULL){
        clear_tst(&(*tree)->left);
        clear_tst(&(*tree)->right);
        clear_tst(&(*tree)->sub);
        free(*tree);
        *tree = NULL;
    }
}

/* ############### TRIE NODE FUNCTIONS #################
 These functions internally implement TST's public interface
 ##################################################### */

/* new_node returns a new node with provided character */
struct TSTnode* new_tst_node(char self) {
    // TODO: TST #1
    struct TSTnode* node = (struct TSTnode*)calloc(1,sizeof(struct TSTnode));
    if(!node){
        allocation_failed();
        return 0;
    }
    node->self = self;
    return node;
}

/* _insert inserts the string str (starting from character at $position into
 tst node @tree. A leaf TSTnode should have a copy of the inserted str
 * Returns 1 if the insertion was successful, otherwise returns 0. */
int _insert(struct TSTnode** tree, const char* str, int position) {
    //condition check start
    if(position >= strlen(str) || position < 0 || !str){
        return 0;
    }//condition check end
    //variable setting
    char c = *(str+position);//end of variable setting
    //check for new node insertion and wording
    if(!*tree){
        *tree = new_tst_node(c);
    }
    char s = (*tree)->self;
    if(!*(str+position+1) && s == c){
        (*tree)->word = str;
        return 1;
    }//end of check new node insertion and wording
    //start of navigating
    if(s == c){
        return _insert(&((*tree)->sub), str, position+1);
    }else if(s < c){
        return _insert(&((*tree)->right), str, position);
    }else{
        return _insert(&((*tree)->left), str, position);
    }//end of navigating
}

int _delete(struct TSTnode** tree, const char* str) {
    int flag = 1;
    if (*str < (*tree)->self)
        flag = _delete(&(*tree)->left, str);
    else if (*str > (*tree)->self)
        flag = _delete(&(*tree)->right, str);
    else if (*(str+1))
        flag = _delete(&(*tree)->sub, str+1);
    else {
        printf("delete:word ends at %s\n",(*tree)->word);
        (*tree)->word = 0;//"delete" the word
        flag = 2;
    }
    struct TSTnode** r = &(*tree)->right;//helper variables
    struct TSTnode** l = &(*tree)->left;
    struct TSTnode** s = &(*tree)->sub;
    if(!*s && !(*tree)->word){//formatting which takes place everytime
        if(*l && *r){
            if((*l)->right){
                struct TSTnode** n = getRightMostNode(l);
                *tree = (*n)->right;
                (*n)->right = (*n)->right->left;
                (*tree)->right = *r;
                (*tree)->left = *l;
            }else{
                _clear(*tree);
                *tree = *l;
                (*tree)->right = *r;
            }
        }else if(*l && !*r){
            _clear(*tree);
            *tree = *l;
        }else if(!*l && *r){
            _clear(*tree);
            *tree = *r;
        }
    }
    if(flag == 2){//initiating the world's most difficult algorithm edit:or so it was
        if(!*l && !*r && (*tree)->self == *str && !(*tree)->word){
            clear_tst(tree);
            return 2;//character deletion complete may have more to delete
        }else{
            return 1;//hit worded node and have no right and left, program may exit
        }
    }
    return flag;
}

struct TSTnode** getRightMostNode(struct TSTnode** tree){
    if(!((*tree)->right))
        return tree;
    if((*tree)->right && !(*tree)->right->right){
        return (tree);
    }
    return getRightMostNode(&((*tree)->right));
}

void _clear(struct TSTnode* node) {
    free(node);
    node = 0;
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


