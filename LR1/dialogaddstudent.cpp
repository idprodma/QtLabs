#include "dialogaddstudent.h"
#include "ui_dialogaddstudent.h"
#include <QMessageBox>
#include "student.h"
#include "utils.h"

DialogAddStudent::DialogAddStudent(CourseController* controller, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddStudent) {
    parent_ = parent;
    controller_ = controller;
    ui->setupUi(this);
}

DialogAddStudent::~DialogAddStudent() {
    delete ui;
}

Student makeStudent(Ui::DialogAddStudent* ui) {
    return Student(
                ui->surnameLineEdit->text().toStdString(),
                ui->nameLineEdit->text().toStdString(),
                ui->patronymicsLineEdit->text().toStdString()
                );
}

void DialogAddStudent::on_addStudentButton_clicked() {

    if (ui->surnameLineEdit->text().isEmpty()   ||
        ui->nameLineEdit->text().isEmpty()      ||
        ui->patronymicsLineEdit->text().isEmpty())
    {
        Utils::showAlert("Заполните все поля", this);
    } else if (controller_->currentCourse_->checkStudent(makeStudent(ui))) {
        Utils::showAlert("Студент уже записан", this);
    } else {
        controller_->currentCourse_->addStudent(makeStudent(ui));
        close();
    }
}
