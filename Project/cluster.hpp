#include "object.hpp"

#ifndef _cluster
#define _cluster

class cluster : public object
{
  private:

  public:
    cluster();
    cluster(std::string name, double ra, double dec, double lum, double dist);
    ~cluster(){};
    void type_data_print(){};
    std::string type_data_string(){return "temp";};
};

#endif