#include "object.hpp"
#include <string>

#ifndef _galaxy
#define _galaxy

class galaxy : public object
{
  private:
    std::string hubble_type;
  public:
    galaxy(std::string name, double ra, double dec, double lum, double dist, 
    std::string hubble_class);
    ~galaxy(){};
    std::string save_string();
    void print_type_data();
};

#endif