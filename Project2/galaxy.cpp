#include "galaxy.hpp"
#include "inputs.hpp"

#include<iostream>
#include<sstream>
#include<vector>

galaxy::galaxy(){
  set_base_params();
  std::string hubble_type;
  std::vector<std::string> hubble_type_options{"E1", "E2", "E3", "E4", "E5",
  "E6", "E7", "Sa", "Sb", "Sc", "Sba", "Sba", "Sbc", "Irr"};
  std::cout << "Hubble classification: ";
  hubble_type = user_input<std::string>(hubble_type_options);
}

galaxy::galaxy(std::string name, double ra, double dec, double lum, double dist, 
std::string hubble_class)
{
  object_type = "galaxy";
  object_name = name;
  right_ascension = ra;
  declination = dec;
  luminosity = lum;
  distance = dist;
  hubble_type = hubble_class;
};

void galaxy::type_data_print()
{
  std::cout << "  Hubble type    : " << hubble_type << std::endl;
}

std::string galaxy::type_data_string()
{
  std::stringstream save_stream;
  save_stream << "," << hubble_type;
  return save_stream.str();
}
