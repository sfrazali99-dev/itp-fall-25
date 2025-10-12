#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <vector>
#include <string>

using namespace std;
int main() 
{
    	double xmin, xmax;
     	cout << "Enter x range (min and max, in radians): ";
    	if (!( cin >> xmin >> xmax)) 
	{
         	cerr << "Invalid input. Please enter two numbers.\n";
        	return 1;
    	}
    	if (xmax <= xmin) 
	{
        	 cerr << "Invalid range: max must be greater than min.\n";
        	return 1;
    	}

    	const int gridW = 80;
    	const int gridH = 20;
    	const double ymin = -1.0, ymax = 1.0;

    
     	vector< string> grid(gridH,  string(gridW, ' '));

    
    	int yAxisCol = (int) round((0.0 - xmin) / (xmax - xmin) * (gridW - 1));
    	int xAxisRow = (int) round((ymax - 0.0) / (ymax - ymin) * (gridH - 1));

    
    	if (0 <= yAxisCol && yAxisCol < gridW) 
	{
        	for (int r = 0; r < gridH; ++r) 
		{
            		grid[r][yAxisCol] = '|';
        	}
    	}
    	if (0 <= xAxisRow && xAxisRow < gridH) 
	{
        	for (int c = 0; c < gridW; ++c) 
		{
            		grid[xAxisRow][c] = '-';
        	}
    	}
    
    	if (0 <= xAxisRow && xAxisRow < gridH && 0 <= yAxisCol && yAxisCol < gridW) 
	{
        	grid[xAxisRow][yAxisCol] = '+';
    	}

    
    	for (int c = 0; c < gridW; ++c) 
	{
        	double x = xmin + (xmax - xmin) * c / (gridW - 1);
        	double y =  sin(x);

        
        	int r = (int) round((ymax - y) / (ymax - ymin) * (gridH - 1));
        	if (r >= 0 && r < gridH) 
		{
        	    
            		grid[r][c] = '*';
        	}
    	}

    
    	for (const auto &row : grid) 
	{
         	cout << row << "\n";
    	}

    return 0;
}