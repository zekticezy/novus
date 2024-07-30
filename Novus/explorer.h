#ifndef EXPLORER_H
#define EXPLORER_H

#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
class Explorer;
}

class Explorer : public QWidget
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = nullptr);
    ~Explorer();

signals:
    void folderClicked(const QString &folderName);
    void fileClicked(const QString &fileName);

private slots:
    void onFolderClicked(const QString &folderName);
    void onFileClicked(const QString &fileName);

private:
    Ui::Explorer *ui;
    void addSection(QVBoxLayout *layout, const QString &sectionTitle);
    void addFolder(QVBoxLayout *layout, const QString &folderName, const QString &iconPath);
    void addFile(const QString &fileName, const QString &iconPath);
};

#endif // EXPLORER_H
