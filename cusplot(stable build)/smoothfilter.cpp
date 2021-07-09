#include "cusplot.h"
#include "ui_cusplot.h"
#include <QDebug>


void cusplot::smoothFilter(int n,int window){

    ui->smooth->setEnabled(true);

    if(outputMedian.isEmpty() == true)       //interpolatedY
        throw ("Input vector is empty. Please init data");
    else{                                            //Если выходной массив пустой, создать новый
        if(!outputSmooth.isEmpty())
            clearQVector(outputSmooth);
        createSmoothMass(n,window);
    }

    //WriteToFile("Функция скользящего среднего:",outputSmooth);
}

void cusplot::createSmoothMass(int n,int window){
    int i,j,z,k1,k2,hw;
    double tmp;

    if(fmod(window,2) == 0.0)
        window++;
    hw=(window-1)/2;

    outputSmooth.push_back(outputMedian[0]);
    for (i=0;i<n;i++)
    {
        tmp=0;
        if(i<hw)
        {
            k1=0;
            k2=2*i;
            z=k2+1;
        }
        else if((i+hw)>(n-1))
        {
            k1=i-n+i+1;
            k2=n-1;
            z=k2-k1+1;
        }
        else
        {
            k1=i-hw;
            k2=i+hw;
            z=window;
        }

        for (j=k1;j<=k2;j++)
        {
            tmp+=outputMedian[j];
        }

        outputSmooth.push_back(tmp/z);
    }
}
