#include "switcher.h"
#include "ui_switcher.h"
#include "cusplot.h"
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>

switcher::switcher(QWidget *parent) :   QMainWindow(parent),    ui(new Ui::switcher)
{
    ui->setupUi(this);
    //ui->tabWidget->addTab(new cusplot,QString("Protocol"));

}

switcher::~switcher()
{
    delete ui;
}

void switcher::on_create_clicked()
{
    QPainter painter(this);

    QString targer_aleft,targer_atop,targer_awidth,targer_aheigth;
    QString source_bleft,source_btop,source_bwidth,source_bheigth;

    targer_aleft = ui->targer_aleft->text();
    targer_atop = ui->targer_atop->text();
    targer_awidth = ui->targer_awidth->text();
    targer_aheigth = ui->targer_aheigth->text();

    source_bleft = ui->source_bleft->text();
    source_btop = ui->source_btop->text();
    source_bwidth = ui->source_bwidth->text();
    source_bheigth = ui->source_bheigth->text();

    qreal t_aleft = targer_aleft.toDouble();
    qreal t_atop = targer_atop.toDouble();
    qreal t_awidth = targer_awidth.toDouble();
    qreal t_aheigth = targer_aheigth.toDouble();

    qreal s_bleft = source_bleft.toDouble();
    qreal s_btop = source_btop.toDouble();
    qreal s_bwidth = source_bwidth.toDouble();
    qreal s_bheigth = source_bheigth.toDouble();

    QRectF target(t_aleft, t_atop, t_awidth, t_aheigth);
    QRectF source(s_bleft, s_btop, s_bwidth, s_bheigth);

    QImage image("C:/Users/Elias/Desktop/projects/cusplot(stable build)/images/sin_1.png");

    QRect rec(100,150,250,25);
    painter.drawText(rec,"Hello world");
    painter.drawImage(target,image,source);
    painter.drawRect(target);
    painter.drawRect(source);
}
