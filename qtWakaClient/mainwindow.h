#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qtipv4ud.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void pb1();
    void pb2();
    void pb3();
    void time1sec();
    void onUdsReceive(const QByteArray ba);

private:
    Ui::MainWindow *ui;
    QtIpV4Ud qudp;
    QTimer   *timer1sec;
};
#endif // MAINWINDOW_H
