#include "head.hpp"
#include <fstream>

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

void INPUT_INFO(const std::string &input_info){
    std::ofstream file("/home/vlad/PROGA/Программирование/RGR/output.txt", std::ios::app);
    if (!file.is_open()){
        ERROR(2);
        return;
    }

    file << input_info << "\n";

    file.close();
}

void INFO(int info_num, const std::string expression, float num){
    std::ofstream file("/home/vlad/PROGA/Программирование/RGR/output.txt", std::ios::app);
    if (!file.is_open()){
        ERROR(2);
        return;
    }

    if (info_num == 1){
        std::cout << "Вы хотите задать уравнение из терминала или импортировать его из файла?\n"
                    << GREEN << "1 - из терминала\n" << RESET
                    << GREEN << "2 - импортировать из файла\n" << RESET
                    << RED << "0 - завершить работу\n" << RESET;
        file << "Вы хотите задать уравнение из терминала или импортировать его из файла?\n"
                    << "1 - из терминала\n"
                    << "2 - импортировать из файла\n"
                    << "0 - завершить работу\n";
    }
    else if (info_num == 2){
        std::cout << "Введите уравнение:    ";
        file << "Введите уравнение:    ";
    }
    else if (info_num == 3){
        std::cout << "Укажите путь до файла:    ";
        file << "Укажите путь до файла:    ";
    }
    else if (info_num == 3){
        std::cout << expression << "\n";
        file << expression << "\n";
    }
    else if (info_num == 4){
        std::cout << "Ответ: " << num << "\n\n";
        file << "Ответ: " << num << "\n\n";
    }

    file.close();
}

void ERROR(int err_num){
    std::ofstream file("/home/vlad/PROGA/Программирование/RGR/output.txt", std::ios::app);
    if (!file.is_open()){
        ERROR(2);
        return;
    }

    if (err_num == 1){
        std::cout << RED << "строка задана неверно\n" << RESET;
        file << "строка задана неверно\n";
    }
    else if (err_num == 2){
        std::cout << RED << "Не удалось открыть файл" << RESET 
                         << "Попробуйте ввести путь до другого файла или задайте уравнение из терминала\n";
        file << "Не удалось открыть файл"
             << "Попробуйте ввести путь до другого файла или задайте уравнение из терминала\n";
    }
    else if (err_num == 3){
        std::cout << "Недопустимое расположение символов\n";
        file << "Недопустимое расположение символов\n";
    }
    else if (err_num == 4){
        std::cout << "error: деление на 0!\n";
        file << "error: деление на 0!\n";
    }
    else if (err_num == 5){
        std::cout << "Есть незакрытые скобки\n";
        file << "Есть незакрытые скобки\n";
    }

    file.close();
}