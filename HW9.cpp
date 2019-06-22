#include "Header\ApplicationOfStackNQueue.h"
using namespace std;

void PrintMaze(int maze[8][10])
{
    cout << "The map of the input maze is: \n";
    for (int i = 0; i != 8; i++)
    {
        for (int j = 0; j != 10; j++)
        {
            cout << (maze[i][j] == 0 ? " " : "*");
        }
        cout << "\n";
    }
}

int main()
{
    int maze[8][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    int start[2] = {1, 1};
    int end[2] = {6, 8};
    PrintMaze(maze);
    MazeRunner(maze, start, end);
    cout << "\n";
    system("pause");
}