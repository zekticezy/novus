#ifndef NOVUS_H
#define NOVUS_H

#include <QMainWindow>
#include "ui_projectWindow.h" // Adjust this if your UI header file has a different name
#include "explorer.h" // Include the header file for the explorer widget

class Novus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Novus(QWidget *parent = nullptr);
    ~Novus();

private slots:
    void onNCenterClicked(); // Slot for handling NCenter button click
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
    void updateBPM(int value);

private:
    Ui::ProjectWindow *ui; // Ensure this matches your UI class name
    Explorer *explorerWidget; // Pointer to the explorer widget

    void setupMenu();
    void setupWindowOptionsButton();
    void setupTimeSignatureButton();
    void setupTimelineSelectionModeButton();
    void setupKey1Button();
    void setupKey2Button();
    void setupBPMButton();
    void setupNCenterMenu(); // Function to setup the NCenter menu

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // NOVUS_H
