#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define stack structure
#define MAX_SIZE 100

char stack[MAX_SIZE];
int top = -1;

// --- Stack Operations ---
void push(char item) {
    if (top >= MAX_SIZE - 1) {
        printf("Stack Overflow.\n");
        return;
    }
    stack[++top] = item;
}

char pop() {
    if (top < 0) {
        printf("Stack Underflow.\n");
        return -1;
    }
    return stack[top--];
}

char peek() {
    return stack[top];
}

int isEmpty() {
    return top == -1;
}

// --- Conversion Logic ---

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to determine the precedence of an operator
int precedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3; // Right-associative operator
    }
    return -1; // For parentheses
}

// Main function to convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    int i = 0; // Infix scanner
    int j = 0; // Postfix writer

    while (infix[i] != '\0') {
        char token = infix[i];

        // If the token is an operand, add it to postfix
        if (isalnum(token)) {
            postfix[j++] = token;
        }
        // If the token is '(', push it to the stack
        else if (token == '(') {
            push(token);
        }
        // If the token is ')', pop and output from the stack
        // until an '(' is encountered.
        else if (token == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            }
            if (!isEmpty() && peek() == '(') {
                pop(); // Pop the '('
            }
        }
        // If an operator is encountered
        else if (isOperator(token)) {
            // '^' is right-associative, others are left-associative
            while (!isEmpty() && precedence(token) <= precedence(peek()) && peek() != '(') {
                 postfix[j++] = pop();
            }
            push(token);
        }
        i++;
    }

    // Pop all the remaining operators from the stack
    while (!isEmpty()) {
        if(peek() == '(') { // Should not happen in a valid expression
            pop();
            continue;
        }
        postfix[j++] = pop();
    }

    postfix[j] = '\0'; // Null-terminate the postfix string
}

// --- Main Driver ---
int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Infix Expression: %s\n", infix);
    printf("Postfix Expression: %s\n", postfix);

    return 0;
}