#include "object.hpp"

#include<string>

#ifndef _planet
#define _planet

class planet : public object
{
  private:
    std::string name;
    std::string type;
    double radius; // At equator
    double mass;
    double orbit_radius; // Assume circular
    double orbit_period;
    double day_length;
  public:
    planet();
    planet(std::string name, double ra, double dec, double lum, double dist);
    ~planet(){};
    void type_data_print(){};
    std::string type_data_string(){return "temp";};
};

#endif