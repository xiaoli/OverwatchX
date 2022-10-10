#include "mainwindow.h"
#include "switch.h"

#include <QWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    QWidget* centralWidget = new QWidget(this);

    //QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    QFormLayout *mainLayout = new QFormLayout(centralWidget);

    // Examples
    /*Switch* switch1 = new Switch("SWITCH");
    mainLayout.addWidget(switch1);
    Switch* switch2 = new Switch("SWITCH");
    mainLayout.addWidget(switch2);
    switch2->setDisabled(true);
    Switch* switch3 = new Switch("SWITCH");
    mainLayout.addWidget(switch3);
    switch3->setLayoutDirection(Qt::RightToLeft);
    Switch* switch4 = new Switch("SWITCH");
    mainLayout.addWidget(switch4);
    switch4->setLayoutDirection(Qt::RightToLeft);
    switch4->setChecked(true);
    switch4->setDisabled(true);

    QButtonGroup bg;
    Switch* item1 = new Switch("ITEM1");
    Switch* item2 = new Switch("ITEM2");
    bg.addButton(item1);
    bg.addButton(item2);
    mainLayout.addWidget(item1);
    mainLayout.addWidget(item2);
    mainLayout.setSpacing(100);*/

    Switch* proxySwitch = new Switch("On/Off");
    proxySwitch->setLayoutDirection(Qt::RightToLeft);

    QLabel* httpProxy = new QLabel();
    httpProxy->setText("HTTP Proxy");
    QLineEdit* httpProxyEdit= new QLineEdit();
    httpProxyEdit->setText("127.0.0.1:7890");

    QLabel* socksHost = new QLabel();
    socksHost->setText("Socks Host");
    QLineEdit* socksHostEdit = new QLineEdit();
    socksHostEdit->setText("127.0.0.1:7891");

    QLabel* ignoreHosts = new QLabel();
    ignoreHosts->setText("Ignore Hosts");
    QLineEdit* ignoreHostsEdit = new QLineEdit();
    ignoreHostsEdit->setText("localhost, 127.0.0.0/8, ::1");

    mainLayout->addRow(proxySwitch);
    mainLayout->addRow(httpProxy, httpProxyEdit);
    mainLayout->addRow(socksHost, socksHostEdit);
    mainLayout->addRow(ignoreHosts, ignoreHostsEdit);

    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    //this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint, true);

    this->setGeometry(0, 0, 350, 400);
}
