#include <iostream>
#include <fstream>
#include <vector>

#define row 5456
#define Xcol 4
#define Ycol 4

using namespace std;

void read_csv(vector<vector<float>> &X, vector<vector<int>> &Y)
{
    fstream fin;
    string data;
    fin.open("dataset.csv", ios::in);
    for (int i = 0; i < row; i++)
    {
        int j;
        for (j = 0; j < Xcol; j++)
        {
            getline(fin, data, ',');
            X[i][j] = stof(data);
        }
        for (j = 0; j < Ycol - 1; j++)
        {
            getline(fin, data, ',');
            Y[i][j] = stoi(data);
        }
        getline(fin, data, '\n');
        Y[i][j] = stoi(data);
    }
    fin.close();
}

int main()
{
    vector<vector<float>> X(row, vector<float>(Xcol));
    vector<vector<int>> Y(row, vector<int>(Ycol));
    read_csv(X, Y);
    return 0;
}
