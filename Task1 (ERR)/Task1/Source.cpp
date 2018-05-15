#include <iostream> 
#include <cmath> 

using namespace std; 

const double x_start = 0.01; 
const double x_step = 0.005; 
const double x_finish = 0.06; 

const double diff = 0.000001; 

int main() 
{ 
	double uMin = (floor(sqrt(0.42)*10))/10;    // 0.6
	double uMax = (floor(sqrt(0.52)*10)+1)/10;  // 0.8
	double vMin = (floor(cos(1.18)*10))/10;	    // 0.3
	double vMax = (floor(cos(1.03)*10)+1)/10;   // 0.6

	double c1 = (floor(atan(vMax)*10)+1)/10;           // 0.6
	double c2 = (floor(uMax/(1+vMin*vMin)*10)+1)/10;   // 0.8

	double e1 = diff/(3*c1); // 10^(-6) / 1.8
	double e2 = diff/(3*c2); // 10^(-6) / 2.4
	double e3 = diff/3;		 // 10^(-6) / 3


	
	double x = x_start;
	cout << "  X" << "	    f" << "	       F" << "	   dF" << endl;

	while (x <= x_finish)
	{
			cout << fixed;
			cout.precision(3);
			cout << x << " ";

			double t = 2*x + 0.4;
			double u0 = 0;
			double u = t;

			while (abs(u - u0) - e1 >= 0) // считаем корень итеративным алгоритмом
			{
				u0 = u;
				u = 0.5*(u0 + t/u0);
			}
			cout.precision(9);
			//cout << u << " ";


			int i = 0;
			double a = 1;
			double v = a;

			while (abs(a) - e2 >= 0) // считаем косинус с помощью разложения
			{
				i += 2;
				a *= -pow((3*x + 1),2) / (i-1) / i;
				v += a;
			}
			//cout << v << " ";


			i = 1;
			a = v;
			double w = a;

			while (abs(a) - e3 >= 0) // считаем арктангенс с помощью разложения
			{
				i += 2;
				a *= -pow(v,2) * (i-2) / i;
				w += a;
			}
			w = w * u;

			cout << w << " ";
			double F = sqrt(2*x+0.4)*atan(cos(3*x+1));
			cout << sqrt(2*x+0.4)*atan(cos(3*x+1)) << " " << abs(F - w) << endl;

			x += x_step;
	}

	system("pause"); 
	return 0; 
}