#include "csv_parser.h"
#include "table_printer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    const char* input_file = "input.csv";
    const char* output_file = "output.txt";

    if (argc > 1) {
        input_file = argv[1];
    }
    if (argc > 2) {
        output_file = argv[2];
    }

    Table* t = parse_csv_file(input_file);
    if (t == NULL) {
        printf("Cannot open file %s or parse error\n", input_file);
        return -1;
    }

    if (print_table_to_file(t, output_file) != 0) {
        printf("Error writing to file %s\n", output_file);
        free_table(t);
        return -1;
    }

    free_table(t);
    printf("Success! Table written to %s\n", output_file);
    return 0;
}
