#include<iostream>
#include<sstream>
#include<iomanip>
#include<string>

int integer_input(int lower_bound = -2147483647, int upper_bound = 2147483647)
{
	std::string input_string{};
	std::string exception1{};
  int integer;
	while(true){
		std::cin >> input_string;
		try{
			integer = std::stoi(input_string);
			if (integer <= upper_bound && integer >= lower_bound){
				break;
			}
			throw(input_string);
		}
		catch(std::string error){
			std::cout << "Input must be between " << lower_bound << " and " << upper_bound << " , try again." <<std::endl;
		}
		catch(...){
			std::cout << "Input must be an integer, try again." << std::endl;
		}
	}
  return integer;
}

int main()
{
  integer_input(1,3);
  return 0;
}