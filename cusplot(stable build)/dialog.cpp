#include "dialog.h"
#include "ui_dialog.h"
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_create_clicked()
{
    QPdfWriter pdf("C:/Users/Elias/Desktop/projects/cusplot(stable build)/Protocols/protocol.pdf");
    QPainter painter(&pdf);

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
    QRectF target2(4300, 1000, 3300, 2300);
    QRectF source(s_bleft, s_btop, s_bwidth, s_bheigth);

    QImage image("C:/Users/Elias/Desktop/projects/cusplot(stable build)/images/sin_1.png");
    QImage image2("C:/Users/Elias/Desktop/projects/cusplot(stable build)/images/sin_1.png");

    painter.drawImage(target,image,source);
    painter.drawImage(target2,image2,source);

}
