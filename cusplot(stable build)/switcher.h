#ifndef SWITCHER_H
#define SWITCHER_H

#include <QMainWindow>

namespace Ui {
class switcher;
}

class switcher : public QMainWindow
{
    Q_OBJECT

public:
    explicit switcher(QWidget *parent = nullptr);
    ~switcher();

private slots:
    void on_create_clicked();

private:
    Ui::switcher *ui;
};

#endif // SWITCHER_H
