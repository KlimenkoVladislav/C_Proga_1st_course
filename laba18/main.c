#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <setjmp.h>
#include <cmocka.h>

/**
 * Парсит строку вида "key:value" и валидирует типы данных
 * Формат: ключ - буквы/цифры, значение - число или строка в кавычках
 * 
 * Возвращает код ошибки:
 *   0 - успех
 *   1 - нет разделителя ':'
 *   2 - пустой ключ
 *   3 - недопустимые символы в ключе
 *   4 - некорректное значение (пустое)
 *   5 - строковое значение без закрывающей кавычки
 *   6 - нечисловое значение (когда ожидается число)
 */
int parse_key_value(const char* str, char* out_key, int* out_number, char* out_string) {
    if (!str || !out_key || !out_number || !out_string) return 1;
    
    // Находим разделитель
    const char* colon = strchr(str, ':');
    if (!colon) return 1;
    
    // Извлекаем ключ
    int key_len = colon - str;
    if (key_len == 0) return 2;
    
    for (int i = 0; i < key_len; i++) {
        if (!isalnum(str[i]) && str[i] != '_') return 3;
        out_key[i] = str[i];
    }
    out_key[key_len] = '\0';
    
    // Проверяем значение
    const char* value_start = colon + 1;
    while (isspace(*value_start)) value_start++;
    
    if (*value_start == '\0') return 4;
    
    // Если значение в кавычках - строка
    if (*value_start == '"') {
        const char* quote_end = strchr(value_start + 1, '"');
        if (!quote_end) return 5;
        
        int str_len = quote_end - (value_start + 1);
        strncpy(out_string, value_start + 1, str_len);
        out_string[str_len] = '\0';
        *out_number = 0;
        return 0;
    }
    
    // Иначе пробуем число
    char* endptr;
    long val = strtol(value_start, &endptr, 10);
    
    // Проверяем, что распарсили всё до конца строки
    while (isspace(*endptr)) endptr++;
    if (*endptr != '\0') return 6;
    
    *out_number = (int)val;
    out_string[0] = '\0';
    return 0;
}


// Тестирую код шайтан-машины (Дипсика)
// Тест 1: Корректное числовое значение
static void test_parse_number(void **state) {    
    char key[100];
    char str[100];
    int num;
    
    int result = parse_key_value("age:25", key, &num, str);
    
    assert_int_equal(result, 0);
    assert_string_equal(key, "age");
    assert_int_equal(num, 25);
}

// Тест 2: Корректное строковое значение в кавычках
static void test_parse_string(void **state) {    
    char key[100];
    char str[100];
    int num;
    
    int result = parse_key_value("name:\"John\"", key, &num, str);
    
    assert_int_equal(result, 0);
    assert_string_equal(key, "name");
    assert_string_equal(str, "John");
}

// Тест 3: Отсутствует разделитель ':'
static void test_missing_colon(void **state) {
    char key[100];
    char str[100];
    int num;
    
    int result = parse_key_value("invalid", key, &num, str);
    
    assert_int_equal(result, 1);
}

// Тест 4: Недопустимые символы в ключе
static void test_invalid_key_chars(void **state) {
    char key[100];
    char str[100];
    int num;
    
    int result = parse_key_value("user-name:123", key, &num, str);
    
    assert_int_equal(result, 3);
}

// Тест 5: Незакрытая кавычка в строковом значении
static void test_unclosed_quote(void **state) {
    char key[100];
    char str[100];
    int num;
    
    int result = parse_key_value("text:\"hello", key, &num, str);
    
    assert_int_equal(result, 5);
}

// Тест 6: Нечисловое значение
static void test_non_numeric_value(void **state) {
    char key[100];
    char str[100];
    int num;
    
    int result = parse_key_value("count:abc", key, &num, str);
    
    assert_int_equal(result, 6);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_parse_number),
        cmocka_unit_test(test_parse_string),
        cmocka_unit_test(test_missing_colon),
        cmocka_unit_test(test_invalid_key_chars),
        cmocka_unit_test(test_unclosed_quote),
        cmocka_unit_test(test_non_numeric_value),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}