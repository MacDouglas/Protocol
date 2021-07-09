#include "cusplot.h"
#include "ui_cusplot.h"
#include "QDebug"
#include <cmath>


void cusplot::Fitting(){

    ui->linear_Regression->setEnabled(true);

    int numOfData = coordinateY.size();

    float * datax = new float[numOfData];
    float * datay = new float[numOfData];
    float * dataz = new float[numOfData];
    float phase(0);
    float mag(0);

    for(int i=0;i < numOfData;i++)
    {
        datax[i] = cos((2*M_PI) * float(i%numOfData) / float(numOfData));
        datay[i] = sin((2*M_PI) * float(i%numOfData) / float(numOfData));
      //datax[i] = 0.3*cos(i*0.2);
      //datay[i] = 0.3*sin(i*0.2);
//      datax[i] = coordinateY[i]+0.01;
//      datay[i] = coordinateY[i];

        dataz[i] = coordinateY[i];
//      dataz[i] = 0.3*sin(i*0.2);
    }

    float a(0);
    float b(0);
    float c(0);
    float p[3] = {0}; // product of fitting equation
    float XiYi(0);
    float XiZi(0);
    float YiZi(0);
    float XiXi(0);
    float YiYi(0);
    float Xi(0);
    float Yi(0);
    float Zi(0);

    for(int i=0; i < numOfData; i++)
      {
        XiYi += datax[i] * datay[i];
        XiZi += datax[i] * dataz[i];
        YiZi += datay[i] * dataz[i];
        XiXi += datax[i] * datax[i];
        YiYi += datax[i] * datay[i];
        Xi   += datax[i];
        Yi   += datay[i];
        Zi   += dataz[i];
      }
    float A[3][3];
    float B[3][3];
    float C[3][3];
    float X[3][3];
    int i;
    int j;
    float x = 0;
    float n = 0; //n is the determinant of A

    A[0][0] = XiXi;
    A[0][1] = XiYi;
    A[0][2] = Xi;
    A[1][0] = XiYi;
    A[1][1] = YiYi;
    A[1][2] = Yi;
    A[2][0] = Xi;
    A[2][1] = Yi;
    A[2][2] = numOfData;

    for( i=0;i<3;i++)
    {
     for(int j=0;j<3;j++)
     {
       B[i][j] = 0;
       C[i][j] = 0;
     }
    }

    for( i=0, j=0;j<3;j++)
    {
     if(j == 2)
     {
       n += A[i][j] * A[i+1][0] * A[i+2][1];
     }
     else if(j == 1)
     {
       n += A[i][j] * A[i+1][j+1] * A[i+2][0];
     }
     else
     {
       n += A[i][j] * A[i+1][j+1] * A[i+2][j+2];
     }
    }

    for( i=2, j=0;j<3;j++)
    {
     if(j == 2)
     {
       n -= A[i][j] * A[i-1][0] * A[i-2][1];
     }
     else if(j == 1)
     {
       n -= A[i][j] * A[i-1][j+1] * A[i-2][0];
     }
     else
     {
       n -= A[i][j]*A[i-1][j+1]*A[i-2][j+2];
     }
    }

    // Check determinant n of matrix A
    if (n)
    {
     x = 1.0/n;

     for(i=0;i<3;i++)
     {
       for(j=0;j<3;j++)
       {
         B[i][j] = A[j][i];
       }
     }

     C[0][0] =  (B[1][1] * B[2][2]) - (B[2][1] * B[1][2]);
     C[0][1] = ((B[1][0] * B[2][2]) - (B[2][0] * B[1][2])) * (-1);
     C[0][2] =  (B[1][0] * B[2][1]) - (B[2][0] * B[1][1]);

     C[1][0] = ((B[0][1] * B[2][2]) - (B[2][1] * B[0][2])) * (-1);
     C[1][1] =  (B[0][0] * B[2][2]) - (B[2][0] * B[0][2]);
     C[1][2] = ((B[0][0] * B[2][1]) - (B[2][0] * B[0][1])) * (-1);

     C[2][0] =  (B[0][1] * B[1][2]) - (B[1][1] * B[0][2]);
     C[2][1] = ((B[0][0] * B[1][2]) - (B[1][0] * B[0][2])) * (-1);
     C[2][2] =  (B[0][0] * B[1][1]) - (B[1][0] * B[0][1]);

     for( i=0;i<3;i++)
     {
       for( j=0;j<3;j++)
       {
         X[i][j] = C[i][j] * x;
       }
     }

     p[0] = XiZi;
     p[1] = YiZi;
     p[2] = Zi;

     a = X[0][0] * p[0] + X[0][1] * p[1] + X[0][2] * p[2];
     b = X[1][0] * p[0] + X[1][1] * p[1] + X[1][2] * p[2];
     c = X[2][0] * p[0] + X[2][1] * p[1] + X[2][2] * p[2];
    }
    else  // determinant=0
    {
     a = 1;
     b = 1;
     c = 0;
    }

    mag = sqrt(a*a + b*b);

    float phi;

    if((b == 0) && (a >= 0))
    {
     phase = M_PI/2;
    }
    else
        if((b == 0) && (a >= 0))
        {
            phase = 3*M_PI/2;
        }
        else
            if ((a >= 0) && (b > 0))
            {
                phi = atan(fabs(a/b));
                phase = phi;
            }
            else
                if ((a >= 0) && (b < 0))
                {
                    phi = atan(fabs(a/b));
                    phase = M_PI - phi;
                }
                else
                    if ((a <  0) && (b > 0))
                    {
                        phi = atan(fabs(a/b));
                        phase = 2 * M_PI - phi;
                    }
                    else
                        if ((a <  0) && (b < 0))
                        {
                            phi = atan(fabs(a/b));
                            phase = phi + M_PI;
                        }

    qDebug() << "a = " << a;
    qDebug() << "b = " << b;
    qDebug() << "c = " << c;
    qDebug() << "mag = " << mag;
    qDebug() << "Phi = " << phi;
    qDebug() << "phase = " << phase;
    qDebug() << "M_PI = " << M_PI;

    double temp;

    LLSQ.clear();LLSQ.squeeze();
    LR.clear();LR.squeeze();

    for(int i =0;i<coordinateX.size();i++){


        //######    A*X + B $    ######



//        temp = a + c*sin(i + b);
//        temp = a + b*sin(i + c);

//        temp = b + a*sin(i + c);
//        temp = b + c*sin(i + a);

//        temp = c + b*sin(i + a);
//        temp = c + a*sin(i + b);


//        temp = _A + _C*sin(i + _B);
        temp = c + mag*sin(i*a + b);


        LLSQ.push_back(temp);
    }

    for (int i = 0; i < LLSQ.size(); i++) {
        temp = coordinateY[i] - LLSQ[i];
        LR.push_back(temp);
    }

}
