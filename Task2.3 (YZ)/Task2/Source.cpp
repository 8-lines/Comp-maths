#include "Matrix.h"


int main()
{
	ifstream fin("Input.txt");

	int size;

	double differenceVec;				//норма разности векторов
	int iter = 0;
	double sumY = 0;
	double sumZ = 0;

	fin >> size;

	matrix matr = matrix(size, size);		// исходная 
	matrix matrB = matrix(size, size);		// матрица obD(L + R)
	matrix bStart = matrix(size, 1);		//столбец значений системы
	matrix X = matrix(size, 1);				//решение системы x(k+1), x(k), так же начальное приближение в первый раз
	matrix Xk1 = matrix(size, 1);
	matrix Xk = matrix(size, 1);
	matrix Xp = matrix(size, 1);

	cout << fixed;
	cout.precision(8);

        // суть: A = L + D + R
	for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            fin >> matr.elements[i][j]; 
	}

	matrB = matr;
            

        for (int i = 0; i < size; i++)
        {
            matrB.elements[i][i] = 0;    // теперь это матрица  L + R
            for (int j = 0; j < size; j++)
                matrB.elements[i][j] /= matr.elements[i][i];
        }


            for (int i = 0; i < size; i++)
                fin >> bStart.elements[i][0];
			matrix b = bStart;

            for (int i = 0; i < size; i++)
            {

                fin >> Xk.elements[i][0];
                fin >> X.elements[i][0];
            }

            for (int i = 0; i < size; i++)
                b.elements[i][0] /= matr.elements[i][i];


            do
            {
                iter++;
                for (int i = 0; i < size; i++)
                    Xp.elements[i][0] = Xk.elements[i][0];

				matrix Temp = matrB * Xk;
				Xk = Temp;
                differenceVec = 0;

                for (int i = 0; i < size; i++)
                {
                    Xk.elements[i][0] = -Xk.elements[i][0] + b.elements[i][0];
                    if (abs(Xk.elements[i][0] - Xp.elements[i][0]) > differenceVec)
                        differenceVec = abs(Xk.elements[i][0] - Xp.elements[i][0]);

                }

                if (differenceVec < 1e-10)
				{
					matrix dYac =  matr*Xk - bStart;
					sumY = 0;
					for (int i =0; i<size; i++)
					sumY += dYac.elements[i][0]*dYac.elements[i][0];
					sumY = sqrt(sumY);
					if (sumY < 1e-10)
						break;
				}

            } while (true);

            cout << endl << "Yacobi method Xk" << endl << Xk << endl;
			cout << endl << "Yacobi mult" << endl << matr*Xk << endl;
			cout << endl << "Yacobi iterations: " << iter << endl;
			cout.precision(12);
			cout << "Norm: " << sumY << endl;
			cout.precision(8);

			iter = 0;

            for (int i = 0; i < size; i++)
                Xk.elements[i][0] = X.elements[i][0];

            do
                {
                    iter++;
                 
                    for (int i = 0; i < size; i++)
                        Xp.elements[i][0] = Xk.elements[i][0];
                    
                    differenceVec = 0;

                    for (int i = 0; i < size; i++)
                    {
                        Xk1.elements[i][0] = b.elements[i][0];
                        for (int j = 0; j < size; j++)
                        {
                            Xk1.elements[i][0] -= Xk.elements[j][0] * matrB.elements[i][j];
                        }
                        //Xk1.elements[i][0] += b.elements[i][0];
                        Xk.elements[i][0] = Xk1.elements[i][0];
                         

                        if (abs(Xk1.elements[i][0] - Xp.elements[i][0]) > differenceVec)
                                differenceVec = abs(Xk1.elements[i][0] - Xp.elements[i][0]);
                         
                    }

                    if (differenceVec < 1e-10)
					{
						matrix dZeyd =  matr*Xk - bStart;
						sumZ = 0;
						for (int i = 0; i<size; i++)
							sumZ += dZeyd.elements[i][0]*dZeyd.elements[i][0];
						sumZ = sqrt(sumZ);
						if (sumZ < 1e-10)
							break;
					}

                } while (true);

			cout << endl << "Zeidel method Xk" << endl << Xk << endl;
			cout << endl << "Zeidel mult" << endl << matr*Xk << endl;
			cout << endl << "Zeidel iterarions: " << iter << endl;
			cout.precision(12);
			cout << "Norm: " << sumZ << endl;
             

	cin >> size;
	return 0;
}