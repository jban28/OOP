#include<string>
#include<iostream>
#include<sstream>
#include<vector>
#include<limits>

#ifndef _inputs
#define _inputs

int menu(std::string prompt, std::vector<std::string> options);

bool validate(double input, std::string input_string);
bool validate(int input, std::string input_string);
bool validate (std::string input, std::string input_string);

template<typename type> 
type user_input()
{
  while(true){
    type input;
    char input_char[256];
    std::stringstream input_stream;
    std::cin.getline(input_char,256);
    std::string input_string{input_char};
    input_stream << input_char;
    try{
      input_stream >> input;
      if (validate(input, input_string) && !(input_stream.fail())){
        return input;        
      }
      else{
        throw(input);
      }
    }
    catch(std::string input_err){
      std::cout << "Input cannot be converted to converted to string" <<
      ", please try again" << std::endl;
    }
    catch(double input_err){
      std::cout << "Input cannot be converted to converted to number" << 
      ", please try again" << std::endl;
    }
    catch(int input_err){
      std::cout << "Input cannot be converted to converted to integer" << 
      ", please try again" << std::endl;
    }
  }
};

// Overload for taking a user input that must match one element from a vector of
// options
template<typename type>
type user_input(std::vector<type> options)
{
  while(true){
    type input = user_input<type>();
    try{
      typename std::vector<type>::iterator start{options.begin()};
      typename std::vector<type>::iterator end{options.end()};
      typename std::vector<type>::iterator option;
      for(option = start ; option < end ; ++option){
        if (*option == input){
          return input;
        }
        else{
          continue;
        }
      }
      throw(input);
    }
    catch(std::string invalid_input){
      std::cout << "Input must be one of: ";
      typename std::vector<type>::iterator start{options.begin()};
			typename std::vector<type>::iterator end{options.end()};
			typename std::vector<type>::iterator option;
      for(option = start ; option < end ; ++option){
				std::cout << "'" << *option << "', ";
			}
			std::cout << std::endl;
    }
  }
};

template<typename type> 
type user_input(type min, type max)
{
  while(true){
    type input = user_input<type>();
    try{
      if ((input < min) || (input > max)){
        throw(input);
      }
      else{
        return input;
      }
    }
    catch(type invalid_input){
      std::cout << "Input must be between " << min << " and " << max << 
      ", please try again:" << std::endl;
    }
  }
};

#endif