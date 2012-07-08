#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi(this);
    unsavedData = false;
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
    on_actionQuit_triggered();
}

void MainWindow::on_actionOpen_triggered()
{
}

void MainWindow::on_actionSave_triggered()
{
}

void MainWindow::on_actionSaveAs_triggered()
{
}

void MainWindow::on_actionQuit_triggered()
{
    if (unsavedData == true)
    {
        if (QMessageBox::question(
                this,
                QString::fromUtf8("Quit"),
                QString::fromUtf8("There's something unsaved. "
                                  "Do you really wanna quit?"),
                QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes
           )
            qApp->quit();
    } else {
        qApp->quit();
    }
}
