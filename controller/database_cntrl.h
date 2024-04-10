#ifndef DATABASE_CNTRL_H
#define DATABASE_CNTRL_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QDateTime>


class database_cntrl
{
public:
    database_cntrl();
    void init_database(QString filename);
    int insert_default_cek_in(QString plat, QByteArray cam, int jenis_kendaraan,int num_parkir);
    int insert_default_cek_out(int id_cek_in, QByteArray cam_out, QByteArray cam_out_face, QDateTime waktu, int price);
    int cek_in_avaliablelity(int id_cek_in, QString plat, QDateTime *waktu, int *no_park);
    int was_cek_out(int id_cek_in);

private:
    QSqlDatabase db;
    void load_database(QString filename);
    void create_database(QString filename);
    void create_new_table(QSqlQuery *q, int driver);
    void create_new_cek_in(QSqlQuery *q, int driver);
    void create_new_cek_out(QSqlQuery *q, int driver);

};

#endif // DATABASE_CNTRL_H
