#include <iostream>
#include <string>
#include <stack>

void Algorithm_Dijkstra_and_Reverse_Polish_Entry(const std::string &expression);
std::string validator(const std::string &expression);

void calculation(std::stack<float> &digits, std::stack<char> &operations);

void INPUT_INFO(const std::string &input_info);
void INFO(int info_num, const std::string expression = "", float num = 0.0f);
void ERROR(int err_num);