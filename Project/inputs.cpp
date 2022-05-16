#include "inputs.hpp"

int menu(std::string prompt, std::string options[], const int length)
{
  std::cout << "\n" << prompt << std::endl;
  for(int i=0; i<length; i++){
    std::cout << i+1 << " : " << options[i] << std::endl;
  }
  return user_input<int>(1,length);
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
  if (input_string.find_first_of(" ") != std::string::npos){
    return false;
  }
  else{
    return true;
  }
}