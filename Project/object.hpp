#include<string>

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
    double absolute_magnitude();
    double apparent_magnitude();
    virtual std::string save_string()=0;
    std::string return_object_type();
    std::string return_object_name();
    void print_data();
    virtual void print_type_data()=0;
};

#endif