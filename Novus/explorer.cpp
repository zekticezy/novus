#include "explorer.h"
#include "ui_explorer.h"
#include "FolderItem.h"
#include "FileItem.h"

Explorer::Explorer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Explorer)
{
    ui->setupUi(this);

    // Ensure the widget uses its own background color
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("QWidget { background-color: #B2B2B2; }");

    // Populate ExplorerMainFoldersLayout
    QVBoxLayout *mainFoldersLayout = ui->ExplorerMainFoldersLayout;

    // Adding sections and folders
    addSection(mainFoldersLayout, "Collections");
    addFolder(mainFoldersLayout, "Favorites", ":/icons/favorites.png");

    addSection(mainFoldersLayout, "Library");
    addFolder(mainFoldersLayout, "All", ":/icons/all_files.png");
    addFolder(mainFoldersLayout, "Sounds", ":/icons/sounds.png");
    addFolder(mainFoldersLayout, "Instruments", ":/icons/instruments.png");
    addFolder(mainFoldersLayout, "Effects", ":/icons/effects.png");
    addFolder(mainFoldersLayout, "Plug-ins", ":/icons/plugins.png");
    addFolder(mainFoldersLayout, "Audio Recordings", ":/icons/audio_recordings.png");
    addFolder(mainFoldersLayout, "Projects", ":/icons/projects.png");

    addSection(mainFoldersLayout, "Places");
    addFolder(mainFoldersLayout, "User", ":/icons/user.png");
    addFolder(mainFoldersLayout, "Documents", ":/icons/documents.png");
    addFolder(mainFoldersLayout, "Music", ":/icons/music.png");

    // Connect folder clicked signals to the slot
    connect(this, &Explorer::folderClicked, this, &Explorer::onFolderClicked);
    connect(this, &Explorer::fileClicked, this, &Explorer::onFileClicked);
}

Explorer::~Explorer()
{
    delete ui;
}

void Explorer::addSection(QVBoxLayout *layout, const QString &sectionTitle)
{
    QLabel *sectionLabel = new QLabel(sectionTitle, this);
    QFont font = sectionLabel->font();
    font.setBold(true);
    sectionLabel->setFont(font);
    layout->addWidget(sectionLabel);
    layout->addSpacing(10); // Add spacing between sections
}

void Explorer::addFolder(QVBoxLayout *layout, const QString &folderName, const QString &iconPath)
{
    FolderItem *folderItem = new FolderItem(folderName, iconPath, this);
    connect(folderItem, &FolderItem::clicked, this, [this, folderName]() {
        emit folderClicked(folderName);
    });
    layout->addWidget(folderItem);
}

void Explorer::addFile(const QString &fileName, const QString &iconPath)
{
    FileItem *fileItem = new FileItem(fileName, iconPath, this);
    connect(fileItem, &FileItem::clicked, this, [this, fileName]() {
        emit fileClicked(fileName);
    });
    ui->ExplorerFilesLayout->addWidget(fileItem);
}

void Explorer::onFolderClicked(const QString &folderName)
{
    qDebug() << "Folder clicked:" << folderName;
    // Implement functionality to update the displayed contents
}

void Explorer::onFileClicked(const QString &fileName)
{
    qDebug() << "File clicked:" << fileName;
    // Implement functionality to handle file click
}
