#include "FileItem.h"

FileItem::FileItem(const QString &fileName, const QString &iconPath, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    iconLabel = new QLabel(this);
    nameLabel = new QLabel(fileName, this);

    iconLabel->setPixmap(QPixmap(iconPath));
    layout->addWidget(iconLabel);
    layout->addWidget(nameLabel);
    setLayout(layout);
}

void FileItem::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    QWidget::mousePressEvent(event);
}
