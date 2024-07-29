#ifndef NOVUS_H
#define NOVUS_H

#include <QMainWindow>
#include "ui_projectWindow.h" // Adjust this if your UI header file has a different name

class Novus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Novus(QWidget *parent = nullptr);
    ~Novus();

private slots:
    void onImageButtonClicked();
    void newProject();
    void openProject();
    void closeFile();
    void addFolderToExplorer();
    void saveProject();
    void saveProjectAs();
    void saveCopyOfProject();
    void exportProject();
    void preferences();
    void quitNovus();

private:
    Ui::ProjectWindow *ui; // Ensure this matches your UI class name
    void setupMenu();
};

#endif // NOVUS_H
