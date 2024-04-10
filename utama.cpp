#include "utama.h"
#include "ui_utama.h"

utama::utama(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::utama)
{
    ui->setupUi(this);
    db.init_database("database_parkee");
    QByteArray ba;
    ba.resize(600);

    //cek input
//    for(int i=0; i<5; i++){
//        quint16 random_cek = QRandomGenerator::global()->generate();
//        db.insert_default_cek_in(QString("W%1GSR").arg(random_cek+i),ba,1,random_cek);
//    }

}

utama::~utama()
{
    delete ui;
}

