#ifndef DIALOGINFOCONTROLELEMENT_H
#define DIALOGINFOCONTROLELEMENT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class DialogInfoControlElement;
}

class DialogInfoControlElement : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInfoControlElement(CourseController* controller, ControlElement*, MainWindow* parent = nullptr);
    ~DialogInfoControlElement();

private slots:
    void on_setMarkButton_clicked();

private:
    Ui::DialogInfoControlElement *ui;
    ControlElement* ctrlElement;
    CourseController* controller_;

    void addOrUpdateRow(const Student&, int32_t);

    void fillTable();
};

#endif // DIALOGINFOCONTROLELEMENT_H
