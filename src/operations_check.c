#include "./include/expression_utils.h"

uint8_t operator_precedence(char operator) {
    switch (operator) {
        case '^':               /* Power Symbol */
            return 8;
        case 'P':               /* Unary Plus Symbol */
        case 'M':               /* Unary Minus Symbol */
        case 'N':               /* Unary Negation Symbol */
            return 7;
        case '*':               /* Multiplication Symbol */
        case '/':               /* Division Symbol */
        case '%':               /* Modulo Symbol */
            return 6;
        case '+':               /* Addition Symbol */
        case '-':               /* Subtraction Symbol */
            return 5;
        case '<':               /* Left Binary Shift Symbol */
        case '>':               /* Right Binary Shift Symbol */
            return 4;
        case '&':               /* Bitwise AND Symbol */
            return 3;
        case 'v':               /* Bitwise XOR Symbol */
            return 2;
        case '|':               /* Bitwise OR Symbol */
            return 1;
        default:                /* Invalid Operator */
            return 0;
    }

    /* Invalid operator */
    return 0;
}

uint8_t is_valid_operand(const char * const operand) {
    if (operand == NULL) {
        return 0;
    }

    for (size_t iter_i = 0; operand[iter_i] != '\0'; ++iter_i) {
        if (operand[iter_i] < '0' || operand[iter_i] > '9') {
            return 0;
        }
    }

    return 1;
}