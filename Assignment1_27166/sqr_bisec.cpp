#include <iostream>
using namespace std;
int main() 
{
    	double N;
    	cout << "Enter a positive number: ";
    	cin >> N;

    	if (N < 0) 
	{
        	cout << "Number must be positive." << endl;
        	return 1;
    	}

    	double a = 0.0;
    	double b = (N < 1.0) ? 1.0 : N;
    	const double tolerance = 0.01;
    	double m;

    	while (true) 
	{
        	m = (a + b) / 2.0;
        	double f_m = m * m - N;

        	double abs_f_m = (f_m < 0) ? -f_m : f_m;

        	if (abs_f_m < tolerance) 
		{
            		break;
        	}

        	double f_a = a * a - N;

        	if ((f_a > 0 && f_m > 0) || (f_a < 0 && f_m < 0)) 
		{
            		a = m;
        	} else 
		{
            		b = m;
        	}
    	}

    	//rounding to 2 decimals
    	int rounded = (int)(m * 100 + 0.5);
    	double result = rounded / 100.0;

    	// Output
    	int int_part = (int)result;
    	int decimal_part = rounded % 100;

    	cout << "Square root of " << N << " is approximately " << int_part << ".";
    	if (decimal_part < 10) 
	{
        	cout << "0";  // leading zero if needed
    	}
    	cout << decimal_part << endl;

    	return 0;
}

