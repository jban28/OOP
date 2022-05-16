// PHYS 30762 Programming in C++
// Assignment 4

// Class for matrices
#include<vector>
#include<iostream>
#include<cstring>
#include<cmath>
#include<string>

class matrix2d
{
  friend std::ostream &operator<<(std::ostream &os, matrix2d &matrix);
  friend std::istream &operator>>(std::istream &is, matrix2d &matrix);
  friend double find_determinant(matrix2d matrix);
private:
  int rows;
  int cols;
  double *data;

public:
  matrix2d(): rows{}, cols{}, data{nullptr} {};
  matrix2d(const int m, const int n);
  matrix2d(matrix2d &matrix);
  matrix2d(matrix2d &&matrix);
  ~matrix2d(){delete[] data;}
  double &operator()(int i, int j);
  void set_all_values(std::string value_string);
  matrix2d del_row_col(int row_del, int col_del);
  matrix2d operator+(const matrix2d &matrix) const;
  matrix2d operator-(const matrix2d &matrix) const;
  matrix2d operator*(const matrix2d &matrix) const;
  matrix2d &operator=(const matrix2d &matrix);
  matrix2d &operator=(matrix2d &&matrix);
};

matrix2d::matrix2d(const int m, const int n)
{
  rows = m; cols = n;
  data = new double[m*n];
}

matrix2d::matrix2d(matrix2d &matrix)
{
  rows = matrix.rows;
  cols = matrix.cols;
  data = new double[rows*cols];
  for (int x=0; x<rows*cols; x++){
    data[x] = matrix.data[x];
  }
}

matrix2d::matrix2d(matrix2d &&matrix)
{
  rows = matrix.rows;
  cols = matrix.cols;
  data = matrix.data;
  matrix.data = nullptr;
  matrix.rows = 0;
  matrix.cols = 0;
}

double &matrix2d::operator()(int i, int j)
{
  return data[j + i*cols];
}

void matrix2d::set_all_values(std::string value_string)
{
  for (int loc=0; loc<(rows*cols); loc++){
    int delim_position = value_string.find(" ", 0);
    double element;
    element = std::stod(value_string.substr(0, delim_position));
    data[loc] = element;
    value_string.erase(0, value_string.find(" ",0)+1);
  }
}

matrix2d matrix2d::del_row_col(const int row_del, const int col_del)
{
  matrix2d new_matrix(rows-1, cols-1);
  int loc{0};
  for (int i{0}; i<rows; i++){
    for (int j{0}; j<cols; j++){
      if ((i != row_del && j != col_del)){
        new_matrix.data[loc] = data[j + i*cols];
        loc += 1;
      }
    }
  }
  return new_matrix;
}

matrix2d matrix2d::operator+(const matrix2d &matrix) const 
{
  matrix2d sum_matrix{rows,cols};
  if ((rows != matrix.rows) || (cols != matrix.cols)){
    std::cout << "Matrix dimensions do not match. First matrix returned:" 
    << std::endl;
    sum_matrix = *this;
  }

  else{
    for (int loc=0; loc<(rows*cols); loc++){
      sum_matrix.data[loc] = data[loc] + matrix.data[loc];
    }
  }
  return sum_matrix;
}

matrix2d matrix2d::operator-(const matrix2d &matrix) const 
{
  matrix2d dif_matrix{rows,cols};
  if ((rows != matrix.rows) || (cols != matrix.cols)){
    std::cout << "Matrix dimensions do not match. First matrix returned:" 
    << std::endl;
    dif_matrix = *this;
  }

  else{
    for (int loc=0; loc<(rows*cols); loc++){
      dif_matrix.data[loc] = data[loc] - matrix.data[loc];
    }
  }
  return dif_matrix;
}

matrix2d matrix2d::operator*(const matrix2d &matrix) const 
{
  double sum = 0;
  matrix2d prod_matrix{rows,matrix.cols};
  if (cols == matrix.rows){
    for (int i=0; i<(rows); i++){
      for (int j=0; j<(rows); j++){
        sum = 0;
        for (int k=0; k<cols; k++){
          sum += data[(k)+(i)*cols] * matrix.data[(j)+(k)*rows];
        }
        prod_matrix.data[(j)+(i)*rows] = sum;
      }
    }
  }
  else{
    std::cout << "Cannot mulitply these dimensions.\n" << std::endl;
  }
  return prod_matrix;
}

