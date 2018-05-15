#include "Matrix.h"


int main()
{
	ifstream fin("Input.txt");

	bool success = true;
	int size;

	double sin, cos;

	fin >> size;

	matrix Top = matrix(size, size);
	matrix T = matrix(size, size);
	matrix Tall = matrix(size, size);
	matrix Temp = matrix(size, size);

	//double* b = new double[size];
	//double* X = new double[size];
	matrix b = matrix(size, 1);
	matrix X = matrix(size, 1);
	
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				fin >> Top.elements[i][j];
			}
			T.elements[i][i] = 1;
			Tall.elements[i][i] = 1;
		}

	matrix A = Top;
	cout << fixed;
	cout.precision(8);
	
		for (int j = 0; j < size - 1; j++) // столбцы
		{
			for (int i = j + 1; i < size; i++) //строки (элементы в этом столбце под диагональю)
			{
				if (Top.elements[i][j] != 0)
				{
					cos = Top.elements[j][j] / (sqrt( pow(Top.elements[j][j], 2) + pow(Top.elements[i][j], 2)));
					sin = Top.elements[i][j] / (sqrt( pow (Top.elements[j][j], 2) + pow (Top.elements[i][j], 2)));

					//cout << "cos:" << cos << endl;
					//cout << "sin:" << sin << endl;

					T.elements[j][j] = cos;   T.elements[j][i] = sin;
					T.elements[i][j] = -sin;  T.elements[i][i] = cos;

					Temp = T*Top;
					Top = Temp;
					Temp = T*Tall;
					Tall = Temp;

					//cout << "Top" << endl << Top << endl;
					//cout << "Tall" << endl << Tall << endl;

					T.elements[i][i] = 1; T.elements[j][i] = 0;
					T.elements[i][j] = 0; T.elements[j][j] = 1;
				}
			}
		}
			cout << "Top:" << endl << Top << endl;
			cout << "Tall:" << endl << Tall << endl;
			Temp = Tall;
			Temp.transp();
			cout << "Tall*Tall_T:" << endl << Tall*Temp << endl;
            

			//решаем систему, вводим вектор b
				for (int j = 0; j < size; j++) 
					fin >> b.elements[j][0];

				b = Tall*b;

				for (int j = size - 1; j > -1; j--) //обратный ход по правой
				{
					if ( Top.elements[j][j] == 0)
					{
						cout << "Error!" << endl;
						success = false;
						break;
					}

					X.elements[j][0] = b.elements[j][0] / Top.elements[j][j];
					//cout << b.elements[j][0] << " " << Top.elements[j][j] << endl;

					for (int i = 0; i < j; i++)
						b.elements[i][0] -= Top.elements[i][j] * X.elements[j][0];
				}


				if (success == true)
					cout << "X:" << endl << X << endl;



				cout << "A*X:" << endl << (A*X) << endl << "b:" << endl << b << endl;

	cin >> size;
	return 0;
}