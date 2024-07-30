#ifndef FILEITEM_H
#define FILEITEM_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class FileItem : public QWidget
{
    Q_OBJECT

public:
    explicit FileItem(const QString &fileName, const QString &iconPath, QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *iconLabel;
    QLabel *nameLabel;
};

#endif // FILEITEM_H
