#ifndef UTAMA_H
#define UTAMA_H

#include <QMainWindow>
#include "controller/database_cntrl.h"
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class utama; }
QT_END_NAMESPACE

class utama : public QMainWindow
{
    Q_OBJECT

public:
    utama(QWidget *parent = nullptr);
    ~utama();

private:
    Ui::utama *ui;
    database_cntrl db;
};
#endif // UTAMA_H
