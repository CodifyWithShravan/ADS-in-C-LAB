#include <stdio.h>
#include <string.h>
#include <ctype.h> // For isdigit() and isalpha()
#include <stdlib.h>

#define MAX_STACK_SIZE 100

// Global stack and top variable
int stack[MAX_STACK_SIZE];
int top = -1;

// --- Stack Operations ---

// Pushes an item onto the stack
void push(int item) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Error: Stack Overflow.\n");
        exit(1);
    }
    stack[++top] = item;
}

// Pops an item from the stack
int pop() {
    if (top < 0) {
        printf("Error: Stack Underflow (invalid expression).\n");
        exit(1);
    }
    return stack[top--];
}

// --- Postfix Evaluation Logic ---

// Function to evaluate a given postfix expression with variables
void evaluatePostfix(char* postfix) {
    int i = 0;
    char symbol;
    int operand1, operand2, result, value;

    // Iterate through the postfix expression string
    while ((symbol = postfix[i++]) != '\0') {
        
        // If the symbol is a digit (operand)
        if (isdigit(symbol)) {
            push(symbol - '0');
        }
        // If the symbol is an alphabet character (variable)
        else if (isalpha(symbol)) {
            printf("Enter value for variable %c: ", symbol);
            scanf("%d", &value);
            push(value);
        }
        // If the symbol is an operator
        else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {
            operand2 = pop();
            operand1 = pop();

            switch (symbol) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/':
                    if (operand2 == 0) {
                        printf("Error: Division by zero.\n");
                        exit(1);
                    }
                    result = operand1 / operand2;
                    break;
            }
            push(result);
        }
    }

    result = pop();
    
    if (top != -1) {
        printf("Error: Invalid Postfix Expression.\n");
    } else {
        printf("✅ Result of Postfix Evaluation: %d\n", result);
    }
}

// --- Main Function ---

int main() {
    char postfix[MAX_STACK_SIZE];

    printf("⚙️ Enter a postfix expression with digits and variables (e.g., ab+c*): ");
    scanf("%s", postfix);

    evaluatePostfix(postfix);

    return 0;
}