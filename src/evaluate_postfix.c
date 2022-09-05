/**
 * @file evaluate_postfix.c
 * @author Matrix22 (determinant289@gmail.com)
 * @brief Source file containing two functions to evaluate a postfix expression.
 * One function is returning an integer result and is performing JUST integer operations,
 * another function is performing mixted operations (floating point and integer) and it is
 * returning an floating point number.
 * @version 0.1
 * @date 2022-09-05
 * 
 */

#include "./include/expression_utils.h"

/**
 * @brief Function to evaluate an integer postfix expression and
 * to return an integer(long long int) number.
 * 
 * @param postfix_str pointer to postfix string literal expression
 * @return long long int evaluation of the postfix expresion or LLONG_MAX
 * if expression is not valid or stack opeartions fails
 */
long long int evaluate_int_postfix(char *postfix_str) {
    if (postfix_str == NULL) {
        return LLONG_MAX;
    }

    stack_t *eval_stack = create_stack(NULL, sizeof(long long int));

    if (eval_stack == NULL) {
        return LLONG_MAX;
    }

    char *save_token = NULL;
    char *token = __strtok_r(postfix_str, WORD_DELIMITERS, &save_token);

    scl_error_t err = SCL_OK;

    uint8_t op_precedence = 0;
    long long int operand = LLONG_MAX;

    while (token != NULL) {
        if ((op_precedence = operator_precedence(token[0])) != 0) {
            operand = LLONG_MAX;

            if (op_precedence == 7) {
                if (is_stack_empty(eval_stack) == 1) {
                    fprintf(stderr, "Invalid postfix expression\n");

                    free_stack(eval_stack);

                    return LLONG_MAX;
                }

                operand  = *(const long long int *)stack_top(eval_stack);

                err = stack_pop(eval_stack);
                
                if (err != SCL_OK) {
                    free_stack(eval_stack);

                    return LLONG_MAX;
                }

                switch (token[0]) {
                    case 'P':
                        operand = +operand;
                        break;
                    case 'M':
                        operand = -operand;
                        break;
                    case 'N':
                        operand = ~operand;
                        break;
                    default:
                        fprintf(stderr, "Error: Invalid operator %c\n", token[0]);
                        free_stack(eval_stack);
                        return LLONG_MAX;
                }
            } else {
                if (is_stack_empty(eval_stack) == 1) {
                    fprintf(stderr, "Invalid postfix expression\n");

                    free_stack(eval_stack);

                    return LLONG_MAX;
                }

                long long int foperand = *(const long long int *)stack_top(eval_stack);

                err = stack_pop(eval_stack);
                
                if (err != SCL_OK) {
                    free_stack(eval_stack);

                    return LLONG_MAX;
                }

                if (is_stack_empty(eval_stack) == 1) {
                    fprintf(stderr, "Invalid postfix expression\n");

                    free_stack(eval_stack);

                    return LLONG_MAX;
                }

                long long int soperand = *(const long long int *)stack_top(eval_stack);

                err = stack_pop(eval_stack);
                
                if (err != SCL_OK) {
                    free_stack(eval_stack);

                    return LLONG_MAX;
                }

                switch (token[0]) {
                    case '^':
                        operand = (long long int)pow(1.0 * soperand, 1.0 * foperand);
                        break;
                    case '*':
                        operand = (soperand * foperand);
                        break;
                    case '/':
                        operand = (soperand / foperand);
                        break;
                    case '%':
                        operand = (soperand % foperand);
                        break;
                    case '+':
                        operand = (soperand + foperand);
                        break;
                    case '-':
                        operand = (soperand - foperand);
                        break;
                    case '<':
                        operand = (soperand << foperand);
                        break;
                    case '>':
                        operand = (soperand >> foperand);
                        break;
                    case '&':
                        operand = (soperand & foperand);
                        break;
                    case 'v':
                        operand = (soperand ^ foperand);
                        break;
                    case '|':
                        operand = (soperand | foperand);
                        break;
                    default:
                        fprintf(stderr, "Error: Invalid operator %c\n", token[0]);
                        free_stack(eval_stack);
                        return LLONG_MAX;
                }
            }
        } else {
            operand = strtoll(token, NULL, 10);

            if ((operand == LLONG_MAX) || (operand == LLONG_MIN)) {
                fprintf(stderr, "Error: Invalid operand \"%s\"\n", token);

                free_stack(eval_stack);

                return LLONG_MAX;
            }
        }

        err = stack_push(eval_stack, toptr(operand));

        if (err != SCL_OK) {
            free_stack(eval_stack);

            return LLONG_MAX;
        }

        token = __strtok_r(NULL, WORD_DELIMITERS, &save_token);
    }

    if (is_stack_empty(eval_stack) == 1) {
        fprintf(stderr, "Invalid postfix expression\n");

        free_stack(eval_stack);

        return LLONG_MAX;
    }

    long long int result = *(const long long int *)stack_top(eval_stack);

    err = stack_pop(eval_stack);

    if (err != SCL_OK) {
        free_stack(eval_stack);

        return LLONG_MAX;
    }

    if (is_stack_empty(eval_stack) == 0) {
        fprintf(stderr, "Error: Invalid postfix expression\n");

        free_stack(eval_stack);

        return LLONG_MAX;
    }

    free_stack(eval_stack);

    return result;
}

