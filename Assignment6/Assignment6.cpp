// PHYS 30762 Programming in C++
// Assignment 6

// Classes for shapes

#define _USE_MATH_DEFINES

#include<iostream>
#include<cmath>

class shape
{
  public:
    virtual ~shape (){};
    virtual double area ()=0;
    virtual void output ()=0;
};

class shape2d : public shape
{
  public:
    virtual double perimeter ()=0;
    virtual double area ()=0;
    virtual void output ()=0;
    virtual ~shape2d (){}; 
};

class shape3d : public shape
{
  public:
    virtual double area ()=0;
    virtual double volume ()=0;
    virtual void output ()=0;
    virtual ~shape3d (){}
};

class rectangle : public shape2d
{
  protected:
    double width;
    double length;
  public:
    rectangle(){width=length=0;}
    rectangle(const double x, const double y){width=x; length=y;}
    ~rectangle(){}
    double area (){return width*length;}
    double perimeter (){return 2*(width+length);}
    void output (){
      std::cout << "Rectangle, Area = " << area() << ", Perimeter = " 
      << perimeter() << std::endl;
    };
};

class square : public rectangle
{
  public:
    square(){width=length=0;}
    square(const double size){width=length=size;}
    ~square(){}
    void output (){
      std::cout << "Square, Area = " << area() << ", Perimeter = " 
      << perimeter() << std::endl;
    };
};

class ellipse : public shape2d
{
  protected:
    double major_axis;
    double minor_axis;
  public:
    ellipse(){major_axis=minor_axis=0;}
    ellipse(const double x, const double y){major_axis=x; minor_axis=y;}
    ~ellipse(){}
    double area (){return M_PI*major_axis*minor_axis;}
    double perimeter (){return 2 * M_PI * std::sqrt(0.5*(std::pow(major_axis,2)
    * std::pow(minor_axis,2)));}
    void output (){
      std::cout << "Ellipse, Area = " << area() << ", Perimeter = " 
      << perimeter() << std::endl;
    };
};

class circle : public ellipse
{
  public:
    circle(){major_axis=minor_axis=0;}
    circle(const double radius){major_axis=minor_axis=radius;}
    ~circle(){}
    void output (){
      std::cout << "Circle, Area = " << area() << ", Perimeter = " 
      << perimeter() << std::endl;
    };
};

class cuboid : public shape3d
{
  protected:
    double width;
    double length;
    double height;
  public:
    cuboid(){width=length=height=0;}
    cuboid(const double x, const double y, const double z){width=x; length=y; 
    height=z;}
    ~cuboid(){}
    double volume (){return width*length*height;}
    double area (){return 2*(width*length+width*height+length*height);}
    void output ()
    {
      std::cout << "Cuboid, Surface Area = " << area() << ", Volume = " << 
      volume() << std::endl;
    };
};

class cube : public cuboid
{
  public:
    cube(){width=length=height=0;}
    cube(const double size){width=length=height=size;}
    ~cube(){}
    void output ()
    {
      std::cout << "Cube, Surface Area = " << area() << ", Volume = " << 
      volume() << std::endl;
    };
};

class ellipsoid : public shape3d
{
  protected:
    double width;
    double length;
    double height;
  public:
    ellipsoid(){width=length=height=0;}
    ellipsoid(const double x, const double y, const double z){width=x; length=y; 
    height=z;}
    ~ellipsoid(){}
    double volume (){return M_PI*width*length*height*4/3;}
    double area ()
    {
      const double p = 1.605;
      const double q = 1/p;
      double area_temp = (std::pow(length*width, p) + 
      std::pow(length*height, p) + std::pow(height*width, p));
      area_temp *= 0.333;
      area_temp = std::pow(area_temp, q);
      area_temp *= 4*M_PI;

      return area_temp;
    }
    void output ()
    {
      std::cout << "Ellipsoid, Surface Area = " << area() << ", Volume = " << 
      volume() << std::endl;
    };
};

class sphere : public ellipsoid
{
  public:
    sphere(){width=length=height=0;}
    sphere(const double radius){width=length=height=radius;}
    ~sphere(){}
    void output ()
    {
      std::cout << "Sphere, Surface Area = " << area() << ", Volume = " << 
      volume() << std::endl;
    };
};

class prism : public shape3d
{
  private:
    shape2d *face;
    double depth;
  public:
    prism(shape2d *prism_face, double z){face = prism_face; depth=z;}
    ~prism(){}
    double volume (){return face->area()*depth;}
    double area (){return (2*face->area() + depth*face->perimeter());}
    void output ()
    {
      std::cout << "Prism, Surface Area = " << area() << ", Volume = " << 
      volume() << std::endl;
    };
};

int main()
{
  shape **shape_array = new shape*[8];
  shape_array[0] = new rectangle(2,3);
  shape_array[1] = new square(3);
  shape_array[2] = new ellipse(2,3);
  shape_array[3] = new circle(3);
  shape_array[4] = new cuboid(2,3,4);
  shape_array[5] = new cube(3);
  shape_array[6] = new ellipsoid(2,3,4);
  shape_array[7] = new sphere(3);

  for (int i=0; i<8; i++){
    shape_array[i]->output();
  }
  
  // Delete array
  for (int i=0; i<8; i++){
    delete shape_array[i];
  }
  delete[] shape_array;

  shape_array = NULL;

  // Use of Prism Class
  shape2d *square1 = new square;
  square1 = new square(3);
  prism square_prism{square1, 5};
  square_prism.output();

  delete square1;

  square1 = NULL;

  return 0;
}