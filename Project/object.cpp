#include"object.hpp"
#include"inputs.hpp"

#include<iostream>

double object::absolute_magnitude()
{
  return (-2.5 * log10(luminosity/3.0128e28));
};

double object::apparent_magnitude()
{
  return (absolute_magnitude() + log10(distance/3.086e17));
};

std::string object::return_object_type()
{
  return object_type;
}

std::string object::return_object_name()
{
  return object_name;
}

void object::print_data()
{
  std::cout << "\n" << object_name << " (" << object_type << ")"
  << "\n  Right acension : " << right_ascension
  << "\n  Declination    : " << declination
  << "\n  Luminosity (W) : " << luminosity
  << "\n  Distance (m)   : " << distance << std::endl;
  type_data_print();
}


std::string object::save_string()
{
  std::stringstream save_stream;
  save_stream << object_type << "," << object_name << "," << right_ascension 
  << "," << declination << "," << luminosity << "," << distance << ","
  << type_data_string();
  return save_stream.str();
}

void object::set_base_params()
{
  std::cout << "Object identifier/name: ";
  object_name = user_input<std::string>();
  std::cout << "Right ascension: ";
  right_ascension = user_input<double>(0, 360);
  std::cout << "Declination: ";
  declination = user_input<double>(-90, +90);
  std::cout << "Luminosity (W): ";
  luminosity = user_input<double>(0, 1e99);
  std::cout << "Distance (m): ";
  distance = user_input<double>(0, 1e99);
}