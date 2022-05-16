#include "inputs.hpp"

#include<iostream>
#include<string>
#include<vector>
#include<limits>

std::string string_input()
{
	char input_char[256];
	std::cin.getline(input_char,256);
	std::string input(input_char);
	return input;
}

int integer_input(int lower_bound, int upper_bound)
/* Takes a user input as a string and (if possible) recasts it as an integer and
returns it, providing the integer value is between the upper and lower bounds. 
If an integer between the bounds cannot be returned, the input is repeated */
{
	std::string input_string;
  int integer;
	while(true){
		input_string = string_input();
		try{
			integer = std::stoi(input_string);
			if (integer <= upper_bound && integer >= lower_bound){
				break;
			}
			throw(input_string);
		}
		catch(std::string error){
			std::cout << "Input must be between " << lower_bound << " and " 
			<< upper_bound << ", try again." <<std::endl;
		}
		catch(...){
			std::cout << "Input must be an integer, try again." << std::endl;
		}
	}
  return integer;
}

double double_input(double lower_bound, 
double upper_bound)
/* Takes a user input as a string and (if possible) recasts it as a double and
returns it, providing the double value is between the upper and lower bounds. 
If a double between the bounds cannot be returned, the input is repeated */
{
	std::string input_string;
  double temp_double;
	while(true){
		input_string = string_input();
		try{
			temp_double = std::stod(input_string);
			if (temp_double <= upper_bound && temp_double >= lower_bound){
				break;
			}
			throw(input_string);
		}
		catch(std::string error){
			std::cout << "Input must be between " << lower_bound << " and " 
			<< upper_bound << ", try again." <<std::endl;
		}
		catch(...){
			std::cout << "Input must be an number, try again." << std::endl;
		}
	}
  return temp_double;
}

std::string input_string_from_options(std::vector<std::string> options)
{
	bool valid_input = false;
	std::string input_string;
	while(valid_input == false){
		input_string = string_input();
		std::vector<std::string>::iterator start{options.begin()};
		std::vector<std::string>::iterator end{options.end()};
		std::vector<std::string>::iterator option;
		for(option = start ; option < end ; ++option){
			if (*option == input_string){
				valid_input = true;
				break;
			}
			else{
				continue;
			}
		}
		if (valid_input == false){
			std::cout << "Invalid input, must be one of ";
			std::vector<std::string>::iterator start{options.begin()};
			std::vector<std::string>::iterator end{options.end()};
			std::vector<std::string>::iterator option;
			for(option = start ; option < end ; ++option){
				std::cout << "'" << *option << "', ";
			}
			std::cout << std::endl;
		}
	}
  return input_string;
}