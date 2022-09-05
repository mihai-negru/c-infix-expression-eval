/**
 * @file convertor.c
 * @author Matrix22 (determinant289@gmail.com)
 * @brief Application source file. The program will read from command line
 * a string expression representing the infix string and a number to calculate the result
 * <1 - for integer result> and <2 - for floating point result>. Program will convert the infix
 * expression into a postfix expression and will evaluate the expresion returning a number.
 * @version 0.1
 * @date 2022-09-05
 * 
 */

#include "./include/expression_utils.h"

/**
 * @brief Application to evaluate an infix expression using stacks
 * 
 * @param argc number of command line params. Must be 3
 * @param argv executable name, infix expression string, control number 1/2
 * @return int EXIT_SUCCESS if every thing calculated correctly, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Wrong commands number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int numbers_type = atoi(argv[2]);

    if (numbers_type != 1 && numbers_type != 2) {
        fprintf(stderr, "Usage: %s <Wrong numbers type>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (numbers_type == 1) {
        printf("Number Selector <1> - Integer result\n\n");
    } else {
        printf("Number Selector <2> - Double result\n\n");
    }

    if (numbers_type == 1) {
        printf("Integer Infix Expression: \"%s\"\n\n", argv[1]);
    } else {
        printf("Double Infix Expression: \"%s\"\n\n", argv[1]);
    }

    char *postfix_str = infix_to_postfix(argv[1]);

    if (postfix_str == NULL) {
        if (numbers_type == 1) {
            printf("Integer Postfix Expression: (None)\n\n");
        } else {
            printf("Double Postfix Expression: (None)\n\n");
        }
        
        return EXIT_FAILURE;
    }

    if (numbers_type == 1) {
        printf("Integer Postfix Expression: \"%s\"\n\n", postfix_str);
    } else {
        printf("Double Postfix Expression: \"%s\"\n\n", postfix_str);
    }

    if (numbers_type == 1) {
        long long int result = evaluate_int_postfix(postfix_str);

        if (result == LLONG_MAX) {
            printf("Integer Postfix Evaluation: <Error>\n\n");    
        } else {
            printf("Integer Postfix Evaluation: %lld\n\n", result);
        }
    } else {
        long double result = evaluate_double_postfix(postfix_str);

        if (result == LDBL_MAX) {
            printf("Double Postfix Evaluation: <Error>\n\n");    
        } else {
            printf("Double Postfix Evaluation: %.100Lg\n\n", result);
        }
    }

    free(postfix_str);

    return EXIT_SUCCESS;
}  