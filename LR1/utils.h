#ifndef UTILS_H
#define UTILS_H

#include <QWidget>
#include <QMessageBox>
#include <QString>

class Utils {
public:
    static void showAlert(const QString& text, QWidget* parent = nullptr) {
        QMessageBox* alert = new QMessageBox(QMessageBox::Icon::Warning, "Ошибка", text, QMessageBox::NoButton, parent);
        alert->exec();
    }
};

#endif // UTILS_H
