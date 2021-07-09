#include "cusplot.h"
#include "ui_cusplot.h"
#include "QDebug"
#include <cmath>


int cusplot::linearRegression(){

    const int n = coordinateX.size();

    int i;                               //Индексная переменная:
    double x[n],y[n];                   //Массивы статистических значений:
    double a,b;                         //Параметры модели:
    double Sx=0,Sy=0,Sxy=0,Sxx=0;       //Средние значения:

    //Вычисление параметров модели:
    for(i=0; i < n; i++){
        Sx+=coordinateX[i];
        Sy+=outputSmooth[i];
        Sxy+=coordinateX[i]*outputSmooth[i];
        Sxx+=coordinateX[i]*coordinateX[i];
    }
    Sx/=n;
    Sy/=n;
    Sxy/=n;
    Sxx/=n;

    a=(Sx*Sy-Sxy)/(Sx*Sx-Sxx);
    b=(Sxy-a*Sxx)/Sx;
    //Результат:

    semulateLinearRegression(a,b);

    return 1;
}
int cusplot::semulateLinearRegression(double a,double b){

    if(!a || !b){
        return 0;
    }
    else{
        if(!LR.isEmpty()){
            clearQVector(LR);
        }
        ui->linear_Regression->setEnabled(true);

        qDebug() << "Линейная регрессия";
        qDebug() << "a = " << a;
        qDebug() << "b = " << b;

        double temp;
        for (int i = 0; i < coordinateX.size(); i++) {
            temp = a * coordinateX[i] + b;
            LR.push_back(temp);
        }

        for (int i = 0; i < LR.size(); i++) {
            outputSmooth[i] = outputSmooth[i] - LR[i];

        }


    }
    return 1;
}

void cusplot::llsq ( int n, QVector <double> &x,QVector <double> &y, double &a, double &b )
{
    if(!LLSQ.isEmpty()){
        clearQVector(LLSQ);
    }

    ui->Linear_Least_Squares->setEnabled(true);

    double bot;
    int i;
    double top;
    double xbar;
    double ybar;

    //  Special case.
    if ( n == 1 )
    {
      a = 0.0;
      b = y[0];
      return;
    }

    //  Average X and Y.
    xbar = 0.0;
    ybar = 0.0;
    for ( i = 0; i < n; i++ )
    {
      xbar = xbar + x[i];
      ybar = ybar + y[i];
    }
    xbar = xbar / ( double ) n;
    ybar = ybar / ( double ) n;

    //  Compute Beta.
    top = 0.0;
    bot = 0.0;
    for ( i = 0; i < n; i++ )
    {
      top = top + ( x[i] - xbar ) * ( y[i] - ybar );
      bot = bot + ( x[i] - xbar ) * ( x[i] - xbar );
    }
    a = top / bot;

    b = ybar - a * xbar;

    qDebug() << "llsq";
    qDebug() << "a = " << a;
    qDebug() << "b = " << b;


    double temp;
    for (int i = 0; i < coordinateX.size(); i++) {
        temp = a*coordinateX[i] + b;

        LLSQ.push_back(temp);
    }
    //for (int i = 0; i < LLSQ.size(); i++) {
    //    outputSmooth[i] = outputSmooth[i] - LLSQ[i];
    //}


    return;
}

void timestamp ( )
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct std::tm *tm_ptr;
  std::time_t now;

  now = std::time ( NULL );
  tm_ptr = std::localtime ( &now );

  std::strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr );

  qDebug() << time_buffer << "\n";

  return;
# undef TIME_SIZE
}




