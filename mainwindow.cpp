#include "mainwindow.h"
#include "switch.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    QWidget* centralWidget = new QWidget(this);

    QGridLayout *mainLayout = new QGridLayout(centralWidget);

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
    connect(proxySwitch, &Switch::stateChanged, this, &MainWindow::toggleProxyHandler);

    QLabel* httpProxy = new QLabel();
    httpProxy->setText("HTTP Proxy");
    mHttpProxyEdit= new QLineEdit();
    mHttpProxyEdit->setText("127.0.0.1");
    mHttpProxyPortEdit= new QLineEdit();
    mHttpProxyPortEdit->setText("7890");

    QLabel* socksHost = new QLabel();
    socksHost->setText("Socks Host");
    mSocksHostEdit = new QLineEdit();
    mSocksHostEdit->setText("127.0.0.1");
    mSocksHostPortEdit= new QLineEdit();
    mSocksHostPortEdit->setText("7891");

    QLabel* ignoreHosts = new QLabel();
    ignoreHosts->setText("Ignore Hosts");
    mIgnoreHostsEdit = new QLineEdit();
    mIgnoreHostsEdit->setText("localhost, 127.0.0.0/8, ::1");

    mainLayout->addWidget(proxySwitch, 0, 0, 1, 2);

    mainLayout->addWidget(httpProxy, 1, 0, 1, 1);
    mainLayout->addWidget(mHttpProxyEdit, 1, 1, 1, 1);
    mainLayout->addWidget(mHttpProxyPortEdit, 1, 2, 1, 1);

    mainLayout->addWidget(socksHost, 2, 0, 1, 1);
    mainLayout->addWidget(mSocksHostEdit, 2, 1, 1, 1);
    mainLayout->addWidget(mSocksHostPortEdit, 2, 2, 1, 1);

    mainLayout->addWidget(ignoreHosts, 3, 0, 1, 1);
    mainLayout->addWidget(mIgnoreHostsEdit, 3, 1, 1, 2);

    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    //this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint, true);

    this->setGeometry(0, 0, 350, 300);
}

void MainWindow::toggleProxyHandler(int value)
{
    // gsettings list-schemas
    // gsettings list-recursively org.gnome.system.proxy

    QString program = "gsettings";

    QStringList proxyModeCMD;
    proxyModeCMD << "set" << "org.gnome.system.proxy" << "mode" << QString("'%1'").arg("manual");
    QStringList proxyModeAutoCMD;
    proxyModeAutoCMD << "set" << "org.gnome.system.proxy" << "mode" << QString("'%1'").arg("auto");

    QStringList proxyHttpHostCMD;
    proxyHttpHostCMD << "set" << "org.gnome.system.proxy.http" << "host" << QString("'%1'").arg(mHttpProxyEdit->text());
    QStringList proxyHttpHostPortCMD;
    proxyHttpHostPortCMD << "set" << "org.gnome.system.proxy.http" << "port" << QString("%1").arg(mHttpProxyPortEdit->text());

    QStringList proxySocksHostCMD;
    proxySocksHostCMD << "set" << "org.gnome.system.proxy.socks" << "host" << QString("'%1'").arg(mSocksHostEdit->text());
    QStringList proxySocksHostPortCMD;
    proxySocksHostPortCMD << "set" << "org.gnome.system.proxy.socks" << "port" << QString("%1").arg(mSocksHostPortEdit->text());


    QStringList ignoreHostsCMD;
    ignoreHostsCMD << "set" << "org.gnome.system.proxy" << "ignore-hosts" << QString("'%1'").arg(mSocksHostPortEdit->text());
    //QString ignoreHostsCMD = QStringLiteral("gsettings set org.gnome.system.proxy ignore-hosts %1 ").arg(mIgnoreHostsEdit->text());

    QProcess process;

    if (value == 2) {
        qDebug() << QProcess::startDetached(program, proxyModeCMD); //Starts execution of command

        qDebug() << QProcess::startDetached(program, proxyHttpHostCMD);
        qDebug() << QProcess::startDetached(program, proxyHttpHostPortCMD);
        qDebug() << QProcess::startDetached(program, proxySocksHostCMD);
        qDebug() << QProcess::startDetached(program, proxySocksHostPortCMD);

    } else if (value ==0) {
        QProcess::startDetached(program, proxyModeAutoCMD); //Starts execution of command
    }
}
