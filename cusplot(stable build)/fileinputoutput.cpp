#include "cusplot.h"
#include "ui_cusplot.h"
#include "QDebug"
#include <QFileDialog>


void cusplot::ReadFileReal(){

    QString path = "C:/Users/Elias/Desktop/projects/cusplot(stable build)/Data";
    QString filter = "Text File (*.txt) ;; All File (*.*)" ;

    QString file_name = QFileDialog::getOpenFileName(this, "open file ", path ,filter);

    QFile inputFile(file_name);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QVector <double> tempY;
        QTextStream in(&inputFile);
        double tmp;

        while (!in.atEnd())
        {
           QString line = in.readLine();
           tmp = (line.toDouble() * 1000) / 1000;
           qDebug() << "Line is " << tmp;
           tempY.push_back(tmp);
        }
        inputFile.close();

        firstBuild(tempY);
    }
}

void cusplot::ReadFileReeGo(){

    QVector<double> X,Y;

    QString path = "C:/Users/Elias/Desktop/projects/cusplot(stable build)/";
    QString filter = "Text File (*.txt) ;; All File (*.*)" ;

    QString file_name = QFileDialog::getOpenFileName(this, "open file ", path ,filter);

    QFile list(file_name);
    if((list.exists()) && (list.open(QIODevice::ReadOnly)))
    {
    QString text(list.readAll());
    QStringList listS = text.split("\n");
    for(int i = 1; i < listS.size()-1; i++)
    {
    QStringList xy = listS[i].split(" ");

    X.push_back(xy[0].toInt());
    Y.push_back(xy[1].toInt());

    }
    }
    list.close();

    firstBuild(X);

    X.clear();X.squeeze();
    Y.clear();Y.squeeze();
}

void cusplot::WriteToFile(QString text, QVector<double> tmpStr){

    QString pathToStorage = "C:/Users/Elias/Desktop/projects/cusplot(stable build)/Protocols/result_storage.txt";

    QFile file(pathToStorage);

    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        // We're going to streaming text to the file
        QTextStream stream(&file);

        stream<< text<<'\n';
        for(int i = 0; i < tmpStr.size();i++){
            stream << tmpStr[i]<<" ";
        }
        stream<<'\n'<<'\n';

        file.close();
    }
}
void cusplot::WriteToFile(QString text, double tmpStr){

    QString pathToStorage = "C:/Users/Elias/Desktop/projects/cusplot(stable build)/Protocols/result_storage.txt";
    QFile file(pathToStorage);

    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        // We're going to streaming text to the file
        QTextStream stream(&file);

        stream<< text<<'\n';
        stream << tmpStr<<" ";
        stream<<'\n'<<'\n';

        file.close();
    }
}




