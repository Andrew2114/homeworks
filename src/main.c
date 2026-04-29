#include "database.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

static void print_help(void) {
    printf("Команды: find <код>, add <код>:<название>, delete <код>, save, quit\n");
}

static void handle_find(Database* db, const char* arg) {
    char code[4];
    if (sscanf(arg, "%3s", code) != 1) {
        printf("Использование: find <код>\n");
        return;
    }
    trim(code);
    
    const char* name = db_find(db, code);
    if (name) {
        printf("%s → %s\n", code, name);
    } else {
        printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
    }
}

static void handle_add(Database* db, const char* arg) {
    char* colon = strchr(arg, ':');
    if (!colon) {
        printf("Неверный формат. Нужно: add SVO:Шереметьево\n");
        return;
    }
    
    char code[4];
    char name[256];
    
    int code_len = colon - arg;
    if (code_len > 3) {
        printf("Код должен быть 3 символа\n");
        return;
    }
    
    strncpy(code, arg, code_len);
    code[code_len] = '\0';
    strcpy(name, colon + 1);
    
    trim(code);
    trim(name);
    
    int result = db_add(db, code, name);
    if (result == -1) {
        printf("Неверный формат кода или названия.\n");
    } else if (result == -2) {
        printf("Аэропорт с кодом '%s' уже существует.\n", code);
    } else {
        printf("Аэропорт '%s' добавлен в базу.\n", code);
    }
}

static void handle_delete(Database* db, const char* arg) {
    char code[4];
    if (sscanf(arg, "%3s", code) != 1) {
        printf("Использование: delete <код>\n");
        return;
    }
    trim(code);
    
    int result = db_delete(db, code);
    if (result == -1) {
        printf("Аэропорт с кодом '%s' не найден.\n", code);
    } else {
        printf("Аэропорт '%s' удалён из базы.\n", code);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Использование: %s <файл>\n", argv[0]);
        return 1;
    }
    
    Database* db = db_create(argv[1]);
    if (!db) {
        printf("Ошибка создания базы данных\n");
        return 1;
    }
    
    if (db_load(db) != 0) {
        printf("Ошибка загрузки файла %s\n", argv[1]);
        db_destroy(db);
        return 1;
    }
    
    printf("Загружено %d аэропортов. Система готова к работе.\n\n", db_get_count(db));
    
    char line[512];
    char cmd[20];
    char arg[300];
    
    while (1) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        line[strcspn(line, "\n")] = '\0';
        
        if (sscanf(line, "%19s %299[^\n]", cmd, arg) < 1) continue;
        
        if (strcmp(cmd, "find") == 0) {
            handle_find(db, arg);
        } else if (strcmp(cmd, "add") == 0) {
            handle_add(db, arg);
        } else if (strcmp(cmd, "delete") == 0) {
            handle_delete(db, arg);
        } else if (strcmp(cmd, "save") == 0) {
            if (db_save(db) == 0) {
                printf("База сохранена: %d аэропортов.\n", db_get_count(db));
            } else {
                printf("Ошибка сохранения.\n");
            }
        } else if (strcmp(cmd, "quit") == 0) {
            break;
        } else {
            print_help();
        }
        printf("\n");
    }
    
    db_destroy(db);
    return 0;
}
