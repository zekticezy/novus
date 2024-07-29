#include "preferences.h"
#include "ui_preferences.h"
#include <QFontDatabase>

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);

    // Load and set the custom font
    QFontDatabase fontDatabase;
    int fontId = fontDatabase.addApplicationFont(":/fonts/JosefinSans-VariableFont-wght.ttf");

    if (fontId != -1) {
        QString fontFamily = fontDatabase.applicationFontFamilies(fontId).at(0);
        QFont customFont(fontFamily);
        ui->AboutButton->setFont(customFont);
        ui->AppearanceButton->setFont(customFont);
        ui->BackupsButton->setFont(customFont);
        ui->DefaultsButton->setFont(customFont);
        ui->DisplayButton->setFont(customFont);
        ui->LibraryButton->setFont(customFont);
        ui->MIDIButton->setFont(customFont);
        ui->PluginsButton->setFont(customFont);
        ui->RecordingButton->setFont(customFont);
        ui->UpdatesButton->setFont(customFont);
    } else {
        qWarning() << "Failed to load custom font.";
    }

    // Set button styles
    QString buttonStyle =
        "QPushButton {"
        "background-color: #B2B2B2;"
        "border: none;"
        "text-align: left;"
        "padding-left: 20px;"
        "}"
        "QPushButton:hover {"
        "background-color: #CFCFCF;"
        "}"
        "QPushButton:pressed {"
        "background-color: #CFCFCF;"
        "}";

    ui->AboutButton->setStyleSheet(buttonStyle);
    ui->AppearanceButton->setStyleSheet(buttonStyle);
    ui->BackupsButton->setStyleSheet(buttonStyle);
    ui->DefaultsButton->setStyleSheet(buttonStyle);
    ui->DisplayButton->setStyleSheet(buttonStyle);
    ui->LibraryButton->setStyleSheet(buttonStyle);
    ui->MIDIButton->setStyleSheet(buttonStyle);
    ui->PluginsButton->setStyleSheet(buttonStyle);
    ui->RecordingButton->setStyleSheet(buttonStyle);
    ui->UpdatesButton->setStyleSheet(buttonStyle);
}

Preferences::~Preferences()
{
    delete ui;
}
