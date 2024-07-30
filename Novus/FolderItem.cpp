#include "FolderItem.h"

FolderItem::FolderItem(const QString &folderName, const QString &iconPath, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    iconLabel = new QLabel(this);
    nameLabel = new QLabel(folderName, this);

    iconLabel->setPixmap(QPixmap(iconPath));
    layout->addWidget(iconLabel);
    layout->addWidget(nameLabel);
    setLayout(layout);
}

void FolderItem::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    QWidget::mousePressEvent(event);
}
