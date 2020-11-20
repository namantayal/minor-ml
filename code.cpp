#include <iostream>
#include <fstream>

#define row 5456
#define col 4

using namespace std;

void display(float *answer,int r1,int c2)
{
    cout << endl << "RESULT: " << endl;
    for(int i = 0; i < r1; ++i)
    {
        cout<<endl;
        for(int j = 0; j < c2; ++j)
        {
            cout << " " << answer[i*c2+j];
        }
    }
}

void matrance(float *a, float *transpose, int r, int c)
{
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            transpose[j*r+i] = a[i*c+j];
        }
    }
}

void m_multiply(float *matrix1,float *matrix2,float *answer,int r1, int c1,int c2)
{
    //multiplying first and second matrix
    for(int i = 0; i < r1; ++i)
    {
        for(int j = 0; j < c2; ++j)
        {
            for(int k = 0; k < c1; ++k)
            {
                answer[i*c2+j] += matrix1[i*c1+k] * matrix2[k*c2+j];
            }
        }
    }
}


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
    float x[2][3]={{4,0,1},{6,1,2}};
    float y[3][2]={{7,2},{0,2},{1,1}};
    float answer[3][3];
    float trans[3][2];
    matrance(x[0],trans[0],2,3);
    display(trans[0],3,2);
    m_multiply(trans[0],x[0],answer[0],3,2,3);
    display(answer[0],3,3);
    
    //read_csv(X, Y);
    return 0;
}
