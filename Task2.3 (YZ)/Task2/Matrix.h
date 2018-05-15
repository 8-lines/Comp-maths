#include <iostream>
#include <fstream>
using namespace std;


class matrix
{
	public:
		double **elements;
	    int N, M;

		// ������������ ������
		matrix (); // ������ ������� 3x3
		matrix (int _N, int _M); // ��������� ������� NxM
		matrix (int _N, int _M, int* _elements); // ������� NxM

		// ���������� �����������
		matrix(const matrix &);

		// ����������
	    ~matrix();

		// �������� ������������
		matrix& operator=(const matrix&);

		// �������� ������ �������
		void SwapStr(int s1, int s2);

		// �������� ������� �������
		void SwapColumn(int c1, int c2);

		// ���������� ������������
		//double det();

		// ��������� �� ����� ������ �������
		void mult(int, double);

		// ���������������� �������
		void transp();

		
};

// ����� ������� � �������
ostream& operator<<(ostream&, matrix&);

// ������������ ���� ������
matrix operator* (matrix, matrix);

// �������� ���� ������
matrix operator+ (matrix, matrix);

// �������� ���� ������
matrix operator- (matrix, matrix);

// ���������� �������� �������
bool inverse(double **matrix, double ** result, int size);

// ���������� �� 8 ������
double rnd(double a);

// ���������� �������� ������� 3x3
//matrix inv(matrix&);

// ����������� ����� �����
//int sign(double);