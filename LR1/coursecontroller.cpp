#include "coursecontroller.h"
#include <QMessageBox>

CourseController::CourseController() {
    currentCourse_ = nullptr;
}

QVector<Course<>>& CourseController::getCourses() {
    return courses_;
}

void CourseController::addCourse(const Course<>& course) {
    courses_.append(course);
}

void CourseController::addStudent(const Student& student) {
    students_.insert(student);
}

const QString CourseController::getCurrentCourseName() const {
    return QString::fromStdString(currentCourse_->getCourseName());
}

QMap<QString, ControlElement> CourseController::getControlElements(const QString& courseName) {
    auto controlElements = (*(std::find_if(courses_.begin(), courses_.end(), [courseName](auto&& val) { return val.getCourseName() == courseName.toStdString(); }))).getControlElements();
    QMap<QString, ControlElement> ret;
    std::for_each(controlElements.begin(), controlElements.end(), [&ret](auto&& x) { ret.insert(QString::fromStdString(x.first), x.second); } );

    return ret;
}

QStringList CourseController::getControlElementStrings() {
    auto controlElements = currentCourse_->getControlElements();
    QStringList ret;
    std::for_each(controlElements.begin(), controlElements.end(), [&ret](auto&& x) { ret.append(QString::fromStdString(x.first) + " - " + QString::fromStdString(x.second.getTypeStr())); } );

    return ret;
}

QVector<Student> CourseController::getStudentsByCourse(const QString & courseName) {
    QVector<Student> ret;
    auto students = (*(std::find_if(courses_.begin(), courses_.end(), [courseName](auto&& val) { return val.getCourseName() == courseName.toStdString(); }))).getStudents();
    std::copy(students.begin(), students.end(), std::back_inserter(ret));
    std::sort(ret.begin(), ret.end());

    return ret;
}

QVector<Course<>> CourseController::getCoursesByStudent(const Student& student) const {
    QVector<Course<>> ret;
    std::for_each(
                courses_.begin(),
                courses_.end(),
                [student, &ret](auto&& course){ if (course.checkStudent(student)) ret.append(course); }
    );

    return ret;
}

const QStringList CourseController::getStudentNames() const {
    QStringList ret;
    auto students = currentCourse_->getStudents();
    std::transform(students.begin(), students.end(), std::back_inserter(ret), [](auto&& student) { return QString::fromStdString(student.toString()); });
    std::sort(ret.begin(), ret.end());

    return ret;
}

QVector<Student> CourseController::getAllStudents() const {
    return QVector<Student>::fromStdVector(std::vector<Student>(students_.begin(), students_.end()));
}

QStringList CourseController::getCourseNames() const {
    QStringList ret;
    std::transform(
                courses_.begin(),
                courses_.end(),
                std::back_inserter(ret),
                [](auto&& course) { return QString::fromStdString(course.getCourseName()); }
    );

    return ret;
}

QMap<QString, double> CourseController::getMarks(const Student& student) const {
    QMap<QString, double> ret;
    auto courses = getCoursesByStudent(student);
    std::for_each(
                courses.begin(),
                courses.end(),
                [&ret, student](auto&& course){ ret.insert(QString::fromStdString(course.getCourseName()), course.countMark(student)); }
    );
    return ret;
}
