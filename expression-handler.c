#include "smartcalc.h"

int scanf_expression(char expression[256]) {
    char ch;
    int index = 0;

    ch = (char) getchar();

    for (; index < 256 && ch != '\n' && ch != '\0' && ch != EOF; index++) {
        expression[index] = ch;
        ch = (char) getchar();
    }

    expression[index + 1] = '\0';

    return strlen(expression) > 0 ? 0 : 1;
}

// int check_expression(char expression[256]) {}

void parse_expression(char expression[256], struct list **head) {
    printf("%s\n", expression);

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
                push(head, 0, 2, 0);
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
                for(; is_digit(expression[i]); i++) {}
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
                int res = strncmp(&expression[i], "sin", 3);

                if (res == 0) {
                    push(head, 0, 10, 4);
                    i += 2;
                } else {
                    res = strncmp(&expression[i], "sqrt", 4);

                    if (res == 0) {
                        push(head, 0, 16, 4);
                        i += 3;
                    }
                }

                break;
            }
            case 'c': {
                int res = strncmp(&expression[i], "cos", 3);

                if (res == 0) {
                    push(head, 0, 11, 4);
                    i += 2;
                }

                break;
            }
            case 't': {
                int res = strncmp(&expression[i], "tan", 3);
                if (res == 0) {
                    push(head, 0, 12, 4);
                    i += 2;
                }

                break;
            }
            case 'a': {
                int res = strncmp(&expression[i], "asin", 3);

                if (res == 0) {
                    push(head, 0, 13, 4);
                    i += 3;
                } else {
                    res = strncmp(&expression[i], "acos", 3);

                    if (res == 0) {
                        push(head, 0, 14, 4);
                        i += 3;
                    }
                    if (res == 0) {
                        res = strncmp(&expression[i], "atan", 3);

                        if (res == 0) {
                            push(head, 0, 15, 4);
                            i += 3;
                        }
                    }
                }

                break;
            }
            case 'l': {
                int res = strncmp(&expression[i], "ln", 2);

                if (res == 0) {
                    push(head, 0, 17, 4);
                    i += 1;
                } else {
                    res = strncmp(&expression[i], "log", 3);

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
                fprintf(stderr, "Something went wrong...");
                printf("Wrong char - %c", expression[i]);
                break;
            }
        }
    }
}

void expression_handler(struct list **initial_list, struct list **resulting_stack) {
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

            // Разделитель аргументов функции (например, запятая)
            // if (запятая) {
            // }

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
                         additional_stack_type,additional_stack_priority);
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
                         additional_stack_type,additional_stack_priority);
                    pop(&additional_stack);

                    additional_res = read_last(&additional_stack, &additional_stack_value,
                                               &additional_stack_type, &additional_stack_priority);
                }

//                Удаляем из стека открывающую скобку.
                pop(&additional_stack);

//                Если лексема на вершине стека — функция, перекладываем её в выходную очередь.
                additional_res = read_last(&additional_stack, &additional_stack_value,
                                           &additional_stack_type, &additional_stack_priority);
                if (additional_res == 0 && initial_list_type > 9) {
                    push(resulting_stack, additional_stack_value,
                         additional_stack_type,additional_stack_priority);
                    pop(&additional_stack);
                }
            }
        } else {
            fprintf(stderr, "Something went wrong...");
        }

        shift(initial_list);
    }

    // Если во входной строке больше не осталось лексем:
    double additional_stack_value = 0;
    enum enum_type additional_stack_type = 0;
    int additional_stack_priority = 0;

    int additional_res = read_last(&additional_stack, &additional_stack_value,
                                   &additional_stack_type, &additional_stack_priority);

    // Пока есть операторы в стеке:
    // Перекладываем оператор из стека в выходную очередь.
    while (additional_res == 0) {
        push(resulting_stack, additional_stack_value,
             additional_stack_type,additional_stack_priority);
        pop(&additional_stack);

        additional_res = read_last(&additional_stack, &additional_stack_value,
                                   &additional_stack_type, &additional_stack_priority);
    }

}
