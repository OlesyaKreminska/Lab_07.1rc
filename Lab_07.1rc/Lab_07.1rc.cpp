#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int row = 0, int col = 0);
void Print(int** a, const int rowCount, const int colCount, int row = 0, int col = 0);
void Sort(int** a, const int rowCount, const int colCount, int i0 = 0, int i1 = 0);
void Change(int** a, const int row1, const int row2, const int colCount, int col = 0);
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k, int row = 0, int col = 0);

int main()
{
    srand((unsigned)time(NULL));
    int Low = 11;
    int High = 67;
    int rowCount = 7;
    int colCount = 5;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High);
    Print(a, rowCount, colCount);
    Sort(a, rowCount, colCount);
    Print(a, rowCount, colCount);

    int S = 0;
    int k = 0;
    Calc(a, rowCount, colCount, S, k);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    Print(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}

// Рекурсивне створення матриці
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int row, int col)
{
    if (row >= rowCount)
        return;

    a[row][col] = Low + rand() % (High - Low + 1);

    if (col + 1 < colCount)
        Create(a, rowCount, colCount, Low, High, row, col + 1);
    else
        Create(a, rowCount, colCount, Low, High, row + 1, 0);
}

// Рекурсивний вивід матриці
void Print(int** a, const int rowCount, const int colCount, int row, int col)
{
    if (row >= rowCount)
        return;

    cout << setw(4) << a[row][col];

    if (col + 1 < colCount)
        Print(a, rowCount, colCount, row, col + 1);
    else
    {
        cout << endl;
        Print(a, rowCount, colCount, row + 1, 0);
    }
}

// Рекурсивне сортування матриці
void Sort(int** a, const int rowCount, const int colCount, int i0, int i1)
{
    if (i0 >= rowCount - 1)
        return;

    if (i1 < rowCount - i0 - 1)
    {
        if ((a[i1][0] < a[i1 + 1][0]) ||
            (a[i1][0] == a[i1 + 1][0] && a[i1][1] < a[i1 + 1][1]) ||
            (a[i1][0] == a[i1 + 1][0] && a[i1][1] == a[i1 + 1][1] && a[i1][2] > a[i1 + 1][2]))
        {
            Change(a, i1, i1 + 1, colCount);
        }
        Sort(a, rowCount, colCount, i0, i1 + 1);
    }
    else
    {
        Sort(a, rowCount, colCount, i0 + 1, 0);
    }
}

// Рекурсивна заміна рядків
void Change(int** a, const int row1, const int row2, const int colCount, int col)
{
    if (col >= colCount)
        return;

    int tmp = a[row1][col];
    a[row1][col] = a[row2][col];
    a[row2][col] = tmp;

    Change(a, row1, row2, colCount, col + 1);
}

// Рекурсивний підрахунок елементів
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k, int row, int col)
{
    if (row >= rowCount)
        return;

    if (!(a[row][col] % 2 == 0 && a[row][col] % 13 == 0))
    {
        S += a[row][col];
        k++;
        a[row][col] = 0;
    }

    if (col + 1 < colCount)
        Calc(a, rowCount, colCount, S, k, row, col + 1);
    else
        Calc(a, rowCount, colCount, S, k, row + 1, 0);
}
