#include <QFontDatabase>
#include <QApplication>
#include "novus.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Load the custom font
    QFontDatabase fontDatabase;
    int fontId = fontDatabase.addApplicationFont(":/Content/Content/Fonts/Josefin/JosefinSans-VariableFont-wght.ttf");
    if (fontId == -1) {
        qWarning() << "Failed to load custom font.";
    }

    // Create and show the main window
    Novus mainWindow;
    mainWindow.show();

    return app.exec();
}
