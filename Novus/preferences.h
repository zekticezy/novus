#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include "ui_preferences.h" // Ensure this matches your UI file name

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = nullptr);
    ~Preferences();

private:
    Ui::Preferences *ui; // Ensure this matches the UI file name
};

#endif // PREFERENCES_H
