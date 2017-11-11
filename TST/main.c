#include <stdlib.h>
#include <stdio.h>
#include "tst.h"

int _test_deletion() {
    fprintf(stderr, "Testing Tree Deletion . . .");
    struct TSTnode* tree = NULL;
    int i;
    char* words[12] = {"ppp", "ddd", "hhh", "ggg", "jjj", "ccc", "bbb", "aaa", "ttt", "rrr", "qqq", "xxx"};
    for (i = 0; i < 12; i++) {
        if (insert_tst(&tree, words[i]) == 0) {
            fprintf(stderr, "\nFailed: unexpected failure in inserting %s\n", words[i]);
            return 0;
        }
    }
    char* deleteOrder[12] = {"ppp", "jjj", "hhh", "ggg", "ttt", "rrr", "ddd", "ccc", "xxx", "bbb", "aaa", "qqq"};
    if (!delete_tst(&tree, deleteOrder[0])) {
        fprintf(stderr, "\nFailed: unexpected failure in deleting %s\n", deleteOrder[0]);
        return 0;
    }
    // testing structure
    if (!tree) {
        fprintf(stderr, "\nFailed: tree root node should not be NULL!\n");
        return 0;
    }
    if (tree->self != 'j') {
        fprintf(stderr, "\nFailed: Your tree should root at \"j\"\n");
        return 0;
    }
    if (!tree->left || tree->left->self != 'd') {
        fprintf(stderr, "\nFailed: Root expect  \"d\" to be its direct left child.\n");
        return 0;
    }
    if (!tree->left->right || tree->left->right->right) {
        fprintf(stderr, "\nFailed: old parent of root should reset its pointer.\n");
        return 0;
    }
    for (i = 1; i < 12; i++) {
        if (!delete_tst(&tree, deleteOrder[i])) {
            fprintf(stderr, "\nFailed: unexpected failure in deleting %s\n", deleteOrder[i]);
            return 0;
        }
        else if (search_tst(tree, deleteOrder[i]))
            return 0;
    }
    fprintf(stderr, "OK\n");
    return 1;
}

int test() {
    struct TSTnode* tree = NULL;
    int i;
    
    char* words[10] = {"hello", "world", "welcome", "to", "computer", "science",
        "class", "at","berkeley", "woohoo"};
    
    fprintf(stderr, "Testing TST Insertion . . .");
    for (int i = 0; i < 10; i++) {
        if (insert_tst(&tree, words[i]) == 0) {
            fprintf(stderr, "unexpected failure in inserting %s\n", words[i]);
            return 0;
        }
    }
    fprintf(stderr, "OK\n");
    
    fprintf(stderr, "Testing TST Search . . .");
    for (i = 0; i < 10; i++) {
        if (!search_tst(tree, words[i])) {
            fprintf(stderr, "unexpected failure in searching %s\n", words[i]);
            return 0;
        }
    }
    fprintf(stderr, "OK\n");
    
    fprintf(stderr, "Testing TST Prefix . . .");
    char* good_prefix_tstes[10] = {"he", "wor", "we", "to", "com", "scienc", "cla", "a", "ber", "woo"};
    for (i = 0; i < 10; i++) {
        if (prefix_tst(tree, good_prefix_tstes[i]) == 0) {
            fprintf(stderr, "unexpected failure in looking for prefix %s!\n", good_prefix_tstes[i]);
            return 0;
        }
    }
    fprintf(stderr, "OK\n");
    
    fprintf(stderr, "Testing Clearing TST . . .");
    clear_tst(&tree);
    for (i = 0; i < 10; i++) {
        if (search_tst(tree, words[i])) {
            fprintf(stderr, "unexpected success in searching %s\n", words[i]);
            return 0;
        }
    }
    fprintf(stderr, "OK\n");
    
    if (!_test_deletion()) // UnComment this line if you would like to test your delete_tst
        return 0;
    clear_tst(&tree);
    _insert(&tree,"p",0);
    print(tree);fprintf(stderr,"\n");
    _insert(&tree,"b",0);
    print(tree);fprintf(stderr,"\n");
    _insert(&tree,"d",0);
    print(tree);fprintf(stderr,"\n");
    _delete(&tree,"p");
    print(tree);fprintf(stderr,"\n");
    _delete(&tree,"d");
    print(tree);fprintf(stderr,"\n");
    
    clear_tst(&tree);
    _insert(&tree,"b",0);
    print(tree);fprintf(stderr,"\n");
    _insert(&tree,"p",0);
    print(tree);fprintf(stderr,"\n");
    // _delete(&tree,"b");
    //print(tree);fprintf(stderr,"\n");
    
    return 1;
}

int main(int argc, char const *argv[]){
    if (test())
        fprintf(stderr, "\nPASS\n");
    else
        fprintf(stderr, "Test Failed.\n");
    
    
    return 0;
}
