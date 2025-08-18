#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Stack structure
struct Stack {
    char items[MAX_SIZE];
    int top;
};

// Initializes the stack
void initialize(struct Stack *s) {
    s->top = -1;
}

// Pushes an item onto the stack
void push(struct Stack *s, char item) {
    if (s->top >= MAX_SIZE - 1) {
        printf("Stack Overflow.\n");
        exit(1);
    }
    s->items[++s->top] = item;
}

// Pops an item from the stack
char pop(struct Stack *s) {
    if (s->top < 0) {
        return '\0';
    }
    return s->items[s->top--];
}

// Peeks at the top item of the stack
char peek(struct Stack *s) {
    if (s->top < 0) {
        return '\0';
    }
    return s->items[s->top];
}

// Checks if the stack is empty
int isEmpty(struct Stack *s) {
    return s->top == -1;
}

// Checks operator precedence
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
    }
    return 0; // For operands and parentheses
}

// Converts infix to postfix expression
void infixToPostfix(char* infix, char* postfix) {
    struct Stack s;
    initialize(&s);
    int i, j;
    i = j = 0;

    while (infix[i] != '\0') {
        char token = infix[i];

        if (isalnum(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(&s, token);
        } else if (token == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            if (!isEmpty(&s) && peek(&s) == '(') {
                pop(&s); // Pop '('
            }
        } else { // Operator
            while (!isEmpty(&s) && precedence(token) <= precedence(peek(&s)) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            push(&s, token);
        }
        i++;
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter an infix expression:\n> ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("\nInfix Expression: %s\n", infix);
    printf("Postfix Expression: %s\n", postfix);

    return 0;
}