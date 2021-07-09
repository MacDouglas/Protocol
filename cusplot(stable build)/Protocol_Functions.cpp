#include "cusplot.h"
#include "ui_cusplot.h"
#include <QMessageBox>
#include <QDebug>
#include <cmath>

void cusplot::findAllMax()
{
    if(!(pointsMax.isEmpty() && posMax.isEmpty())){
        clearQVector(pointsMax);
        clearQVector(posMax);
    }
    QVector<double> points_max_local, pos_max_local;

    double max = 0, pos = 0;
    double tmp0,tmp1,tmp2,tmp3,tmp4;
    for (int i = 0, j = 0; i < outputSmooth.size() - 4; i++)
    {
        tmp0 = outputSmooth[i];tmp1=outputSmooth[i+1];tmp2=outputSmooth[i+2];tmp3=outputSmooth[i+3];tmp4 = outputSmooth[i+4];
        if ((tmp1 > tmp0) && (tmp2 > tmp1) && (tmp2 > tmp0) && (tmp3 > tmp2) && (tmp3 > tmp1) && (tmp3 > tmp0)
                && (tmp4 > tmp3) && (tmp4 > tmp2) && (tmp3 > tmp1) && (tmp4 > tmp0))

        {
            max = outputSmooth[i + 4];
            pos = i + 4;

        }
        else if (max != 0.0) {
            points_max_local.push_back(max);
            pos_max_local.push_back(pos);

            j++;
            max = 0;
        }
    }

    correct_points_max(points_max_local,pos_max_local);

    WriteToFile("Точки Максимума:",pointsMax);
    WriteToFile("Позиции Максимума:",posMax);


}
void cusplot::correct_points_max(QVector<double> &points,QVector<double> &pos){
    if((points.isEmpty()) == true && (pos.isEmpty() == true))
        throw "points max is empty! Please fill the points";
    else{
        double max = 0;

//        for(int i = 0; i < points.size();i++)
//            qDebug() << "before = "<<points[i];

        for (int i = 0; i < points.size(); i++){
            if(points[i] > max)
                max = points[i];

        }
        double percent = max - max * 0.25;

        for(int i = 0; i < points.size(); i++){
            if(points[i] > 0){
                pointsMax.push_back(points[i]);
                posMax.push_back(pos[i]);
            }
        }
//        for(int i = 0; i < pointsMax.size();i++)
//            qDebug() << "after = "<<pointsMax[i];
    }
}

void cusplot::findAllMin() {

    if(!(pointsMin.isEmpty() && posMin.isEmpty())){
        clearQVector(pointsMin);
        clearQVector(posMin);
    }

    QVector<double> points_min_local, pos_min_local;

    double tmp0,tmp1,tmp2,tmp3,tmp4;
    double min = 100000, pos = 0;
    for (int i = 0; i < outputSmooth.size() - 4 ; i++)
    {
        tmp0 = outputSmooth[i];tmp1=outputSmooth[i+1];tmp2=outputSmooth[i+2];tmp3=outputSmooth[i+3];tmp4 = outputSmooth[i+4];
        if ((tmp1 < tmp0) && (tmp2 < tmp1) && (tmp2 < tmp0) && (tmp3 < tmp2) && (tmp3 < tmp1) && (tmp3 < tmp0)
                && (tmp4 < tmp3) && (tmp4 < tmp2) && (tmp3 < tmp1) && (tmp4 < tmp0))

        {
            min = outputSmooth[i + 4];
            pos = i + 4;

        }
        else if(min != 100000.0){
            //qDebug() << "pos min= "<< pos << " = " <<min;
            points_min_local.push_back(min);
            pos_min_local.push_back(pos);

            min = 100000;
        }
    }
    correct_points_min(points_min_local,pos_min_local);

    WriteToFile("Точки Ммнимума:",pointsMin);
    WriteToFile("Позиции Минимума:",posMin);
}

void cusplot::correct_points_min(QVector<double> &points,QVector<double> &pos){
    if((points.isEmpty()) == true && (pos.isEmpty() == true))
        throw "points max is empty! Please fill the points";
    else{
        double min = 0;

        for(int i = 0; i < points.size();i++)
            qDebug() << "min before = "<<points[i];

        for (int i = 0; i < points.size(); i++){
            if(points[i] < min)
                min = points[i];

        }
        qDebug() << "min = " << min;
        double percent = min - min * 0.30;
        qDebug() << "percent = " << percent;

        for(int i = 0; i < points.size(); i++){
            if(points[i] < 0){
                pointsMin.push_back(points[i]);
                posMin.push_back(pos[i]);
            }
        }
        for(int i = 0; i < pointsMax.size();i++)
            qDebug() << "min after = "<<pointsMax[i];
    }
}

