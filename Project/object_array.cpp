#include "object.hpp"
#include "object_array.hpp"
#include "inputs.hpp"
#include "star.hpp"
#include "galaxy.hpp"
#include "cluster.hpp"
#include "nebula.hpp"
#include "planet.hpp"

#include<iostream>
#include<fstream>
#include<sstream>
#include<typeinfo>
#include<string>
#include<vector>

object_array::object_array(){}

object_array::~object_array(){}

void object_array::new_object_from_input()
{
  std::cout << "\nInput object" << std::endl;
  std::cout << "Select object type"
  << "\n1 : Star"
  << "\n2 : Galaxy"
  << "\n3 : Star Cluster" 
  << "\n4 : Nebula"
  << "\n5 : Planet" 
  << std::endl;

  int selection = user_input(1,5);

  switch(selection){
    case 1:{
      array.push_back(std::make_unique<star>(star()));
      break;
    }
    case 2:{
      array.push_back(std::make_unique<galaxy>(galaxy()));
      break;
    }
    case 3:{
      array.push_back(std::make_unique<cluster>(cluster()));
      break;
    }
    case 4:{
      array.push_back(std::make_unique<nebula>(nebula()));
      break;
    }
    case 5:{
      array.push_back(std::make_unique<planet>(planet()));
      break;
    }
  }
}

void object_array::new_object_from_file()
{
  int delimiter_start; int delimiter_end;
  object* new_object;
  while (true){
    std::string filename;
    std::cout << "Input the name of the csv file you would like to load: ";
    filename = user_input<std::string>();
    filename += ".csv";
    std::fstream file{filename};

    if(file.good()) {
      std::string line;

      while (std::getline(file, line)){
        std::string object_type;
        std::string object_name;
        std::string right_acension_string; double right_acension;
        std::string declination_string; double declination;
        std::string luminosity_string; double luminosity;
        std::string distance_string; double distance;
        delimiter_start = 0; delimiter_end = line.find(',', 0);
        object_type = line.substr(delimiter_start, delimiter_end);
        
        delimiter_start = delimiter_end + 1; 
        delimiter_end = line.find(',', delimiter_start);
        object_name = line.substr(delimiter_start, 
        delimiter_end-delimiter_start);

        delimiter_start = delimiter_end + 1; 
        delimiter_end = line.find(',', delimiter_start);
        right_acension_string = line.substr(delimiter_start, 
        delimiter_end-delimiter_start);

        delimiter_start = delimiter_end + 1; 
        delimiter_end = line.find(',', delimiter_start);
        declination_string = line.substr(delimiter_start, 
        delimiter_end-delimiter_start);

        delimiter_start = delimiter_end + 1; 
        delimiter_end = line.find(',', delimiter_start);
        luminosity_string = line.substr(delimiter_start, 
        delimiter_end-delimiter_start);

        delimiter_start = delimiter_end + 1; 
        delimiter_end = line.find(',', delimiter_start);
        distance_string = line.substr(delimiter_start, 
        delimiter_end-delimiter_start);

        right_acension = std::stod(right_acension_string);
        declination = std::stod(declination_string);
        luminosity = std::stod(luminosity_string);
        distance = std::stod(distance_string);

        if (object_type == "star"){
          std::string effective_temperature_string;double effective_temperature;
          delimiter_start = delimiter_end + 1; 
          effective_temperature_string = line.substr(delimiter_start);
          effective_temperature = std::stod(effective_temperature_string);
          array.push_back(std::make_unique<star>(star(object_name, right_acension, 
          declination, luminosity, distance, effective_temperature)));
        }
        else if (object_type == "galaxy"){
          std::string hubble_type;
          delimiter_start = delimiter_end + 1;
          hubble_type = line.substr(delimiter_start);
          array.push_back(std::make_unique<galaxy>(galaxy(object_name, right_acension, 
          declination, luminosity, distance, hubble_type)));
        }
        else if (object_type == "cluster"){
          array.push_back(std::make_unique<cluster>(cluster(object_name, right_acension, 
          declination, luminosity, distance)));
        }
        else if (object_type == "nebula"){
          array.push_back(std::make_unique<nebula>(nebula(object_name, right_acension, 
          declination, luminosity, distance)));
        }
        else if (object_type == "planet"){
          array.push_back(std::make_unique<planet>(planet(object_name, right_acension, 
          declination, luminosity, distance)));
        }
      }
      file.close();
      break;
    }
    else{
      std::cout << "Could not read file, please input a valid filename" 
      << std::endl;
      continue;
    }
  }
}

void object_array::list_all()
{
  std::vector<std::unique_ptr<object>>::iterator start{array.begin()};
  std::vector<std::unique_ptr<object>>::iterator end{array.end()};
  std::vector<std::unique_ptr<object>>::iterator object;
  for(object = start ; object < end ; ++object){
    (*object)->print_data();
  }
}

void object_array::list_type()
{
  int selection;
  std::string type;
  selection = menu("Select object type:", object_type_options);
  type = object_type_options[selection-1];
  std::vector<std::unique_ptr<object>>::iterator start{array.begin()};
  std::vector<std::unique_ptr<object>>::iterator end{array.end()};
  std::vector<std::unique_ptr<object>>::iterator object;
  for(object = start ; object < end ; ++object){
    if ((*object)->return_object_type() == type){
      (*object)->print_data();
    }
    else{
      continue;
    }
  }
}

void object_array::list_by_name(std::string name)
{
  int objects_found = 0;
  std::vector<std::unique_ptr<object>>::iterator start{array.begin()};
  std::vector<std::unique_ptr<object>>::iterator end{array.end()};
  std::vector<std::unique_ptr<object>>::iterator object;
  for(object = start ; object < end ; ++object){
    if ((*object)->return_object_name() == name){
      (*object)->print_data();
      objects_found += 1;
    }
    else{
      continue;
    }
  }
  if (objects_found == 0){
    std::cout << "No object found with that name" << std::endl;
  }
}

void object_array::save_to_file()
{
  std::string filename;
  std::cout << "Type the filename to save the data to: ";
  filename = user_input<std::string>();
  filename += ".csv";
  std::fstream file;
  file.open(filename, std::fstream::in);
  int selection = 1;
  if (file){
    file.close();
    std::vector<std::string> write_options{"Overwrite file", 
    "Append to existing file"};
    selection = menu("File already exists. Please select write method",
    write_options);
  }
  switch(selection){
    case(1):{
      file.open(filename, std::fstream::out);
      break;
    }
    case(2):{
      file.open(filename, std::fstream::app);
      break;
    }
  }
  std::vector<std::unique_ptr<object>>::iterator start{array.begin()};
  std::vector<std::unique_ptr<object>>::iterator end{array.end()};
  std::vector<std::unique_ptr<object>>::iterator object;
  for(object = start ; object < end ; ++object){
    file << (*object)->save_string() << std::endl;
  }
  file.close();
}