#include "object.hpp"

#include<vector>
#include<memory>

#ifndef _object_array
#define _object_array

class object_array
{
  private: 
    std::vector<std::unique_ptr<object>> array;
    std::string object_type_options[5]{"star", "galaxy", "cluster", 
    "nebula", "planet"};
  public:
    object_array();
    ~object_array();
    void new_object_from_input();
    void new_object_from_file();
    std::string select_type();
    void list_type();
    void list_by_name(std::string name);
    void save_to_file();
    template <typename type>
    void iterate(type function)
    {
      std::vector<std::unique_ptr<object>>::iterator start{array.begin()};
      std::vector<std::unique_ptr<object>>::iterator end{array.end()};
      std::vector<std::unique_ptr<object>>::iterator object;
      for(object = start ; object < end ; ++object){
        function(object);
      }
    };
};

#endif