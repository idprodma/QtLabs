#ifndef DIALOGADDSTUDENT_H
#define DIALOGADDSTUDENT_H

#include <QDialog>
#include "mainwindow.h"
#include "coursecontroller.h"

namespace Ui {
class DialogAddStudent;
}

class DialogAddStudent : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddStudent(CourseController* controller, MainWindow *parent = nullptr);
    ~DialogAddStudent();

private slots:
    void on_addStudentButton_clicked();

private:
    Ui::DialogAddStudent *ui;
    MainWindow* parent_;
    CourseController* controller_;
};

#endif // DIALOGADDSTUDENT_H
