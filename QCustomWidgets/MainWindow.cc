#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "Buttons/SlideButton.h"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SlideButton * btn1 = new SlideButton(this);
    SlideButton * btn2 = new SlideButton(this);
    btn2->move(0, 64);
    connect(btn1, &SlideButton::clicked, [=](bool clicked)
    {
       qDebug() << "Clicked:" << clicked;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

