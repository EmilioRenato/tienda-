#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include "producto.h"
#include "facturacion.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <QTime>
using namespace std;

#define IVA 12
#define VERSION "1.0"

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();
    bool validarCedula();
    bool extraer(char b[]);
    void borrar(char a[]);
    void obtenerDatos();

    const QList<Producto *> &productos() const;
    void setProductos(const QList<Producto *> &newProductos);


    float subtotal() const;
    void setSubtotal(float newSubtotal);

    float iva() const;
    void setIva(float newIva);
    float total() const;
    void setTotal(float newTotal);

    const QString &detalles() const;
    void setDetalles(const QString &newDetalles);

private slots:
    void on_cmdAgregar_released();

    void on_inProducto_currentIndexChanged(int index);

    void on_btnFacturacion_clicked();


    void on_btn_consFinal_clicked();

private:
    Ui::Principal *ui;
    QList<Producto*> m_productos;

    QString m_nombre;
    QString m_direccion;
    QString m_correo;
    QString m_telefono;
    QString m_cedula;
    QString m_detalles;

    float m_iva;
    float m_total;
    float m_subtotal;
    void calcular(float stProducto);
    void enteroAchar(int n,char cad[]);
    QString datos2String();
    QString datos2StringConsFin();



};
#endif // PRINCIPAL_H
