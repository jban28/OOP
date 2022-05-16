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
    planet(std::string name, double ra, double dec, double lum, double dist);
    ~planet(){};
    std::string save_string();
    void print_type_data(){};
};

#endif