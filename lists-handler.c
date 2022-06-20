#include "smartcalc.h"

/**
 * Вставляет элемент в начало списка
 */
void unshift(struct list **head, double value, enum enum_type type, int priority) {
    // TODO(maddiega): Обработать ситуацию, если new_node == NULL
    struct list *new_node = create_node(value, type, priority);

    if (*head == NULL) {
        *head = new_node;
    } else {
        new_node->next = *head;
        *head = new_node;
    }
}

/**
 * Удаляет первый элемент списка
 */
void shift(struct list **head) {
    if (*head != NULL) {
        struct list *tmp = *head;
        *head = tmp->next;
        free(tmp);
    }
}

/**
 * Вставляет элемент в конец списка
 */
void push(struct list **head, double value, enum enum_type type, int priority) {
    // TODO(maddiega): Обработать ситуацию, если new_node == NULL
    struct list *new_node = create_node(value, type, priority);

    if (*head == NULL) {
        *head = new_node;
    } else {
        struct list *tmp = *head;

        while (tmp->next != NULL) {
            tmp = tmp->next;
        }

        tmp->next = new_node;
    }
}

/**
 * Удаляет последний элемент списка
 */
void pop(struct list **head) {
    if (*head != NULL) {
        struct list *tmp_first = *head;
        struct list *tmp_last = *head;

        if (tmp_last->next != NULL) {
            while (tmp_last->next != NULL) {
                tmp_first = tmp_last;
                tmp_last = tmp_last->next;
            }

            tmp_first->next = NULL;
            free(tmp_last);
        } else {
            *head = NULL;
            free(tmp_last);
        }
    }
}

/**
 * Печатает данные первого элемента в списке
 */
int read_first(struct list **head, double *value, enum enum_type *type, int *priority) {
    int execution_status = 0;

    if (*head != NULL) {
        struct list *node = *head;
        *value = node->value;
        *type = node->type;
        *priority = node->priority;
    } else {
        execution_status = 1;
    }

    return execution_status;
}

/**
 * Печатает данные последнего элемента в списке
 */
int read_last(struct list **head, double *value, enum enum_type *type, int *priority) {
    int execution_status = 0;

    if (*head != NULL) {
        struct list *node = *head;

        while (node->next != NULL) {
            node = node->next;
        }

        *value = node->value;
        *type = node->type;
        *priority = node->priority;
    } else {
        execution_status = 1;
    }

    return execution_status;
}

/**
 * Создаёт новый элемент списка
 */
struct list *create_node(double value, enum enum_type type, int priority) {
    struct list *node = malloc(sizeof(struct list));

    if (node != NULL) {
        node->value = value;
        node->type = type;
        node->priority = priority;
        node->next = NULL;
    } else {
        // TODO(maddiega): Обработать ситуацию, если malloc не выделил память
        fprintf(stderr, "something went wrong\n");
    }

    return node;
}