/**
 * @brief Function to evaluate a mixted postfix expression and
 * to return an dloating point(long double) number.
 * 
 * @param postfix_str pointer to postfix string literal expression
 * @return long double evaluation of the postfix expresion or LDBL_MAX
 * if expression is not valid or stack opeartions fails
 */
long double evaluate_double_postfix(char *postfix_str) {
    if (postfix_str == NULL) {
        return LDBL_MAX;
    }

    stack_t *eval_stack = create_stack(NULL, sizeof(long double));

    if (eval_stack == NULL) {
        return LDBL_MAX;
    }

    char *save_token = NULL;
    char *token = __strtok_r(postfix_str, WORD_DELIMITERS, &save_token);

    scl_error_t err = SCL_OK;

    uint8_t op_precedence = 0;
    long double operand = LDBL_MAX;

    while (token != NULL) {
        if ((op_precedence = operator_precedence(token[0])) != 0) {
            operand = LDBL_MAX;

            if (op_precedence == 7) {
                if (is_stack_empty(eval_stack) == 1) {
                    fprintf(stderr, "Invalid postfix expression\n");

                    free_stack(eval_stack);

                    return LDBL_MAX;
                }

                operand  = *(const long double *)stack_top(eval_stack);

                err = stack_pop(eval_stack);
                
                if (err != SCL_OK) {
                    free_stack(eval_stack);

                    return LDBL_MAX;
                }

                switch (token[0]) {
                    case 'P':
                        operand = +operand;
                        break;
                    case 'M':
                        operand = -operand;
                        break;
                    case 'N':
                        operand = 1.0L * (~(long long int)operand);
                        break;
                    default:
                        fprintf(stderr, "Error: Invalid operator %c\n", token[0]);
                        free_stack(eval_stack);
                        return LDBL_MAX;
                }
            } else {
                if (is_stack_empty(eval_stack) == 1) {
                    fprintf(stderr, "Invalid postfix expression\n");

                    free_stack(eval_stack);

                    return LDBL_MAX;
                }

                long double foperand = *(const long double *)stack_top(eval_stack);

                err = stack_pop(eval_stack);
                
                if (err != SCL_OK) {
                    free_stack(eval_stack);

                    return LDBL_MAX;
                }

                if (is_stack_empty(eval_stack) == 1) {
                    fprintf(stderr, "Invalid postfix expression\n");

                    free_stack(eval_stack);

                    return LDBL_MAX;
                }

                long double soperand = *(const long double *)stack_top(eval_stack);

                err = stack_pop(eval_stack);
                
                if (err != SCL_OK) {
                    free_stack(eval_stack);

                    return LDBL_MAX;
                }

                switch (token[0]) {
                    case '^':
                        operand = 1.0L * pow((double)soperand, (double)foperand);
                        break;
                    case '*':
                        operand = (soperand * foperand);
                        break;
                    case '/':
                        operand = (soperand / foperand);
                        break;
                    case '%':
                        operand = 1.0L * ((long long int)soperand % (long long int)foperand);
                        break;
                    case '+':
                        operand = (soperand + foperand);
                        break;
                    case '-':
                        operand = (soperand - foperand);
                        break;
                    case '<':
                        operand = 1.0L * ((long long int)soperand << (long long int)foperand);
                        break;
                    case '>':
                        operand = 1.0 * ((long long int)soperand >> (long long int)foperand);
                        break;
                    case '&':
                        operand = 1.0L * ((long long int)soperand & (long long int)foperand);
                        break;
                    case 'v':
                        operand = 1.0L * ((long long int)soperand ^ (long long int)foperand);
                        break;
                    case '|':
                        operand = 1.0L * ((long long int)soperand | (long long int)foperand);
                        break;
                    default:
                        fprintf(stderr, "Error: Invalid operator %c\n", token[0]);
                        free_stack(eval_stack);
                        return LDBL_MAX;
                }
            }
        } else {
            operand = strtold(token, NULL);

            if ((operand == LDBL_MAX) || (operand == LDBL_MIN)) {
                fprintf(stderr, "Error: Invalid operand \"%s\"\n", token);

                free_stack(eval_stack);

                return LDBL_MAX;
            }
        }

        err = stack_push(eval_stack, toptr(operand));

        if (err != SCL_OK) {
            free_stack(eval_stack);

            return LDBL_MAX;
        }

        token = __strtok_r(NULL, WORD_DELIMITERS, &save_token);
    }

    if (is_stack_empty(eval_stack) == 1) {
        fprintf(stderr, "Invalid postfix expression\n");

        free_stack(eval_stack);

        return LDBL_MAX;
    }
    
    long double result = *(const long double *)stack_top(eval_stack);

    err = stack_pop(eval_stack);

    if (err != SCL_OK) {
        free_stack(eval_stack);

        return LDBL_MAX;
    }

    if (is_stack_empty(eval_stack) == 0) {
        fprintf(stderr, "Error: Invalid postfix expression\n");

        free_stack(eval_stack);

        return LDBL_MAX;
    }

    free_stack(eval_stack);

    return result;
}