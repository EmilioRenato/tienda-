#include "principal.h"
#include "ui_principal.h"

#include <QDebug>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Lista de productos
    m_productos.append(new Producto(1,"Leche",0.85));
    m_productos.append(new Producto(2,"Pan",0.15));
    m_productos.append(new Producto(3,"Queso",2.00));
    m_productos.append(new Producto(4,"ositos de goma",1.50));
    // Mostrar la lista en la ventana
    for (int i = 0; i < m_productos.size(); ++i) {
        ui->inProducto->addItem(m_productos.at(i)->nombre());
    }
    // Colocar cabecera de la tabla
    QStringList cabecera = {"Cantidad", "Producto", "Subtotal"};
    ui->outDetalle->setColumnCount(3);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    // Inicializar subtotal global
    m_subtotal = 0;
    m_total=0;
    m_iva=0;
    m_direccion ="";
    m_telefono="";
    m_nombre="";
    m_correo="";
    m_cedula="";
    m_detalles="";
}

Principal::~Principal()
{
    delete ui;
}

bool Principal::validarCedula()
{
    long long int numero;
    bool ok;
    char cedula1[11]={};
    bool t=true;

    m_cedula = ui->inCedula->text();
    numero=m_cedula.toInt(&ok);
    enteroAchar(numero,cedula1);

    for(int i=0; i<11;i++){
        if (cedula1[i] == '\n')
            cedula1[i] = '\0';
    }
    int v[10], num, limite;
    limite = strlen(cedula1);
    if (limite != 10)
        t=false;
    if (limite == 10){
        for (int i=0;i<10;i++){
            num = cedula1[i]-48;
            v[i] = num; }

        //VALIDACION CEDULA PROCESO

        int vec[10], suma, ultimo, ultimon;
        if (v[0] == 1 || v[0] == 2){
            if (v[2] > 0 && v[2] < 6 ){
                for (int i=0; i<9; i+=2){
                    vec[i] = v[i] *2;
                    if (vec[i] >= 10)
                        vec[i] -= 9;
                }
                for (int i=1; i<9; i+=2){
                    vec[i] = v[i];
                }
                suma= 0;
                for(int i=0; i<10; i++){
                    suma = suma + vec[i];
                }
                if (suma == 10)
                    ultimo = 0;
                else if(suma >10 && suma<20)
                    ultimo = 20;
                else if (suma >20 && suma<30)
                    ultimo = 30;
                else if (suma >30 && suma<40)
                    ultimo = 40;
                else t=false;
                ultimon = ultimo - suma;

                if (ultimon == v[9])
                    t=true;
                else
                    t=false;
            }

            else
                t=false;
        }
    }
    return t;
}



void Principal::on_cmdAgregar_released()
{
    QString str="";
    // Validar que no se agregen productos con 0 cantidad
    int cantidad = ui->inCantidad->value();
    if (cantidad == 0){
        return ;
    }
    // Obtener datos de la GUI
    int index = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(index);


    // Calcular el subtotal del producto
    float subtotal = cantidad * p->precio();

    // Agregar datos a la tabla
    int fila = ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(fila);
    ui->outDetalle->setItem(fila,0,new QTableWidgetItem(QString::number(cantidad)));

    ui->outDetalle->setItem(fila,1,new QTableWidgetItem(p->nombre()));

    ui->outDetalle->setItem(fila,2,new QTableWidgetItem(QString::number(subtotal,'f',2)));


    str=str+ QString::number(cantidad)+" "+p->nombre()+" "+QString::number(subtotal,'f',2)+" ";
    // Limpiar datos
    setDetalles(str);
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();
    calcular(subtotal);



}

void Principal::on_inProducto_currentIndexChanged(int index)
{
    // Obtener el precio del producto
    float precio = m_productos.at(index)->precio();
    // Mostrar el precio
    ui->outPrecio->setText("$ " + QString::number(precio,'f',2));
}

