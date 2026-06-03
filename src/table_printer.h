#pragma once

#include "csv_parser.h"

int print_table_to_file(Table* t, const char* filename);
int print_table_to_file_with_header(Table* t, const char* filename);
