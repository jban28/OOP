//g++ ./*.cpp

#include "object_array.hpp"
#include "inputs.hpp"

#include<iostream>
#include<vector>
#include<string>
#include<limits>

int main()
{
  object_array objects;
  std::vector<std::string> object_types{"star", "galaxy", "cluster", "nebula", 
  "planet"};
  int selection;
  bool run = true;
  while (run){
    std::cout << "\nMain Menu" 
    << "\n1 : Input object"
    << "\n2 : Load object(s) from file"
    << "\n3 : List all objects"
    << "\n4 : Search objects by type"
    << "\n5 : Search object by name"
    << "\n6 : Save current object list"
    << "\n0 : Exit program\n" << std::endl;
    selection = integer_input(0,6);
    switch(selection){
      case 0:
      {
        std::cout << "\nExiting...\n" << std::endl;
        run = false;
        break;
      }
      case 1:{
        objects.new_object_from_input();
        break;
      }
      case 2:
      {
        objects.new_object_from_file();
        break;
      }
      case 3:
      {
        objects.list_all();
        break;
      }
      case 4:
      {
        std::string object_type;
        std::cout << "Select object type"
        << "\n1 : Star"
        << "\n2 : Galaxy"
        << "\n3 : Star Cluster" 
        << "\n4 : Nebula"
        << "\n5 : Planet" 
        << std::endl;

        int type_selection = integer_input(1,5);
        switch(type_selection){
          case(1):{
            object_type = "star";
            break;
          }
          case(2):{
            object_type = "galaxy";
            break;
          }
          case(3):{
            object_type = "cluster";
            break;
          }
          case(4):{
            object_type = "nebula";
            break;
          }
          case(5):{
            object_type = "planet";
            break;
          }
        }
        objects.list_type(object_type);
        break;
      }
      case 5:
      {
        std::string object_name;
        std::cout << "Input the name of the object to search for: ";
        object_name = string_input();
        objects.list_by_name(object_name);
        break;
      }
      case 6:
      {
        objects.save_to_file();
        break;
      }
    }
  }
  return 0;
}