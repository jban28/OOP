#include"object.hpp"

#include<cmath>
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
  print_type_data();
}