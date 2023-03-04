#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "coursecontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void updateUI();

    void addCourse(const QString& course);

private slots:
    void on_addCoursePushButton_clicked();

    void on_coursesComboBox_currentIndexChanged(int index);

    void on_addStudentButton_clicked();

    void on_addControlElementButton_clicked();

    void on_controlElementsListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_studentsListWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    CourseController controller_;

    void loadCourses();

    void loadStudents();

    void loadControlElements();

    void setCurrentCourse();

    void clearInfo();

    void updateFormula();
};
#endif // MAINWINDOW_H
