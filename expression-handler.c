#include "smartcalc.h"

int parse_expression(char expression[256], struct list **head, double value_of_x) {
    int expression_length = (int) strlen(expression);

    for (int i = 0; i < expression_length; i++) {
        switch (expression[i]) {
            case '(': {
                push(head, 0, 0, -1);
                break;
            }
            case ')': {
                push(head, 0, 1, -1);
                break;
            }
            case 'x': {
                push(head, value_of_x, 3, 0);
                break;
            }
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
            case '.': {
                char *start_ptr = &expression[i];
                for (; is_digit(expression[i]); i++) {}
                char *end_ptr = &expression[--i];

                double number = strtod(start_ptr, &end_ptr);
                push(head, number, 3, 0);
                break;
            }
            case '+': {
                push(head, 0, 4, 1);
                break;
            }
            case '-': {
                push(head, 0, 5, 1);
                break;
            }
            case '*': {
                push(head, 0, 6, 2);
                break;
            }
            case '/': {
                push(head, 0, 7, 2);
                break;
            }
            case '^': {
                push(head, 0, 8, 3);
                break;
            }
            case 'm': {
                int res = strncmp(&expression[i], "mod", 3);

                if (res == 0) {
                    push(head, 0, 9, 2);
                    i += 2;
                }

                break;
            }
            case 's': {
                int res = strncmp(&expression[i], "sin(", 4);

                if (res == 0) {
                    push(head, 0, 10, 4);
                    i += 2;
                } else {
                    res = strncmp(&expression[i], "sqrt(", 5);

                    if (res == 0) {
                        push(head, 0, 16, 4);
                        i += 3;
                    }
                }

                break;
            }
            case 'c': {
                int res = strncmp(&expression[i], "cos(", 4);

                if (res == 0) {
                    push(head, 0, 11, 4);
                    i += 2;
                }

                break;
            }
            case 't': {
                int res = strncmp(&expression[i], "tan(", 4);
                if (res == 0) {
                    push(head, 0, 12, 4);
                    i += 2;
                }

                break;
            }
            case 'a': {
                int res = strncmp(&expression[i], "asin(", 5);

                if (res == 0) {
                    push(head, 0, 13, 4);
                    i += 3;
                } else {
                    res = strncmp(&expression[i], "acos(", 5);

                    if (res == 0) {
                        push(head, 0, 14, 4);
                        i += 3;
                    }
                    if (res == 0) {
                        res = strncmp(&expression[i], "atan(", 5);

                        if (res == 0) {
                            push(head, 0, 15, 4);
                            i += 3;
                        }
                    }
                }

                break;
            }
            case 'l': {
                int res = strncmp(&expression[i], "ln(", 3);

                if (res == 0) {
                    push(head, 0, 17, 4);
                    i += 1;
                } else {
                    res = strncmp(&expression[i], "log(", 4);

                    if (res == 0) {
                        push(head, 0, 18, 4);
                        i += 2;
                    }
                }

                break;
            }
            case ' ': {
                break;
            }
            default: {
//                fprintf(stderr, "Something went wrong...");
//                printf("Wrong char - %c", expression[i]);
                return 1;
            }
        }
    }

    return 0;
}

