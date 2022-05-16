#include "object.hpp"
#include<string>
#include<iostream>

#ifndef _star
#define _star

class star : public object
{
  private:
    double effective_temperature;
  public:
    star(std::string name, double ra, double dec, double lum, double dist, 
    double temp);
    ~star(){};
    std::string save_string();
    void print_type_data();
};

#endif