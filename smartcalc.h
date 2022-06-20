#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define is_digit(ch) (((ch) >= '0' && (ch) <= '9') || (ch) == '.')

enum enum_type {
    open_bracket,
    close_bracket,
    x,
    number,
    add,
    sub,
    multiply,
    divide,
    e_exp,
    e_mod,
    e_sin,
    e_cos,
    e_tan,
    e_asin,
    e_acos,
    e_atan,
    e_sqrt,
    e_ln,
    e_log
};

struct list {
    double value;
    enum enum_type type;
    int priority;
    struct list* next;
};

int scanf_expression(char expression[256]);
//int check_expression(char expression[256]);
void parse_expression(char expression[256], struct list **head);
void expression_handler(struct list **initial_list, struct list **resulting_stack);
void calculate_expression(struct list **resulting_stack);


struct list *create_node(double value, enum enum_type type, int priority);
void unshift(struct list **head, double value, enum enum_type type, int priority);
void shift(struct list **head);
void push(struct list **head, double value, enum enum_type type, int priority);
void pop(struct list **head);
int read_first(struct list **head, double *value, enum enum_type *type, int *priority);
int read_last(struct list **head, double *value, enum enum_type *type, int *priority);