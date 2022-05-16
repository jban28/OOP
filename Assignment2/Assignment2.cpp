
// PHYS 30762 Programming in C++
// Assignment 2

#include<cmath>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
#include<iostream>
#include <algorithm>

int integer_input(int lower_bound = -2147483647, int upper_bound = 2147483647)
/* Takes a user input as a string and (if possible) recasts it as an integer and
returns it, providing the integer value is between the upper and lower bounds. 
If an integer between the bounds cannot be returned, the input is repeated */
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
			std::cout << "Input must be between " << lower_bound << " and " 
			<< upper_bound << ", try again." <<std::endl;
		}
		catch(...){
			std::cout << "Input must be an integer, try again." << std::endl;
		}
	}
  return integer;
}

struct course 
{
  int year;
  int code;
  std::string name;
  double mark;
};

bool Compare_09(course a, course b)
// Comparison operator used for sorting course list by code
{
	return a.code < b.code;
}

bool Compare_AZ(course a, course b)
// Comparison operator used for sorting course list by name
{
	return a.name < b.name;
}

void print_courses(std::vector<course> data)
// Display all courses from the the data vector as string streams
{
  std::vector<course>::iterator start{data.begin()};
  std::vector<course>::iterator end{data.end()};
  std::vector<course>::iterator course;

  std::cout << "\n" << std::endl;

  for(course = start ; course < end ; ++course){
    std::cout << "PHYS " << (*course).code << " " << (*course).name << std::endl;
  }
}

void mean_std_dev_std_err(std::vector<course> data)
{
  double sum;
  double sum_residuals_squared{0};
  double mean;
  double std_dev;
  double std_err;
  int N_data = data.size();

  std::vector<course>::iterator start{data.begin()};
  std::vector<course>::iterator end{data.end()};
  std::vector<course>::iterator course;

  // Calculate the sum of course marks used for calculating the mean
  for(course = start ; course < end ; ++course){
    sum += (*course).mark;
  }
  mean = sum/N_data;

  // Calculate the sum of square residuals used for standard deviation
  for(course = start ; course < end ; ++course){
    sum_residuals_squared += std::pow(((*course).mark-mean), 2);
  }

  std_dev = std::sqrt(sum_residuals_squared/(N_data-1));
  std_err = std_dev/std::sqrt(N_data);

  std::cout << "\nMean = " << mean << "\nStandard Deviation = " << std_dev << 
  "\nStandard Error = " << std_err << std::endl;
}

std::vector<course> filter_by_year(std::vector<course> data, int year)
/* Returns a vector of all courses which have the first digit of the code equal
to the year argument, or returns all courses if the year argument is 0*/
{
  std::vector<course> data_for_year;

  if (year == 0){
    data_for_year = data;
  }

  else{
    std::vector<course>::iterator start{data.begin()};
    std::vector<course>::iterator end{data.end()};
    std::vector<course>::iterator course;
    for(course = start ; course < end ; ++course){
      if ((*course).year == year){
        data_for_year.push_back(*course);
      }
      else{
        continue;
      }
    }
  }
  return data_for_year;
}

int main()
{
  std::vector<course> course_data;
  int option; int year{0};
  std::string filename;

  std::cout << "\nThis program displays information about physics courses at" 
  " the University of Manchester. Please input the filepath you would like to"
  " retrieve data from." << std::endl;
  
  while (true){
    // Open file from user input
    std::cin >> filename;
    std::fstream file_to_read{filename};

    if(file_to_read.good()) {
      /* If user input file exists, read line by line, pick out information 
      for each course and store it as a vector*/
      int i{0}; std::string line;
      while (std::getline(file_to_read, line)){
        course_data.push_back(course());
        course_data[i].year = std::stoi(line.substr(5,1));
        course_data[i].code = std::stoi(line.substr(5, 5));
        course_data[i].name = line.substr(13, line.npos);
        course_data[i].mark = std::stod(line.substr(0, 4));
        i += 1;
      }
      std::cout << "\n" << course_data.size() << " courses retrieved"<< std::endl;
      file_to_read.close();
      break;
    }
    else{
      std::cout << "Could not read file, please input a valid filename" 
      << std::endl;
      continue;
    }
  }

  while (true){
    std::cout << "\nEnter a number to choose between the following options:"
    "\n [1]: Sort courses by name (A-Z)"
    "\n [2]: Sort courses by code (0-9)"
    "\n [3]: Print out course names and codes"
    "\n [4]: Compute mean, standard deviation, and standard error for marks"
    "\n [5]: Filter by year"
    "\n [6]: Exit"
    << std::endl;

    option = integer_input(1,6);

    if (option == 1){
      // Sort A-Z
      std::sort(course_data.begin(), course_data.end(), Compare_AZ);
      continue;
    }
    else if (option == 2){
      // Sort 0-9
      std::sort(course_data.begin(), course_data.end(), Compare_09);
      continue;
    }
    else if (option == 3){
      // Print out courses in year selected (or all years if year=0)
      print_courses(filter_by_year(course_data, year));
      continue;
    }
    else if (option == 4){
      // Calculate stats for courses in year selected (or all years if year=0)
      mean_std_dev_std_err(filter_by_year(course_data, year));
      continue;
    }
    else if (option == 5){
      // Allow user input for year to view
      std::cout << "Select which year to view (or input 0 to show all)" 
      << std::endl;
      year = integer_input(0,4);
      continue;
    }
    else if (option == 6){
      break;
    }
    else{
      continue;
    }
  }
  return 0;
}