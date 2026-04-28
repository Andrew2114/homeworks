#include "finite_automaton.h"
#include <ctype.h>
#include <stdio.h>

typedef enum {
    CLASS_DIGIT,
    CLASS_DOT,
    CLASS_E,
    CLASS_SIGN,
    CLASS_OTHER
} CharClass;

static const State transition_table[8][5] = {
    //      DIGIT  DOT    E      SIGN   OTHER
    /*Q0*/ {Q1,    ERR,   ERR,   ERR,   ERR},
    /*Q1*/ {Q1,    Q2,    Q4,    ERR,   ERR},
    /*Q2*/ {Q3,    ERR,   ERR,   ERR,   ERR},
    /*Q3*/ {Q3,    ERR,   Q4,    ERR,   ERR},
    /*Q4*/ {Q6,    ERR,   ERR,   Q5,    ERR},
    /*Q5*/ {Q6,    ERR,   ERR,   ERR,   ERR},
    /*Q6*/ {Q6,    ERR,   ERR,   ERR,   ERR},
    /*ERR*/{ERR,   ERR,   ERR,   ERR,   ERR}
};

int get_char_class(char c) {
    if (isdigit(c)) return CLASS_DIGIT;
    if (c == '.') return CLASS_DOT;
    if (c == 'E') return CLASS_E;
    if (c == '+' || c == '-') return CLASS_SIGN;
    return CLASS_OTHER;
}

int match(const char* str) {
    State cur = Q0;
    for (int i = 0; str[i] != '\0'; i++) {
        int class = get_char_class(str[i]);
        cur = transition_table[cur][class];
        if (cur == ERR) return 0;
    }
    return (cur == Q1 || cur == Q3 || cur == Q6);
}

void print_transition_table(void) {
    printf("\n=== ТАБЛИЦА ПЕРЕХОДОВ ДКА ===\n");
    printf("---------------------------------------------\n");
    printf("Состояние | digit |  .   |  E   | + / - | другое\n");
    printf("---------------------------------------------\n");
    
    const char* state_names[] = {"Q0", "Q1", "Q2", "Q3", "Q4", "Q5", "Q6", "ERR"};
    const char* class_names[] = {"digit", ".", "E", "+/-", "other"};
    
    for (int s = 0; s <= ERR; s++) {
        printf("   %-2s     |", state_names[s]);
        for (int c = 0; c < 5; c++) {
            State next = transition_table[s][c];
            if (next == ERR) 
                printf("  -   |");
            else
                printf("  %-2s  |", state_names[next]);
        }
        printf("\n");
    }
    printf	"-----\n");
    printf("Допускающие состояния: Q1, Q3, Q6\n");
    printf(	"=====\n");
}
