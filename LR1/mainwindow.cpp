#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogaddcourse.h"
#include "dialogaddstudent.h"
#include "dialogaddcontrolelement.h"
#include "dialoginfocontrolelement.h"
#include "dialoginfostudent.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    loadCourses();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateUI() {
    ui->addStudentButton->setEnabled(false);
    ui->addControlElementButton->setEnabled(false);
    clearInfo();
    setCurrentCourse();
    if (controller_.currentCourse_ != nullptr) {
        ui->addStudentButton->setEnabled(true);
        ui->addControlElementButton->setEnabled(true);
    }
}

void MainWindow::loadCourses() {
    ui->coursesComboBox->addItems(controller_.getCourseNames());
}

void MainWindow::addCourse(const QString& course) {
    ui->coursesComboBox->addItem(course);
}

void MainWindow::loadStudents() {
    ui->studentsListWidget->addItems(controller_.getStudentNames());
}

void MainWindow::setCurrentCourse() {
    loadStudents();
    loadControlElements();
    updateFormula();
    ui->courseGroupBox->setTitle(QString("Курс: \"%1\"").arg(controller_.getCurrentCourseName()));
}

void MainWindow::clearInfo() {
    ui->studentsListWidget->clear();
    ui->controlElementsListWidget->clear();
}

void MainWindow::loadControlElements() {
    ui->controlElementsListWidget->addItems(controller_.getControlElementStrings());
}

void MainWindow::on_addCoursePushButton_clicked() {
    DialogAddCourse* newWindow = new DialogAddCourse(&controller_, this);
    newWindow->setModal(true);
    newWindow->exec();
}

void MainWindow::on_coursesComboBox_currentIndexChanged(int index) {
    if (index >= 0 &&
        index < controller_.getCourses().size()) {
        controller_.currentCourse_ = &(controller_.getCourses()[index]);
    }
    updateUI();
}

void MainWindow::updateFormula() {
    auto coefs = controller_.currentCourse_->coefs();
    ui->formulaLabel->setText(
                QString("Формула оценки: %1*практ. + %2*сем. + %3*сам. + %4*дз + %5*экз.")
                .arg(
                    QString::number(coefs[0]),
                    QString::number(coefs[1]),
                    QString::number(coefs[2]),
                    QString::number(coefs[3]),
                    QString::number(coefs[4])
                ));
}

void MainWindow::on_addStudentButton_clicked() {
    DialogAddStudent* newWindow = new DialogAddStudent(&controller_, this);
    newWindow->setModal(true);
    newWindow->exec();
    updateUI();
}


void MainWindow::on_addControlElementButton_clicked() {
    DialogAddControlElement* newWindow = new DialogAddControlElement(&controller_, this);
    newWindow->setModal(true);
    newWindow->exec();
    updateUI();
}


void MainWindow::on_controlElementsListWidget_itemDoubleClicked(QListWidgetItem *item) {
    std::string toFind = item->text().toStdString();
    toFind = toFind.substr(0, toFind.find('-') - 1);
    DialogInfoControlElement* newWindow =
            new DialogInfoControlElement(
                &controller_,
                controller_.currentCourse_->getControlElement(toFind),
                this
            );
    newWindow->setWindowTitle(QString::fromStdString(toFind));
    newWindow->setModal(true);
    newWindow->exec();
    updateUI();
}


void MainWindow::on_studentsListWidget_itemDoubleClicked(QListWidgetItem *item) {
    auto fio = item->text().split(' ');
    auto student = Student(fio[0].toStdString(), fio[1].toStdString(), fio[2].toStdString());
    DialogInfoStudent* newWindow =
            new DialogInfoStudent(
                &controller_,
                student,
                this
            );
    newWindow->setWindowTitle(item->text());
    newWindow->setModal(true);
    newWindow->exec();
}

