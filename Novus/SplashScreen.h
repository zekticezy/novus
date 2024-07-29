#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>

// Forward declare Ui namespace
namespace Ui {
class SplashScreen;
}

class SplashScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SplashScreen(QWidget *parent = nullptr);
    ~SplashScreen();

    void updateLoadingStatus(const QString &statusText);

private:
    Ui::SplashScreen *ui;  // This pointer will be used to access the UI components
};

#endif // SPLASHSCREEN_H
