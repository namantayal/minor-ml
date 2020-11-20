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



void m_transpose(vector<vector<float>> &matrix, vector<vector<float>> &transpose)
{
    for(int i=0;i<matrix.size();i++)
    {
        for(int j=0;j<matrix[0].size();j++)
        {
            transpose[j][i] = matrix[i][j];
        }
    }
}

void m_multiply(vector<vector<float>> &matrix1,vector<vector<float>> &matrix2,vector<vector<float>> &answer)
{
    //multiplying first and second matrix
    for(int i = 0; i < matrix1.size(); ++i)
    {
        for(int j = 0; j < matrix2[0].size(); ++j)
        {
            for(int k = 0; k < matrix1[0].size(); ++k)
            {
                answer[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void display(vector<vector<float>> &matrix)
{
    cout << endl << "RESULT: " << endl;
    for(int i = 0; i < matrix.size(); i++)
    {
        cout<<endl;
        for(int j = 0; j <matrix[0].size(); j++)
        {
            cout << " " << matrix[i][j];
        }
    }
}

int main()
{
    vector<vector<float>> X(row, vector<float>(Xcol));
    vector<vector<int>> Y(row, vector<int>(Ycol));
    vector<vector<float>> X_transpose(Xcol,vector<float>(row));
    read_csv(X, Y);
    m_transpose(X,X_transpose);
    vector<vector<float>> B1(Xcol,vector<float>(Xcol));
    m_multiply(X_transpose,X,B1);
    display(B1);
    
    return 0;
}
