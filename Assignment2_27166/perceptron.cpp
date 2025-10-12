#include <iostream>
using namespace std;

int main() 
{
	//X and target have not been defined to save memory
    	double y, w = 0.0, b = 0.0, error;
    	double a = 0.01;

    	cout << "Step 0: prediction = 0.00, error = 14.00" << endl;

    	for (int i = 1; i <= 1000; i++) 
    	{
        	y = w * 3 + b;
        	error = 14 - y;

        	w = w + a * error * 3;
        	b = b + a * error;

        	if (i % 100 == 0) 
        	{
            		cout << "Step: " << i << ": prediction = " << y << ", error = " << error << endl;
        	}

        	// question does not ask for e3it condition but I'm gonna leave it here just in case
        	//if (error < 0.001 && error > -0.001) 
        	//{
        	//  cout << "Training converged at step " << i << ": prediction = " << y << ", error = " << error << endl;
        	// break;
        	//}
    	}

    	cout << "Final prediction at 3=3: " << y << endl;
    	cout << "Target value: 14.00" << endl;
    	cout << "Final w = " << w << ", b = " << b << endl;

return 0;
}
