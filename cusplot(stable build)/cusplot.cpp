#include "cusplot.h"
#include "ui_cusplot.h"
#include "QDebug"
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>

//using namespace protocol_subjects;

cusplot::cusplot(QWidget *parent) : QMainWindow(parent), ui(new Ui::cusplot)
{
    ui->setupUi(this);
}



cusplot::~cusplot()
{
    delete ui;
}

void cusplot::on_ReadFileReal_clicked()
{
    ReadFileReal();
    initCusPlot();

}
void cusplot::on_ReadFileReeGo_clicked()
{
    ReadFileReeGo();
    initCusPlot();
}

void cusplot::on_startButton_clicked()
{
    QString string_a,string_b,string_c,string_e;

    string_a = ui->lineEdit_a->text();
    string_b = ui->lineEdit_b->text();
    string_c = ui->lineEdit_c->text();
    string_e = ui->lineEdit_e->text();

    firstBuild(string_a.toDouble(),string_b.toDouble() ,string_c.toDouble(),string_e.toDouble());

}

void cusplot::on_source_clicked()
{
    double max = *std::max_element(coordinateY.begin(),coordinateY.end());
    double min = *std::min_element(coordinateY.begin(),coordinateY.end());

    wGraphic->xAxis->setRange(0,coordinateY.size());
    wGraphic->yAxis->setRange(min,max);

    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(coordinateX,coordinateY);
    wGraphic->replot();
}

void cusplot::on_interpolation_clicked()
{
    double max = *std::max_element(interpolatedY.begin(),interpolatedY.end());
    double min = *std::min_element(interpolatedY.begin(),interpolatedY.end());

    wGraphic->xAxis->setRange(0,interpolatedY.size());
    wGraphic->yAxis->setRange(min,max);

    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(interpolatedX,interpolatedY);
    wGraphic->replot();
}

void cusplot::on_smooth_clicked()
{
    double max = *std::max_element(outputSmooth.begin(),outputSmooth.end());
    double min = *std::min_element(outputSmooth.begin(),outputSmooth.end());

//    QPen pen0,pen1,pen2;  // creates a default pen

//    pen0.setWidth(1);
//    pen0.setBrush(Qt::red);

//    pen1.setWidth(1);
//    pen1.setBrush(Qt::blue);

//    pen2.setWidth(1);
////    pen2.setStyle(Qt::DotLine);
//    pen2.setBrush(Qt::black);

    wGraphic->xAxis->setRange(0,outputSmooth.size());
    wGraphic->yAxis->setRange(min,max);


    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(coordinateX,outputSmooth);

//    wGraphic->addGraph();
//    wGraphic->graph(1)->setData(coordinateX,outputSmooth);
//    wGraphic->graph(1)->setPen(pen1);
//    wGraphic->graph(1)->setName("Модель");


//    //шум
//    wGraphic->addGraph();
//    wGraphic->graph(2)->setData(coordinateX,modelY);
//    wGraphic->graph(2)->setPen(pen2);
//    wGraphic->graph(2)->setName("Шум");

    wGraphic->replot();
}
void cusplot::on_medianFilter_clicked()
{
    double max = *std::max_element(outputMedian.begin(),outputMedian.end());
    double min = *std::min_element(outputMedian.begin(),outputMedian.end());

    wGraphic->xAxis->setRange(0,outputMedian.size());
    wGraphic->yAxis->setRange(min,max);

    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(coordinateX,outputMedian);
    wGraphic->replot();
}

void cusplot::on_merge_clicked()
{
    double max = *std::max_element(outputSmooth.begin(),outputSmooth.end());
    double min = *std::min_element(outputSmooth.begin(),outputSmooth.end());

    wGraphic->xAxis->setRange(0,outputSmooth.size());
    wGraphic->yAxis->setRange(min,max);

    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(posMerge,pointsMerge);
    wGraphic->replot();
}

void cusplot::on_sigma_clicked()
{
    double max = *std::max_element(outputSmooth.begin(),outputSmooth.end());
    double min = *std::min_element(outputSmooth.begin(),outputSmooth.end());

    wGraphic->xAxis->setRange(0,outputSmooth.size());
    wGraphic->yAxis->setRange(min,max);

    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(posSigma,pointsSigma);
    wGraphic->replot();
}

void cusplot::on_interpolationX_clicked()
{
    wGraphic->xAxis->setRange(0,interpolatedY.size());
//    wGraphic->xAxis->setRange(250, 350);
    wGraphic->yAxis->setRange(0,80);

    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(interpolatedX,interpolatedY);
    wGraphic->replot();
}

void cusplot::on_spaceXsmooth_clicked()
{
    wGraphic->xAxis->setRange(0,outputSmooth.size());
    wGraphic->yAxis->setRange(0,80);

    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(interpolatedX,outputSmooth);
    wGraphic->replot();
}

void cusplot::on_spaceXmerge_clicked()
{
    wGraphic->xAxis->setRange(0,outputSmooth.size());
    wGraphic->yAxis->setRange(0,80);

    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(posMerge,pointsMerge);
    wGraphic->replot();
}

void cusplot::on_linear_Regression_clicked()
{
    double max = *std::max_element(LR.begin(),LR.end());
    double min = *std::min_element(LR.begin(),LR.end());

    wGraphic->xAxis->setRange(0,LR.size());
    wGraphic->yAxis->setRange(min,max);

    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(coordinateX,LR);
    wGraphic->replot();

}
void cusplot::on_Linear_Least_Squares_clicked()
{
    double max = *std::max_element(LLSQ.begin(),LLSQ.end());
    double min = *std::min_element(LLSQ.begin(),LLSQ.end());

    wGraphic->xAxis->setRange(0,LLSQ.size());
    wGraphic->yAxis->setRange(min,max);

    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(coordinateX,LLSQ);
    wGraphic->replot();
}

