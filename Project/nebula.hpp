#include "object.hpp"

#ifndef _nebula
#define _nebula

class nebula : public object
{
  private:

  public:
    nebula();
    nebula(std::string name, double ra, double dec, double lum, double dist);
    ~nebula(){};
    void type_data_print(){};
    std::string type_data_string(){return "temp";};
};

#endif