#ifndef COURSE_H
#define COURSE_H

#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <vector>

#include "controlelement.h"

template<typename T = double>
class Course {
public:
    Course() = default;

    Course(const std::string& name, const std::array<double, 5>& coefs) {
        courseName_ = name;
        std::copy(std::begin(coefs), std::end(coefs), std::begin(coefs_));
    }

    void addControlElement(
            const std::string& controlElementName,
            const ControlElement& controlElement) {
        controlElements_.insert(std::make_pair(controlElementName, controlElement));
    }

    std::map<std::string, ControlElement>& getControlElements() {
        return controlElements_;
    }

    void addStudent(const Student& student) {
        students_.insert(Student(student));
    }

    bool checkStudent(const Student& student) const {
        return students_.find(student) != students_.end();
    }

    bool checkControlElement(const std::string& name) const {
        return controlElements_.find(name) != controlElements_.end();
    }

    const std::set<Student>& getStudents() const {
        return students_;
    }

    ControlElement* getControlElement(const std::string& name) {
        return &(controlElements_[name]);
    }

    T countMark(const Student& student) const {
        if (!checkStudent(student)) return T(0);
        std::vector<T> pract_marks, sem_marks, test_marks, hw_marks, exam_marks;
        pract_marks = getAllMarksByType(ControlType::Practical, student);
        sem_marks = getAllMarksByType(ControlType::Seminar, student);
        test_marks = getAllMarksByType(ControlType::Test, student);
        hw_marks = getAllMarksByType(ControlType::Homework, student);
        exam_marks = getAllMarksByType(ControlType::Exam, student);
        return coefs_[0] * std::accumulate(pract_marks.begin(), pract_marks.end(), 0.0) / pract_marks.size() +
               coefs_[1] * std::accumulate(sem_marks.begin(), sem_marks.end(), 0.0) / sem_marks.size() +
               coefs_[2] * std::accumulate(test_marks.begin(), test_marks.end(), 0.0) / test_marks.size() +
               coefs_[3] * std::accumulate(hw_marks.begin(), hw_marks.end(), 0.0) / hw_marks.size() +
               coefs_[4] * std::accumulate(exam_marks.begin(), exam_marks.end(), 0.0) / exam_marks.size();
    }

    const std::map<Student, T> countMarks() const {
        std::map<Student, T> ret;
        std::for_each(
                    students_.begin(),
                    students_.end(),
                    [&ret, this](auto&& student) { ret[student] = countMark(student); }
        );
        return ret;
    }

    const double* coefs() const {
        return coefs_;
    }

    const std::string& getCourseName() const {
        return courseName_;
    }

private:
    std::string courseName_;
    double coefs_[5];
    std::map<std::string, ControlElement> controlElements_;
    std::set<Student> students_;

    std::vector<T> getAllMarksByType(ControlType type, const Student& student) const {
        std::vector<T> ret;

        for (auto&& x : controlElements_) {
          if(x.second.getType() == type) {
            ret.emplace_back(x.second.getMark(student));
          }
        }

        if (ret.empty()) ret.push_back(T(0));
            return ret;
    }
};

#endif // COURSE_H
