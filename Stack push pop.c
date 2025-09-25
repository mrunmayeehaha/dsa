//Stack push pop 
#include <stdio.h>
#include <stdbool.h>

#define MAX 100


char stack[MAX];
int top = -1;


void push(char c) {
    if (top < MAX - 1) {
        stack[++top] = c;
    }
}


char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0'; // Return null char if stack is empty
}


int isBalanced(char* expr) {
    for (int i = 0; expr[i] != '\0'; i++) { //i is for each char
        if (expr[i] == '(') {
            push('(');
        } else if (expr[i] == ')') {
            if (top == -1) {
                // Nothing to pop, so unbalanced
                return false;
            }
            pop();
        }
    }
    // If stack empty, parentheses are balanced
    return top == -1;
}

int main() {
    char expr[100];
    printf("Enter an expression: ");
    scanf("%s", expr);

    if (isBalanced(expr)) {
        printf("Parentheses are balanced.\n");
    } else {
        printf("Parentheses are NOT balanced.\n");
    }

    return 0;
}