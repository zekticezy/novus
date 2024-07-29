#include "novus.h"
#include "preferences.h"
#include <QPushButton>
#include <QMenu>
#include <QIcon>
#include <QAction>
#include <QDebug>



Novus::Novus(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ProjectWindow) // Ensure this matches your UI class name
{
    ui->setupUi(this);
    setupMenu();

    // Set window properties
    setWindowState(Qt::WindowMaximized);
    setWindowTitle("Novus (Development Build)");
    setWindowIcon(QIcon(":/Content/Content/Images/Icons/novusblack.ico"));
}

Novus::~Novus()
{
    delete ui;
}


void Novus::onImageButtonClicked() {
    QPushButton *novusCenterButton = ui->NovusCenter; // Updated button name
    static bool isSelected = false; // Toggle state

    if (isSelected) {
        novusCenterButton->setStyleSheet("border: none; "
                                         "background: url(:/Content/Content/Images/Icons/novuscenter.png) no-repeat center center; "
                                         "background-size: cover;");
    } else {
        novusCenterButton->setStyleSheet("border: none; "
                                         "background: url(:/Content/Content/Images/Icons/novuscenter-selected.png) no-repeat center center; "
                                         "background-size: cover;");
    }
    isSelected = !isSelected;
}

void Novus::setupMenu() {
    QMenu *menu = new QMenu(this);

    // Define actions
    QAction *newProjectAction = new QAction("New Project", this);
    QAction *openProjectAction = new QAction("Open Project", this);
    QAction *openRecentProjectAction = new QAction("Open Recent Project", this);
    QAction *closeFileAction = new QAction("Close File", this);
    QAction *addFolderAction = new QAction("Add Folder To Explorer...", this);
    QAction *saveProjectAction = new QAction("Save Project", this);
    QAction *saveProjectAsAction = new QAction("Save Project As...", this);
    QAction *saveCopyAction = new QAction("Save Copy Of Project", this);
    QAction *exportProjectAction = new QAction("Export Project", this);
    QAction *preferencesAction = new QAction("Preferences", this);
    QAction *quitAction = new QAction("Quit Novus", this);

    // Set shortcuts
    newProjectAction->setShortcut(QKeySequence("CTRL+N"));
    openProjectAction->setShortcut(QKeySequence("CTRL+O"));
    closeFileAction->setShortcut(QKeySequence("CTRL+ALT+C"));
    saveProjectAction->setShortcut(QKeySequence("CTRL+S"));
    saveProjectAsAction->setShortcut(QKeySequence("CTRL+SHIFT+S"));
    exportProjectAction->setShortcut(QKeySequence("CTRL+R"));
    preferencesAction->setShortcut(QKeySequence("CTRL+P"));
    quitAction->setShortcut(QKeySequence("ALT+F4"));

    // Connect actions to slots
    connect(newProjectAction, &QAction::triggered, this, &Novus::newProject);
    connect(openProjectAction, &QAction::triggered, this, &Novus::openProject);
    connect(closeFileAction, &QAction::triggered, this, &Novus::closeFile);
    connect(addFolderAction, &QAction::triggered, this, &Novus::addFolderToExplorer);
    connect(saveProjectAction, &QAction::triggered, this, &Novus::saveProject);
    connect(saveProjectAsAction, &QAction::triggered, this, &Novus::saveProjectAs);
    connect(saveCopyAction, &QAction::triggered, this, &Novus::saveCopyOfProject);
    connect(exportProjectAction, &QAction::triggered, this, &Novus::exportProject);
    connect(preferencesAction, &QAction::triggered, this, &Novus::preferences);
    connect(quitAction, &QAction::triggered, this, &Novus::quitNovus);

    // Add actions to the menu
    menu->addAction(newProjectAction);
    menu->addAction(openProjectAction);

    QMenu *recentMenu = new QMenu("Open Recent Project", this);
    recentMenu->addAction("Recent File 1");
    recentMenu->addAction("Recent File 2");
    // Add more recent files as needed

    menu->addMenu(recentMenu);
    menu->addAction(closeFileAction);
    menu->addSeparator();
    menu->addAction(addFolderAction);
    menu->addSeparator();
    menu->addAction(saveProjectAction);
    menu->addAction(saveProjectAsAction);
    menu->addAction(saveCopyAction);
    menu->addSeparator();
    menu->addAction(exportProjectAction);
    menu->addSeparator();
    menu->addAction(preferencesAction);
    menu->addSeparator();
    menu->addAction(quitAction);

    // Set the menu to the button
    ui->NovusCenter->setMenu(menu); // Updated button name
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
