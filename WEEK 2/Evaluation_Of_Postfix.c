#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Stack structure
struct Stack {
    int top;
    int items[MAX_SIZE];
};

// Initializes a stack
void initialize(struct Stack *s) {
    s->top = -1;
}

// Pushes a value onto the stack
void push(struct Stack *s, int value) {
    if (s->top >= MAX_SIZE - 1) {
        printf("Error: Stack Overflow.\n");
        exit(1);
    }
    s->items[++(s->top)] = value;
}

// Pops a value from the stack
int pop(struct Stack *s) {
    if (s->top < 0) {
        printf("Error: Invalid Postfix Expression (Stack Underflow).\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

// Evaluates a postfix expression
void evaluatePostfix(char* postfix) {
    struct Stack s;
    initialize(&s);
    int i = 0;
    int operand1, operand2, result, value;

    while (postfix[i] != '\0') {
        char symbol = postfix[i];

        if (isdigit(symbol)) {
            push(&s, symbol - '0');
        } else if (isalpha(symbol)) {
            printf("Enter value for variable '%c': ", symbol);
            scanf("%d", &value);
            push(&s, value);
        } else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {
            operand2 = pop(&s);
            operand1 = pop(&s);

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
            push(&s, result);
        }
        i++;
    }

    if (s.top != 0) {
        printf("Error: Invalid Postfix Expression (Stack not empty).\n");
    } else {
        printf("✅ Result of Postfix Evaluation: %d\n", s.items[s.top]);
    }
}

int main() {
    char postfix[MAX_SIZE];
    printf("⚙️ Enter a postfix expression with digits and variables (e.g., ab+c*):\n> ");
    scanf("%s", postfix);
    evaluatePostfix(postfix);
    return 0;
}