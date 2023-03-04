#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    std::string name_;
    std::string surname_;
    std::string patronymics_;

public:
    Student() = default;

    Student(const std::string& surname, const std::string& name, const std::string& patronymics) {
        name_ = name;
        surname_ = surname;
        patronymics_ = patronymics;
    }

    Student(const Student& other) {
        name_ = other.name_;
        surname_ = other.surname_;
        patronymics_ = other.patronymics_;
    }

    std::string toString() const {
        return surname_ + " " + name_ + " " + patronymics_;
    }

    bool operator==(const Student& other) const {
        return name_ == other.name_ && surname_ == other.surname_ && patronymics_ == other.patronymics_;
    }

    Student& operator=(const Student& other) {
        name_ = other.name_;
        surname_ = other.surname_;
        patronymics_ = other.patronymics_;

        return *this;
    }

    bool operator<(const Student& other) const {
        if (surname_ < other.surname_) return true;
        else if (surname_ == other.surname_ && name_ < other.name_) return true;
        else if (surname_ == other.surname_ && name_ == other.name_) return patronymics_ < other.patronymics_;

        return false;
    }

    size_t operator()(const Student& student) const noexcept {
            size_t hash = std::hash<std::string>()(student.surname_)    +
                          std::hash<std::string>()(student.name_)       +
                          std::hash<std::string>()(student.patronymics_);
            return hash;
    };
};

namespace std {
    template<> struct hash<Student>
    {
        std::size_t operator()(const Student& p) const noexcept
        {
            return p(p);
        }
    };
}

#endif // STUDENT_H
