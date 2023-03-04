#include "controlelement.h"

ControlElement::ControlElement(ControlType controlType) {
    controlType_ = controlType;
}

void ControlElement::setMark(const Student& student, int32_t mark) {
    marks_.insert(std::make_pair(student, mark));
}

const std::map<Student, double>& ControlElement::getMarks() const {
    return marks_;
}

double ControlElement::getMark(const Student& student) const {
    if (checkMark(student))
        return marks_.at(student);
    return 0;
}

bool ControlElement::checkMark(const Student& student) const {
    return marks_.find(student) != marks_.end();
}

ControlType ControlElement::getType() const {
    return controlType_;
}

std::string ControlElement::getTypeStr() const {
    const char* convert_enum[] = {
        stringify( Practical ),
        stringify( Seminar ),
        stringify( Test ),
        stringify( Homework ),
        stringify( Exam )
    };

    return convert_enum[controlType_];
}

std::vector<std::string> ControlElement::getTypes() {
    const char* convert_enum[] = {
        stringify( Practical ),
        stringify( Seminar ),
        stringify( Test ),
        stringify( Homework ),
        stringify( Exam )
    };
    std::vector<std::string> ret;
    for (int i = 0; i < 5; ++i) {
        ret.push_back(convert_enum[i]);
    }
    return ret;
}
