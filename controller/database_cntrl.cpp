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
        //return;
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
            //QSqlQuery q(db);

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
     QString HRini = QDate::currentDate().toString("yyyyMMdd");
     create_new_cek_in(q,driver);
     create_new_cek_out(q,driver);
}

void database_cntrl::create_new_cek_in(QSqlQuery *q,int driver)
{
    if(driver==1){
        QString query;
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
            QString buat = QString("CREATE TABLE IF NOT EXISTS cek_in (id integer PRIMARY KEY AUTOINCREMENT, \
                                  plat varchar(128), cam BLOB, jenis_kendaraan integer, num_parking integer, \
                                  waktu DATETIME default (datetime('now','localtime')))");

            q->prepare(buat);
            q->exec();
        }
    }
}

void database_cntrl::create_new_cek_out(QSqlQuery *q, int driver)
{
    if(driver==1){
        QString query;
        query = QString("select count(name) from sqlite_master where name = 'cek_out'");//.arg(HRini.toUtf8().data());
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
            QString buat = QString("CREATE TABLE IF NOT EXISTS cek_out (id integer PRIMARY KEY AUTOINCREMENT, \
                                  id_cek_in integer, cam_out BLOB, cam_out_face BLOB, price integer, \
                                  waktu DATETIME default (datetime('now','localtime')))");

            q->prepare(buat);
            q->exec();
        }
    }
}

int database_cntrl::insert_default_cek_in(QString plat, QByteArray cam, int jenis_kendaraan,int num_parkir)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO cek_in ( plat, cam, jenis_kendaraan, num_parking ) "
              "VALUES (?, ?, ?, ?)");

    query.addBindValue( plat );
    query.addBindValue( cam );
    query.addBindValue( jenis_kendaraan );
    query.addBindValue( num_parkir );
    if(!query.exec())
    {
        qDebug() << "ERROR "<< query.lastError().text();
        return 0;
    }
    else{
        return 1;
    }
}

int database_cntrl::insert_default_cek_out(int id_cek_in, QByteArray cam_out, QByteArray cam_out_face, QDateTime waktu, int price)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO cek_out ( id_cek_in, cam_out, cam_out_face, waktu, price) "
              "VALUES (?, ?, ?, ?, ?)");

    query.addBindValue( id_cek_in );
    query.addBindValue( cam_out );
    query.addBindValue( cam_out_face );
    query.addBindValue( waktu );
    query.addBindValue( price );
    if(!query.exec())
    {
        qDebug() << "ERROR "<< query.lastError().text();
        return 0;
    }
    else{
        return 1;
    }
}

int database_cntrl::cek_in_avaliablelity(int id_cek_in, QString plat, QDateTime *waktu, int *no_park)
{
    QSqlQuery query( db );
    QString st = QString("SELECT id, num_parking, waktu FROM cek_in WHERE plat='%1'").arg(plat);
    //QString st = QString("select id_kind from aset where id=1");//.arg(plat);
    qDebug()<<st;
    if (!query.exec( st ))
    {
        //id_cek_in = 0;
        qDebug()<<"tidak ada daftar cek in";
        //return 0;
    }
    else{
        while(query.next()){

            id_cek_in = id_cek_in=query.value("id").toInt();
            *no_park = query.value("num_parking").toInt();
            *waktu = query.value("waktu").toDateTime();
            qDebug()<<"id cek in = " << id_cek_in;
            return id_cek_in;
        }
    }
    query.clear();
    return id_cek_in;
}


int database_cntrl::was_cek_out(int id_cek_in)
{
    QSqlQuery query( db );
    QString st = QString("DELETE FROM cek_in WHERE id=%1").arg(id_cek_in);
    qDebug()<<st;
    if (!query.exec( st ))
    {
        //id_cek_in = 0;
        qDebug()<<"tidak ada daftar cek in";
        //return 0;
    }
    else{

            return 1;
    }
    return 0;
}
