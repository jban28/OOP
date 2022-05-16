#include "object.hpp"

#ifndef _object_array
#define _object_array

class object_array
{
  private: 
    object** array;
    int max_index;
    int last_index_filled;
  public:
    object_array();
    ~object_array();
    void extend(int increase);
    void add_object(object* objects_to_add);
    void new_object_from_input();
    void new_object_from_file();
    void list_all();
    void list_type(std::string type);
    void list_by_name(std::string name);
    void save_to_file();
};

#endif