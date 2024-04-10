#include "utama.h"
#include "ui_utama.h"

utama::utama(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::utama)
{
    ui->setupUi(this);
    db.init_database("database_parkee");
    durasi_parkir ="";
    harga_total= "Rp. 0,00";
    counter_bayar=0;
    price_last=0;
    ui->button_pay->setText("Generate");

}

utama::~utama()
{
    delete ui;
}

void utama::keyPressEvent(QKeyEvent *e)
{
    if(this->ui->tabWidget->currentIndex()==0){
        switch(e->key()){
            case Qt::Key_F5:
                this->setWindowTitle("Refresh window");
                this->ui->line_platnomor_in->clear();
                this->show();
                break;
            case Qt::Key_F7:
                this->setWindowTitle("Insert Vehicle plate");
                this->ui->line_platnomor_in->setFocus();
                //this->show();
                break;
            case Qt::Key_F8:
                this->setWindowTitle("select jenis kendaraan");
                this->show();
                break;
            case Qt::Key_Space:
                this->setWindowTitle("Cetak Tiket");
                this->ui->button_ticket->click();
                this->show();
                break;
            case Qt::Key_Enter:
                this->setWindowTitle("Show");
                //this->ui->button_ticket->click();
                this->show();
                break;
        }
    }
    else{
        switch(e->key()){
            case Qt::Key_F5:
                this->setWindowTitle("Refresh window checkout");
                this->ui->line_platnomor_in_3->clear();
                this->ui->line_codevo->clear();
                this->ui->line_no_parking->clear();
                this->show();
                break;
            case Qt::Key_F6:
                this->setWindowTitle("Nomor plat");
                this->show();
                break;
            case Qt::Key_F7:
                this->setWindowTitle("Nomor slip parkir");
                this->show();
                break;
            case Qt::Key_F8:
                this->setWindowTitle("Jenis Kendaraan");
                this->show();
                break;
            case Qt::Key_F9:
                this->setWindowTitle("Metode Pembayaran");
                this->show();
                break;
            case Qt::Key_Space:
                this->setWindowTitle("Bayar Finish");

                //this->show();
                break;
        }

    }

}

QString utama::secondsToString(qint64 seconds, int *hari,int *jam, int *menit, int *detik)
{
  const qint64 DAY = 86400;
  qint64 days = seconds / DAY;
  QTime t = QTime(0,0).addSecs(seconds % DAY);
  *hari = days;
  *jam = t.hour();
  *menit = t.minute();
  *detik = t.second();
  return QString("%1 days, %2 hours, %3 minutes, %4 seconds")
    .arg(days).arg(t.hour()).arg(t.minute()).arg(t.second());

}

int utama::kalkulasi_harga(int harga_perjam, int hari, int jam, int menit, int detik)
{
    int harga=0;
    int pengali=0;

    pengali+= (hari*24);
    pengali+= (jam*1);
    if(menit>0)pengali+= 1;
    harga = pengali*harga_perjam;

    return harga;
}

void utama::gen_tampung()
{
//    QByteArray ba;
//    ba.resize(600);
//    QDateTime waktu_cek;

//    int info_plat_ada = db.cek_in_avaliablelity(0, "W39370GSR",&waktu_cek);
//    if(info_plat_ada)qDebug()<<"plat nomor sama, tidak dapat masuk";
//    else qDebug()<<"plat sudah dicek silahkan masuk!";

//    //cek input
////    for(int i=0; i<5; i++){
////        quint16 random_cek = QRandomGenerator::global()->generate();
////        db.insert_default_cek_in(QString("W%1GSR").arg(random_cek+i),ba,1,random_cek);
////    }

//    QDateTime waktu_now = QDateTime::currentDateTime();

//    int id_cek_in = db.cek_in_avaliablelity(0, "W39370GSR",&waktu_cek);

//    //calculation date parking
//    int hari;
//    int jam;
//    int menit;
//    int detik;
//   qDebug()<<secondsToString(waktu_cek.secsTo(waktu_now),&hari,&jam, &menit, &detik);
//   qDebug()<<hari<<jam<< menit<< detik;
//   qDebug()<<"harga:"<<kalkulasi_harga( 3000, hari, jam, menit, detik);
//    int price=kalkulasi_harga( 3000, hari, jam, menit, detik);

//   //masukkan data
//   int sukses_kah = db.insert_default_cek_out(id_cek_in, ba, ba, waktu_now, price);
//   qDebug()<<"cek sukses cek out:"<<sukses_kah;
}


