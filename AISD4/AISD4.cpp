#include <iostream>
#include <climits> // Для INT_MAX
using namespace std;

int C[6][6] = {
      {0,    28,      21,      59,      12,    27},//    1
      {7,    0,      24,      INT_MAX, 21,    9},//    2
      {9,    32,      0,      13,      11,    INT_MAX},// 3
      {8,    INT_MAX, 5,      0,      16,    INT_MAX},// 4
      {14, 13,      15,      10,      0,    22},//    5
      {15, 18,      INT_MAX, INT_MAX, 6,    0},//    6
      // 1   2      3      4      5    6  
};
int S[6][6] = {
    {0, 2, 3, 4, 5, 6},// 1
    {1, 0, 3, 4, 5, 6},// 2
    {1, 2, 0, 4, 5, 6},// 3
    {1, 2, 3, 0, 5, 6},// 4
    {1, 2, 3, 4, 0, 6},// 5
    {1, 2, 3, 4, 5, 0},// 6
    //   1 2 3 4 5 6
};

void FloydWarshall();

int main()
{
    setlocale(LC_ALL, "Rus");
    FloydWarshall();
    return 0; 
}

void FloydWarshall()
{
    for (int m = 0; m < 6; m++)
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 6; j++)
                if (C[i][j] > C[i][m] + C[m][j])
                {
                    C[i][j] = C[i][m] + C[m][j]; // Обновляем кратчайший путь
                    S[i][j] = S[i][m]; // Обновляем предшественника
                }

    cout << "Матрица расстояний:\n";
    for (int i = 0; i < 6; i++)
    {
        for (int k = 0; k < 6; k++)
        {
            cout << C[i][k] << "\t";
        }
        cout << "\n";
    }


    cout << "Матрица предшественников:\n";
    for (int i = 0; i < 6; i++)
    {
        for (int k = 0; k < 6; k++)
        {
            cout << S[i][k] << "\t";
        }
        cout << "\n";
    }
}