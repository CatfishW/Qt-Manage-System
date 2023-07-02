#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include <QWidget>

namespace Ui {
class register_window;
}

class register_window : public QWidget
{
    Q_OBJECT

public:
    explicit register_window(QWidget *parent = nullptr);
    ~register_window();

private slots:

    void on_close_button_2_clicked();

private:
    Ui::register_window *ui;
};

#endif // REGISTER_WINDOW_H
