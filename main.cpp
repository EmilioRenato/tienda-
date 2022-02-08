#include "principal.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTranslator traducion;
    // Solicitando al usuario que seleccione un idioma
    QString idiomas = QLocale::system().name();
//    idiomas << "Ingles" <<  "Español"<<"Frances"<<"Japones";
//    QString idiomaSeleccionado = QInputDialog::getItem(NULL,
//                               "Idioma",
//                               "Seleccione un idioma",
    //                               idiomas);


    int idiom=idiomas.indexOf('_');
    idiomas=idiomas.mid(0,idiom);

    // Dependiendo del idioma seleccionado, carga el archivo de rtaducción
    if (idiomas == "en"){
        traducion.load(":/tienda_en.qm");

    }
    if (idiomas == "fr"){
        traducion.load(":/tienda_fr.qm");

    }
    if (idiomas == "ja"){
        traducion.load(":/tienda_jp.qm");

    }
    // Si es diferente de español, se instala la traducción en TODA la aplicación
    if (idiomas != "es"){
        a.installTranslator(&traducion);
    }



    Principal w;
    w.show();
    return a.exec();
}
