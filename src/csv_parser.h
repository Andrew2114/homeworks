#pragma once

typedef struct {
    int rows;
    int cols;
    char*** data;
} Table;

Table* create_table(void);
void free_table(Table* t);
int add_row(Table* t, const char* line);
Table* parse_csv_file(const char* filename);
