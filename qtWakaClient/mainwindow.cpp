#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>

extern "C" int main_wakaama(int argc, char *argv[]);

QtIpV4Ud *g_qudp = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer1sec = new QTimer(this);

    connect(ui->pb1,SIGNAL(clicked()),this,SLOT(pb1()));
    connect(ui->pb2,SIGNAL(clicked()),this,SLOT(pb2()));
    connect(ui->pb3,SIGNAL(clicked()),this,SLOT(pb3()));

    connect(timer1sec,SIGNAL(timeout()),this,SLOT(time1sec()));
    timer1sec->start(1000);

}

MainWindow::~MainWindow()
{
    timer1sec->stop();
    delete timer1sec;
    delete ui;
}

extern "C" void xxx_onUdsReceive(uint8_t *b, int len);  // can't include other
extern "C" void lwm2m_PollNow(void);


void MainWindow::onUdsReceive(const QByteArray ba)
{
    qDebug() << " XXXX onUdsReceive len: " << ba.size();
    uint8_t *b = (uint8_t *)ba.data();
    int len = ba.size();
    xxx_onUdsReceive(b, len);

    lwm2m_PollNow();
  // !!!???  conn_s_updateRxStatistic(objArray[7], numBytes, false);

}

extern "C" {
#include "../examples/client/lwm2mclient.h"

extern MY_TYPE g_LwM2M;
}

void MainWindow::pb1()
{
    myClientInit();
    qDebug() << " XXXX PB1";

    connect(&qudp,SIGNAL( onReceive(const QByteArray)    ),this,SLOT( onUdsReceive(const QByteArray) ));

  //  qudp.doConnect("192.168.43.200",5683);  // no coaps BS !
    uint32_t port = atoi(g_LwM2M.serverPort);
    qudp.doConnect(g_LwM2M.server,port);  // coaps !
    qDebug() << " XXXX PB1 udp connected" << g_LwM2M.server << " "<< g_LwM2M.serverPort;
    g_qudp = &qudp;
}

void MainWindow::pb2()
{
    qDebug() << " XXXX PB2";

   // qudp.sendUDPhex("0002");

    main_wakaama(0,NULL);

}

void MainWindow::pb3()
{
    qDebug() << " XXXX PB3";
    qudp.doDisconnect();
}

extern "C" void lwm2m_PollNow(void);

extern "C" int Xsendto(int sockfd, const void *buf, size_t len, int flags ) {
    printf("XXXXX2\r\n");



    g_qudp->sendUDP((const char *)buf,len);
 //   xxxx(data.lwm2mH); // check timeout

    return len;
}

extern "C" void lwm2m_oneSec(void);

void MainWindow::time1sec()
{
 //   qDebug() << "MainWindow::time1sec";
    lwm2m_oneSec();
}

extern "C" void log_handler(int level, const char *message)
{
    fprintf( stderr, "%d %s", level, message);
    // for DTLS logging
   // qDebug() << "log_handler: " << message;

}

extern "C" long clock_time() {
    return 42;
}
