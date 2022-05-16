#include<string>
#include<iostream>
#include<sstream>
#include<vector>

template<typename type> 
type user_input()
{
  while(true){
    type input;
    char input_char[256];
    std::stringstream input_stream;
    std::cin.getline(input_char,256);
    input_stream << input_char;
    try{
      input_stream >> input;

      if (input_stream.fail()){
        throw(input);
      }
      else{
        return input;
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
}

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
}

std::string user_input(std::vector<std::string> options)
{
  while(true){
    std::string input = user_input<std::string>();
    try{
      std::vector<std::string>::iterator start{options.begin()};
      std::vector<std::string>::iterator end{options.end()};
      std::vector<std::string>::iterator option;
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
      std::vector<std::string>::iterator start{options.begin()};
			std::vector<std::string>::iterator end{options.end()};
			std::vector<std::string>::iterator option;
      for(option = start ; option < end ; ++option){
				std::cout << "'" << *option << "', ";
			}
			std::cout << std::endl;
    }
  }
}

int main()
{
  int test = user_input<double>(2, 4);
  return 0;
}