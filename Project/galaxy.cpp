#include "galaxy.hpp"

#include<iostream>
#include<sstream>

galaxy::galaxy(std::string name, double ra, double dec, double lum, double dist, 
std::string hubble_class)
{
  object_type = "galaxy";
  object_name = name;
  right_ascension = ra;
  declination = dec;
  luminosity = lum;
  distance = dist;
  hubble_type = hubble_class;
};

std::string galaxy::save_string()
{
  std::stringstream save_stream;
  save_stream << object_type << "," << object_name << "," << right_ascension 
  << "," << declination << "," << luminosity << "," << distance << ","
  << hubble_type;
  return save_stream.str();
}

void galaxy::print_type_data()
{
  std::cout << "  Hubble type    : " << hubble_type << std::endl;
}