void cusplot::mergePoints(){

    if(pointsMax.isEmpty()==true && pointsMin.isEmpty() == true){
        return;
    }
    else if(pointsMax.size() > pointsMin.size()){

        qDebug() << "Points max: "<< pointsMax.size() << " >  points min: "<<pointsMin.size();
        merge(pointsMax,pointsMin,posMax,posMin);

    }else if(pointsMax.size() < pointsMin.size()){
        qDebug() << "Points max: "<< pointsMax.size() << " <  points min: "<<pointsMin.size();

        merge(pointsMin,pointsMax,posMin,posMax);

    }else if(pointsMax.size() == pointsMin.size()){
        qDebug() << "Points max: "<< pointsMax.size() << " ==  points min: "<<pointsMin.size();
        qDebug() << "pos Max: " << posMax[0] << " posMin: " << posMin[0];
        if(posMax[0] > posMin[0])
            merge(pointsMin,pointsMax,posMin,posMax);
        else
            merge(pointsMax,pointsMin,posMax,posMin);
    }

    ui->merge->setEnabled(true);
    FindAmplitude();

    WriteToFile("Точки максимума и минимума:",pointsMerge);
    WriteToFile("Позиции максимума и минимума:",posMerge);

}
int cusplot::merge(QVector<double> a,QVector<double> b,QVector<double> posA,QVector<double> posB){

    if(!(pointsMerge.isEmpty() && posMerge.isEmpty())){
        clearQVector(pointsMerge);
        clearQVector(posMerge);
    }

    for(int i = 0; i < posA.size(); i++){
        posMerge.push_back(posA[i]);
        pointsMerge.push_back(a[i]);
    }

    for(int i = 0; i < posB.size(); i++){
        posMerge.push_back(posB[i]);
        pointsMerge.push_back(b[i]);
    }

    double tempPos,tempPoints;
    for (int i = 0; i < posMerge.size() - 1; i++) {
            for (int j = 0; j < posMerge.size() - i - 1; j++) {
                if (posMerge[j] > posMerge[j + 1]) {
                    // меняем элементы местами
                    tempPos = posMerge[j];
                    posMerge[j] = posMerge[j + 1];
                    posMerge[j + 1] = tempPos;

                    tempPoints = pointsMerge[j];
                    pointsMerge[j] = pointsMerge[j + 1];
                    pointsMerge[j + 1] = tempPoints;
                }
            }
        }
    return 1;
}
void cusplot::FindAmplitude(){

    if(!amplitude.isEmpty()){
        clearQVector(amplitude);
        clearQVector(stepTime);
        clearQVector(amplitudeHalf);
    }

    if(pointsMax.isEmpty() == true){
//            QMessageBox::warning(this,"Внимание!","Необходимо найти точки максимума");
        return;
    }else
    {
        double deltaX,deltaY;
        for (int i = 0;i < pointsMerge.size() - 1; i++) {
            deltaY = pointsMerge[i+1] - pointsMerge[i];         //Считается амплитуда  = y2 - у1
            amplitude.push_back(abs(deltaY));

            deltaX = posMerge[i+1] - posMerge[i];               //Считается дельта Х между точками минимума и максимума, отвечающими за расчет амплитуды
            stepTime.push_back(abs(deltaX));

            amplitudeHalf.push_back(abs(deltaY/2));
        }
    }
        WriteToFile("Точки амлитуды:",amplitude);
        WriteToFile("Время j-го шага:",stepTime);
        WriteToFile("Точки амплитуды/2:",amplitudeHalf);
}

void cusplot::FindDeltaAmplitude(){

    if(!deltaAmplitude.isEmpty())
        clearQVector(deltaAmplitude);

    if(amplitude.isEmpty() == true){
//            QMessageBox::warning(this,"Внимание!","Необходимо найти амплитуду");
        return;
    }else
    {
        double answer;
        for (int i = 0;i < amplitude.size() - 1 ; i++) {
           answer = amplitude[i+1]/amplitude[i];
           deltaAmplitude.push_back(answer);
        }
            WriteToFile("Дельта амплитуды:",deltaAmplitude);
    }
}

void cusplot::FindSigma(){

    if(!(pointsSigma.isEmpty() && posSigma.isEmpty())){
        clearQVector(pointsSigma);
        clearQVector(posSigma);
    }

    if(coordinateY.isEmpty() == true){
//            QMessageBox::warning(this,"Внимание","Невозможно найти сигма1, сигма2. Создайте массив");
        return;
    }
    else{
        for(int i = 0; i < pointsMerge.size() - 1;i++)
        {
            double tempT,tempY;
            for(int j = posMerge[i]; j < posMerge[i+1]; j++)
            {

                if(pointsMerge[i+1] > pointsMerge[i])
                {
                    if(amplitudeHalf[i] >= outputSmooth[j])
                    {
                        tempT = j;
                        tempY = outputSmooth[j];
                    }
                }
                else
                {
                    if(amplitudeHalf[i] <= outputSmooth[j])
                    {
                        tempT = j;
                        tempY = outputSmooth[j];
                    }
                }
            }
            posSigma.push_back(tempT);
            pointsSigma.push_back(tempY);
            //qDebug() << "t3 = " << tempT << ", y3 = " << tempY;
        }
            ui->sigma->setEnabled(true);

            WriteToFile("Точка Сигма:",pointsSigma);
            WriteToFile("Позиция Сигма:",posSigma);
    }
}
void cusplot::FindDeltaSigma(){

    if(!deltaSigma.isEmpty())
        clearQVector(deltaSigma);

    if(pointsSigma.isEmpty() == true){
//            QMessageBox::warning(this,"Внимание","Невозможно найти сигма1, сигма2. Создайте массив");
        return;
    } else {
        double answer;
        for(int i = 0; i < pointsSigma.size() - 1;i++){
            answer = pointsSigma[i+1] / pointsSigma[i];
            //qDebug() << "DS = " << answer << " = " << pointsSigma[i+1] << "/" << pointsSigma[i];
            deltaSigma.push_back(answer);
        }
            WriteToFile("Дельта Сигма:",deltaSigma);
    }
}

