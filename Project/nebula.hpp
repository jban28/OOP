#include "object.hpp"

#ifndef _nebula
#define _nebula

class nebula : public object
{
  private:

  public:
    nebula(std::string name, double ra, double dec, double lum, double dist);
    ~nebula(){};
    std::string save_string();
    void print_type_data(){};

};

#endif