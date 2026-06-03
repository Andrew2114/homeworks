#include "csv_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Table* create_table(void)
{
    Table* t = malloc(sizeof(Table));
    if (t == NULL)
        return NULL;
    t->data = NULL;
    t->rows = 0;
    t->cols = 0;
    return t;
}

void free_table(Table* t)
{
    if (t == NULL) {
        return;
    }

    for (int i = 0; i < t->rows; i++) {
        for (int j = 0; j < t->cols; j++) {
            free(t->data[i][j]);
        }
        free(t->data[i]);
    }

    free(t->data);
    free(t);
}

int add_row(Table* t, const char* line)
{
    if (t == NULL || line == NULL)
        return -1;

    int new_row_count = t->rows + 1;

    char*** new_data = realloc(t->data, sizeof(char**) * new_row_count);
    if (new_data == NULL)
        return -1;
    t->data = new_data;

    char temp[1024];
    strcpy(temp, line);

    // Подсчет колонок
    int col_count = 0;
    char* token = strtok(temp, ",\n");
    while (token != NULL) {
        col_count++;
        token = strtok(NULL, ",\n");
    }

    t->data[t->rows] = malloc(sizeof(char*) * col_count);
    if (t->data[t->rows] == NULL)
        return -1;

    strcpy(temp, line);
    token = strtok(temp, ",\n");
    int col_index = 0;
    while (token != NULL) {
        char* field = malloc(strlen(token) + 1);
        if (field == NULL)
            return -1;
        strcpy(field, token);
        t->data[t->rows][col_index] = field;
        col_index++;
        token = strtok(NULL, ",\n");
    }

    if (t->cols == 0) {
        t->cols = col_count;
    }

    t->rows = new_row_count;
    return 0;
}

Table* parse_csv_file(const char* filename)
{
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        return NULL;
    }

    Table* t = create_table();
    if (t == NULL) {
        fclose(f);
        return NULL;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (add_row(t, buffer) != 0) {
            free_table(t);
            fclose(f);
            return NULL;
        }
    }

    fclose(f);
    return t;
}
