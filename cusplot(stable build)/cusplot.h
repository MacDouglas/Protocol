#ifndef CUSPLOT_H
#define CUSPLOT_H

#include <QMainWindow>
#include <qcustomplot.h>

#include <QDebug>
#include <QApplication>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QMessageBox>

namespace Ui {
class cusplot;
}

class cusplot : public QMainWindow
{
    Q_OBJECT

public:
    explicit cusplot(QWidget *parent = nullptr);

    QVector<double> coordinateX,coordinateY,SimulatedY,modelY;                            //Координаты X,Y - Исходные координаты
    QVector<double> interpolatedX,interpolatedY;                        //Координаты X,Y - После интерполиции
    QVector<double> outputSmooth,outputMedian;                                       //Координаты Y - После обработки скользящего среднего
    QVector<double> LLSQ,LR;                                      //Реальные координаты двумерного пространства

    ~cusplot();

    void WriteToFile(QString text, QVector<double> tmpStr);
    void WriteToFile(QString text, double tmpStr);

protected:

    void firstBuild(double a,double b,double c,double e);       //Моделирование кривой
    void firstBuild(QVector <double> &a);
    void firstBuild(QVector<double> &a,QVector<double> &b);

    double frequency,speed,midsteplen;

    QVector<double> pointsMax,pointsMin,posMax,posMin,pointsMerge,posMerge;         //Массивы для скользящего среднего, Значений минимума/максимума, позиций минимума/максимума
    QVector<double> amplitude,amplitudeHalf,deltaAmplitude;
    QVector<double> pointsSigma, posSigma, deltaSigma;
    QVector<double> deltaRate,rate,stepTime,deltaStepTime,doubleStepTime,deltaDoubleStepTime;

    void FindAmplitude();                          //Вычисляет Амплитуды максимумов и Амплитуда/2
    void FindDeltaAmplitude();

    void FindSigma();                               //Вычисляет сигма = Амплитуде/2, слева и справа на оси координат
    void FindDeltaSigma();

    void findRate();
    void FindDeltaRate();

    void FindFrequency();                       //Вычисляет частоту движения
    void FindSpeed();
    void MiddleStepLength();

    void FindStepTime();                        //Находит время j-го шага
    void FindDeltaStepTime();
    void FindDoubleStepTime();
    void FindDeltaDoubleStepTime();

    void ArrayPutDown(QVector<double> &temp);                           //Вычитает из каждого элемента минимальную точку минимума.

    void interpolation();
    void interpolation(QVector<double> &temp,int a);

    int linearRegression();
    int semulateLinearRegression(double a,double b);

    void Fitting();
    void llsq0 ( int n, double x[], double y[], double &a );
    void llsq ( int n, QVector <double> &x,QVector <double> &y, double &a, double &b );

    void findAllMax();
    void findAllMin();
    void correct_points_max(QVector<double> &points,QVector<double> &pos);
    void correct_points_min(QVector<double> &points,QVector<double> &pos);

    void mergePoints();
    int merge(QVector<double> a,QVector<double> b,QVector<double> posA,QVector<double> posB);

    void smoothFilter(int n,int window);
    void createSmoothMass(int n,int window);

    void qvectorToDouble(double* copy);
    void doubleToQvector(double* signal);
    void initMedianFilter();
    void _medianfilter(const double* signal, double* result, int N);
    void medianfilter(double* signal, double* result, int N);

    int clearQVector(QVector<double> &garbage);
    void clearQVectors();
private:
    Ui::cusplot *ui;

    QCustomPlot *wGraphic;              // Объявляем объект QCustomPlot
    QCPCurve *verticalLine;             // Объявляем объект для вертикальной линии
    QCPItemTracer *tracer;              // Трасировщик по точкам графика

    QString A,w,a,f;

//    void initCusPlot(QVector<double> &a,QVector<double> &b);
    void initCusPlot();

    void ReadFileReal();
    void ReadFileReeGo();


private slots:
    void slotMousePress(QMouseEvent * event);
    void slotMouseMove(QMouseEvent * event);
//    void on_startButton_clicked();
    void on_ReadFileReal_clicked();
    void on_ReadFileReeGo_clicked();
    void on_source_clicked();
    void on_interpolation_clicked();

    void on_merge_clicked();
    void on_sigma_clicked();

    void on_interpolationX_clicked();
    void on_spaceXsmooth_clicked();
    void on_spaceXmerge_clicked();

    void on_smooth_clicked();
    void on_medianFilter_clicked();

    void on_Linear_Least_Squares_clicked();
    void on_linear_Regression_clicked();
    void on_tracer_clicked();
    void on_startButton_clicked();
    void on_createPDF_clicked();
};

#endif // CUSPLOT_H
