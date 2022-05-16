#include "star.hpp"
#include<sstream>

star::star(std::string name, double ra, double dec, double lum, double dist, 
double temp)
{
  object_type = "star";
  object_name = name;
  right_ascension = ra;
  declination = dec;
  luminosity = lum;
  distance = dist;
  effective_temperature = temp;
};

std::string star::save_string()
{
  std::stringstream save_stream;
  save_stream << object_type << "," << object_name << "," << right_ascension 
  << "," << declination << "," << luminosity << "," << distance << "," 
  << effective_temperature;
  return save_stream.str();
}

void star::print_type_data()
{
  std::cout << "  Effective temp : " << effective_temperature << std::endl;
}