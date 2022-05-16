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
    star();
    star(std::string name, double ra, double dec, double lum, double dist, 
    double temp);
    ~star(){};
    void type_data_print();
    std::string type_data_string();
};

#endif