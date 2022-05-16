// PHYS 30762 Programming in C++
// Assignment 4
// Simple demonstration of a C++ class
//
// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]
#include<iostream>
#include<string>
#include<vector>
#include<cmath>

class galaxy
{
private:
  std::string name;
  std::string hubble_type;
  double redshift;
  double total_mass;
  double stellar_mass_fraction;
  std::vector<galaxy> satellites;

public:
  // Constructors
  galaxy(): name{"Milky Way"}, hubble_type{"Sb"}, redshift{0}, 
  total_mass{1e12}, stellar_mass_fraction{0.03} {};
  
  galaxy(std::string gal_name, std::string type, double galaxy_redshift, 
  double galaxy_total_mass, double galaxy_mass_frac): 
  name{gal_name}, hubble_type{type}, redshift{galaxy_redshift}, 
  total_mass{galaxy_total_mass}, stellar_mass_fraction{galaxy_mass_frac} {};

  // Destructor
  ~galaxy(){};

  // Return stellar mass (M_* = f_* x M_tot)
  double stellar_mass() {return stellar_mass_fraction * total_mass;};
  
  // Change galaxy's Hubble type
  void change_type(std::string new_type){hubble_type = new_type;};
  
  void add_satellite(galaxy new_sat){satellites.push_back(new_sat);}

  // Prototype for function to print out an object's data
  void print_data();
  // Add satellite galaxy

};

// Print out an object's data
void galaxy::print_data()
{
  std::cout << 
  "\nName                  " << name <<
  "\nHubble Type           " << hubble_type <<
  "\nRedshift              " << redshift <<
  "\nTotal Mass            " << total_mass << " MO" <<
  "\nStellar Mass Fraction " << stellar_mass_fraction <<
  "\nSatellites            " << satellites.size();;
  
  std::vector<galaxy>::iterator start{satellites.begin()};
  std::vector<galaxy>::iterator end{satellites.end()};
  std::vector<galaxy>::iterator satellite;
  for(satellite = start ; satellite < end ; ++satellite){
    std::cout << ", " << satellite->name;
  }
  std::cout << std::endl;
}

// End of class and associated member functions

// Main program
int main()
{
  // Vector to store galaxies
  std::vector<galaxy> galaxies;

  // Example using default constructor
  std::cout << "\nGalaxy built with default constructor" << std::endl;
  galaxy g1;
  g1.print_data();

  // Examples using parameterised constructor
  std::cout << "\n\nGalaxies built with paramterised constructor" << std::endl;
  galaxy g2("Large Magellanic Cloud", "SBm", 1e10, 0.00093, 0.01);
  g2.print_data();

  galaxy g3("Small Magellanic Cloud", "Irr", 7e9, 0.00053, 0.01);
  g3.print_data();

  // Change Hubble type from Sb to Sbc
  std::cout << "\n\nChange type of default Galaxy (Sb to Sbc)" << std::endl;
  g1.change_type("Sbc");
  g1.print_data();

  // Get and print out stellar mass
  std::cout << "\n\nFunction for stellar mass of default galaxy" << std::endl;
  std::cout << "Stellar Mass = " << g1.stellar_mass() << " MO" << std::endl;

  // Create another paramterised galaxy with g1 as satellite
  std::cout << "\n\nAdd LMC and SMC as satellites of the Milky Way" 
  << std::endl;
  g1.add_satellite(g2);
  g1.add_satellite(g3);
  g1.print_data();

  // Add all galaxies to vector and print out
  galaxies.push_back(g1);
  galaxies.push_back(g2);
  galaxies.push_back(g3);
  
  // Iterate over galaxies and print all data for each
  std::cout << "\n\nPrint all galaxies from vector using iterator" << std::endl;
  std::vector<galaxy>::iterator start{galaxies.begin()};
  std::vector<galaxy>::iterator end{galaxies.end()};
  std::vector<galaxy>::iterator galaxy;
  for(galaxy = start ; galaxy < end ; ++galaxy){
    galaxy->print_data();
  }
  return 0;
}