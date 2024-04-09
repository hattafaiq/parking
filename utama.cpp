#include "utama.h"
#include "ui_utama.h"

utama::utama(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::utama)
{
    ui->setupUi(this);
    db.init_database("database_parkee");
}

utama::~utama()
{
    delete ui;
}

