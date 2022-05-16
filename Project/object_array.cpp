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
  int selection;
  std::string type;
  selection = menu("Select object type:", object_type_options, 5);
  type = object_type_options[selection-1];

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
  while (true){
    std::string filename;
    std::cout << "Input the name of the csv file you would like to load: ";
    filename = user_input<std::string>();
    filename += ".dat";
    std::fstream file{filename};

    if(file.good()) {
      std::string line;

      while (std::getline(file, line)){
        std::string object_type;
        std::string object_name;
        double right_acension;
        double declination;
        double luminosity;
        double distance;

        std::stringstream line_stream;
        line_stream << line;
        line_stream >> object_type >> object_name >> right_acension >> 
        declination >> luminosity >> distance;

        if (object_type == "star"){
          std::string effective_temperature_string;double effective_temperature;
          line_stream >> effective_temperature;
          array.push_back(std::make_unique<star>(star(object_name, right_acension, 
          declination, luminosity, distance, effective_temperature)));
        }
        else if (object_type == "galaxy"){
          std::string hubble_type;
          line_stream >> hubble_type;
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

void object_array::list_type()
{
  int selection;
  std::string type;
  selection = menu("Select object type:", object_type_options, 5);
  type = object_type_options[selection-1];
  iterate([&](std::vector<std::unique_ptr<object>>::iterator obj)
  {
    if ((*obj)->return_object_type() == type){
      (*obj)->print_data();
    }
  });
}

void object_array::list_by_name(std::string name)
{
  int objects_found = 0;
  iterate([&](std::vector<std::unique_ptr<object>>::iterator obj)
  {
    if ((*obj)->return_object_type() == name){
      (*obj)->print_data();
      objects_found += 1;
    }
  });
  if (objects_found == 0){
    std::cout << "No object found with that name" << std::endl;
  }
}

void object_array::save_to_file()
{
  std::string filename;
  std::cout << "Type the filename to save the data to: ";
  filename = user_input<std::string>();
  filename += ".dat";
  std::fstream file;
  file.open(filename, std::fstream::in);
  int selection = 1;
  if (file){
    file.close();
    std::string write_options[2]{"Overwrite file", 
    "Append to existing file"};
    selection = menu("File already exists. Please select write method",
    write_options, 2);
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

  iterate([&](std::vector<std::unique_ptr<object>>::iterator obj)
  {
    file << (*obj)->save_string() << std::endl;
  });

  file.close();
}