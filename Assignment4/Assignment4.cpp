// PHYS 30762 Programming in C++
// Assignment 4

// Class for complex numbers

#include<iostream>
#include<cmath>
#include<sstream>

class complex
{
  // Make function to overload operator<< a friend
  friend std::ostream & operator<<(std::ostream &os, const complex &z);
  friend std::istream & operator>>(std::istream &is, complex &z);
private:
  double re,im;
public:
  // Constructors & destructor
  complex(){re=im=0;}
  complex(double real_part, double im_part){re=real_part; im=im_part;}
  ~complex(){}

  // Return real component
  double real() const{return re;}

  // Return imaginary component
  double imag() const{return im;}

  // Return modulus
  double mod() const {return std::pow(std::pow(re,2) + std::pow(im,2),0.5);}

  // Return argument
  double arg() const {return std::atan(im/re);}

  // Return complex conjugate
  complex conj() const {return complex(re, -im);}

  // Overload + operator for addition 
  complex operator+(const complex &z) const {return complex(re + z.re, im + z.im);}

  // Overload - operator for subtraction
  complex operator-(const complex &z) const {return complex(re - z.re, im - z.im);}

  // Overload * operator for multiplication, z1*z2
  complex operator*(const complex &z) const
  {
    return complex(
      (re * z.re - im * z.im),
      (im * z.re + re * z.im)
    );
  }

  // Overload / operator for division, z1/z2
  complex operator/(const complex &z) const
  {
    complex temp = *this * z.conj();
    double denominator = std::pow(z.mod(),2);
    temp.re /= denominator;
    temp.im /= denominator;
    return temp;
  }
};

// Function to overload << operator for complex numbers
std::ostream & operator<<(std::ostream &os, const complex &z)
{
  if (z.im < 0){
    os << z.re << " - i" << -z.im;
  }
  else{
    os << z.re << " + i" << z.im;
  }
  return os;
}

// Function to overload >> operator for complex numbers
std::istream & operator>>(std::istream &is, complex &z)
{
  std::string temp;
  std::string sign;
  is >> z.re >> sign >> temp;

  if (sign == "+"){
    z.im = std::stod(temp.substr(1,1));
  }

  else if (sign == "-"){
    z.im = -std::stod(temp.substr(1,1));
  }

  return is;
}

int main()
{  
  std::cout.precision(3);

  // Create complex numbers
  complex a{3,4};
  complex b{1,-2};
  complex c;

  // Print out results, also demonstrating use of overloaded operator<<
  std::cout << "\nComplex number    a = " << a 
  << "\n  Real part         = " << a.real()
  << "\n  Imag part         = " << a.imag()
  << "\n  Modulus           = " << a.mod()
  << "\n  Argument          = " << a.arg() 
  << "\n  Complex Conjugate = "<< a.conj() << std::endl;

  std::cout << "\nComplex number    b = " << b 
  << "\n  Real part         = " << b.real()
  << "\n  Imag part         = " << b.imag()
  << "\n  Modulus           = " << b.mod()
  << "\n  Argument          = " << b.arg()
  << "\n  Complex Conjugate = "<< b.conj() << "\n"<< std::endl;

  // Show results of overloading arithmetic operators
  std::cout << "a + b = " << a + b << std::endl;
  std::cout << "a - b = " << a - b << std::endl;
  std::cout << "a * b = " << a * b << std::endl;
  std::cout << "a / b = " << a / b << "\n" << std::endl;

  // Showing use of overloaded input operator
  std::cout << "Input complex number in the form x + iy or x - iy" << std::endl;
  std::cin >> c;
  std::cout << "You inputted " << c;
  return 0;
}