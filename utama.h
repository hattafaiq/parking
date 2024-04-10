#ifndef UTAMA_H
#define UTAMA_H

#include <QMainWindow>
#include "controller/database_cntrl.h"
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QMessageBox>

#define harga_3000an 3000

QT_BEGIN_NAMESPACE
namespace Ui { class utama; }
QT_END_NAMESPACE

class utama : public QMainWindow
{
    Q_OBJECT

public:
    utama(QWidget *parent = nullptr);
    ~utama();

protected:
    void keyPressEvent(QKeyEvent *e);

private slots:
    void on_button_ticket_clicked();

    void on_button_pay_clicked();

private:
    Ui::utama *ui;
    database_cntrl db;
    QString secondsToString(qint64 seconds,int *hari,int *jam, int *menit, int *detik);
    int kalkulasi_harga(int harga_perjam,int hari,int jam, int menit, int detik);
    void gen_tampung();
    QString harga_total;
    QString durasi_parkir;
    int counter_bayar;
    QDateTime waktu_now_last;
    int price_last;
};
#endif // UTAMA_H