matrix2d &matrix2d::operator=(const matrix2d &matrix)
{
  if (&matrix == this) return *this;
  delete[] data; rows = 0; cols = 0;
  return *this;
}

matrix2d &matrix2d::operator=(matrix2d &&matrix)
{
  std::swap(rows, matrix.rows);
  std::swap(cols, matrix.cols);
  //std::swap(data, matrix.data);
  delete[] data;
  data = matrix.data;
  matrix.data = nullptr;
  return *this;
}

std::ostream &operator<<(std::ostream &os, matrix2d &matrix)
{
  for(int i=0; i<matrix.rows; ++i){
    for(int j=0; j<matrix.cols; ++j){
      std::cout << matrix(i,j) << " ";
    }
    std::cout << std::endl;
  }
  return os;
}

std::istream &operator>>(std::istream &is, matrix2d &matrix)
{
  std::string data;
  std::getline(is, data);
  matrix.set_all_values(data);

  return is;
}

matrix2d build_empty_matrix()
{
  int rows;
  int cols;
  std::cout << "Input the number of rows for your matrix:" << std::endl;
  std::cin >> rows;
  std::cout << "Input the number of columns for your matrix:" << std::endl;
  std::cin >> cols;
  matrix2d matrix{rows, cols};
  return matrix;
}

double find_determinant(matrix2d matrix)
{
  double determinant = 0;
  if ((matrix.rows == 2) && (matrix.cols == 2)){
    determinant = matrix(0,0)*matrix(1,1) - matrix(0,1)*matrix(1,0);
  }
  else{
    for (int i=0; i<matrix.rows; i++){
      determinant += (std::pow(-1, (i)) * matrix(i,0) * 
      find_determinant(matrix.del_row_col(i,0)));
    }
  }
  return determinant;
}

int main()
{
  std::cout.precision(3);
  
  //Define 3 empty matrices
  matrix2d matrixA{3,3};
  matrix2d matrixB{3,3};
  matrix2d matrixC{2,3};

  // Assign the example values to the matrices
  matrixA.set_all_values("1 2 3 9 8 7 4 2 6");
  matrixB.set_all_values("5 5 4 1 2 3 6 9 8");
  matrixC.set_all_values("3 4 1 2 5 6");

  // Output the example matrices
  std::cout << "Example Matrices:" << std::endl;
  std::cout << "Matrix A:\n" << matrixA << std::endl;
  std::cout << "Matrix B:\n" << matrixB << std::endl;
  std::cout << "Matrix C:\n" << matrixC << std::endl;
  
  // + operator with copy assignment operator
  matrix2d matrixD = matrixA+matrixB;
  std::cout << "Matrix A + Matrix B =\n" << matrixD << std::endl;

  // - operator with copy assignment operator
  matrixD = matrixA-matrixB;
  std::cout << "Matrix A - Matrix B =\n" << matrixD << std::endl;

  // * operator  with copy assignment operator
  matrixD = matrixA*matrixB;
  std::cout << "Matrix A * Matrix B =\n" << matrixD << std::endl;

  // * operator  with copy assignment operator
  matrixD = matrixC*matrixB;
  std::cout << "Matrix C * Matrix B =\n" << matrixD << std::endl;

  // * operator for impossible calculation with copy assignment operator
  std::cout << "Matrix B * Matrix C =" << std::endl;
  matrixD = matrixB*matrixC;

  // Removal of row i and column j, with copy constructor
  std::cout << "Matrix A with middle row and column deleted:" << std::endl;
  matrix2d matrixE{matrixA.del_row_col(1,1)};
  std::cout << matrixE << std::endl;

  // Determinant Calculator
  double determinant_matrixA = find_determinant(matrixA);
  std::cout << "Matrix A determinant = " << determinant_matrixA << std::endl;

  // Move constructor
  matrix2d matrixF{std::move(matrixA)};
  std::cout << "\nMove constructor\n" << matrixF << std::endl;

  // Move assignment operator
  matrix2d matrixG;
  matrixG = std::move(matrixB);
  std::cout << "Move assignment operator\n" << matrixG << std::endl;

  // User input of matrix
  std::cout << "Example of user input matrix using overloaded >> operator" 
  << std::endl;
  matrix2d matrixH = build_empty_matrix();
  std::cin.clear();
  std::cin.ignore();
  std::cout << "Input matrix values in the form a b c ..." << std::endl;
  std::cin >> matrixH;
  std::cout << "Your input was interpreted as:\n" << matrixH << std::endl;

  return 0;
}