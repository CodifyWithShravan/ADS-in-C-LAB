#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Stack structure
struct Stack {
    int top;
    char items[MAX_SIZE];
};

// Initializes a stack
void initialize(struct Stack *s) {
    s->top = -1;
}

// Pushes an item onto the stack
void push(struct Stack *s, char value) {
    if (s->top == MAX_SIZE - 1) {
        printf("Error: Stack Overflow\n");
        exit(1);
    }
    s->items[++(s->top)] = value;
}

// Pops an item from the stack
char pop(struct Stack *s) {
    if (s->top == -1) {
        return '\0';
    }
    return s->items[(s->top)--];
}

// Checks if brackets match
int doBracketsMatch(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// Checks if brackets in an expression are balanced
int areBracketsBalanced(char exp[]) {
    struct Stack s;
    initialize(&s);
    int i = 0;

    while (exp[i] != '\0') {
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[') {
            push(&s, exp[i]);
        } else if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            if (!doBracketsMatch(pop(&s), exp[i])) {
                return 0; // Mismatch or stack was empty
            }
        }
        i++;
    }

    // Return 1 if the stack is empty at the end, otherwise 0
    return s.top == -1;
}

// Main function
int main() {
    char expression[MAX_SIZE];
    printf("Enter an expression to check for balanced parentheses:\n> ");
    fgets(expression, sizeof(expression), stdin);

    // Remove the trailing newline character from fgets
    expression[strcspn(expression, "\n")] = '\0';

    if (areBracketsBalanced(expression)) {
        printf("\nResult: The expression is balanced.\n");
    } else {
        printf("\nResult: The expression is NOT balanced.\n");
    }

    return 0;
}