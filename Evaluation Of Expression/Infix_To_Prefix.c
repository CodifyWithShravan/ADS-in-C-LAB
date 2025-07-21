#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For isalnum

#define MAX_SIZE 100 // Maximum size for expression and stack

// --- Stack Implementation ---
typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, char value) {
    if (isFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->items[++s->top] = value;
}

char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow!\n");
        return '\0'; // Return null character to indicate error
    }
    return s->items[s->top--];
}

char peek(Stack *s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

// --- Helper Functions ---

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to get the precedence of an operator
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3; // Exponentiation usually has higher precedence
        default:
            return 0; // Not an operator
    }
}

// Function to reverse a string
void reverseString(char *str) {
    int length = strlen(str);
    int i, j;
    char temp;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// Function to convert infix to prefix
void infixToPrefix(char *infix, char *prefix) {
    Stack s;
    initialize(&s);
    char reversedInfix[MAX_SIZE];
    char tempPostfix[MAX_SIZE]; // To store the postfix of the reversed infix
    int i, j = 0;

    // 1. Reverse the infix expression and swap parentheses
    strcpy(reversedInfix, infix);
    reverseString(reversedInfix);

    for (i = 0; i < strlen(reversedInfix); i++) {
        if (reversedInfix[i] == '(') {
            reversedInfix[i] = ')';
        } else if (reversedInfix[i] == ')') {
            reversedInfix[i] = '(';
        }
    }

    // 2. Convert the modified (reversed and parenthesis-swapped) infix to postfix
    for (i = 0; i < strlen(reversedInfix); i++) {
        char currentChar = reversedInfix[i];

        if (isalnum(currentChar)) { // If it's an operand (letter or digit)
            tempPostfix[j++] = currentChar;
        } else if (currentChar == '(') {
            push(&s, currentChar);
        } else if (currentChar == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                tempPostfix[j++] = pop(&s);
            }
            if (!isEmpty(&s) && peek(&s) == '(') {
                pop(&s); // Pop the '('
            } else {
                // Mismatched parentheses - this case should ideally be handled at input validation
                printf("Error: Mismatched parentheses.\n");
                return;
            }
        } else if (isOperator(currentChar)) {
            // For infix to prefix, when converting reversed infix to postfix,
            // for operators of same precedence, we pop if stack top has higher or EQUAL precedence.
            // This ensures right-to-left associativity for the original operators (which become left-to-right when reversed)
            // and correctly handles the reversal.
            while (!isEmpty(&s) && precedence(peek(&s)) > precedence(currentChar)) {
                tempPostfix[j++] = pop(&s);
            }
            push(&s, currentChar);
        }
    }

    // Pop any remaining operators from the stack
    while (!isEmpty(&s)) {
        tempPostfix[j++] = pop(&s);
    }
    tempPostfix[j] = '\0'; // Null-terminate the string

    // 3. Reverse the resulting postfix expression to get the prefix expression
    strcpy(prefix, tempPostfix);
    reverseString(prefix);
}

// --- Main Function (User Interface) ---
int main() {
    char infixExpression[MAX_SIZE];
    char prefixExpression[MAX_SIZE];

    printf("Infix to Prefix Converter\n");
    printf("--------------------------\n");

    while (1) {
        printf("\nEnter an infix expression (or 'exit' to quit): ");
        fgets(infixExpression, MAX_SIZE, stdin);
        infixExpression[strcspn(infixExpression, "\n")] = 0; // Remove newline character

        if (strcmp(infixExpression, "exit") == 0) {
            printf("Exiting program. Goodbye!\n");
            break;
        }

        // Basic input validation (can be enhanced)
        if (strlen(infixExpression) == 0) {
            printf("Error: Expression cannot be empty.\n");
            continue;
        }

        // Convert and display
        infixToPrefix(infixExpression, prefixExpression);

        if (strlen(prefixExpression) > 0) { // Check if conversion was successful
            printf("Infix Expression:  %s\n", infixExpression);
            printf("Prefix Expression: %s\n", prefixExpression);
        } else {
            printf("Conversion failed. Please check your expression.\n");
        }
    }

    return 0;
}