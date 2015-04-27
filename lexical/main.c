#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define IF_CODE 31
#define ELSE_CODE 32
#define WHILE_CODE 33
#define DO_CODE 34
#define INT_CODE 35
#define FLOAT_CODE 36
#define SWITCH_CODE 37




//typedef
//struct analyzer{
    int charClass;
    char lexeme [100];
    char nextChar;
    int lexLen;
    int token;
    int nextToken;
    FILE *in_fp;
//}analyzer;

void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
        //printf("valor de lexeme ");
        //printf(lexeme[lexLen]);
        //printf("\n");
    }
    else
        printf("Error - lexeme is too long \n");
}

int lookup(char ch) {
    //analyzer ann;
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            //ann.nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            //ann.nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            //ann.nextToken = ADD_OP;
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            //ann.nextToken = SUB_OP;
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            //ann.nextToken = MULT_OP;
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            //ann.nextToken = DIV_OP;
            nextToken = DIV_OP;
            break;
        default:
            addChar();
            //ann.nextToken = EOF;
            nextToken = EOF;
            break;
        }
    return nextToken;
}

bool is_special(char* word){
    int i = 0;
    while( i < length(lexeme) && isalpha(lexeme[i])){
        strcat(word,lexeme[i]);
    }

    switch(word){
        case "if":
            addChar();
            nextToken = IF_CODE;
            break;

        case "else":
            addChar();
            nextToken = ELSE_CODE;
            break;

        case "while":
            addChar();
            nextToken = WHILE_CODE;
            break;

        case "do":
            addChar();
            nextToken = DO_CODE;
            break;

        case "int":
            addChar();
            nextToken = INT_CODE;
            break;
    }

}

void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}

int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;
        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;
        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */
    printf("Next token is: %d, Next lexeme is %s\n",
    nextToken, lexeme);
    return nextToken;
} /* End of function lex */

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

main() {
/* Open the input data file and process its contents */



    if ((in_fp = fopen("front.in", "r")) == NULL)
        printf("ERROR - cannot open front.in \n");
    else {
        getChar();
        do {
            lex();
        } while (nextToken != EOF);
    }




}
