#include "Matrix.h"


// конструктор нулевой матрицы 3x3
matrix::matrix()
	{
		N = 3; 
		M = 3; 
		elements = new double *[N];

		for (int i = 0; i < N; ++ i)
		{
			elements[i] = new double[M];
			for (int j = 0; j < M; ++ j)
				elements[i][j] = 0;
		}
	}

// матрица NxM
matrix::matrix(int _N, int _M, int* _elements)
{
	N = _N;
	M = _M;
	int k = 0;

	elements = new double *[N];

	for (int i = 0; i < N; ++ i)
	{
		elements[i] = new double[M];
		for (int j = 0; j < M; ++ j)
		{
			elements[i][j] = _elements[k];
			k++;
		}
	}

}

// единичная матрица NxM
matrix::matrix(int _N, int _M)
{
	N = _N;
	M = _M;
	int k = 0;

	elements = new double *[N];

	for (int i = 0; i < N; ++ i)
	{
		elements[i] = new double[M];

		for (int j = 0; j < M; ++ j)
			elements[i][j] = 0;

	}

}

// копирующий контруктор
 matrix::matrix(const matrix& mtr)
    {      
		N = mtr.N;
		M = mtr.M;

        elements = new double *[N];

		for (int i = 0; i < N; ++ i)
		{
			elements[i] = new double[M];

			for (int j = 0; j < M; ++j)
				elements[i][j] = mtr.elements[i][j];
		}

		
    }
    

// деструктор
matrix::~matrix()
	{
		for (int i = 0; i < N; i++)
			delete[] elements[i];

		delete[] elements;
	}

// транспонирование
void matrix::transp()
	{

		for (int i = 0; i < N; ++ i)
			for (int j = i; j < M; ++ j)
			{
				double tmp = elements[i][j];
				elements[i][j] = elements[j][i];
				elements[j][i] = tmp;
			}

	}

//
//// умножение на число
//void matrix::del (double k)
//	{
//		for (int i = 0; i < N; ++ i)
//			for (int j = 0; j < M; ++ j)
//				elements[i][j] = elements[i][j] * k;
//	}

// умножение строки на число
void matrix::mult (int i, double k)
	{
			for (int j = 0; j < M; ++ j)
				elements[i][j] = elements[i][j] * k;
	}

// оператор присваивания
matrix& matrix::operator=(const matrix& mtr)
{

	for (int i = 0; i < N; i++)
			delete[] elements[i];

		delete[] elements;

	N = mtr.N;
	M = mtr.M;

	elements = new double *[N];

	for (int i = 0; i < N; ++ i)
	{
		elements[i] = new double[M];

		for (int j = 0; j < M; ++ j)
			elements[i][j] = mtr.elements[i][j];

	}
	return *this;
}

// оператор умножения матриц
matrix operator* (matrix m1, matrix m2)
	{
		matrix mtrOut = matrix (m1.N, m2.M);

		for (int i = 0; i < m1.N; ++ i)
			for (int j = 0; j < m2.M; ++ j)
				for (int k = 0; k < m1.M; ++ k)
				mtrOut.elements[i][j] += m1.elements[i][k] * m2.elements[k][j];

		return mtrOut;
	}

// сложение двух матриц
matrix operator+ (matrix m1, matrix m2)
	{
		matrix mtrOut = matrix (m1.N, m2.M);

		for (int i = 0; i < m1.N; ++ i)
			for (int j = 0; j < m2.M; ++ j)
				mtrOut.elements[i][j] = m1.elements[i][j] + m2.elements[i][j];

		return mtrOut;
	}

// сложение двух матриц
matrix operator- (matrix m1, matrix m2)
	{
		matrix mtrOut = matrix (m1.N, m2.M);

		for (int i = 0; i < m1.N; ++ i)
			for (int j = 0; j < m2.M; ++ j)
				mtrOut.elements[i][j] = m1.elements[i][j] - m2.elements[i][j];

		return mtrOut;
	}

// поменять строки местами
void matrix::SwapStr(int s1, int s2)
{
	double current;
        for (int i = 0; i < M; i++)
        {
            current = elements[s1][i];
            elements[s1][i] = elements[s2][i];
            elements[s2][i] = current;
        }
}

// поменять столбцы местами
void matrix::SwapColumn(int c1, int c2)
{
	double current;
        for (int i = 0; i < M; i++)
        {
            current = elements[i][c1];
            elements[i][c1] = elements[i][c2];
            elements[i][c2] = current;
        }
}


// оператор вывода
ostream& operator<<(ostream& out, matrix& mtrIn)
	{
		out << "matrix " << mtrIn.N << "x" << mtrIn.M << endl;
		for (int i = 0; i < mtrIn.N; ++ i)
		{
			for (int j = 0; j < mtrIn.M; ++ j)
			{
				if ((mtrIn.elements[i][j] < 0) && (abs(mtrIn.elements[i][j]) < 0.0000001))
					mtrIn.elements[i][j] = 0;
				out << mtrIn.elements[i][j] << " ";
			}
			out << endl;
		}
		return out;
	}

//округление до 8 знаков
double rnd(double a)
{
	a = a*100000000;
	a = (int)a;
	a = a/100000000;
	return a;		   
}