void utama::on_button_ticket_clicked()
{

    QString plat_nomor = this->ui->line_platnomor_in->text();
    int jenis_kendaraannya = this->ui->combo_kendaraan1->currentIndex();

    QByteArray foto; //perumpamaan fotonya agar bisa dicompress
    foto.resize(600);

    int random=0;
    QDateTime waktu_cek;

    int info_plat_ada  = db.cek_in_avaliablelity(jenis_kendaraannya, plat_nomor,&waktu_cek,&random);
    if(info_plat_ada){
        qDebug()<<"plat nomor sama, tidak dapat masuk "<<info_plat_ada;
        QMessageBox box;
        box.setText(QString("Plat Nomor %1 ").arg(plat_nomor)+" Masih Terdaftar");
        box.exec();
    }
    else {
        qDebug()<<"plat sudah dicek silahkan masuk!";

        //cek input
    //    for(int i=0; i<5; i++){
    //        quint16 random_cek = QRandomGenerator::global()->generate();
    //        db.insert_default_cek_in(QString("W%1GSR").arg(random_cek+i),ba,1,random_cek);
    //    }

        quint16 random_cek = QRandomGenerator::global()->generate();
        db.insert_default_cek_in(plat_nomor,foto,jenis_kendaraannya,random_cek);

        qDebug()<<"print tiketttt "<< plat_nomor<< random_cek;
         QDateTime waktu_now = QDateTime::currentDateTime();
        ui->tanggal1->setText(waktu_now.toString());
         QMessageBox box;
         box.setText(QString("Tiket %1 ").arg(plat_nomor)+" Berhasil dicetak");
         box.exec();
    }

}


void utama::on_button_pay_clicked()
{
    QDateTime waktu_now = QDateTime::currentDateTime();
    ui->Tanggal2->setText(waktu_now.toString());
    QString plat_nomor = this->ui->line_platnomor_in_3->text();
    int jenis_kendaraannya = this->ui->combo_kendaraan2->currentIndex();
    QDateTime waktu_cek;
    int no_parkir;
    QByteArray foto; //perumpamaan fotonya agar bisa dicompress
    foto.resize(600);

    int id_cek_in = db.cek_in_avaliablelity(jenis_kendaraannya, plat_nomor,&waktu_cek,&no_parkir);

    //calculation date parking
    int hari;
    int jam;
    int menit;
    int detik;
   durasi_parkir = secondsToString(waktu_cek.secsTo(waktu_now),&hari,&jam, &menit, &detik);
   qDebug()<<hari<<jam<< menit<< detik;
   qDebug()<<"harga:"<<kalkulasi_harga( harga_3000an, hari, jam, menit, detik);
    int price=kalkulasi_harga( harga_3000an, hari, jam, menit, detik);
    harga_total = "Rp. ";
    harga_total+= QString(QString::number(price));
    harga_total+= ",00";

    this->ui->durasi_parkir->setText(durasi_parkir);
    this->ui->harga_total->setText(harga_total);
    this->ui->line_no_parking->setText(QString(QString::number(no_parkir)));
    counter_bayar+=1;
    waktu_now_last = waktu_now;
    price_last = price;
    ui->button_pay->setText("Pay for Rp. "+QString(QString::number(price))+",00");
    if(counter_bayar==2){
       //masukkan data
       int sukses_kah = db.insert_default_cek_out(id_cek_in, foto, foto, waktu_now_last, price_last);
       qDebug()<<"cek sukses cek out:"<<sukses_kah;
       if(sukses_kah){qDebug()<<"harganya: "<<price;
           counter_bayar=0;
           price_last=0;
           ui->button_pay->setText("Done");
           QMessageBox box;
           box.setText(QString("Pembayaran %1 ").arg(plat_nomor)+" Berhasil");
           db.was_cek_out(id_cek_in);
           box.exec();
       }
       else{
           QMessageBox box;
           box.setText(QString("Pembayaran %1 ").arg(plat_nomor)+" GAGAL");
            box.exec();
       }
    }
}

