#include "nebula.hpp"
#include<sstream>

nebula::nebula(std::string name, double ra, double dec, double lum, double dist)
{
  object_type = "nebula";
  object_name = name;
  right_ascension = ra;
  declination = dec;
  luminosity = lum;
  distance = dist;
};

std::string nebula::save_string()
{
  std::stringstream save_stream;
  save_stream << object_type << "," << object_name << "," << right_ascension 
  << "," << declination << "," << luminosity << "," << distance;
  return save_stream.str();
}