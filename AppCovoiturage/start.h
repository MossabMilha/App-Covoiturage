#ifndef START_H
#define START_H


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class start;
}
QT_END_NAMESPACE

class start : public QMainWindow
{
    Q_OBJECT

public:
    start(QWidget *parent = nullptr);
    ~start();

private:
    Ui::start *ui;
};
#endif // START_H
