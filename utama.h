#ifndef UTAMA_H
#define UTAMA_H

#include <QMainWindow>

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
};
#endif // UTAMA_H
