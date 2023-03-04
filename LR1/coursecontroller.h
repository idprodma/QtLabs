#ifndef COURSECONTROLLER_H
#define COURSECONTROLLER_H

#include "course.h"
#include <QMap>
#include <QSet>
#include <QStringList>
#include <QVector>

class CourseController {
public:
    CourseController();

    QVector<Course<>>& getCourses();

    QStringList getCourseNames() const;

    QMap<QString, ControlElement> getControlElements(const QString&);

    QStringList getControlElementStrings();

    QVector<Student> getStudentsByCourse(const QString&);

    QMap<QString, double> getMarks(const Student&) const;

    QVector<Course<>> getCoursesByStudent(const Student& student) const;

    QVector<Student> getAllStudents() const;

    void addCourse(const Course<>&);

    void addStudent(const Student&);

    const QString getCurrentCourseName() const;

    const QStringList getStudentNames() const;

    Course<>* currentCourse_;

private:
    QVector<Course<>> courses_;
    std::set<Student> students_;
};

#endif // COURSECONTROLLER_H
