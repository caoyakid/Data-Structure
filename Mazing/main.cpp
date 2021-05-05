#include <iostream>
#include <fstream>
#include "Maze.h"
using namespace std;

#define row 12 //9
#define col 15 //9

char maze[row+2][col+2];
int mark[row+2][col+2];

// the algorithm Dr. provided 
void Path(const int m, const int p)
{
    mark[1][1] = '1';
    Stack<Items> stack(m * p);
    Items temp(1, 1, E);
    stack.Push(temp);
    while (!stack.isEmpty())
    {
        temp = stack.Top();
        stack.Pop();
        int i = temp.x;
        int j = temp.y;
        int d = temp.dir;
        bool havepathflag = false;
        while (d < 8)
        {
            int g = i + movearray[d].di;
            int h = j + movearray[d].dj;
            if ((g == m) && (h == p))
            {
                mark[g][h] = 1;
                temp.x = i;
                temp.y = j;
                temp.dir = d + 1;
                stack.Push(temp);
                cout << stack;
                cout << "The end (" << g << "," << h << ")\n";
                return;
            }

            if ((maze[g][h] == '0') && (mark[g][h] == 0))
            {
                havepathflag = true;
                mark[g][h] = 1;
                temp.x = i;
                temp.y = j;
                temp.dir = d + 1;
                stack.Push(temp);
                i = g;
                j = h;
                d = N;
            }
            else
            {
                d++;
            }
        }
    }
    cout << "No path in maze." << endl;
}


int main()
{
    //read file 
    fstream file;
    file.open("./maze311.txt"); //maze314.txt
    if(!file){
        cout<<"Can't open the file\n";
    }
    //put in array
    for (int i = 1; i<=row; i++){
        for(int j = 1; j<=col; j++){
            file >> maze[i][j];    
        }
    }
    //create boundary
    for (int j = 0; j < col + 2; j++)
        maze[0][j] = maze[row + 1][j] = '1';
    for (int i = 1; i < row + 1; i++)
        maze[i][0] = maze[i][col + 1] = '1';
    maze[1][0] = 'S';
    maze[row][col + 1] = 'E';

    file.close();
    // output maze
    for (int i = 0; i < row + 2; i++)
    {
        for (int j = 0; j < col + 2; j++)
            cout << maze[i][j] << " ";
        cout << endl;
    }

    cout << endl;

    setmovearray(); // in offset.hpp
    Path(row, col);

    cout << endl;

    return 0;
}