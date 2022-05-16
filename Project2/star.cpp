#include "star.hpp"
#include "inputs.hpp"
#include<sstream>

star::star()
{
  set_base_params();
  std::cout << "Effective temperature: ";
  effective_temperature = user_input<double>(0, 1e99);
  object_type = "star";
}

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

std::string star::type_data_string()
{
  std::stringstream save_stream;
  save_stream << "," << effective_temperature;
  return save_stream.str();
}

void star::type_data_print()
{
  std::cout << "  Effective temp : " << effective_temperature << std::endl;
}