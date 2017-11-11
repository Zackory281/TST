#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tst.h"

int _test_deletion2() {
    fprintf(stderr, "Testing TST Exhaust Test by Zackory C . . .");
    struct TSTnode* tree = NULL;
    int i,ds = 33,l;
    char* words[33] = {
        "mmm", "mmn", "mml", "mlm", "mln", "mll", "mnl", "mnn", "mnm",
        "nmm", "nmn", "nml", "nlm", "nln", "nll", "nnl", "nnn", "nnm",
        "lmm", "lmn", "lml", "llm", "lln", "lll", "lnl", "lnn", "lnm",
        "ll", "mm", "nn", "l", "m", "n",
        
    };
    for(int l=0;l<9999;l++)//testing memory dump
        for (i = 0; i < ds; i++) {
            if (insert_tst(&tree, words[i]) == 0) {
                fprintf(stderr, "\nFailed: unexpected failure in inserting %s\n", words[i]);
                return 0;
            }
        }
    for (i = 0; i < ds; i++) {
        if (!search_tst(tree, words[i])) {
            fprintf(stderr, "\nFailed: unexpected failure in searching %s\n", words[i]);
            return 0;
        }
    }
    char* deleteOrder[33] = {
        "lmm", "lmn", "lml", "llm", "lln", "lll", "lnl", "lnn", "lnm",
        "nmm", "nmn", "nml", "nlm", "nln", "nll", "nnl", "nnn", "nnm",
        "mmm", "mmn", "mml", "mlm", "mln", "mll", "mnl", "mnn", "mnm",
        "ll", "mm", "nn", "l", "m", "n",
    };
    for (i = 0; i < ds; i++) {
        if (!delete_tst(&tree, deleteOrder[i])) {
            fprintf(stderr, "\nFailed: unexpected failure in deleting %s\n", deleteOrder[i]);
            return 0;
        }
    }
    for (i = 0; i < ds; i++) {
        if (search_tst(tree, words[i])) {
            fprintf(stderr, "\nFailed: unexpected success in searching %s\n", deleteOrder[i]);
            return 0;
        }
    }
    fprintf(stderr, "OK\n");
    return 1;
}

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
    }
    fprintf(stderr, "OK\n");
    return 1;
}

int test() {
    struct TSTnode* tree = NULL;
    int i;
    
    char* words[10] = {"hello", "world", "welcome", "to", "computer", "science",
        "class", "at", "berkeley", "woohoo"};
    
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
    fprintf(stderr, "OK\n\n");
    
    return _test_deletion() && _test_deletion2(); // UnComment this line if you would like to test your delete_tst
    return 1;
}

int main(int argc, char const *argv[]){
    if (test())
        fprintf(stderr, "PASS\n");
    else
        fprintf(stderr, "Test Failed.\n");
    
    return 0;
}


