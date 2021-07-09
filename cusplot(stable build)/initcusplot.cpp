#include "cusplot.h"
#include "ui_cusplot.h"

void cusplot::initCusPlot()
{
    wGraphic = new QCustomPlot();
    ui->gridLayout_2->addWidget(wGraphic,1,0,1,1); // ... и устанавливаем

    verticalLine = new QCPCurve(wGraphic->xAxis, wGraphic->yAxis);

    connect(wGraphic, &QCustomPlot::mousePress, this, &cusplot::slotMousePress);
    connect(wGraphic, &QCustomPlot::mouseMove, this, &cusplot::slotMouseMove);

     QVector<double> x1(2) , y1(2);
     x1[0] = 0;
     y1[0] = -50;
     x1[1] = 0;
     y1[1] = 50;

    verticalLine->setName("Vertical");      // Устанавливаем ей наименование
    verticalLine->setData(x1, y1);          // И устанавливаем координаты


    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(coordinateX,coordinateY);

    tracer = new QCPItemTracer(wGraphic);
    tracer->setGraph(wGraphic->graph(0));   // Трассировщик будет работать с графиком
    tracer->setStyle(QCPItemTracer::tsCircle);

    wGraphic->xAxis->setLabel("x");
    wGraphic->yAxis->setLabel("y");


    double max = *std::max_element(coordinateY.begin(),coordinateY.end());
    double min = *std::min_element(coordinateY.begin(),coordinateY.end());

    wGraphic->xAxis->setRange(0,coordinateX.size());
    wGraphic->yAxis->setRange(min,max);

    wGraphic->replot();
}

void cusplot::slotMousePress(QMouseEvent *event)
{
    double coordX = wGraphic->xAxis->pixelToCoord(event->pos().x());

    QVector<double> x(2), y(2);
    x[0] = coordX;
    y[0] = -50;
    x[1] = coordX;
    y[1] = 50;

    verticalLine->setData(x, y);

    tracer->setGraphKey(coordX);


    ui->lineEdit->setText("x: " + QString::number(tracer->position->key()) +
                          " y: " + QString::number(tracer->position->value()));
    wGraphic->replot();
}

void cusplot::slotMouseMove(QMouseEvent *event)
{

    if(QApplication::mouseButtons()) slotMousePress(event);
}
