#ifndef FOLDERITEM_H
#define FOLDERITEM_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class FolderItem : public QWidget
{
    Q_OBJECT

public:
    explicit FolderItem(const QString &folderName, const QString &iconPath, QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *iconLabel;
    QLabel *nameLabel;
};

#endif // FOLDERITEM_H
