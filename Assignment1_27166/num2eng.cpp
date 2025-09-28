#include <iostream>
#include <string>
using namespace std;

int main() 
{
	int num;
	cout << "Enter an amount in figures: ";
	cin >> num;

 	cout << "In words: ";

 	// Given words
 	string ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine","ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen","sixteen", "seventeen", "eighteen", "nineteen"};

 	string tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

 	if (num == 0) 
	{
        	cout << "zero" << endl;
        	return 0;
    	}

 	if (num < 0) 
	{
        	cout << "negative ";
        	num = -num;
 	}

 	// seperate thousands and non-thousands
 	int thousands = num / 1000;
 	int belowThousand = num % 1000;

    	// store seperated values
 	int parts[2] = {thousands, belowThousand}; // index 0 -> thousands, 1 -> remainder
 	string labels[2] = {" thousand ", ""};

 	for (int i = 0; i < 2; i++) 
	{
        	int n = parts[i];
        	if (n == 0) continue;

        	int h = n / 100;
        	int t = n % 100;

        	if (h > 0) 
		{
			cout << ones[h] << " hundred";
			if (t > 0) cout << " ";
        	}

		if (t < 20) 
		{
            		cout << ones[t];
		} else 
		{
            		int ten = t / 10;
			int one = t % 10;
			cout << tens[ten];
			if (one > 0) cout << " " << ones[one];
        	}

        	cout << labels[i];
    	}

    cout << endl;
    return 0;
}
