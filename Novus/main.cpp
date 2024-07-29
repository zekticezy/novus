#include <QFontDatabase>
#include <QApplication>
#include <QThread>
#include "novus.h"
#include "splashscreen.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Load the custom font
    QFontDatabase fontDatabase;
    int fontId = fontDatabase.addApplicationFont(":/Content/Content/Fonts/Josefin/JosefinSans-VariableFont-wght.ttf");
    if (fontId == -1) {
        qWarning() << "Failed to load custom font.";
    }

    // Show splash screen
    SplashScreen splashScreen;
    splashScreen.show();

    // Simulate loading process
    for (int i = 0; i <= 100; ++i) {
        splashScreen.updateLoadingStatus(QString("Loading files %1%").arg(i));
        QCoreApplication::processEvents();  // Ensure UI updates are processed
        QThread::sleep(1);  // Simulate time-consuming task
    }

    // Close the splash screen
    splashScreen.close();

    // Create and show the main window
    Novus mainWindow;
    mainWindow.show();

    return app.exec();
}
