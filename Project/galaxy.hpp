#include "object.hpp"
#include <string>

#ifndef _galaxy
#define _galaxy

class galaxy : public object
{
  private:
    std::string hubble_type;
  public:
    galaxy();
    galaxy(std::string name, double ra, double dec, double lum, double dist, 
    std::string hubble_class);
    ~galaxy(){};
    void type_data_print();
    std::string type_data_string();
};

#endif