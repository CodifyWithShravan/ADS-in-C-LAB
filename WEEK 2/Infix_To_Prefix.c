#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Stack structure
typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

// Initializes stack
void initialize(Stack *s) {
    s->top = -1;
}

// Checks if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Pushes an item
void push(Stack *s, char value) {
    if (s->top >= MAX_SIZE - 1) {
        printf("Stack Overflow!\n");
        exit(1);
    }
    s->items[++s->top] = value;
}

// Pops an item
char pop(Stack *s) {
    if (isEmpty(s)) {
        return '\0'; // Return null char on underflow
    }
    return s->items[s->top--];
}

// Peeks at the top item
char peek(Stack *s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

// Gets operator precedence
int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
    }
    return 0;
}

// Reverses a string
void reverseString(char *str) {
    int length = strlen(str);
    for (int i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// Converts infix to prefix
void infixToPrefix(char *infix, char *prefix) {
    Stack s;
    initialize(&s);
    char reversedInfix[MAX_SIZE];
    char tempPostfix[MAX_SIZE];
    int i, j = 0;

    // 1. Reverse the infix and swap parentheses
    strcpy(reversedInfix, infix);
    reverseString(reversedInfix);

    for (i = 0; i < strlen(reversedInfix); i++) {
        if (reversedInfix[i] == '(') {
            reversedInfix[i] = ')';
        } else if (reversedInfix[i] == ')') {
            reversedInfix[i] = '(';
        }
    }

    // 2. Convert to postfix
    for (i = 0; i < strlen(reversedInfix); i++) {
        char token = reversedInfix[i];
        if (isalnum(token)) {
            tempPostfix[j++] = token;
        } else if (token == '(') {
            push(&s, token);
        } else if (token == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                tempPostfix[j++] = pop(&s);
            }
            if (!isEmpty(&s) && peek(&s) == '(') {
                pop(&s);
            }
        } else { // Operator
            while (!isEmpty(&s) && precedence(peek(&s)) > precedence(token)) {
                tempPostfix[j++] = pop(&s);
            }
            push(&s, token);
        }
    }

    while (!isEmpty(&s)) {
        tempPostfix[j++] = pop(&s);
    }
    tempPostfix[j] = '\0';

    // 3. Reverse the result to get prefix
    strcpy(prefix, tempPostfix);
    reverseString(prefix);
}

// Main function
int main() {
    char infixExpression[MAX_SIZE];
    char prefixExpression[MAX_SIZE];

    printf("Infix to Prefix Converter\n");
    printf("--------------------------\n");
    printf("Enter an infix expression:\n> ");
    fgets(infixExpression, MAX_SIZE, stdin);
    infixExpression[strcspn(infixExpression, "\n")] = 0;

    infixToPrefix(infixExpression, prefixExpression);

    if (strlen(prefixExpression) > 0) {
        printf("\nInfix Expression:  %s\n", infixExpression);
        printf("Prefix Expression: %s\n", prefixExpression);
    } else {
        printf("Conversion failed. Please check your expression.\n");
    }

    return 0;
}