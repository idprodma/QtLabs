#include "dialoginfostudent.h"
#include "ui_dialoginfostudent.h"

DialogInfoStudent::DialogInfoStudent(CourseController* controller, const Student& student, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfoStudent) {
    controller_ = controller;
    student_ = student;
    ui->setupUi(this);
    fillTable();
}

DialogInfoStudent::~DialogInfoStudent() {
    delete ui;
}

void DialogInfoStudent::fillTable() {
    QMap<QString, double> marks = controller_->getMarks(student_);
    ui->marksTableWidget->clear();
    ui->marksTableWidget->setColumnCount(2);
    ui->marksTableWidget->setRowCount(marks.size());
    ui->marksTableWidget->setHorizontalHeaderLabels(QStringList { "Название курса", "Оценка" });
    int i = 0;
    QMap<QString, double>::const_iterator mark = marks.constBegin();
    while (mark != marks.constEnd()) {
        ui->marksTableWidget->setItem(i, 0, new QTableWidgetItem(mark.key()));
        ui->marksTableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(mark.value())));
        mark++;
        i++;
    }
    ui->marksTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}
