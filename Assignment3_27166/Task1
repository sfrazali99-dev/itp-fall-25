#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool cmp(char a, char b) 
{
      return tolower(a) < tolower(b);
}

void insertion_sort(string &s, int n)
{
      for(int i = 1; i < n; i++)
      {
          char key = s[i];
          int j = i - 1;
          while(j >= 0 && cmp(key, s[j]))
          {
              s[j+1] = s[j];
              j--;
          }
          s[j+1] = key;
      }
}

string sort_string(const string& str, int n = -1)
{
      string result = str;
      if(n < 0 || n > result.size()) n = result.size();
      insertion_sort(result, n);
      return result;
}

void sort_string_inplace(string &str, int n = -1)
{
      if(n < 0 || n > str.size()) n = str.size();
      insertion_sort(str, n);
}

int main()
{
      string s;
      int n;

      cout<<"Enter a string: ";
      getline(cin, s);

      cout<<"Enter number of characters to sort (negative for all): ";
      cin>>n;

      string new_sorted = sort_string(s, n);
      cout<<"Sorted string (new): " << new_sorted << "\n";

      sort_string_inplace(s, n);
      cout<<"Sorted string (in place): " << s << "\n";
}
