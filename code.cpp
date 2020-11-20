#include <iostream>
#include <fstream>

#define row 5456
#define col 4

using namespace std;

void read_csv(float X[][col], int Y[])
{
    fstream fin;
    string data;
    fin.open("dataset.csv", ios::in);
    for (int i = 0; i < row; i++)
    {
        int j;
        for (j = 0; j < col; j++)
        {
            getline(fin, data, ',');
            X[i][j] = stof(data);
        }
        getline(fin, data, '\n');
        Y[i] = stoi(data);
    }
    fin.close();
}

int main()
{
    float X[row][col];
    int Y[row];
    read_csv(X, Y);
    return 0;
}
