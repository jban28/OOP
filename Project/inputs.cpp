#include "inputs.hpp"

int menu(std::string prompt, std::vector<std::string> options)
{
  int index = 1;
  std::cout << "\n" << prompt << std::endl;
  std::vector<std::string>::iterator start{options.begin()};
  std::vector<std::string>::iterator end{options.end()};
	std::vector<std::string>::iterator option;
  for(option = start ; option < end ; ++option){
    std::cout << index << " : " << *option << std::endl;
    index += 1;
  }
  return user_input<int>(1,index-1);
}


bool validate(double input, std::string input_string)
{
  bool valid;
  if ((input_string.find_first_not_of("+-0123456789.e") 
  == std::string::npos) && (input_string.find_first_of("e") ==
  input_string.find_last_of("e")) && (input_string.find_first_of(".") ==
  input_string.find_last_of(".")) && ((input_string.find_first_of("e")>=
  input_string.find_last_of("."))) || (input_string.find_last_of(".") == 
  std::string::npos)){
      return true;
  }
  else{
    return false;
  }
}

bool validate(int input, std::string input_string)
{
  if (input_string.find_first_not_of("+-0123456789") == std::string::npos){
    return true;
  }
  else{
    return false;
  }
}

bool validate (std::string input, std::string input_string)
{
  return true;
}