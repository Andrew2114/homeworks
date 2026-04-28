#include "table_printer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int* calculate_column_widths(Table* t) {
    int* col_width = malloc(sizeof(int) * t->cols);
    if (col_width == NULL)
        return NULL;

    for (int i = 0; i < t->cols; i++) {
        col_width[i] = 0;
    }

    for (int i = 0; i < t->rows; i++) {
        for (int j = 0; j < t->cols; j++) {
            int len = strlen(t->data[i][j]);
            if (len > col_width[j])
                col_width[j] = len;
        }
    }

    return col_width;
}

static void print_horizontal_line(FILE* f, int* col_width, int cols, char line_char) {
    fprintf(f, "+");
    for (int j = 0; j < cols; j++) {
        for (int k = 0; k < col_width[j]; k++) {
            fprintf(f, "%c", line_char);
        }
        fprintf(f, "+");
    }
    fprintf(f, "\n");
}

static void print_header(FILE* f, Table* t, int* col_width) {
    print_horizontal_line(f, col_width, t->cols, '=');
    fprintf(f, "|");
    for (int j = 0; j < t->cols; j++) {
        fprintf(f, "%-*s|", col_width[j], t->data[0][j]);
    }
    fprintf(f, "\n");
    print_horizontal_line(f, col_width, t->cols, '=');
}

static void print_data_rows(FILE* f, Table* t, int* col_width) {
    for (int i = 1; i < t->rows; i++) {
        fprintf(f, "|");
        for (int j = 0; j < t->cols; j++) {
            if (is_number(t->data[i][j])) {
                fprintf(f, "%*s|", col_width[j], t->data[i][j]);
            } else {
                fprintf(f, "%-*s|", col_width[j], t->data[i][j]);
            }
        }
        fprintf(f, "\n");

        if (i < t->rows - 1) {
            print_horizontal_line(f, col_width, t->cols, '-');
        }
    }
}

int print_table_to_file_with_header(Table* t, const char* filename) {
    if (t == NULL || t->rows == 0)
        return -1;

    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        return -1;
    }

    int* col_width = calculate_column_widths(t);
    if (col_width == NULL) {
        fclose(f);
        return -1;
    }

    print_header(f, t, col_width);
    print_data_rows(f, t, col_width);

    free(col_width);
    fclose(f);
    return 0;
}

int print_table_to_file(Table* t, const char* filename) {
    return print_table_to_file_with_header(t, filename);
}

