#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

#include "dialog.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

private slots:


    void on_btnVerificar_released();

private:
    Ui::Principal *ui;
    QString decifrado(QString contra);

};
#endif // PRINCIPAL_H
