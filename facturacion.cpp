#include "facturacion.h"
#include "ui_facturacion.h"

facturacion::facturacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::facturacion)
{
    ui->setupUi(this);
}

facturacion::~facturacion()
{
    delete ui;
}

int facturacion::valor() const
{
    return m_valor;
}

void facturacion::mostrar(QString datos)
{
    this->ui->outFactura->appendPlainText(datos);
}


void facturacion::on_btn_guardar_clicked()
{
    QDateTime time = QDateTime::currentDateTime();
    time.toString();
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         QDir::home().absolutePath()
                                                         ,fecha(),
                                                         "Archivos de Facturas (*.slr)");


    QFile archivo(nombreArchivo);
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream salida(&archivo);
        salida << ui->outFactura->toPlainText();



    }else {
        QMessageBox::warning(this,
                             "Guardar datos",
                             "No se pudo guardar el archivo");
    }
    archivo.close();

}

QString facturacion::fecha()
{
    QDateTime time = QDateTime::currentDateTime();

    QString str=  time.toString();
    return str;

}

