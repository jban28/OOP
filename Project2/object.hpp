#include<string>
#include<cmath>
#include<iostream>
#include<sstream>

#ifndef _object
#define _object

class object
{
  protected:
    std::string object_type;
    std::string object_name;
    double right_ascension;
    double declination;
    double luminosity; // Watts
    double distance; // Metres
  public:
    virtual ~object(){};
    void set_base_params();
    double absolute_magnitude();
    double apparent_magnitude();
    virtual std::string save_string();
    std::string return_object_type();
    std::string return_object_name();
    void print_data();
    virtual void type_data_print()=0;
    virtual std::string type_data_string()=0;
    
};

#endif