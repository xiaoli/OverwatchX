#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlineedit.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void toggleProxyHandler(int);
    void copyShellCommandHandler();

    QLineEdit* mHttpProxyEdit;
    QLineEdit* mHttpProxyPortEdit;
    QLineEdit* mSocksHostEdit;
    QLineEdit* mSocksHostPortEdit;
    QLineEdit* mIgnoreHostsEdit;

    QLineEdit* mClashConfigURIEdit;

signals:

};

#endif // MAINWINDOW_H
