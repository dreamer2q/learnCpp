#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRCMP(a, o, b) (strcmp(a, b) o 0)

#define MAXTOKENLEN 100
#define MAXTOKENS 100

enum type_tag {
    IDENTIFIER,
    QUALIFIRE,
    TYPE
};

struct token {
    char type;
    char string[MAXTOKENLEN];
};

int index_top = -1;
struct token stack[MAXTOKENS];
struct token this;

#define top stack[index_top]
#define pop stack[index_top--]
#define push(s) (stack[++index_top] = s)

enum type_tag classify_strinig(void) {
    char* s = this.string;
    if (STRCMP(s, ==, "const")) {
        strcpy(s, "read-only");
        return QUALIFIRE;
    }
    if (STRCMP(s, ==, "volatile")) return QUALIFIRE;
    if (STRCMP(s, ==, "void")) return TYPE;
    if (STRCMP(s, ==, "char")) return TYPE;
    if (STRCMP(s, ==, "signed")) return TYPE;
    if (STRCMP(s, ==, "unsigned")) return TYPE;
    if (STRCMP(s, ==, "short")) return TYPE;
    if (STRCMP(s, ==, "int")) return TYPE;
    if (STRCMP(s, ==, "long")) return TYPE;
    if (STRCMP(s, ==, "float")) return TYPE;
    if (STRCMP(s, ==, "double")) return TYPE;
    if (STRCMP(s, ==, "struct")) return TYPE;
    if (STRCMP(s, ==, "union")) return TYPE;
    if (STRCMP(s, ==, "enum")) return TYPE;

    return IDENTIFIER;
}

void get_token(void) {
    char* p = this.string;
    while ((*p = getchar()) == ' ')
        //skip blank
        ;
    if (isalnum(*p)) {
        //A-Z,0-9
        while (isalnum(*++p = getchar()))
            //read alnum
            ;
        ungetc(*p, stdin);
        *p = '\0';
        this.type = classify_strinig();
        return;
    }
    if (*p == '*') {
        strcpy(this.string, "pointer to");
        this.type = '*';
        return;
    }
    this.string[1] = '\0';
    this.type = *p;
    return;
}

void read_to_first_identifier() {
    get_token();
    while (this.type != IDENTIFIER) {
        push(this);
        get_token();
    }
    printf("%s is ", this.string);
    get_token();
}

void deal_with_arrays() {
    while (this.type == '[') {
        printf("array ");
        get_token();
        if (isdigit(this.string[0])) {
            printf("0..%d ", atoi(this.string) - 1);
            get_token();
        }
        get_token();
        printf("of ");
    }
}

void deal_with_function_args() {
    while (this.type != ')') {
        get_token();
    }
    get_token();
    printf("function returning ");
}

void deal_with_pointer() {
    while (top.type == '*') {
        printf("%s ", pop.string);
    }
}

void deal_with_declarator() {
    switch (this.type) {
        case '[':
            deal_with_arrays();
            break;
        case '(':
            deal_with_function_args();
            break;
    }
    deal_with_pointer();

    while (index_top >= 0) {
        if (top.type == '(') {
            pop;
            get_token();
            deal_with_declarator();
        } else {
            printf("%s ", pop.string);
        }
    }
}

int main() {
    read_to_first_identifier();
    deal_with_declarator();
    printf("\n");

    return 0;
}
