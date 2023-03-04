#include "dialoginfocontrolelement.h"
#include "ui_dialoginfocontrolelement.h"
#include <QMessageBox>

DialogInfoControlElement::DialogInfoControlElement(CourseController* controller, ControlElement* controlElement, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfoControlElement) {
    controller_ = controller;
    ctrlElement = controlElement;
    ui->setupUi(this);
    ui->studentsComboBox->addItems(controller_->getStudentNames());
    if (ui->studentsComboBox->count() == 0) {
        ui->setMarkButton->setEnabled(false);
    }
    fillTable();
}

DialogInfoControlElement::~DialogInfoControlElement() {
    delete ui;
}

void DialogInfoControlElement::on_setMarkButton_clicked() {
    QVector<QString> fio = ui->studentsComboBox->currentText().split(" ").toVector();
    auto student = Student(fio[0].toStdString(), fio[1].toStdString(), fio[2].toStdString());
    addOrUpdateRow(student, ui->markSpinBox->value());
    ctrlElement->setMark(student, ui->markSpinBox->value());
}

void DialogInfoControlElement::addOrUpdateRow(const Student& student, int32_t mark) {
    auto index = ui->studentsTableWidget->rowCount();
    if (ctrlElement->checkMark(student)) {
        for (int i = 0; i < index; ++i) {
            if (ui->studentsTableWidget->item(i, 0)->text() == QString::fromStdString(student.toString())) {
                ui->studentsTableWidget->item(i, 1)->setText(QString::number(mark));
                return;
            }
        }
    } else {
        ui->studentsTableWidget->insertRow(index);
        ui->studentsTableWidget->setItem(index, 0, new QTableWidgetItem(QString::fromStdString(student.toString())));
        ui->studentsTableWidget->setItem(index, 1, new QTableWidgetItem(QString::number(mark)));
    }
}

void DialogInfoControlElement::fillTable() {
    ui->studentsTableWidget->clear();
    ui->studentsTableWidget->setColumnCount(2);
    ui->studentsTableWidget->setRowCount(ctrlElement->getMarks().size());
    ui->studentsTableWidget->setHorizontalHeaderLabels(QStringList { "ФИО", "Оценка" });
    int i = 0;
    for (auto&& mark : ctrlElement->getMarks()) {
        ui->studentsTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(mark.first.toString())));
        ui->studentsTableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(mark.second)));
        i++;
    }
    ui->studentsTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}
