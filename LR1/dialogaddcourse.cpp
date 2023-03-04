#include "dialogaddcourse.h"
#include "ui_dialogaddcourse.h"
#include "utils.h"
#include <QMessageBox>

DialogAddCourse::DialogAddCourse(CourseController* controller, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddCourse) {
    this->parent_ = parent;
    this->controller = controller;
    ui->setupUi(this);
}

DialogAddCourse::~DialogAddCourse() {
    delete ui;
}

bool DialogAddCourse::checkCoefSum() {
    return (ui->practCoefSpinBox->value()   +
            ui->testCoefSpinBox->value()     +
            ui->semCoeffSpinBox->value()    +
            ui->hwCoefSpinBox->value()      +
            ui->examCoefSpinBox->value()) == 1.0;
}

void DialogAddCourse::on_addCourseButton_clicked() {
    if (!checkCoefSum()) {
        Utils::showAlert("Сумма коэффициентов должна быть равна 1", this);

    } else if (ui->courseNameLineEdit->text().isEmpty()) {
        Utils::showAlert("Название курса не может быть пустым", this);
    } else {
        controller->addCourse(Course<>(
                    ui->courseNameLineEdit->text().toStdString(),
                    {
                        ui->practCoefSpinBox->value(),
                        ui->semCoeffSpinBox->value(),
                        ui->testCoefSpinBox->value(),
                        ui->hwCoefSpinBox->value(),
                        ui->examCoefSpinBox->value()
                    }));
        parent_->addCourse(ui->courseNameLineEdit->text());
        close();
    }
}

