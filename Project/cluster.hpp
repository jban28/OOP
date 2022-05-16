#include "object.hpp"

#ifndef _cluster
#define _cluster

class cluster : public object
{
  private:

  public:
    cluster(std::string name, double ra, double dec, double lum, double dist);
    ~cluster(){};
    std::string save_string();
    void print_type_data(){};
};

#endif