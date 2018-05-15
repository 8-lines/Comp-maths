#include <iostream>
#include <fstream>
using namespace std;


class matrix
{
	public:
		double **elements;
	    int N, M;

		// конструкторы матриц
		matrix (); // пустая матрица 3x3
		matrix (int _N, int _M); // единичная матрица NxM
		matrix (int _N, int _M, int* _elements); // матрица NxM

		// копирующий конструктор
		matrix(const matrix &);

		// деструктор
	    ~matrix();

		// оператор присваивания
		matrix& operator=(const matrix&);

		// поменять строки местами
		void SwapStr(int s1, int s2);

		// поменять столбцы местами
		void SwapColumn(int c1, int c2);

		// нахождение определителя
		//double det();

		// умножение на число строки матрицы
		void mult(int, double);

		// транспонирование матрицы
		void transp();

		
};

// вывод матрицы в консоль
ostream& operator<<(ostream&, matrix&);

// перемножение двух матриц
matrix operator* (matrix, matrix);

// сложение двух матриц
matrix operator+ (matrix, matrix);

// сложение двух матриц
matrix operator- (matrix, matrix);

// нахождение обратной матрицы
bool inverse(double **matrix, double ** result, int size);

// округление до 8 знаков
double rnd(double a);

// нахождение обратной матрицы 3x3
//matrix inv(matrix&);

// определение знака числа
//int sign(double);