void Principal::calcular(float stProducto)
{
    m_subtotal += stProducto;
    m_iva = m_subtotal * IVA / 100;
    m_total = m_subtotal + m_iva;

    ui->outSubtotal->setText(QString::number(m_subtotal,'f',2));
    ui->outIva->setText(QString::number(m_iva,'f',2));
    ui->outTotal->setText(QString::number(m_total,'f',2));


}

void Principal::enteroAchar(int n, char cad[])
{
    int nroDig =0;
    int aux=n;
    while (aux>0){
        aux=aux/10;
        nroDig++;
    }
    cad[nroDig]='\0';
    aux = n;
    int pos= nroDig-1,dig;
    while(pos>=0){

        dig=aux%10;
        aux=aux/10;
        cad[pos]= dig + '0';
        pos--;
    }
}

QString Principal::datos2String()
{
    QString s,t,i;
    t.setNum(m_total);
    i.setNum(m_iva);
    s.setNum(m_subtotal);
    QDateTime time = QDateTime::currentDateTime();
    time.toString();

    QString str = "Nombre: "+m_nombre+ "\n" +"Cedula: "+m_cedula+"\n"+"Detalles de compra: "+m_detalles+"\n"+
            "Telefono: "+m_telefono +"\n"+ "Direccion: "+m_direccion+"\n"+"Correo: "
                  + m_correo+"\n"+"Subtotal: "+s+"\n"+"Iva: "+i+"\n"+"Total: "+t +"\n"+"Fecha: "+ time.toString();
    return str;
}

QString Principal::datos2StringConsFin()
{
    QString s,t,i;
    t.setNum(m_total);
    i.setNum(m_iva);
    s.setNum(m_subtotal);
    QDateTime time = QDateTime::currentDateTime();
    time.toString();
    m_nombre="9999999999999";
    m_telefono="9999999999999";
    m_correo="9999999999999";
    m_cedula="9999999999999";
    m_direccion="999999999999";

    QString str = "Nombre: "+m_nombre+ "\n" +"Cedula: "+m_cedula+"\n"+"Detalles de compra: "+m_detalles+"\n"+
            "Telefono: "+m_telefono +"\n"+ "Direccion: "+m_direccion+"\n"+"Correo: "
                  + m_correo+"\n"+"Subtotal: "+s+"\n"+"Iva: "+i+"\n"+"Total: "+t +"\n"+"Fecha: "+ time.toString();
    return str;
}


void Principal::on_btnFacturacion_clicked()
{

    m_nombre=ui->inNombre->text();
    m_correo=ui->inEmail->text();
    m_telefono=ui->inTelefono->text();
    m_direccion=ui->inDireccion->toPlainText();
    ui->statusbar->showMessage("Realizando la factura " , 5000);
    if (validarCedula()==true and m_nombre !="" && m_correo !="" && m_telefono!="" && m_direccion!=""){
        // Crear un objeto de la ventana que queremos invocar
        facturacion *factura = new facturacion(this);

        factura->mostrar(datos2String());



        factura->exec();
    }else {
        QMessageBox::warning(this,"Advertencia","Datos incorrectos intete de nuevo");
        return;
    }

}

const QString &Principal::detalles() const
{
    return m_detalles;
}

void Principal::setDetalles(const QString &newDetalles)
{
    m_detalles = newDetalles;
}

float Principal::iva() const
{
    return m_iva;
}

void Principal::setIva(float newIva)
{
    m_iva = newIva;
}

float Principal::total() const
{
    return m_total;
}

void Principal::setTotal(float newTotal)
{
    m_total = newTotal;
}

float Principal::subtotal() const
{
    return m_subtotal;
}

void Principal::setSubtotal(float newSubtotal)
{
    m_subtotal = newSubtotal;
}

const QList<Producto *> &Principal::productos() const
{
    return m_productos;
}

void Principal::setProductos(const QList<Producto *> &newProductos)
{
    m_productos = newProductos;
}




void Principal::on_btn_consFinal_clicked()
{
    ui->statusbar->showMessage("Realizando la factura " , 5000);

        facturacion *factura = new facturacion(this);

        factura->mostrar(datos2StringConsFin());
        factura->exec();

}

