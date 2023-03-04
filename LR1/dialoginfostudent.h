#ifndef DIALOGINFOSTUDENT_H
#define DIALOGINFOSTUDENT_H

#include <QDialog>
#include "student.h"
#include "coursecontroller.h"

namespace Ui {
class DialogInfoStudent;
}

class DialogInfoStudent : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInfoStudent(CourseController* controller, const Student& student, QWidget *parent = nullptr);
    ~DialogInfoStudent();

private:
    Ui::DialogInfoStudent *ui;
    CourseController* controller_;
    Student student_;

    void fillTable();
};

#endif // DIALOGINFOSTUDENT_H
