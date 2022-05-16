#include "cluster.hpp"
#include<string>
#include<sstream>

cluster::cluster()
{
  set_base_params();
  object_type = "cluster";
}

cluster::cluster(std::string name, double ra, double dec, double lum, 
double dist)
{
  object_type = "cluster";
  object_name = name;
  right_ascension = ra;
  declination = dec;
  luminosity = lum;
  distance = dist;
};