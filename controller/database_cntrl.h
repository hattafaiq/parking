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

private:
    QSqlDatabase db;
    void load_database(QString filename);
    void create_database(QString filename);
    void create_new_table(QSqlQuery *q, int driver);

};

#endif // DATABASE_CNTRL_H
