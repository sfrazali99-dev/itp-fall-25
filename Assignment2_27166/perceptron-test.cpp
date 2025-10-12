#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() 
{

	srand(time(0));

    
    	double w = ( (rand() / (double)RAND_MAX) * 2.0 ) - 1.0;
    	double b = ( (rand() / (double)RAND_MAX) * 2.0 ) - 1.0;	
    	cout << "Random model parameters: w = " << w << ", b = " << b << endl;
    	
    	const int TEST_COUNT = 10;
   	 double x, y, target;
    	int correct = 0;
    	int validInputs = 0;

    	cout << "Enter 10 integer values for x:" << endl;

    	while (validInputs < TEST_COUNT) 
	{
        	cout << "x[" << validInputs + 1 << "]: ";
        	cin >> x;

        	if (cin.fail()) 
		{
            		cout << "Invalid input! Please enter an integer." << endl;
            		cin.clear();
            		cin.ignore(1000, '\n');
            		continue;
        	}

        	y = w * x + b;
        	target = 2 * x * x - 4;

        	cout << "x = " << x 
             	<< ", prediction = " << y 
             	<< ", target = " << target << " --> ";

        	if ((y - target <= 1.0) && (y - target >= -1.0)) 
		{
            		cout << "Correct" << endl;
            		correct++;
        	} else 
		{
            		cout << "Incorrect" << endl;
        	}

        	validInputs++;
    	}

    	double accuracy = (correct / (double)TEST_COUNT) * 100;
    	cout << "Accuracy: " << accuracy << "%" << endl;

    return 0;
}
