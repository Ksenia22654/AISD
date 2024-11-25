#include <iostream>
using namespace std;
const int V = 9;

void Dijkstra(int GR[V][V], int st);

void main()
{
    setlocale(LC_ALL, "Rus");
    int start;
    int GR[V][V] = {
        {0, 7, 10, 0, 0, 0, 0 , 0, 0},//   A
        {7, 0, 0, 0, 0, 9, 27, 0, 0},//   B
        {10, 0, 0, 0, 31, 8, 0, 0, 0},//   C
        {0, 0, 0, 0, 32, 0, 0, 17, 21},// D
        {0, 0, 31, 32, 0, 0, 0, 0, 0},//   E
        {0, 9, 8, 0, 0, 0, 0, 11, 0},//   F
        {0, 27, 0, 0, 0, 0, 0, 0, 15},// G
        {0, 0, 0, 17, 0, 11, 0, 0, 15},// H
        {0, 0, 0, 21, 0, 0, 15, 15, 0} };// I
    //  A   B   C   D   E   F   G   H   I

    char symb[40];
    bool pr = false;
    printf("Введите начальную вершину: ");
    while (pr == false) { //Цикл для проверки корректности ввода вершины.
        cin >> symb;
        if (symb[1] == '\0' && (symb[0] == 'A' || symb[0] == 'B' || symb[0] == 'C' ||
            symb[0] == 'D' || symb[0] == 'E' || symb[0] == 'F' ||
            symb[0] == 'G' || symb[0] == 'H' || symb[0] == 'I'))
            pr = true;
        else
            printf("Некорректный ввод. Введите вершину: ");
    }
    int letter = (int)symb[0] - 65; // Преобразование символа вершины в индекс.
    Dijkstra(GR, letter);
}

void Dijkstra(int GR[V][V], int st)
{
    int distance[V], index, u, m = st + 1;//Объявление массивов и переменных.
    bool visited[V]; //Объявление массива логических переменных для отслеживания посещенных вершин.
    for (int i = 0; i < V; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    distance[st] = 0;
    for (int count = 0; count < V - 1; count++)
    {
        int min = INT_MAX;
        for (int i = 0; i < V; i++)
            if (!visited[i] && distance[i] <= min)
            {
                min = distance[i];
                index = i;
            }
        u = index;
        visited[u] = true;
        for (int i = 0; i < V; i++)
            if (!visited[i] && GR[u][i] && distance[u] != INT_MAX && distance[u] + GR[u][i] < distance[i])
                distance[i] = distance[u] + GR[u][i];
    }
    printf("Расстояния до вершин:\n");
    for (int i = 0; i < V; i++)
    {
        if (distance[i] != INT_MAX)
            printf("От вершины %c до %c : %d\n", (char)(m + 64), (char)(i + 65), distance[i]);
        else
            printf("От вершины %c до %c : недостижима\n", (char)(m + 64), (char)(i + 65));
    }
}