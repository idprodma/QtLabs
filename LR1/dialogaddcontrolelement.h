#ifndef DIALOGADDCONTROLELEMENT_H
#define DIALOGADDCONTROLELEMENT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DialogAddControlElement;
}

class DialogAddControlElement : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddControlElement(CourseController* controller, MainWindow *parent = nullptr);
    ~DialogAddControlElement();

private slots:
    void on_addControlElementButton_clicked();

private:
    Ui::DialogAddControlElement *ui;
    CourseController* controller_;

    void fillTypes();
};

#endif // DIALOGADDCONTROLELEMENT_H
