#ifndef FINITE_AUTOMATON_H
#define FINITE_AUTOMATON_H

typedef enum {
    Q0,
    Q1,
    Q2,
    Q3,
    Q4,
    Q5,
    Q6,
    ERR
} State;

int get_char_class(char c);

int match(const char* str);

void print_transition_table(void);

#endif
