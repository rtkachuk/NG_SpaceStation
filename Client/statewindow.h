#ifndef STATEWINDOW_H
#define STATEWINDOW_H

#include <QMainWindow>

namespace Ui {
class StateWindow;
}

class StateWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StateWindow(QWidget *parent = nullptr);
    ~StateWindow();
public slots:
    void showHP(int number);

private:
    Ui::StateWindow *ui;
};

#endif // STATEWINDOW_H
