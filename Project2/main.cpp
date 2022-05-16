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
  int selection;
  bool run = true;

  std::vector<std::string> main_menu_options{"Input object", 
  "Load object(s) from file", "List all objects", "Search objects by type",
  "Search object by name", "Save current object list", "Exit program"};

  while (run){
    selection = menu("Main Menu", main_menu_options);
    switch(selection){
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
        objects.list_type();
        break;
      }
      case 5:
      {
        std::string object_name;
        std::cout << "Input the name of the object to search for: ";
        object_name = user_input<std::string>();
        objects.list_by_name(object_name);
        break;
      }
      case 6:
      {
        objects.save_to_file();
        break;
      }
      case 7:
      {
        std::cout << "\nExiting...\n" << std::endl;
        run = false;
        break;
      }
    }
  }
  return 0;
}