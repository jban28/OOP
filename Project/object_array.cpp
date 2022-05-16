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

object_array::object_array()
{
  array = new object*[1];
  max_index = 0;
  last_index_filled = -1;
}

object_array::~object_array()
{
  std::cout << "Clearing objects" << std::endl;
  for (int i=0; i<=last_index_filled; i++){
    delete array[i];
  }
  delete[] array;
  array = NULL;
}

void object_array::extend(int increase)
{
  max_index = max_index + increase;
  object** new_array = new object*[max_index + 1];
  for (int i=0; i<=max_index; i++){
    new_array[i] = array[i];
  }
  delete[] array;
  array = new_array;
  new_array = NULL;
}

void object_array::add_object(object* object_to_add)
{
  if (max_index == last_index_filled){
    extend(1);
  }
  last_index_filled += 1;
  array[last_index_filled] = object_to_add;
}

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

  int selection = integer_input(1,5);

  std::string name;
  double right_ascension; double declination;
  double luminosity; double distance;
  std::cout << "Object identifier/name: ";
  name = string_input();
  std::cout << "Right ascension: ";
  right_ascension = double_input(0, 360);
  std::cout << "Declination: ";
  declination = double_input(-90, +90);
  std::cout << "Luminosity (W): ";
  luminosity = double_input(0);
  std::cout << "Distance (m): ";
  distance = double_input(0);

  switch(selection){
    case 1:{
      double effective_temperature;
      std::cout << "Effective temperature: ";
      effective_temperature = double_input(0);
      object* new_object = new star(name, right_ascension, declination, 
      luminosity, distance, effective_temperature);
      add_object(new_object);
      new_object = NULL;
      break;
    }
    case 2:{
      std::string hubble_type;
      std::vector<std::string> hubble_type_options{"E1", "E2", "E3", "E4", "E5",
      "E6", "E7", "Sa", "Sb", "Sc", "Sba", "Sba", "Sbc", "Irr"};
      std::cout << "Hubble classification: ";
      hubble_type = input_string_from_options(hubble_type_options);
      object* new_object = new galaxy(name, right_ascension, declination, 
      luminosity, distance, hubble_type);
      add_object(new_object);
      new_object = NULL;
      break;
    }
    case 3:
    {
      object* new_object = new cluster(name, right_ascension, declination, 
      luminosity, distance);
      add_object(new_object);
      new_object = NULL;
      break;
    }
    case 4:{
      object* new_object = new nebula(name, right_ascension, declination, 
      luminosity, distance);
      add_object(new_object);
      new_object = NULL;
      break;
    }
    case 5:{
      object* new_object = new planet(name, right_ascension, declination, 
      luminosity, distance);
      add_object(new_object);
      new_object = NULL;
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
    filename = string_input();
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
          new_object = new star(object_name, right_acension, 
          declination, luminosity, distance, effective_temperature);
          add_object(new_object);
          new_object = NULL;
        }
        else if (object_type == "galaxy"){
          std::string hubble_type;
          delimiter_start = delimiter_end + 1;
          hubble_type = line.substr(delimiter_start);
          new_object = new galaxy(object_name, right_acension, 
          declination, luminosity, distance, hubble_type);
          add_object(new_object);
          new_object = NULL;
        }
        else if (object_type == "cluster"){
          new_object = new cluster(object_name, right_acension, 
          declination, luminosity, distance);
          add_object(new_object);
          new_object = NULL;
        }
        else if (object_type == "nebula"){
          new_object = new nebula(object_name, right_acension, 
          declination, luminosity, distance);
          add_object(new_object);
          new_object = NULL;
        }
        else if (object_type == "planet"){
          new_object = new planet(object_name, right_acension, 
          declination, luminosity, distance);
          add_object(new_object);
          new_object = NULL;
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
  for (int i=0; i<=last_index_filled; i++){
    std::cout << array[i]->return_object_name() << std::endl;
  }
}

void object_array::list_type(std::string type)
{
  for (int i=0; i<=last_index_filled; i++){
    if (array[i]->return_object_type() == type){
      array[i]->print_data();
    }
    else{
      continue;
    }
  }
}

void object_array::list_by_name(std::string name)
{
  int objects_found = 0;
  for (int i=0; i<=last_index_filled; i++){
    if (array[i]->return_object_name() == name){
      std::cout << array[i]->return_object_name() << std::endl;
      objects_found += 1;
    }
    else{
      continue;
    }
  }
  if (objects_found == 0){
    std::cout << "No objects found with that name" << std::endl;
  }
}

void object_array::save_to_file()
{
  std::string filename;
  std::cout << "Type the filename to save the data to: ";
  filename = string_input();
  filename += ".csv";
  std::fstream file;
  file.open(filename, std::fstream::in);
  int selection = 1;
  if (file){
    file.close();
    std::cout << "File already exists. Please select write method"
    << "\n1 : Overwrite file"
    << "\n2 : Append new objects to existing file" << std:: endl;
    selection = integer_input(1,2);
  }
  if (selection == 1){
    file.open(filename, std::fstream::out);
  }
  else if (selection == 2){
    file.open(filename, std::fstream::app);
  }
  for (int i=0; i<=last_index_filled; i++){
    file << array[i]->save_string() << std::endl;
  }
  file.close();
}