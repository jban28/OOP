#include "planet.hpp"
#include<string>
#include<sstream>

planet::planet()
{
  set_base_params();
}

planet::planet(std::string name, double ra, double dec, double lum, 
double dist)
{
  object_type = "planet";
  object_name = name;
  right_ascension = ra;
  declination = dec;
  luminosity = lum;
  distance = dist;
};