#include <iostream>
using namespace std;

int main() 
{
	int num1, den1, num2, den2,result_num = 0, result_den = 1;
 	char op;

	// Input 
 	cout << "Enter numerator and denominator of first fraction: ";
 	cin >> num1 >> den1;

 	cout << "Enter numerator and denominator of second fraction: ";
 	cin >> num2 >> den2;

 	cout << "Choose operation (+, -, *, /): ";
 	cin >> op;


 	


	switch (op) 
	{
    		case '+':
        		result_num = num1 * den2 + num2 * den1;
        		result_den = den1 * den2;
        		break;
    		case '-':
        		result_num = num1 * den2 - num2 * den1;
        		result_den = den1 * den2;
        		break;
    		case '*':
        		result_num = num1 * num2;
        		result_den = den1 * den2;
        		break;
    		case '/':
        		if (num2 == 0) 
			{
            			cout << "Error: Division by zero!" << endl;
            			return 1;
        		}
        
			result_num = num1 * den2;
        		result_den = den1 * num2;
        		break;
    		default:
        		cout << "Invalid operation!" << endl;
        		return 1;
	}


	//simplify
    	int a = result_num;
    	int b = result_den;


    	
    	if (a < 0) a = -a;
    	if (b < 0) b = -b;


    	
    	while (b != 0) 
	{
        	int temp = b;
        	b = a % b;
        	a = temp;
    	}
    	int gcd = a;


    	
    	result_num /= gcd;
    	result_den /= gcd;


    	
    	if (result_den < 0) 
	{
        	result_num = -result_num;
        	result_den = -result_den;
    	}


    // Output 
    cout << "Result: " << result_num << "/" << result_den << endl;

    return 0;
}
