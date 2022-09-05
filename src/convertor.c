#include "./include/expression_utils.h"

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
            printf("Double Postfix Evaluation: %.50Lf\n\n", result);
        }
    }

    free(postfix_str);

    return 0;
}  