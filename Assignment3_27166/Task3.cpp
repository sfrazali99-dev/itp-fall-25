#include <iostream>
#include <vector>
#include <string>
using namespace std;

void show_help()
{
      cout << "Usage:\n<operator> <num1> <num2>\n\n"
           << "Operators: + - * /\n"
           << "Commands:\nhistory\nhelp\nquit\n";
}

int main()
{
      vector<int[4]> history;
      string cmd;

      cout<<"Simple Command-Line Calculator\nType 'help' for commands.\n";

      while(true)
      {
          cout<<"> ";
          cin>>cmd;

          if(cmd=="quit") break;
          if(cmd=="help"){ show_help(); continue;   
      }
      if(cmd=="history")
      {
          for(auto &h: history)
              cout<<h[0]<<" "<<char(h[1])<<" "<<h[2]<<" = "<<h[3]<<"\n";
          continue;
      }

      int a,b; 
      char op = cmd[0];
      cin>>a>>b;

      int result;
      switch(op)
      {
            case '+': result = a+b; break;
            case '-': result = a-b; break;
            case '*': result = a*b; break;
            case '/':
                if(b==0){ cout<<"Error: Division by zero.\n"; continue; }
                result = a/b; break;
            default: cout<<"Unknown operator.\n"; continue;
      }

      int entry[4] = {a, op, b, result};
      history.push_back(entry);

      cout<<result<<"\n";
    }
}
