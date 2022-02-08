#ifndef FACTURACION_H
#define FACTURACION_H
#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "principal.h"
#include <QTime>

namespace Ui {
class facturacion;
}

class facturacion : public QDialog
{
    Q_OBJECT

public:
    explicit facturacion(QWidget *parent = nullptr);
    ~facturacion();

    int valor() const;
    void mostrar(QString datos);


private slots:
    void on_btn_guardar_clicked();

private:
    Ui::facturacion *ui;
    QString m_version;
    int m_valor;

    QString fecha();

    QString m_nombre2;
    QString m_cedula2;
    QString m_direccion2;
    QString m_correo2;
    QString m_telefono2;


};

#endif // FACTURACION_H
