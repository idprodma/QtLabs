#ifndef DIALOGADDCOURSE_H
#define DIALOGADDCOURSE_H

#include <QDialog>
#include "coursecontroller.h"
#include "mainwindow.h"

namespace Ui {
class DialogAddCourse;
}

class DialogAddCourse : public QDialog
{
    Q_OBJECT

public:
    DialogAddCourse(CourseController* controller, MainWindow *parent = nullptr);
    ~DialogAddCourse();

private slots:

    void on_addCourseButton_clicked();

private:
    Ui::DialogAddCourse *ui;
    MainWindow* parent_;
    CourseController* controller;

    bool checkCoefSum();
};

#endif // DIALOGADDCOURSE_H
