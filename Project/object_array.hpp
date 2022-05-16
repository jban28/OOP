#include "object.hpp"

#include<vector>
#include<memory>

#ifndef _object_array
#define _object_array

class object_array
{
  private: 
    std::vector<std::unique_ptr<object>> array;
    std::vector<std::string> object_type_options{"star", "galaxy", "cluster", 
    "nebula", "planet"};
  public:
    object_array();
    ~object_array();
    void new_object_from_input();
    void new_object_from_file();
    void list_all();
    std::string select_type();
    void list_type();
    void list_by_name(std::string name);
    void save_to_file();
};

#endif