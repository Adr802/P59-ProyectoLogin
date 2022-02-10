#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
     ui->InContra->setEchoMode(QLineEdit::Password);
}

Principal::~Principal()
{
    delete ui;
}


void Principal::on_btnVerificar_released()
{
    bool op = false;
    QTextStream io;
    QFile archivo;
    archivo.setFileName(QDir::homePath()+"/Documents/USERS.csv");

    archivo.open(QIODevice::ReadOnly|QIODevice::Text);
    if (archivo.isOpen()){
        io.setDevice(&archivo);
        while(!io.atEnd()){
            auto linea = io.readLine();
            auto texto=linea.split(";");

            if (ui->inUsuario->text() == texto[0]&& ui->InContra->text()==decifrado(texto[1])){
                op = true;
                break;
            }

        }
        archivo.close();

    }
    else {
        QMessageBox::critical(this,tr("Error"),tr("No se pudo abrir el archivo con los datos"));
    }
    if (op){
        QString nom = ui->inUsuario->text();
        Dialog p;
        p.setNombre(nom);
        p.exec();


    }
    else {
        QMessageBox::critical(this,tr("Error"),tr("Usuario o contraseña incorrecta"));
    }
}

QString Principal::decifrado(QString contra)
{
    string part=contra.toStdString();

        for(int i=0;i<contra.length();i++){
            if(part[i]==65){
                part[i]=90;
            }
            else if(part[i]==97){
                part[i]=122;
            }
            else{
                part[i]=part[i]-1;
            }
        }
        contra=QString::fromStdString(part);
        return contra;
}

