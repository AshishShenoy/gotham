#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node;

union NodeVal {
    int i;
    float f;
    char str[100];
    char name[100];
    char b;
    char op[5];
    struct node* n;
};

typedef struct node {
    int type;
    union NodeVal value;
    struct node* lop;
    struct node* rop;
} Node;

Node* makeNode(int type, union NodeVal value, Node* lop, Node* rop);
int seqLen(Node* seq);

int yylex();

void yyerror(const char* error);
