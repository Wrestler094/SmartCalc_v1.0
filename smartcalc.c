#include "smartcalc.h"

int main(void) {
    char expression[256] = "";
    struct list *initial_list = NULL;
    struct list *resulting_stack = NULL;

    int scanf_result = scanf_expression(expression);

    if (scanf_result == 0) {
        // check_expression();
        parse_expression(expression, &initial_list);
        expression_handler(&initial_list, &resulting_stack);
        calculate_expression(&resulting_stack);
    }

    printf("%f", (*resulting_stack).value);

    return 0;
}

void calculate_expression(struct list **resulting_stack) {
    // Пока в списке не останется 1 элемент
    while ((*resulting_stack)->next != NULL) {
        struct list *buffer_list = NULL;
        struct list operator = {0, 0, 0, NULL};
        struct list operand2 = {0, 0, 0, NULL};
        struct list operand3 = {0, 0, 0, NULL};
        struct list operand4 = {0, 0, 0, NULL};

        read_first(resulting_stack, &operator.value,
                   &operator.type, &operator.priority);

        while (operator.type < 4) {
            push(&buffer_list, operator.value, operator.type, operator.priority);
            shift(resulting_stack);

            read_first(resulting_stack, &operator.value,
                       &operator.type, &operator.priority);
        }

        shift(resulting_stack);

        if (operator.type < 10) {
            read_last(&buffer_list, &operand2.value,
                      &operand2.type, &operand2.priority);
            pop(&buffer_list);
            read_last(&buffer_list, &operand3.value,
                      &operand3.type, &operand3.priority);
            pop(&buffer_list);
        } else {
            read_last(&buffer_list, &operand2.value,
                      &operand2.type, &operand2.priority);
            pop(&buffer_list);
        }

        switch (operator.type) {
            case 4: {
                operand4.value = operand3.value + operand2.value;
                break;
            }
            case 5: {
                operand4.value = operand3.value - operand2.value;
                break;
            }
            case 6: {
                operand4.value = operand3.value * operand2.value;
                break;
            }
            case 7: {
                operand4.value = operand3.value / operand2.value;
                break;
            }
            case 8: {
                operand4.value = pow(operand3.value, operand2.value);
                break;
            }
            case 9: {
                operand4.value = fmod(operand3.value, operand2.value);
                break;
            }
            case 10: {
                operand4.value = sin(operand2.value);
                break;
            }
            case 11: {
                operand4.value = cos(operand2.value);
                break;
            }
            case 12: {
                operand4.value = tan(operand2.value);
                break;
            }
            case 13: {
                operand4.value = asin(operand2.value);
                break;
            }
            case 14: {
                operand4.value = acos(operand2.value);
                break;
            }
            case 15: {
                operand4.value = atan(operand2.value);
                break;
            }
            case 16: {
                operand4.value = sqrt(operand2.value);
                break;
            }
            case 17: {
                operand4.value = log(operand2.value);
                break;
            }
            case 18: {
                operand4.value = log10(operand2.value);
                break;
            }
            default: {
                fprintf(stderr, "Something went wrong...");
                break;
            }
        }

        operand4.type = operand3.type;
        operand4.priority = operand4.priority;

        unshift(resulting_stack, operand4.value, operand4.type, operand4.priority);

        while (buffer_list != NULL) {
            double value = 0;
            enum enum_type type = 0;
            int priority = 0;

            int res = read_last(&buffer_list, &value, &type, &priority);

            if (res == 0) {
                unshift(resulting_stack, value, type, priority);
                pop(&buffer_list);
            }
        }
    }
}
