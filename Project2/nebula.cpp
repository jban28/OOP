#include "nebula.hpp"
#include<sstream>

nebula::nebula()
{
  set_base_params();
}

nebula::nebula(std::string name, double ra, double dec, double lum, double dist)
{
  object_type = "nebula";
  object_name = name;
  right_ascension = ra;
  declination = dec;
  luminosity = lum;
  distance = dist;
};
