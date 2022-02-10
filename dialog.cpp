#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->inNombre->setFocus();
    ui->imagen->resize(alto+180,ancho+20);
    pixmap = QPixmap(ui->imagen->size());
    iniciar(ancho,10);
    ejes(iniciox, inicioy, 2,ancho,alto,Qt::black);
    ui->imagen->setPixmap(pixmap);

}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::iniciar(int ancho, int alto)
{
    pixmap.fill(Qt::white);
    painter.begin(&pixmap);
    pen.setColor(Qt::red);
    texto((ancho/2), alto+5, tr(" GRAFICO DE NOTAS"), 15);
}

void Dialog::texto(int x, int y, QString texto, int tamanio)
{
    painter.setPen(pen);
    QFont font = painter.font();
    font.setPixelSize(tamanio);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(x,y,texto);
}

void Dialog::ejes(int iniciox, int inicioy, int grosor, int ancho, int alto, QColor color)
{
    pen.setWidth(grosor);
    pen.setColor(color);//Qt::red
    pen.setJoinStyle(Qt::MiterJoin);
    painter.setPen(pen);
    painter.drawLine(iniciox,inicioy-30,iniciox,alto);
    texto(iniciox-12, 20, "Y", 16);
    painter.drawLine(iniciox,alto,ancho+90,alto);
    texto(ancho+100, alto+10, "X", 16);
    painter.drawLine(iniciox-3,alto/2,12,alto/2);
    pen.setColor(Qt::black);
    texto(0, alto/2, "50", 9);
}

void Dialog::barra(int desplazamiento, int iniciox, int inicioy, int alto, int notaf, QString nombre)
{
    if (notaf>69){
        painter.setBrush(Qt::green);
    }else if(notaf>49 && notaf<70){
        painter.setBrush(Qt::yellow);
    }else{
        painter.setBrush(Qt::red);

    }
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    if (notaf==0)
        inicioy=alto;
    else
        if (notaf==50)
            inicioy=(alto/2);
        else
            inicioy= alto -((alto*notaf)/100)+15;
    texto(iniciox+20+desplazamiento, inicioy-2, nombre, 10);
    texto(iniciox+30+desplazamiento, inicioy-10, QString::number(notaf), 10);
    painter.drawRect(iniciox+20+desplazamiento, inicioy, 20,alto - inicioy);
}

void Dialog::lineaPromedio(int iniciox, int alto, int notaPromedio)
{
    painter.setBrush(Qt::green);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    int valor;
    if (notaPromedio==0)
        valor=0;
    else
        if (notaPromedio==50)
            valor=-(alto/2);
        else
            valor= alto -((alto*notaPromedio)/100)+15;
    painter.drawRect(iniciox+10, valor ,ancho+60,1);
    texto(iniciox+10, valor+10 ,QString::number(notaPromedio), 10);
    ui->imagen->setPixmap(pixmap);
}

void Dialog::setNombre(const QString &newNombre)
{
    m_Nombre = newNombre;
    ui->outNombre->setText(m_Nombre);
}

void Dialog::on_btnIngresar_released()
{

    if(ui->inNota->value() == 0 or ui->inNombre->text().isEmpty()){
        return;
    }

    if(m_numeroNotas <= 10){
        QString vnombre;
        vnombre = ui->inNombre->text();
        QStringList p = vnombre.split(" ");
        QString fiName = ui->inNombre->text();
        if(p.size() == 2){
            fiName = p[0].at(0);
            fiName += ". " + p[1];
        }else if(p.size()==1){
            fiName = p[0];
        }

        int vnotaf;
        vnotaf = ui->inNota->value();
        //tamanio
        barra(vi1,iniciox, inicioy,alto,vnotaf,fiName);
        vi1=vi1+45;
        m_numeroNotas++;

        m_acumulaNota += vnotaf;

        ui->inNombre->clear();
        ui->inNota->setValue(0);


        ui->imagen->setPixmap(pixmap);
    }else{
        QMessageBox::warning(this,tr("Advertencia"),tr("Llego al maximo de notas ingresadas(10)"));
    }

}


void Dialog::on_btnLimpiar_released()
{

    iniciar(ancho,10);
    ejes(iniciox,inicioy,2,ancho,alto,Qt::blue);
    ui->imagen->setPixmap(pixmap);
    m_acumulaNota=0;
    vi1=0;
    m_numeroNotas=0;

}

void Dialog::on_btnGuardar_released()
{
    QString imagen;
    imagen=QFileDialog::getSaveFileName(this,tr("Guardar"),QString(),tr("Imagen(*.png"));
    if(!imagen.isEmpty()){
        if(pixmap.save(imagen)){
            QMessageBox::information(this,tr("Guardado"),tr("Archivo almacenado")+imagen);
        }else{
            QMessageBox::warning(this,tr("Error"),tr("No se pudo guardar"));
        }
    }
}


void Dialog::on_btnPromedio_released()
{
    if(m_numeroNotas>0){
        lineaPromedio(iniciox,alto,(m_acumulaNota/m_numeroNotas));
    }
}

