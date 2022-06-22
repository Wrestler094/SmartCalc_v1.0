#include "smartcalc.h"

int main_c(char *str, double value_of_x, double *result) {
    int execution_status = 0;

    char expression[256] = "";
    struct list *initial_list = NULL;
    struct list *resulting_stack = NULL;

    snprintf(expression, sizeof(expression), "%s", str);

    if (strlen(expression) > 0) {
        execution_status = parse_expression(expression, &initial_list, value_of_x);

        if (execution_status == 0) {
            execution_status = expression_handler(&initial_list, &resulting_stack);

            if (execution_status == 0) {
                execution_status = calculate_expression(&resulting_stack);

                if (execution_status == 0) {
                    *result = (*resulting_stack).value;
                }
            }
        }
    }

    while (initial_list != NULL) {
        pop(&initial_list);
    }

    while (resulting_stack != NULL) {
        pop(&resulting_stack);
    }

    return execution_status;
}
