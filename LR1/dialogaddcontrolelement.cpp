#include "dialogaddcontrolelement.h"
#include "ui_dialogaddcontrolelement.h"
#include "utils.h"
#include "controlelement.h"

DialogAddControlElement::DialogAddControlElement(CourseController* controller, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddControlElement) {
    controller_ = controller;
    ui->setupUi(this);
    fillTypes();
}

DialogAddControlElement::~DialogAddControlElement() {
    delete ui;
}

void DialogAddControlElement::fillTypes() {
    ui->typeComboBox->clear();
    auto types = ControlElement::getTypes();
    for (int i = 0; i < 5; ++i) {
        ui->typeComboBox->addItem(QString::fromStdString(types[i]));
    }
}


void DialogAddControlElement::on_addControlElementButton_clicked() {
    if (ui->nameLineEdit->text().isEmpty()) {
        Utils::showAlert("Название не может быть пустым", this);
    } else if (controller_->currentCourse_->checkControlElement(ui->nameLineEdit->text().toStdString())) {
        Utils::showAlert("Такой элемент контроля уже есть", this);
    } else {
        controller_->currentCourse_->addControlElement(
                    ui->nameLineEdit->text().toStdString(),
                    ControlElement(ControlType(ui->typeComboBox->currentIndex()))
        );
        close();
    }
}

