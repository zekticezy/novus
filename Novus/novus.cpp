#include "novus.h"
#include "preferences.h"
#include "explorer.h" // Include the header file for the explorer widget
#include <QPushButton>
#include <QMenu>
#include <QIcon>
#include <QAction>
#include <QDebug>
#include <QScrollEvent>
#include <QWheelEvent>
#include <QVBoxLayout> // Include the necessary layout header

Novus::Novus(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ProjectWindow), explorerWidget(new Explorer(this)) // Initialize explorerWidget
{
    ui->setupUi(this);
    setupMenu();
    setupWindowOptionsButton();
    setupTimeSignatureButton();
    setupTimelineSelectionModeButton();
    setupKey1Button();
    setupKey2Button();
    setupBPMButton();

    // Set window properties
    setWindowState(Qt::WindowMaximized);
    setWindowTitle("Novus (Development Build)");
    setWindowIcon(QIcon(":/Content/Content/Images/Icons/novusblack.ico"));

    // Check if the ProjectWidgets widget has a layout set
    if (!ui->ProjectWidgets->layout()) {
        // If no layout is set, create one and assign it to ProjectWidgets
        QVBoxLayout *layout = new QVBoxLayout(ui->ProjectWidgets);
        ui->ProjectWidgets->setLayout(layout);
    }

    // Add the Explorer widget to the ProjectWidgets frame
    ui->ProjectWidgets->layout()->addWidget(explorerWidget);
}

Novus::~Novus()
{
    delete ui;
    // No need to delete explorerWidget as it's a child of Novus and will be deleted automatically
}

// Implementations for the actions
void Novus::newProject() {
    qDebug() << "New Project action triggered";
    // Implement New Project action
}

void Novus::openProject() {
    qDebug() << "Open Project action triggered";
    // Implement Open Project action
}

void Novus::closeFile() {
    qDebug() << "Close File action triggered";
    // Implement Close File action
}

void Novus::addFolderToExplorer() {
    qDebug() << "Add Folder To Explorer action triggered";
    // Implement Add Folder To Explorer action
}

void Novus::saveProject() {
    qDebug() << "Save Project action triggered";
    // Implement Save Project action
}

void Novus::saveProjectAs() {
    qDebug() << "Save Project As action triggered";
    // Implement Save Project As action
}

void Novus::saveCopyOfProject() {
    qDebug() << "Save Copy Of Project action triggered";
    // Implement Save Copy Of Project action
}

void Novus::exportProject() {
    qDebug() << "Export Project action triggered";
    // Implement Export Project action
}

void Novus::preferences() {
    Preferences *prefsWindow = new Preferences(this); // Create the Preferences window
    prefsWindow->setModal(true); // Make it a modal window
    prefsWindow->show(); // Show the window
}

void Novus::quitNovus() {
    qDebug() << "Quit Novus action triggered";
    QApplication::quit();
}

void Novus::onImageButtonClicked() {
    qDebug() << "Image Button Clicked";
    // Implement functionality for when an image button is clicked
}

void Novus::updateBPM(int value) {
    qDebug() << "BPM Updated to:" << value;
    // Implement functionality to update BPM
}

bool Novus::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);
        qDebug() << "Wheel event detected:" << wheelEvent->angleDelta();
        // Implement custom handling for wheel events if needed
        return true; // Indicate that the event has been handled
    }
    // Pass the event on to the base class
    return QMainWindow::eventFilter(obj, event);
}

void Novus::setupMenu() {
    qDebug() << "Setup Menu";
    // Implement menu setup here
}

void Novus::setupWindowOptionsButton() {
    qDebug() << "Setup Window Options Button";
    // Implement window options button setup here
}

void Novus::setupTimeSignatureButton() {
    qDebug() << "Setup Time Signature Button";
    // Implement time signature button setup here
}

void Novus::setupTimelineSelectionModeButton() {
    qDebug() << "Setup Timeline Selection Mode Button";
    // Implement timeline selection mode button setup here
}

void Novus::setupKey1Button() {
    qDebug() << "Setup Key 1 Button";
    // Implement key 1 button setup here
}

void Novus::setupKey2Button() {
    qDebug() << "Setup Key 2 Button";
    // Implement key 2 button setup here
}

void Novus::setupBPMButton() {
    qDebug() << "Setup BPM Button";
    // Implement BPM button setup here
}
