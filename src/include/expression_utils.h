#ifndef _EXPRESSION_UTILS_H_
#define _EXPRESSION_UTILS_H_

#include <scl_stack.h>
#include <scl_func_types.h>

#define WORD_DELIMITERS "\n ,;:`'\""
#define MAX_NUMBER_LENGTH 20
#define UNIT_LENGTH 1

uint8_t operator_precedence(char operator);
uint8_t is_valid_operand(const char * const operand);
char* infix_to_postfix(char *infix_str);
long long int evaluate_int_postfix(char *postfix_str);
long double evaluate_double_postfix(char *postfix_str);

#endif /* _EXPRESSION_UTILS_H */