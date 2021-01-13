#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "Buttons/SlideButton.h"
#include "Buttons/HoldButton.h"

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
    HoldButton * btn2 = new HoldButton(this);
    btn2->move(0, 64);
    connect(btn1, &SlideButton::clicked, [=](bool clicked)
    {
       qDebug() << "Clicked:" << clicked;
    });

    connect(btn2, &HoldButton::longPressed, [=]()
    {
       qDebug() << "Long Pressed";
    });

    connect(btn2, &QAbstractButton::pressed, this, [=](){
        qDebug() << "Pressed";
    });

    connect(btn2, &QAbstractButton::clicked, this, [=](bool clicked){
        qDebug() << "Clicked:" << clicked;
    });

    connect(btn2, &QAbstractButton::released, this, [=](){
        qDebug() << "Released";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

