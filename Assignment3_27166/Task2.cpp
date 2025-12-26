#include <iostream>
#include <vector>
#include <regex>
#include <string>
using namespace std;

bool valid_submission(int lab, int erp, const vector<string>& files, bool verbose=false) 
{
      if(files.empty()) return false;

      string expected_zip = "lab" + to_string(lab) + "_" + to_string(erp) + ".zip";
      int total = files.size(), pass = 0;

      bool zip_ok = (files[0] == expected_zip);
      if(zip_ok) pass++;
      if(verbose) cout << "- " << files[0] << (zip_ok ? " ✓\n" : " ✗\n");

      regex pattern("^task[0-9]+\\.cpp$");

      for(int i = 1; i < total; i++)
      {
          bool ok = regex_match(files[i], pattern);
          if(ok) pass++;
          if(verbose) cout << "- " << files[i] << (ok ? " ✓\n" : " ✗\n");
      }

      if(verbose)
          cout << "Summary for " << files[0] << ": " << pass << "/" << total << " passed\n\n";

      return pass == total;
}

int main()
{
      vector<string> case1 = {"lab8_12345.zip", "task1.cpp", "task2.cpp"};
      vector<string> case2 = {"lab08_12345.zip", "task1.cpp", "task2.cpp"};
      vector<string> case3 = {"lab8_12345.zip", "task01.cpp", "task2.cpp"};
      vector<string> case4 = {"lab8_12345.zip", "task1!.cpp", "task2.cpp"};

      cout << (valid_submission(8,12345,case1) ? "pass\n":"fail\n");
      cout << (valid_submission(8,12345,case2) ? "pass\n":"fail\n");
      cout << (valid_submission(8,12345,case3) ? "pass\n":"fail\n");
      cout << (valid_submission(8,12345,case4) ? "pass\n":"fail\n");
}
