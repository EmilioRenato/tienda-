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
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar archivo",
                                                         QDir::home().absolutePath(),
                                                         "Archivos de salarios (*.slr)");
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

