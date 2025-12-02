#include <iostream>
#include <vector>
using namespace std;

const int MAX_COLS = 50;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};

bool solve_maze(char maze[][MAX_COLS], int rows, int cols, int x, int y,
                vector<pair<int,int>>& path)
{

      if(x<0||y<0||x>=rows||y>=cols) return false;
      if(maze[x][y]=='#' || maze[x][y]=='*') return false;

      if(maze[x][y]=='E')
      {
          path.push_back({x,y});
          return true;
      }

      char temp = maze[x][y];
      if(temp!='S') maze[x][y]='*';
      path.push_back({x,y});

      for(int i=0;i<4;i++)
      {
          if(solve_maze(maze,rows,cols,x+dx[i],y+dy[i],path))
            return true;
      }

      path.pop_back();
      if(temp!='S') maze[x][y]='.';
      return false;
}

int main()
{
      int r,c;
      cout<<"Enter maze dimensions: ";
      cin>>r>>c;

      char maze[50][MAX_COLS];
      int sx=-1,sy=-1,ex=0,ey=0;
      int start=0,end=0;

      cout<<"Enter maze:\n";
      for(int i=0;i<r;i++)
      {
          for(int j=0;j<c;j++)
          {
              cin>>maze[i][j];
              if(maze[i][j]=='S'){ sx=i; sy=j; start++; }
          if(maze[i][j]=='E'){ ex=i; ey=j; end++; }
          }
      }

    if(start!=1 || end!=1)
    {
        cout<<"Invalid maze!\n";
        return 0;
    }

    vector<pair<int,int>> path;
    cout<<"Solving...\n";

    if(solve_maze(maze,r,c,sx,sy,path))
    {
          cout<<"Solution found!\nPath length: "<<path.size()<<"\n";

          maze[sx][sy]='S';
          for(auto &p: path) maze[p.first][p.second]='*';
          maze[ex][ey]='E';

          for(int i=0;i<r;i++)
          {
              for(int j=0;j<c;j++) cout<<maze[i][j];
              cout<<"\n";
          }

          cout<<"Path:\n";
          for(auto &p:path)
            cout<<"("<<p.first<<","<<p.second<<") -> ";
          cout<<"END\n";
    }
    else
    {
        cout<<"No solution exists.\n";
    }
}
