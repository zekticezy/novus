#include "explorer.h"
#include "ui_explorer.h"

Explorer::Explorer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Explorer)
{
    ui->setupUi(this);
}

Explorer::~Explorer()
{
    delete ui;
}
