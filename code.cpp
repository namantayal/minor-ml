#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#define Xrow 4092
#define Xcol 5
#define Ycol 4
#define Xrow_test 1364

using namespace std;

void display(vector<vector<double>> &);

void read_csv(vector<vector<double>> &X, vector<vector<int>> &Y, vector<vector<double>> &X_test, vector<vector<int>> &Y_test)
{
    fstream fin;
    string data;
    fin.open("dataset.csv", ios::in);
    for (int i = 0; i < Xrow; i++)
    {
        int j;
        X[i][0] = 1;
        for (j = 1; j < Xcol; j++)
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

    for (int i = 0; i < Xrow_test; i++)
    {
        int j;
        X_test[i][0] = 1;
        for (j = 1; j < Xcol; j++)
        {
            getline(fin, data, ',');
            X_test[i][j] = stof(data);
        }
        for (j = 0; j < Ycol - 1; j++)
        {
            getline(fin, data, ',');
            Y_test[i][j] = stoi(data);
        }
        getline(fin, data, '\n');
        Y_test[i][j] = stoi(data);
    }
    fin.close();
}

string map_to_answer(int value)
{
    if(value==0)
        return "Slight Right";
    else if(value==1)
        return "Sharp Right";
    else if(value==2)
        return "Move Forward";
    else
        return "Slight Left";
}

void write_csv(vector<vector<double>> &X, vector<vector<int>> &Y_test, vector<vector<double>> &Y_hat)
{
    fstream fout;
    fout.open("predicted.csv", ios::out);
    fout<<"Sensor1,Sensor2,Sensor3,Sensor4,,Actual,Predicted\n";
    for(int i=0;i<X.size();i++)
    {
        for(int j=1;j<X[0].size();j++)
        {
            fout<<X[i][j]<<",";
        }
        int index = max_element(Y_test[i].begin(), Y_test[i].end()) - Y_test[i].begin();
        fout<<","<<map_to_answer(index);
        index = max_element(Y_hat[i].begin(), Y_hat[i].end()) - Y_hat[i].begin();
        fout<<","<<map_to_answer(index)<<"\n";
    }
    fout.close();
}

void m_transpose(vector<vector<double>> &matrix, vector<vector<double>> &transpose)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            transpose[j][i] = matrix[i][j];
        }
    }
}

template <typename T1, typename T2>
void m_multiply(vector<vector<T1>> &matrix1, vector<vector<T2>> &matrix2, vector<vector<double>> &answer)
{
    //multiplying first and second matrix
    for (int i = 0; i < matrix1.size(); ++i)
    {
        for (int j = 0; j < matrix2[0].size(); ++j)
        {
            for (int k = 0; k < matrix1[0].size(); ++k)
            {
                answer[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void m_inverse(vector<vector<double>> matrix, vector<vector<double>> &inverse)
{
    //-----------------------------------creating identity  matrix----------------------------------------------
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            if (j == i)
                inverse[i][j] = 1;
            else
                inverse[i][j] = 0;
        }
    }
    //-----------------------------------------------------------------------------------------------------------

    //------------------------------- elementary transformation column by column-----------------------------------
    for (int col = 0; col < matrix.size(); col++)
    {
        //--------------------------------making diagnol elements as 1------------------------------------
        int index = col;
        for (int row = col + 1; row < matrix[0].size(); row++)
        {
            if (matrix[row][col] != 0)
            {
                index = row;
                break;
            }
        }
        if (index != col)
        {
            double factor = (matrix[col][col] - 1) / matrix[index][col];
            for (int j = 0; j < matrix[0].size(); j++)
            {
                matrix[col][j] -= matrix[index][j] * factor;
                inverse[col][j] -= inverse[index][j] * factor;
            }
        }
        else
        {
            double temp = matrix[index][col];
            for (int j = 0; j < matrix[0].size(); j++)
            {
                matrix[col][j] /= temp;
                inverse[col][j] /= temp;
            }
        }
        //------------------------------------------------------------------------------------------------

        //----------------------------------making remaining elements of column 0-------------------------

        for (int row = 0; row < matrix[0].size(); row++)
        {

            if (row != col)
            {
                double temp = matrix[row][col];
                for (int j = 0; j < matrix[0].size(); j++)
                {
                    matrix[row][j] -= matrix[col][j] * temp;
                    inverse[row][j] -= inverse[col][j] * temp;
                }
            }
        }
        //--------------------------------------------------------------------------------------------------
    }
}

void display(vector<vector<int>> &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            cout <<"\t"<<matrix[i][j]<<"\t";
        }
        cout << endl;
    }
}

void estimate(vector<vector<double>> &X, vector<vector<int>> &Y, vector<vector<double>> &beta)
{
    vector<vector<double>> X_transpose(Xcol, vector<double>(Xrow));
    vector<vector<double>> B1(Xcol, vector<double>(Xcol));
    vector<vector<double>> B1_inv(Xcol, vector<double>(Xcol));
    vector<vector<double>> B2(Xcol, vector<double>(Xrow));

    m_transpose(X, X_transpose);
    m_multiply(X_transpose, X, B1);
    m_inverse(B1, B1_inv);
    m_multiply(B1_inv, X_transpose, B2);
    m_multiply(B2, Y, beta);
}

void predict(vector<vector<double>> &X, vector<vector<double>> &beta, vector<vector<double>> &Y_hat)
{
    m_multiply(X, beta, Y_hat);
    for (int i = 0; i < Y_hat.size(); i++)
    {
        for (int j = 0; j < Y_hat[0].size(); j++)
        {
            Y_hat[i][j] = 1 / (1 + exp(-Y_hat[i][j]));
        }
    }
}

void confusion_matrix(vector<vector<int>> &Y_test, vector<vector<double>> &Y_hat)
{
    vector<vector<int>> matrix(Ycol, vector<int>(Ycol,0));
    for(int i=0;i<Y_test.size();i++)
    {
        int row = max_element(Y_hat[i].begin(), Y_hat[i].end()) - Y_hat[i].begin();
        int col = max_element(Y_test[i].begin(), Y_test[i].end()) - Y_test[i].begin();
        matrix[row][col]+=1;
    }
    cout<<"\n\n\tConfusion Matrix - \n\n";
    display(matrix);
    int correct=0;
    for(int i=0;i<matrix.size();i++)
    {
        for(int j=0;j<matrix[0].size();j++)
        {
            if(i==j)
                correct+=matrix[i][j];
        }
    }
    cout<<"\nAccuracy - "<<((float)correct/Xrow_test)*100<<" %";
}

int main()
{
    vector<vector<double>> X(Xrow, vector<double>(Xcol));
    vector<vector<int>> Y(Xrow, vector<int>(Ycol));
    vector<vector<double>> X_test(Xrow_test, vector<double>(Xcol));
    vector<vector<int>> Y_test(Xrow_test, vector<int>(Ycol));
    vector<vector<double>> beta(Xcol, vector<double>(Ycol));
    vector<vector<double>> Y_hat(Xrow_test, vector<double>(Ycol));
    
    read_csv(X, Y, X_test, Y_test);
    
    estimate(X, Y, beta);
    predict(X_test,beta,Y_hat);
    write_csv(X_test,Y_test,Y_hat);
    confusion_matrix(Y_test,Y_hat);
    return 0;
}
