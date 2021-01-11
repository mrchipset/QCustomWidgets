#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "Buttons/SlideButton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SlideButton * button = new SlideButton(this);
    setCentralWidget(button);
}

MainWindow::~MainWindow()
{
    delete ui;
}

