// Assignment 1
// James Bannister 9th February 2022
// Program to calculate transition energy using simple Bohr formula

#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>

double transition_energy(double constant, int atom, int n_initial, int n_final)
// Calculates and returns energy change of transition between energy levels
{
	double energy;
	energy = fabs(
		constant*std::pow(atom,2)*(1/std::pow(n_final,2)-1/std::pow(n_initial,2))
		);
	return energy;
}

int integer_input(int lower_bound = -2147483647, int upper_bound = 2147483647)
/* Takes a user input as a string and (if possible) recasts it as an integer and
returns it, providing the integer value is between the upper and lower bounds. 
If an integer between the bounds cannot be returned, the input is repeated */
{
	std::string input_string{};
	std::string exception1{};
  int integer;
	while(true){
		std::cin >> input_string;
		try{
			integer = std::stoi(input_string);
			if (integer <= upper_bound && integer >= lower_bound){
				break;
			}
			throw(input_string);
		}
		catch(std::string error){
			std::cout << "Input must be between " << lower_bound << " and " 
			<< upper_bound << ", try again." <<std::endl;
		}
		catch(...){
			std::cout << "Input must be an integer, try again." << std::endl;
		}
	}
  return integer;
}

int main()
{
	while(true){
		std::string unit_selection{};
		int atomic_number; int initial_state; int final_state;
		double photon_energy; double rydberg; std::string units; 
		std::string transition;
		std::string repeat;
		
		std::cout << "Enter the atomic number of the element you wish to use:"
		<<std::endl;
		atomic_number = integer_input(0,118);

		std::cout << "Enter the quantum number of the initial state:" << std::endl;
		initial_state = integer_input(1);

		std::cout << "Enter the quantum number of the final state:" << std::endl;
		final_state = integer_input(1);

		/* Compare the intitial and final states to deduce whether the transition 
		will be an emmission or absorption, or if there will be no transition */
		if (initial_state < final_state){
			transition = "absorbed";
			rydberg = -rydberg;
		}

		else if (initial_state > final_state){
			transition = "released";
		}

		else{
			std::cout << "The initial and final states are the same and no transition" 
			" will occur." << std::endl;

			// Repeat the inputs if there is no transition
			continue;
		}


		std::cout << "Would you like the transition energy to be stated in Joules" 
		" (J) or Electron Volts (e)?" << std::endl;
		while (units == ""){
			std::cin >> unit_selection;
			if (unit_selection == "e" || unit_selection == "eV"){
				rydberg = 13.6;
				units = "eV";
			}

			else if (unit_selection == "J" || unit_selection == "j"){
				rydberg = 2.18e-18;
				units = "J";
			}

			else{
				std::cout << "Invalid unit, please enter either J or e" << std::endl;
			}
		}

		photon_energy = transition_energy(
			rydberg, atomic_number, initial_state, final_state
			);

		std::cout << "The energy of a photon " << transition << " during the"
		" transition of an atom with atomic number " << atomic_number << " from the"
		" initial quantum state n=" << initial_state << " to the final state n=" 
		<< final_state <<" is "<<
		std::setprecision(3)<<photon_energy<<units<<std::endl;

		std::cout<<"Would you like to repeat the calculation (y/n)"<<std::endl;
		std::cin>>repeat;
		if (repeat == "y" || repeat == "yes" || repeat == "Y" || repeat == "Yes"){
			continue;
		}	
		else if (repeat == "n" || repeat == "N" || repeat == "no" || repeat == "No")
		{
			break;
		}
		else{
			continue;
		}
	}
	return 0;
}

