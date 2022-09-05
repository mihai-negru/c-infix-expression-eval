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
        printf("Integer Postfix Evaluation: %lld\n\n", evaluate_int_postfix(postfix_str));
    } else {
        printf("Double Postfix Evaluation: %Lf\n\n", evaluate_double_postfix(postfix_str));
    }

    free(postfix_str);

    return 0;
}  