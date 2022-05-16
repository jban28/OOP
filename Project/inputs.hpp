#include<string>
#include<vector>

#ifndef _inputs
#define _inputs

int integer_input(int lower_bound = -2147483647, int upper_bound = 2147483647);
double double_input(double lower_bound = -1.7976931348623157E+308, 
double upper_bound = 1.7976931348623157E+308);
std::string input_string_from_options(std::vector<std::string> options);
std::string string_input();

#endif