int expression_handler(struct list **initial_list, struct list **resulting_stack) {
    struct list *additional_stack = NULL;

    while (*initial_list != NULL) {
        double initial_list_value = 0;
        enum enum_type initial_list_type = 0;
        int initial_list_priority = 0;

        int res = read_first(initial_list, &initial_list_value,
                             &initial_list_type, &initial_list_priority);

        if (res == 0) {
            // Число - добавляем в строку вывода
            if (initial_list_type == 3 || initial_list_type == 2) {
                push(resulting_stack, initial_list_value,
                     initial_list_type, initial_list_priority);
            }

            // Функция или открывающая скобка - помещаем в стек
            if (initial_list_type > 9 || initial_list_type == 0) {
                push(&additional_stack, initial_list_value,
                     initial_list_type, initial_list_priority);
            }

            // Оператор (O1)
//              Пока присутствует на вершине стека лексема-оператор (O2)
//              чей приоритет выше или равен приоритету O1,
//              либо при равенстве приоритетов O1 является левоассоциативным:
//              Перекладываем O2 из стека в выходную очередь
            if (initial_list_type > 3 && initial_list_type < 10) {
                double additional_stack_value = 0;
                enum enum_type additional_stack_type = 0;
                int additional_stack_priority = 0;

                int additional_res = read_last(&additional_stack, &additional_stack_value,
                                               &additional_stack_type, &additional_stack_priority);

                while (additional_stack_priority >= initial_list_priority && additional_res == 0) {
                    push(resulting_stack, additional_stack_value,
                         additional_stack_type, additional_stack_priority);
                    pop(&additional_stack);

                    additional_res = read_last(&additional_stack, &additional_stack_value,
                                               &additional_stack_type, &additional_stack_priority);
                }

                // Помещаем O1 в стек.
                push(&additional_stack, initial_list_value,
                     initial_list_type, initial_list_priority);
            }

//            // Закрывающая скобка
            if (initial_list_type == 1) {
//                Пока лексема на вершине стека не станет открывающей скобкой,
//                перекладываем лексемы-операторы из стека в выходную очередь.
                double additional_stack_value = 0;
                enum enum_type additional_stack_type = 0;
                int additional_stack_priority = 0;

                int additional_res = read_last(&additional_stack, &additional_stack_value,
                                               &additional_stack_type, &additional_stack_priority);

                while (additional_stack_type != 0 && additional_res == 0) {
                    push(resulting_stack, additional_stack_value,
                         additional_stack_type, additional_stack_priority);
                    pop(&additional_stack);

                    additional_res = read_last(&additional_stack, &additional_stack_value,
                                               &additional_stack_type, &additional_stack_priority);
                }

//                Удаляем из стека открывающую скобку.
                if (additional_res == 0) {
                    pop(&additional_stack);
                } else {
                    return 1;
                }

//                Если лексема на вершине стека — функция, перекладываем её в выходную очередь.
                additional_res = read_last(&additional_stack, &additional_stack_value,
                                           &additional_stack_type, &additional_stack_priority);
                if (additional_res == 0 && initial_list_type > 9) {
                    push(resulting_stack, additional_stack_value,
                         additional_stack_type, additional_stack_priority);
                    pop(&additional_stack);
                }
            }
        } else {
//            fprintf(stderr, "Something went wrong...");
            while (additional_stack != NULL) {
                pop(&additional_stack);
            }

            return 1;
        }

        shift(initial_list);
    }

    // Если во входной строке больше не осталось лексем:
    double additional_stack_value = 0;
    enum enum_type additional_stack_type = 0;
    int additional_stack_priority = 0;

    int additional_res = read_last(&additional_stack, &additional_stack_value,
                                   &additional_stack_type, &additional_stack_priority);

    if (additional_res == 0 && (additional_stack_type == 0 || additional_stack_type == 1)) {
        while (additional_stack != NULL) {
            pop(&additional_stack);
        }

        return 1;
    }

    // Пока есть операторы в стеке:
    // Перекладываем оператор из стека в выходную очередь.
    while (additional_res == 0) {
        push(resulting_stack, additional_stack_value,
             additional_stack_type, additional_stack_priority);
        pop(&additional_stack);

        additional_res = read_last(&additional_stack, &additional_stack_value,
                                   &additional_stack_type, &additional_stack_priority);

        if (additional_res == 0 && (additional_stack_type == 0 || additional_stack_type == 1)) {
            while (additional_stack != NULL) {
                pop(&additional_stack);
            }

            return 1;
        }
    }

    return 0;
}

int calculate_expression(struct list **resulting_stack) {
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

            int res = read_first(resulting_stack, &operator.value,
                       &operator.type, &operator.priority);

            if (res == 1) {
                return 1;
            }
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
//                fprintf(stderr, "Something went wrong...");
                return 1;
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

    return 0;
}
