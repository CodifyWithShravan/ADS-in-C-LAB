#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a maximum size for the stack and the input expression
#define MAX_SIZE 100

// A structure to represent the stack
struct Stack {
    int top;
    char items[MAX_SIZE];
};

// Function to initialize the stack
void initialize(struct Stack *s) {
    s->top = -1;
}

// Function to check if the stack is empty
// Returns 1 if empty, 0 otherwise
int isEmpty(struct Stack *s) {
    return s->top == -1;
}

// Function to push an item onto the stack
void push(struct Stack *s, char value) {
    // Check for stack overflow
    if (s->top == MAX_SIZE - 1) {
        printf("Error: Stack Overflow\n");
        exit(1); // Exit if the stack is full
    }
    // Increment top and add the item
    s->items[++(s->top)] = value;
}

// Function to pop an item from the stack
// Returns the popped character
char pop(struct Stack *s) {
    // Check for stack underflow
    if (isEmpty(s)) {
        // This is a key part of the logic: if we try to pop for a closing
        // bracket and the stack is empty, it's unbalanced.
        // Returning a null character helps identify this.
        return '\0'; 
    }
    // Return the top item and decrement top
    return s->items[(s->top)--];
}

// Function to check if a pair of brackets match
// Takes the opening bracket from the stack and the closing from the expression
// Returns 1 if they match, 0 otherwise
int doBracketsMatch(char openBracket, char closeBracket) {
    if (openBracket == '(' && closeBracket == ')')
        return 1;
    else if (openBracket == '{' && closeBracket == '}')
        return 1;
    else if (openBracket == '[' && closeBracket == ']')
        return 1;
    else
        return 0;
}

// The main function to check for balanced parentheses in an expression
// Returns 1 if balanced, 0 if not
int areBracketsBalanced(char exp[]) {
    struct Stack s;
    initialize(&s);
    int i = 0;

    // Traverse the expression character by character
    while (exp[i]) {
        // If the character is an opening bracket, push it onto the stack
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[') {
            push(&s, exp[i]);
        }

        // If the character is a closing bracket, check the stack
        if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            // Pop the top of the stack and check if it's the matching pair.
            // If pop() returns '\0' (because the stack was empty),
            // doBracketsMatch will correctly return 0.
            if (!doBracketsMatch(pop(&s), exp[i])) {
                return 0; // Not balanced
            }
        }
        i++; // Move to the next character
    }

    // After traversing the whole expression, if the stack is empty,
    // it means every opening bracket had a matching closing bracket.
    return isEmpty(&s);
}

// Main function to drive the program
int main() {
    char expression[MAX_SIZE];

    // Prompt the user to enter an expression
    printf("Enter an expression to check for balanced parentheses:\n> ");

    // Read the string from the user using fgets for safety
    if (fgets(expression, sizeof(expression), stdin) != NULL) {
        // fgets includes the newline character, so we remove it
        size_t len = strlen(expression);
        if (len > 0 && expression[len - 1] == '\n') {
            expression[len - 1] = '\0';
        }

        // Check if the entered expression is balanced
        if (areBracketsBalanced(expression)) {
            printf("\nResult: The expression is balanced.\n");
        } else {
            printf("\nResult: The expression is NOT balanced.\n");
        }
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}
