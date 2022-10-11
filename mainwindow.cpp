#include "mainwindow.h"
#include "switch.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowTitle("OverwatchX");

    QFont uniqueFont = QFont("Roboto medium", 10);
    this->setFont(uniqueFont);

    QWidget* centralWidget = new QWidget(this);
    QGridLayout *mainLayout = new QGridLayout(centralWidget);

    Switch* proxySwitch = new Switch("Proxy On/Off");
    proxySwitch->setFont(uniqueFont);
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

    QPushButton* copyShellCommand = new QPushButton();
    copyShellCommand->setText("Copy shell command");
    connect(copyShellCommand, &QPushButton::clicked, this, &MainWindow::copyShellCommandHandler);

    mainLayout->addWidget(proxySwitch, 0, 0, 1, 2);

    mainLayout->addWidget(httpProxy, 1, 0, 1, 1);
    mainLayout->addWidget(mHttpProxyEdit, 1, 1, 1, 1);
    mainLayout->addWidget(mHttpProxyPortEdit, 1, 2, 1, 1);

    mainLayout->addWidget(socksHost, 2, 0, 1, 1);
    mainLayout->addWidget(mSocksHostEdit, 2, 1, 1, 1);
    mainLayout->addWidget(mSocksHostPortEdit, 2, 2, 1, 1);

    mainLayout->addWidget(ignoreHosts, 3, 0, 1, 1);
    mainLayout->addWidget(mIgnoreHostsEdit, 3, 1, 1, 2);

    mainLayout->addWidget(copyShellCommand, 4, 0, 1, 3);

    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->setWindowFlags(Qt::WindowStaysOnTopHint
                         | Qt::WindowMinimizeButtonHint
                         //| Qt::WindowMaximizeButtonHint
                         | Qt::WindowCloseButtonHint);

    this->setGeometry(0, 0, 300, 250);
}

void MainWindow::toggleProxyHandler(int value)
{
    // gsettings list-schemas
    // gsettings list-recursively org.gnome.system.proxy

    QString program = "gsettings";

    QStringList proxyModeManualCMD;
    proxyModeManualCMD << "set" << "org.gnome.system.proxy" << "mode" << QString("'%1'").arg("manual");
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

    QStringList ignoreHostsList = mIgnoreHostsEdit->text().split(",");
    QStringList ignoreHostsListWithSingleQuote;
    foreach (QString h, ignoreHostsList)
    {
        ignoreHostsListWithSingleQuote.append(QString("'%1'").arg(h));
    }
    QStringList ignoreHostsCMD;
    ignoreHostsCMD << "set" << "org.gnome.system.proxy" << "ignore-hosts" << QString("[%1]").arg(ignoreHostsListWithSingleQuote.join(","));

    QProcess process;

    if (value == 2) {
        qDebug() << QProcess::startDetached(program, proxyModeManualCMD); //Starts execution of command

        qDebug() << QProcess::startDetached(program, proxyHttpHostCMD);
        qDebug() << QProcess::startDetached(program, proxyHttpHostPortCMD);
        qDebug() << QProcess::startDetached(program, proxySocksHostCMD);
        qDebug() << QProcess::startDetached(program, proxySocksHostPortCMD);
        qDebug() << QProcess::startDetached(program, ignoreHostsCMD);

    } else if (value ==0) {
        QProcess::startDetached(program, proxyModeAutoCMD); //Starts execution of command
    }
}

void MainWindow::copyShellCommandHandler()
{
    QString shellCommand = QString("export http_proxy=http://%1 all_proxy=sock5://%2 no_proxy='%3'")
                            .arg(mHttpProxyEdit->text()+":"+mHttpProxyPortEdit->text(),
                                 mSocksHostEdit->text()+":"+mSocksHostPortEdit->text(),
                                 mIgnoreHostsEdit->text());
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(shellCommand);
}