void cusplot::findRate(){

    if(!rate.isEmpty())
        clearQVector(rate);

    if(pointsMerge.isEmpty() == true){
//            QMessageBox::warning(this,"Внимание","Невозможно найти темп. Точки min,max не найдены");
        return;
    }
    else
    {
        double answer;
        for(int i = 0; i < amplitude.size(); i ++){
            answer = amplitude[i] / stepTime[i];
            //qDebug() << "Rate = " << answer;
            rate.push_back(answer);
        }
            WriteToFile("Темп:",rate);
    }
}
void cusplot::FindDeltaRate(){

    if(!deltaRate.isEmpty())
        clearQVector(deltaRate);

    if(rate.isEmpty() == true){
//            QMessageBox::warning(this,"Внимание","Невозможно найти dRate");
        return;
    }else{
        double a,b,answer;
        for(int i = 0;i < rate.size() - 1;i++){
            a = rate[i];
            b = rate[i+1];
            answer = a/b;

            deltaRate.push_back(answer);
        }
            WriteToFile("Дельта темпа:",deltaRate);
    }
}
void cusplot::FindSpeed(){
    if(posMerge.isEmpty() == true){
//            QMessageBox::warning(this,"Внимание","Невозможно найти частоту");
        return;
    }else{
        double t1,tn;
        tn = posMerge.last();
        t1 = posMerge.first();
        speed = 300 / (tn - t1);

            WriteToFile("Средняя скорость движения:",speed);
    }
}

void cusplot::FindFrequency(){
    if(posMerge.isEmpty() == true){
//            QMessageBox::warning(this,"Внимание","Невозможно найти частоту");
        return;
    }else{
        double t1,tn;
        tn = posMerge.last();
        t1 = posMerge.first();
        frequency = pointsMerge.size() / (tn - t1);

            WriteToFile("Частота:",frequency);
    }

}
void cusplot::MiddleStepLength(){
    if(!frequency && !speed){
//            QMessageBox::warning(this,"Внимание","Невозможно среднюю длину шага");
        return;
    }else{
        midsteplen = speed/frequency;
            WriteToFile("Средняя длина шага:",midsteplen);
    }

}
void cusplot::FindDeltaStepTime(){

    if(!deltaStepTime.isEmpty())
        clearQVector(deltaStepTime);

    if(stepTime.isEmpty() == true){
        //QMessageBox::warning(this,"Внимание","Невозможно найти DT1");
        return;
    }else{
        double a,b,answer;
        for(int i = 0;i < stepTime.size()-1;i++){
            a = stepTime[i];
            b = stepTime[i+1];
            answer = b/a;
            deltaStepTime.push_back(answer);
        }
            WriteToFile("Изменение времени между шагами:",deltaStepTime);
    }
}
void cusplot::FindDoubleStepTime(){

    if(!doubleStepTime.isEmpty())
        clearQVector(doubleStepTime);

    if(pointsMerge.isEmpty() == true){
        //QMessageBox::warning(this,"Внимание","Невозможно найти время j-го шага");
        return;
    }else{
        double a,b,answer;
        for(int i = 0;i < pointsMerge.size()-2;i++){
            a = posMerge[i];
            b = posMerge[i+2];

            answer = b - a;
            //qDebug()<<"Answer = " << answer << "ti+2 =" << b << "- ti ="<< a;
            doubleStepTime.push_back(answer);
            }
            WriteToFile("Время двойного шага:",doubleStepTime);
    }
}
void cusplot::FindDeltaDoubleStepTime(){

    if(!deltaDoubleStepTime.isEmpty())
        clearQVector(deltaDoubleStepTime);

    if(doubleStepTime.isEmpty() == true){
        //QMessageBox::warning(this,"Внимание","Невозможно найти DT1");
        return;
    }else{
        double a,b,answer;
        for(int i = 0;i < doubleStepTime.size()-1;i++){
            a = doubleStepTime[i];
            b = doubleStepTime[i+1];
            answer = b/a;
            deltaDoubleStepTime.push_back(answer);
        }
            WriteToFile("Изменение двойного шага:",deltaDoubleStepTime);
    }
}
