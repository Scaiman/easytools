#include "mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi(this);
    unsavedData = false;

#if defined(WIN32) || defined(WIN64)
    settings = new QSettings(
        QString("%1/" APP_NAME ".conf").arg(qApp->applicationDirPath()),
        QSettings::IniFormat
    );
#else
    settings = new QSettings(APP_NAME);
#endif
}

MainWindow::~MainWindow()
{
    delete settings;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
    on_actionQuit_triggered();
}

void MainWindow::on_actionOpen_triggered()
{
    QString lastDirectory = settings->value("lastDirectory", QDir::homePath()).toString();
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open XML File"),
        lastDirectory,
        tr("XML Files (*.xml);;All Files (*.*)")
    );
    
    if (!fileName.isEmpty()) {
        settings->setValue("lastDirectory",
                            QFileInfo(fileName).absoluteDir().absolutePath());

        if (!parseXML(fileName))
            return;

        zoomSlider->setEnabled(true);
        setWindowTitle(QString(APP_NAME " - %1").arg(fileName));
    }
}

bool MainWindow::parseXML(QString & fileName)
{
    return true;
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
                tr("Quit"),
                tr("There's something unsaved. Do you really wanna quit?"),
                QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes
           )
            qApp->quit();
    } else {
        qApp->quit();
    }
}
