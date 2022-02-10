#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
//se define librerías graficas
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItem>
#include <QTextStream>
#include <QDebug>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);

    ~Dialog();
    //variables de control
    int ancho=420;
    int alto=420;
    int iniciox=20;
    int inicioy=40;


    void iniciar(int ancho,int alto);
    void texto(int x, int y, QString texto, int tamanio);
    void ejes(int iniciox,int inicioy, int grosor, int ancho, int alto, QColor color);
    void barra(int desplazamiento,int iniciox, int inicioy, int alto, int notaf, QString nombre);
    void lineaPromedio(int iniciox, int alto, int notaPromedio);
    void setNombre(const QString &newNombre);

private slots:
    void on_btnIngresar_released();

    void on_btnLimpiar_released();

    void on_btnGuardar_released();

    void on_btnPromedio_released();

private:
    Ui::Dialog *ui;
    QPixmap pixmap;
    QPen pen;
    QPainter painter;
    QString m_Nombre;
    int m_acumulaNota=0;
    int vi1=0;
    int m_numeroNotas=0;

};

#endif // DIALOG_H
