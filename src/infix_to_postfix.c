/**
 * @file infix_to_postfix.c
 * @author Matrix22 (determinant289@gmail.com)
 * @brief File containing only one function to convert an infix expression into
 * the postfix expression using a stack.
 * @version 0.1
 * @date 2022-09-05
 * 
 */

#include "./include/expression_utils.h"

/**
 * @brief Function to convert an valid infix expression into a valid
 * postfix expression.
 * 
 * @param infix_str String infix literal
 * @return char* pointer to an allocated string object representing
 * the postfix expression
 */
char* infix_to_postfix(char *infix_str) {
    if (infix_str == NULL) {
        return NULL;
    }
    
    stack_t *op_stack = create_stack(NULL, UNIT_LENGTH);

    if (op_stack == NULL) {
        return NULL;
    }

    char *postfix_str = malloc(strlen(infix_str) + UNIT_LENGTH);

    if (postfix_str == NULL) {
        return NULL;
    }

    postfix_str[0] = '\0';

    char *save_token = NULL;
    char *token = __strtok_r(infix_str, WORD_DELIMITERS, &save_token);

    scl_error_t err = stack_push(op_stack, ltoptr(char, '('));

    if (err != SCL_OK) {
        free_stack(op_stack);
        free(postfix_str);

        return NULL;
    }

    uint8_t op_precedence = 0;

    while (token != NULL) {
        if (is_valid_operand(token) == 1) {
            strncat(postfix_str, token, MAX_NUMBER_LENGTH);
            strncat(postfix_str, " ", UNIT_LENGTH);
        } else if (token[0] == '(') {
            err = stack_push(op_stack, ltoptr(char, '('));

            if (err != SCL_OK) {
                free(postfix_str);
                free_stack(op_stack);

                return NULL;
            }
        } else if ((op_precedence = operator_precedence(token[0])) != 0) {
            const char *top_op = stack_top(op_stack);

            while (operator_precedence(top_op[0]) >= op_precedence) {
                strncat(postfix_str, top_op, UNIT_LENGTH);
                strncat(postfix_str, " ", UNIT_LENGTH);

                err = stack_pop(op_stack);

                if (err != SCL_OK) {
                    free(postfix_str);
                    free_stack(op_stack);

                    return NULL;
                }

                top_op = stack_top(op_stack);
            }

            err = stack_push(op_stack, token);

            if (err != SCL_OK) {
                free(postfix_str);
                free_stack(op_stack);

                return NULL;
            }
        } else if (token[0] == ')') {
            if (is_stack_empty(op_stack) == 1) {
                fprintf(stderr, "Invalid infix expression\n");
        
                free(postfix_str);
                free_stack(op_stack);

                return NULL;
            }

            const char *top_op = stack_top(op_stack);

            while (top_op[0] != '(') {
                strncat(postfix_str, top_op, UNIT_LENGTH);
                strncat(postfix_str, " ", UNIT_LENGTH);

                err = stack_pop(op_stack);
                
                if (err != SCL_OK) {
                    free(postfix_str);
                    free_stack(op_stack);

                    return NULL;
                }

                top_op = stack_top(op_stack);
            }

            err = stack_pop(op_stack);

            if (err != SCL_OK) {
                free(postfix_str);
                free_stack(op_stack);

                return NULL;
            }
        } else {
            fprintf(stderr, "Found invalid token: %s\n", token);
            
            free(postfix_str);
            free_stack(op_stack);

            return NULL;
        }

        token = __strtok_r(NULL, WORD_DELIMITERS, &save_token);
    }

    if (is_stack_empty(op_stack) == 1) {
        fprintf(stderr, "Invalid infix expression\n");

        free(postfix_str);
        free_stack(op_stack);

        return NULL;
    }

    const char *top_op = stack_top(op_stack);

    while (top_op[0] != '(') {
        strncat(postfix_str, top_op, UNIT_LENGTH);
        strncat(postfix_str, " ", UNIT_LENGTH);

        err = stack_pop(op_stack);
        
        if (err != SCL_OK) {
            free(postfix_str);
            free_stack(op_stack);

            return NULL;
        }

        top_op = stack_top(op_stack);
    }

    err = stack_pop(op_stack);

    if (err != SCL_OK) {
        free(postfix_str);
        free_stack(op_stack);

        return NULL;
    }

    if (is_stack_empty(op_stack) == 0) {
        fprintf(stderr, "Invalid infix expression\n");
        
        free(postfix_str);
        free_stack(op_stack);

        return NULL;
    }

    free_stack(op_stack);

    postfix_str[strlen(postfix_str) - 1] = '\0';

    return postfix_str;
} 