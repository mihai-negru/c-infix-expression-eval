/**
 * @file operations_check.c
 * @author Matrix22 (determinant289@gmail.com)
 * @brief Source file to check if an operator is valid to perform an operation and
 * to check the precedence of an opeartor from the infix/postfix expression.
 * @version 0.1
 * @date 2022-09-05
 * 
 */

#include "./include/expression_utils.h"

/**
 * @brief Function to get the precedence of an operator from the given expression.
 * 
 * @param operator char rpresentation of an operator to check its precedence
 * @return uint8_t a number within [1, 8] range. Greater the number, greater the precedence
 * if returned number is 0 then input char doe not represent an operator
 */
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

/**
 * @brief Function to check if a char expresion represents an integer
 * or a double number expression.
 * 
 * @param operand char expression representing a number
 * @return uint8_t 1 if expression is a valid number or 0 otherwise
 */
uint8_t is_valid_operand(const char * const operand) {
    if (operand == NULL) {
        return 0;
    }

    for (size_t iter_i = 0; operand[iter_i] != '\0'; ++iter_i) {
        if (((operand[iter_i] < '0') || (operand[iter_i] > '9')) && (operand[iter_i] != '.')) {
            return 0;
        }
    }

    return 1;
}