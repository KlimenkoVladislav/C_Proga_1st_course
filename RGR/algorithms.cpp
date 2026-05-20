#include "head.hpp"
#include <unordered_map>
#include <math.h>

void Algorithm_Dijkstra_and_Reverse_Polish_Entry(const std::string &expression){
    /* Алгоритм Дейкстры и обратной польской записи за один проход
                    (то есть вычисления "онлайн")
        - Input: строка
        - Output: число

        Если элемент - число, то оно сразу кладётся в стек чисел.
        Если элемент - знак, то
            - если стек операций пуст, сразу кладём туда знак;
            - если знаком является открывающая скобка, то кладём 
              её в стек операций. Так как она имеет приоритет 0, 
              происходит обнуление приоритетов;
            - если знаком является закрывающая скобка, то 
              вытаскиваем из стека все операции, выполняя их.
              Проводим данные действия пока не вытащим открывающую
              скобку;
            - если знаком является обычная операция, то сверяем
              приоритеты по словарю. Если приоритет данной операции
              выше приоритета операции, лежащей на вершине стека,
              кладём в стек.
              Иначе берём последнюю операцию из стека операций и
              2 числа из стека чисел, проводим соответствующее
              действие, после чего результат кладём в стек чисел,
              а новую операцию - в стек операций.
        Если строка закончилась, вытаскиваем все операции по одной
        из стека операций и проводим соответствующие действия над
        последними двумя числами стека чисел, после чего результат
        кладём обратно в стек чисел. Делаем данные действия, пока
        стек операций не опустеет.
    */

    static const std::unordered_map<char, int> priority = {
        {'(', 0},
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2},
        {'^', 3}
    };

    std::stack<float> digits;
    std::stack<char> operations;

    std::string digit;
    for (char elem : expression){
        if (std::isdigit(elem) or elem == '.'){
            digit += elem;
        }
        else if (elem == '~'){
            digit += '-';
        }
        else if (elem == 'p'){
            digits.push(M_PI);
        }
        else {
            if (!digit.empty()){
                digits.push(std::stof(digit));
                digit.clear();
            }
            if (operations.empty() or (elem == '(')){
                operations.push(elem);
            }
            else if (elem == ')'){
                while (operations.top() != '('){
                    calculation(digits, operations);
                }
                operations.pop();
            }
            else if (priority.at(elem) > priority.at(operations.top())){
                operations.push(elem);
            }
            else {
                calculation(digits, operations);
                operations.push(elem);
            }
        }
    }
    if (!digit.empty()){ digits.push(std::stof(digit)); }
    while (!operations.empty()){
        calculation(digits, operations);
    }

    INFO(4, "", digits.top());
}

std::string validator(const std::string &expression){
    /*                  Валидатор входных данных
        На вход получает исходную строку, содержащую выражение. 
        Проверяет:
         - корректность количества идущих подряд операций;
         - деление на 0;
         - корректность работы с float;
         - наличие корней, синусов или косинусов. В случае 
           их присутствия в выражении, они заменяются на 
           'r', 's' и 'c' соответственно;
         - закрытие скобок.

        - Преобразует унарный минус в "~", что бы в алгоритме 
          Дейктсры было чёткое отличие от обычного минуса;
        - Обрабатывает число pi.
    */
    std::string new_string;

    char prev = '0';
    int kol_operations_in_a_row = 0;
    int kol_open_brackets = 0;
    std::string long_name_func;
    if (expression[0] == '-'){ new_string = "0"; }
    for (const char elem : expression){
        if (long_name_func.empty()){
            if ((elem == '-') and (!std::isdigit(prev)) and (prev != ')')){
                new_string.push_back('~');
                kol_operations_in_a_row = 1;
            }
            else if ((elem == 's') or (elem == 'c')){
                long_name_func += elem;
                kol_operations_in_a_row = 1;
            }
            else if (((prev == 's') or (prev == 'c') or 
                      (prev == 'r')) and (elem != '(')){
                ERROR(3);
                new_string.clear();
                return new_string;
            }
            else if ((elem == '.') and (std::isdigit(prev))){
                kol_operations_in_a_row = 2;
                new_string.push_back(elem);
            }
            else if (elem == 'p'){
                long_name_func += elem;
                kol_operations_in_a_row = 0;
            }
            else if ((kol_operations_in_a_row == 2) and !std::isdigit(elem)){
                ERROR(3);
                new_string.clear();
                return new_string;
            }
            else if ((elem == '0') and (prev == '/')){
                ERROR(4);
                new_string.clear();
                return new_string;
            }
            else if (elem == '('){
                new_string.push_back(elem);
                kol_operations_in_a_row = 0;
                kol_open_brackets++;
            }
            else if (elem == ')'){
                new_string.push_back(elem);
                kol_operations_in_a_row = 0;
                kol_open_brackets--;
            }
            else {
                kol_operations_in_a_row++;
                new_string.push_back(elem);
                if (std::isdigit(elem)){ kol_operations_in_a_row = 0; }
            }
            prev = elem;
        }
        else {
            if (((prev == 's') and ((elem == 'i') or (elem == 'q'))) or
                ((prev == 'i') and (elem == 'n')) or
                ((prev == 'q') and (elem == 'r')) or
                ((prev == 'r') and (elem == 't')) or
                ((prev == 'c') and (elem == 'o')) or
                ((prev == 'o') and (elem == 's'))){
                long_name_func += elem;
                prev = elem;
            }
            else if ((prev == 'p') and (elem == 'i')){
                new_string += 'p';
                long_name_func.clear();
                prev = '0';
            }
            else {
                ERROR(3);
                new_string.clear();
                return new_string;
            }
            if (long_name_func == "sin"){
                new_string += 's';
                long_name_func.clear();
                prev = 's';
            }
            else if (long_name_func == "cos"){
                new_string += 'c';
                long_name_func.clear();
                prev = 'c';
            }
            else if (long_name_func == "sqrt"){
                new_string += 'r';
                long_name_func.clear();
                prev = 'r';
            }
        }
    }

    if (kol_open_brackets != 0){ ERROR(5); new_string.clear(); }
    return new_string;  
}