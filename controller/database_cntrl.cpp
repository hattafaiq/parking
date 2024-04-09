#include "database_cntrl.h"

database_cntrl::database_cntrl()
{

}

void database_cntrl::init_database(QString fileName)
{
    QFile file(fileName);

    if(file.exists()== true)
    {
        load_database(fileName);
    }
    else
    {
        create_database(fileName);
        return;
    }
}

void database_cntrl::load_database(QString fileName)
{
    QString con_name = QString("LOC_DB0");//ini untuk loketing
    db =QSqlDatabase::addDatabase("QSQLITE",con_name);
#ifdef WIN32
        db.setDatabaseName(fileName);
#else
        db.setDatabaseName(fileName += ".dbb"); //tambah ekstensi ".dbb" pada nama database
#endif// namanya con_name "LOC_DB1"

        if(!db.open())
        {
            qDebug()<<"db gak kebukak";
            return;
        }
        else
        {
            //global.db = db;
            qDebug()<<"db ok";
            return;
        }
}

void database_cntrl::create_database(QString fileName)
{
    QString con_name = QString("LOC_DB0");//ini untuk loketing
    db =QSqlDatabase::addDatabase("QSQLITE",con_name);
#ifdef WIN32
        db.setDatabaseName(fileName);
#else
        db.setDatabaseName(fileName += ".dbb"); //tambah ekstensi ".dbb" pada nama database
#endif// namanya con_name "LOC_DB1"

        if(!db.open())
        {
            qDebug()<<"db gak kebukak";
            return;
        }
        else
        {
            QSqlQuery q(db);
            create_new_table(&q, 1);
            qDebug()<<"db ok";
            return;
        }
}

void database_cntrl::create_new_table(QSqlQuery *q, int driver)
{
     QString query;
     QString HRini = QDate::currentDate().toString("yyyyMMdd");
    if(driver==1){
        query = QString("select count(name) from sqlite_master where name = 'cek_in'");//.arg(HRini.toUtf8().data());
        int jml=0;
        qDebug("q = %s",query.toUtf8().data());
        q->prepare(query);
        if(!q->exec())
        {
            qDebug("errorrr");
        }
        else {
            qDebug("lanjutttt");
            q->first();
            jml = q->value(0).toInt();
            qDebug() << "jumlahnya =  "<< q->value(0).toInt();

        }
        q->clear();
        if (jml < 1){
            QString buat = QString("create table cek_in (id integer PRIMARY KEY AUTOINCREMENT, \
                                  waktu DATETIME default(strftime('%Y%m%d%H%M%S', 'now', 'localtime')), \
                                  year DATETIME default(strftime('%Y', 'now', 'localtime')) , \
                                  month DATETIME default(strftime('%m', 'now', 'localtime')), \
                                  day DATETIME default(strftime('%d', 'now', 'localtime')), \
                                  hour DATETIME default(strftime('%H', 'now', 'localtime')), \
                                  minute DATETIME default(strftime('%M', 'now', 'localtime')), \
                                  plat text, cam BLOB, jenis_kendaraan integer)");

            q->prepare(buat);
            q->exec();
        }
    }
}