void cusplot::on_tracer_clicked()
{
    if(tracer->style() ==  QCPItemTracer::tsCircle)
        tracer->setStyle(QCPItemTracer::tsNone);
    else
        tracer->setStyle(QCPItemTracer::tsCircle);

}


void cusplot::on_createPDF_clicked()
{
    QPdfWriter pdf("C:/Users/Elias/Desktop/projects/cusplot(stable build)/Protocols/protocol.pdf");
    QPainter painter(&pdf);

    painter.drawText(1000,100,"Результат обследования за 08.06.2021");

    QFont font = painter.font();
    font.setWeight(QFont::Bold);
    painter.setFont(font);

    QRect secondname(1000,400,1000,200);
    painter.drawText(secondname,Qt::AlignLeft | Qt::AlignVCenter,"Фамилия");
    QRect name(2000,400,1000,200);
    painter.drawText(name,Qt::AlignLeft | Qt::AlignVCenter,"Имя");
    QRect thirdname(3000,400,1000,200);
    painter.drawText(thirdname,Qt::AlignLeft | Qt::AlignVCenter,"Отчетсво");
    QRect gender(4000,400,1000,200);
    painter.drawText(gender,Qt::AlignLeft | Qt::AlignVCenter,"Пол");
    QRect birthdate(5000,400,1000,200);
    painter.drawText(birthdate,Qt::AlignLeft | Qt::AlignVCenter,"Дата рождения");

    font.setWeight(QFont::Normal);
    painter.setFont(font);

    QRect real_secondname(1000,600,1000,200);
    painter.drawText(real_secondname,Qt::AlignLeft | Qt::AlignVCenter,"Чернышов");
    QRect real_name(2000,600,1000,200);
    painter.drawText(real_name,Qt::AlignLeft | Qt::AlignVCenter,"Илья");
    QRect real_thirdname(3000,600,1000,200);
    painter.drawText(real_thirdname,Qt::AlignLeft | Qt::AlignVCenter,"Юрьевич");
    QRect real_gender(4000,600,1000,200);
    painter.drawText(real_gender,Qt::AlignLeft | Qt::AlignVCenter,"М");
    QRect real_birthdate(5000,600,1000,200);
    painter.drawText(real_birthdate,Qt::AlignLeft | Qt::AlignVCenter,"15.02.1999");


    QRectF target1(1000.0, 1000.0, 3300.0, 2300.0);
    QRectF target2(4300, 1000, 3300, 2300);
    QRectF target3(1000.0, 3300.0, 3300.0, 2300.0);
    QRectF target4(4300.0, 3300.0, 3300.0, 2300.0);
    QRectF source(0.0, 0.0, 350.0, 220.0);

    QImage image1("C:/Users/Elias/Desktop/projects/cusplot(stable build)/images/sin_1.png");
    QImage image2("C:/Users/Elias/Desktop/projects/cusplot(stable build)/images/sin_2.png");
    QImage image3("C:/Users/Elias/Desktop/projects/cusplot(stable build)/images/sin_3.png");
    QImage image4("C:/Users/Elias/Desktop/projects/cusplot(stable build)/images/sin_4.png");

    painter.drawImage(target1,image1,source);
    painter.drawImage(target2,image2,source);
    painter.drawImage(target3,image3,source);
    painter.drawImage(target4,image4,source);

    font.setWeight(QFont::Bold);
    painter.setFont(font);

    QRect name_parametr_1(1000,5800,4000,200);
    painter.drawText(name_parametr_1,Qt::AlignLeft | Qt::AlignVCenter,"Количество шагов:");
    QRect name_parametr_2(1000,6000,4000,200);
    painter.drawText(name_parametr_2,Qt::AlignLeft | Qt::AlignVCenter,"Симметрия шагов:");
    QRect name_parametr_3(1000,6200,4000,200);
    painter.drawText(name_parametr_3,Qt::AlignLeft | Qt::AlignVCenter,"Коэффициент Хёрста (Н):");
    QRect name_parametr_4(1000,6400,4000,200);
    painter.drawText(name_parametr_4,Qt::AlignLeft | Qt::AlignVCenter,"Средняя скорость движения:");
    QRect name_parametr_5(1000,6600,4000,200);
    painter.drawText(name_parametr_5,Qt::AlignLeft | Qt::AlignVCenter,"Средняя частота движения:");

    font.setWeight(QFont::Normal);
    painter.setFont(font);

    QRect parametr_1(4300,5800,1000,200);
    painter.drawText(parametr_1,Qt::AlignLeft | Qt::AlignVCenter,"88");
    QRect parametr_2(4300,6000,1000,200);
    painter.drawText(parametr_2,Qt::AlignLeft | Qt::AlignVCenter,"0.9");
    QRect parametr_3(4300,6200,1000,200);
    painter.drawText(parametr_3,Qt::AlignLeft | Qt::AlignVCenter,"1");
    QRect parametr_4(4300,6400,1000,200);
    painter.drawText(parametr_4,Qt::AlignLeft | Qt::AlignVCenter,"90");
    QRect parametr_5(4300,6600,1000,200);
    painter.drawText(parametr_5,Qt::AlignLeft | Qt::AlignVCenter,"0.3");



//    QVector<QRect> mainRects;
//    painter.drawText(2000,1000,"Protocol");
//    QRect rec1(1000,2100,2500, 500);
//    QRect rec2(3500,2100,2500, 500);
//    mainRects.push_back(rec1);
//    mainRects.push_back(rec2);
//    painter.drawRects(mainRects);
//    painter.drawText(rec1,"Скорость");




}
