#include "../src/csv_parser.h"
#include "test_utils.h"
#include <stdio.h>
#include <string.h>

TEST(test_create_table)
{
    Table* t = create_table();
    ASSERT(t != NULL);
    ASSERT(t->rows == 0);
    ASSERT(t->cols == 0);
    ASSERT(t->data == NULL);
    free_table(t);
}

TEST(test_add_row)
{
    Table* t = create_table();
    ASSERT(add_row(t, "col1,col2,col3") == 0);
    ASSERT(t->rows == 1);
    ASSERT(t->cols == 3);

    ASSERT(add_row(t, "a,b,c") == 0);
    ASSERT(t->rows == 2);
    ASSERT(t->cols == 3);

    ASSERT(strcmp(t->data[0][0], "col1") == 0);
    ASSERT(strcmp(t->data[0][1], "col2") == 0);
    ASSERT(strcmp(t->data[0][2], "col3") == 0);

    free_table(t);
}

TEST(test_parse_csv_file)
{
    // Создаем временный CSV файл
    FILE* f = fopen("test_input.csv", "w");
    fprintf(f, "Name,Age,City\n");
    fprintf(f, "John,25,NYC\n");
    fprintf(f, "Jane,30,LA\n");
    fclose(f);

    Table* t = parse_csv_file("test_input.csv");
    ASSERT(t != NULL);
    ASSERT(t->rows == 3);
    ASSERT(t->cols == 3);

    ASSERT(strcmp(t->data[0][0], "Name") == 0);
    ASSERT(strcmp(t->data[1][1], "25") == 0);
    ASSERT(strcmp(t->data[2][2], "LA") == 0);

    free_table(t);
    remove("test_input.csv");
}

TEST(test_parse_csv_file_not_found)
{
    Table* t = parse_csv_file("nonexistent.csv");
    ASSERT(t == NULL);
}
