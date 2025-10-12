#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>

using namespace std;

int main() 
{
     	srand(time(0));

    	enum State 
	{
        	HEALTHY = 0,
        	RECOVERED = -1,
        	DEAD = 10
    	};

    	int W, H;
     	cout << "Enter grid width and height: ";
    	if (!( cin >> W >> H)) 
	{
         	cerr << "Invalid input for dimensions.\n";
        	return 1;
    	}
    	if (W <= 0 || H <= 0) 
	{
        	cerr << "Width and height must be positive.\n";
        	return 1;
    	}

    	int total = W * H;
    	int I;
     	cout << "Enter initial number of infected individuals: ";
    	if (!( cin >> I)) 
	{
         	cerr << "Invalid input.\n";
        	return 1;
    	}
    	if (I < 1 || I > total) 
	{
         	cerr << "Initial infected must be between 1 and " << total << ".\n";
        	return 1;
    	}

    	double p, w_prob;
     	cout << "Enter infection probability p (0..1): ";
    	if (!( cin >> p) || p < 0.0 || p > 1.0) 
	{
         	cerr << "Invalid p. Must be between 0 and 1.\n";
        	return 1;
    	}	
     	cout << "Enter worsening probability w (0..1): ";
    	if (!( cin >> w_prob) || w_prob < 0.0 || w_prob > 1.0) 
	{
         	cerr << "Invalid w. Must be between 0 and 1.\n";
        	return 1;
    	}

    	int R = 5;
    	int T = 30;

     	vector< vector<int>> grid(H,  vector<int>(W, HEALTHY));
     	vector< vector<int>> daysInfected(H,  vector<int>(W, 0));

    	int placed = 0;
    	while (placed < I) 
	{
        	int r =  rand() % H;
        	int c =  rand() % W;
        	if (grid[r][c] == HEALTHY) 
		{
            		int severity = 1 + ( rand() % 9);
            		grid[r][c] = severity;
            		daysInfected[r][c] = 0;
            		placed++;
        	}
    	}

    	auto isInfected = [](int s) 
	{
        	return (s >= 1 && s <= 9);
    	};

    	auto printGrid = [&](void) 
	{
        	for (int r = 0; r < H; ++r) 
		{
            		for (int c = 0; c < W; ++c) 
			{
                		int s = grid[r][c];
                		char ch;
                		if (s == HEALTHY) ch = '.';
                		else if (s == RECOVERED) ch = 'R';
                		else if (s == DEAD) ch = 'X';
                		else if (isInfected(s)) ch = char('0' + s);
                		else ch = '?';
                 		cout << ch;
            		}
             	cout << "\n";
        	}
    	};

     	cout << "Initial grid state:\n";
    	printGrid();

    	const int dr[4] = { -1, +1, 0, 0 };
    	const int dc[4] = { 0, 0, -1, +1 };

    	for (int day = 1; day <= T; ++day) 
	{
         	vector< vector<int>> next = grid;
         	vector< vector<int>> nextDays = daysInfected;

        	int countHealthy = 0, countInfected = 0, countRecovered = 0, countDead = 0;

        	for (int r = 0; r < H; ++r) 
		{
            		for (int c = 0; c < W; ++c) 
			{
                		int s = grid[r][c];
                		if (s == HEALTHY) countHealthy++;
                		else if (isInfected(s)) countInfected++;
                		else if (s == RECOVERED) countRecovered++;
                		else if (s == DEAD) countDead++;
            		}
        	}

        	for (int r = 0; r < H; ++r) 
		{
            		for (int c = 0; c < W; ++c) 
			{
                		int s = grid[r][c];
                		if (s == HEALTHY) 
				{
                    			int bestSeverity = 0;
                    			for (int k = 0; k < 4; ++k) 
					{
                        			int rr = r + dr[k];
                        			int cc = c + dc[k];
                        			if (rr < 0 || rr >= H || cc < 0 || cc >= W) continue;
                        			int sn = grid[rr][cc];
                        			if (isInfected(sn)) 
						{
                            				int severityNew = 1 + ( rand() % sn);
                            				if (severityNew > bestSeverity) 
							{
                                				bestSeverity = severityNew;
                            				}
                        			}
                    			}
                    			if (bestSeverity > 0) 
					{
                        			double roll = ( rand() / (double)RAND_MAX);
                        			if (roll < p) 
						{
                            				next[r][c] = bestSeverity;
                            				nextDays[r][c] = 0;
                        			}
                    			}
                		}
                		else if (isInfected(s)) 
				{
                    		nextDays[r][c] = daysInfected[r][c] + 1;
                    		if (nextDays[r][c] >= R) 
				{
                        		next[r][c] = RECOVERED;
                        		nextDays[r][c] = 0;
                    		} else 
				{
                        		double roll = ( rand() / (double)RAND_MAX);
                        		if (roll < w_prob) 
					{
                            			int sev = s + 1;
                            			if (sev > 9) 
						{
                                			next[r][c] = DEAD;
                            			} else 
						{
                                			next[r][c] = sev;
                            			}
                        			} else 
						{
                            			int sev = s - 1;
                            			if (sev < 1) 
						{
                                			sev = 1;
                            			}
                            			next[r][c] = sev;
                        		}
                    		}
                	}
            	}
        }

        grid = next;
        daysInfected = nextDays;

        countHealthy = countInfected = countRecovered = countDead = 0;
        for (int r = 0; r < H; ++r) 
	{
            	for (int c = 0; c < W; ++c) 
		{
                	int s = grid[r][c];
                	if (s == HEALTHY) countHealthy++;
                	else if (isInfected(s)) countInfected++;
                	else if (s == RECOVERED) countRecovered++;
                	else if (s == DEAD) countDead++;
            	}
        }

        cout << "Day " << day
                  << ": Healthy: " << countHealthy
                  << ", Infected: " << countInfected
                  << ", Recovered: " << countRecovered
                  << ", Dead: " << countDead << "\n";
    }

     cout << "Final grid state:\n";
    printGrid();

    return 0;
}
