#include "head.hpp"
#include <sstream>
#include <fstream>

int main(){
    while (true){
        int choice;
        do{
            INFO(1);
            std::cin >> choice;
        } while (choice < 0 and choice > 2);
        INPUT_INFO(std::to_string(choice));
        std::cin.ignore();

        if (choice == 0){ return 0; }
        else if (choice == 1){
            std::string expression;
            INFO(2);
            std::getline(std::cin, expression);
            INPUT_INFO(expression);
            expression = validator(expression);
            if (!expression.empty()){ Algorithm_Dijkstra_and_Reverse_Polish_Entry(expression); }
            else { ERROR(1); continue; }
        }
        else {
            std::string file_name;
            INFO(3);
            std::getline(std::cin, file_name);
            std::ifstream file(file_name);
            if (!file.is_open()){
                ERROR(2);
                continue;
            }

            std::string expression;
            while (std::getline(file, expression)){
                INPUT_INFO(expression);
                expression = validator(expression);
                if (!expression.empty()){
                    INFO(3, expression);
                    Algorithm_Dijkstra_and_Reverse_Polish_Entry(expression);
                }
                else { ERROR(1); return -1; }
            }

            file.close();
        }
    }
}