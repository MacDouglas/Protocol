#include "cusplot.h"
#include <QDebug>
#include <QMessageBox>
#include "ui_cusplot.h"
#include <time.h>


void cusplot::firstBuild(QVector<double> &vectorFromFile){                    //Стандартная функция, которая будет использоваться при протоколе.

    if(!(coordinateX.isEmpty() && coordinateX.isEmpty())){
        clearQVector(coordinateX);
        clearQVector(coordinateY);
    }

    if(vectorFromFile.isEmpty() == true)
        throw "Vector from file is empty!";
    else{
        for(int i=0;i<vectorFromFile.size();i++){
            coordinateX.push_back(i);
            coordinateY.push_back(vectorFromFile[i]);
        }
    }

    initMedianFilter();
    smoothFilter(coordinateY.size()-1,8);

    linearRegression();

    ui->source->setEnabled(true);

    findAllMax();
    findAllMin();
    mergePoints();
    FindDeltaAmplitude();
    FindSigma();
    FindDeltaSigma();
    findRate();
    FindDeltaRate();
    FindSpeed();
    FindFrequency();
    MiddleStepLength();
    FindDeltaStepTime();
    FindDoubleStepTime();
    FindDeltaDoubleStepTime();
}

void cusplot::firstBuild(double a,double b,double c,double e){
    //a - смещение человека относительно камеры
    //b - угол направления движения человека относительно камеры
    //c - частота шагов
    //e - шум на изображении

    srand(time_t(nullptr));
    ui->source->setEnabled(true);

    double random_a;
    double temp;
    int da;

    if(!(coordinateX.isEmpty() && coordinateX.isEmpty())){
        clearQVector(coordinateX);
        clearQVector(coordinateY);
        clearQVector(modelY);
    }


    for(int i = 0; i < 250; i++){

        random_a = static_cast<double>(rand() % ( (int)a - (-(int)a) + 1) + (-(int)a))/100;
        //qDebug() << "random = " << random_a;
        temp = b * sin(c * i + e);
        modelY.push_back(temp);

        temp += random_a;
        coordinateX.push_back(i);
        coordinateY.push_back(temp);
    }

    //WriteToFile("coordinate y",coordinateY);

    initCusPlot();

    double x,y;

//    llsq(coordinateX.size(),coordinateX,coordinateY,x,y);

//    linearRegression();

    initMedianFilter();

    smoothFilter(coordinateY.size()-1,5);

    ui->source->setEnabled(true);

    findAllMax();
    findAllMin();
    mergePoints();
    FindDeltaAmplitude();
    FindSigma();
    FindDeltaSigma();
    findRate();
    FindDeltaRate();
    FindSpeed();
    FindFrequency();
    MiddleStepLength();
    FindDeltaStepTime();
    FindDoubleStepTime();
    FindDeltaDoubleStepTime();

}

void cusplot::ArrayPutDown(QVector<double> &temp){           //Функция опускания графика функции к оси X
    qDebug()<<"Put Array down is done!" << "size is = " << temp.size();

    double pointMin = temp[0];

    for (int i =0;i<temp.size();i++) {         //Находится минимальная точка из всех минимумов

        if(temp[i]<pointMin)
            pointMin = temp[i];
    }

    for (int i = 0;i<temp.size();i++) {
        temp[i] -=  pointMin;
    }

    //WriteToFile("Функция опускания массива до оси координат Х",coordinateY);
}

void cusplot::interpolation(QVector<double> &temp,int a = 0){
    if(temp.isEmpty() == true){
//        QMessageBox::warning(this,"Винмание","Невозможно провести интерполирование");
        return;
    }
    else
    {
        if(interpolatedX.isEmpty() == true){
            for(int i = 0; i < temp.size() * 5;i++){
                interpolatedX.push_back(i);
            }
        }

        for(int i = 0;i < temp.size() * 5;i++){
            interpolatedY.push_back(0);
        }


    for(int i = 0, j = 0; i < temp.size(); i++, j+=5){
        interpolatedY[j] = temp[i];
    }
    for (int i = 0; i < interpolatedY.size() - 5; i += 5) {
        for (int j = 1; j < 5; j++) {
            interpolatedY[i + j] = interpolatedY[i + j - 1] + ((interpolatedY[i + 5] - interpolatedY[i + j - 1]) / (interpolatedX[i + j + 1] - interpolatedX[i + j - 1])) * (interpolatedX[i + j] - interpolatedX[i + j - 1]);
        }
    }

    }
    ui->interpolation->setEnabled(true);
}

void cusplot::interpolation(){
    if(coordinateY.isEmpty() == true){
        return;
    }
    else
    {
        for(int i = 0; i < coordinateX.size() * 2;i++){
            interpolatedX.push_back(i);
        }
        for(int i = 0;i < coordinateY.size() * 2;i++){
            interpolatedY.push_back(0);
        }
        for(int i = 0; i < coordinateY.size(); i++){
            interpolatedY[i*2] = coordinateY[i];
        }
        for(int i = 1 ; i < (coordinateY.size() * 2) - 1 ; i += 2){
            interpolatedY[i] = interpolatedY[i - 1] + ((interpolatedY[i + 1] - interpolatedY[i - 1]) / (interpolatedX[i + 1] - interpolatedX[i - 1])) * (interpolatedX[i] - interpolatedX[i - 1]);
//            qDebug() << " NewY[ " << i << " ] = " << interpolatedY[i] << Qt::endl;
        }
    }
}

int cusplot::clearQVector(QVector<double> &garbage){
    if (garbage.isEmpty())
        throw "Qvector 'garbage' is empty";
    else{
        garbage.clear();
        garbage.squeeze();
    }
    return 0;
}

void cusplot::clearQVectors(){
   coordinateX.clear(); coordinateY.clear();SimulatedY.clear();
   interpolatedX.clear();interpolatedY.clear(); outputSmooth.clear();
   pointsMax.clear();pointsMin.clear();posMax.clear();posMin.clear();
   amplitude.clear(); amplitudeHalf.clear(); deltaAmplitude.clear();
   pointsMerge.clear();posMerge.clear();
   posSigma.clear();pointsSigma.clear();deltaSigma.clear();
   rate.clear(); deltaRate.clear(); stepTime.clear();deltaStepTime.clear();
   doubleStepTime.clear();deltaDoubleStepTime.clear();
   LLSQ.clear(); LR.clear(); outputMedian.clear();

}
