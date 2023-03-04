#ifndef CONTROLELEMENT_H
#define CONTROLELEMENT_H

#include "student.h"
#include <map>
#include <string>
#include <vector>

enum ControlType {
    Practical,
    Seminar,
    Test,
    Homework,
    Exam
};

#define stringify( name ) #name

class ControlElement {
public:
    ControlElement() = default;

    explicit ControlElement(ControlType);

    void setMark(const Student&, int32_t);

    const std::map<Student, double>& getMarks() const;

    double getMark(const Student&) const;

    bool checkMark(const Student&) const;

    ControlType getType() const;

    std::string getTypeStr() const;

    static std::vector<std::string> getTypes();

    std::string toString() const;

private:
    std::map<Student, double> marks_;
    ControlType controlType_;
};

#endif // CONTROLELEMENT_H
