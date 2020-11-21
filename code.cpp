#include <iostream>
#include <fstream>
#include <vector>

#define Xrow 5456
#define Xcol 5
#define Ycol 4

using namespace std;

void display(vector<vector<double>>&);

void read_csv(vector<vector<double>> &X, vector<vector<int>> &Y)
{
    fstream fin;
    string data;
    fin.open("dataset.csv", ios::in);
    for (int i = 0; i < Xrow; i++)
    {
        int j;
        X[i][0]=1;
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
    fin.close();
}



void m_transpose(vector<vector<double>> &matrix, vector<vector<double>> &transpose)
{
    for(int i=0;i<matrix.size();i++)
    {
        for(int j=0;j<matrix[0].size();j++)
        {
            transpose[j][i] = matrix[i][j];
        }
    }
}
template<typename T1, typename T2>
void m_multiply(vector<vector<T1>> &matrix1,vector<vector<T2>> &matrix2,vector<vector<double>> &answer)
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

void m_inverse(vector<vector<double>> matrix, vector<vector<double>> &inverse)
{
//-----------------------------------creating identity  matrix----------------------------------------------
    for(int i=0;i<matrix.size();i++)
    {
        for(int j=0;j<matrix[0].size();j++)
        {
            if(j==i)
                inverse[i][j]=1;
            else
                inverse[i][j]=0;
        }
    }
//-----------------------------------------------------------------------------------------------------------


//------------------------------- elementary transformation column by column-----------------------------------
    for(int col=0;col<matrix.size();col++)
    {
    //--------------------------------making diagnol elements as 1------------------------------------
        int index=col;
        for(int row=col+1;row<matrix[0].size();row++)
        {
            if(matrix[row][col]!=0)
            {
                index=row;
                break;
            }
        }
        if(index!=col)
        {
            double factor = (matrix[col][col] - 1)/matrix[index][col];
            for(int j=0;j<matrix[0].size();j++)
            {
                matrix[col][j]-=matrix[index][j]*factor;
                inverse[col][j]-=inverse[index][j]*factor;
            }
        }
        else
        {
            double temp=matrix[index][col];
            for(int j=0;j<matrix[0].size();j++)
            { 
                matrix[col][j]/=temp;
                inverse[col][j]/=temp;
            }
        }
    //------------------------------------------------------------------------------------------------

    //----------------------------------making remaining elements of column 0-------------------------

        for(int row = 0;row<matrix[0].size();row++){
        
            if(row!=col){
                double temp = matrix[row][col];
                for(int j=0;j<matrix[0].size();j++)
                {   
                    matrix[row][j]-=matrix[col][j]*temp;
                    inverse[row][j]-=inverse[col][j]*temp; 
                             
                }
            }
        }
    //--------------------------------------------------------------------------------------------------
    }
}

void display(vector<vector<double>> &matrix)
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
    vector<vector<double>> X(Xrow, vector<double>(Xcol));
    vector<vector<int>> Y(Xrow, vector<int>(Ycol));
    vector<vector<double>> X_transpose(Xcol,vector<double>(Xrow));
    vector<vector<double>> B1(Xcol,vector<double>(Xcol));
    vector<vector<double>> B1_inv(Xcol,vector<double>(Xcol));
    vector<vector<double>> B2(Xcol,vector<double>(Xrow));
    vector<vector<double>> Beta(Xcol,vector<double>(Ycol));

    read_csv(X, Y);
    
    m_transpose(X,X_transpose);
    m_multiply(X_transpose,X,B1);
    m_inverse(B1,B1_inv);
    m_multiply(B1_inv,X_transpose,B2);
    m_multiply(B2,Y,Beta);
    display(Beta);
    return 0;
}
