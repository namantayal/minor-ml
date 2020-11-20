#include<iostream>
using namespace std;

const int size=1000;

float m_multiply(float matrix1[][4],float matrix2[][2],float answer[][2],int r1, int c1,int c2)
{


    //multiplying first and second matrix
    for(int i = 0; i < r1; ++i)
    {
        for(int j = 0; j < c2; ++j)
        {
            for(int k = 0; k < c1; ++k)
            {
                answer[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    //displaying the result
    cout << endl << "RESULT: ";
    for(int i = 0; i < r1; ++i)
    {
        cout<<endl;
        for(int j = 0; j < c2; ++j)
        {
            cout << " " << answer[i][j];
        }
    }
}

int main()
{
    float x[3][4] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}};
    float y[4][2] = {{1,2},{2,3},{5,7},{1,1}};
    float result[3][2];

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<2;j++)
        {
            result[i][j]=0;
        }
    }
    m_multiply(x,y,result,3,4,2);

    return 0;

}
