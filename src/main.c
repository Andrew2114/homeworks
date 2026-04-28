#include "finite_automaton.h"
#include <stdio.h>

int main()
{

    print_transition_table();

    printf("\n=== ПРОВЕРКА РАБОТЫ АВТОМАТА ===\n");

    const char* tests[] = {
        "123",
        "456.789",
        "123E45",
        "123E+45",
        "123E-45",
        "1.",
        ".123",
        "E123",
        "123E"
    };

    int n = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n; i++) {
        printf("%-12s -> %s\n", tests[i], match(tests[i]) ? "ПРИНЯТЬ" : "ОТКЛОНИТЬ");
    }

    return 0;
}
