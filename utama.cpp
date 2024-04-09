#include "utama.h"
#include "ui_utama.h"

utama::utama(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::utama)
{
    ui->setupUi(this);
}

utama::~utama()
{
    delete ui;
}

