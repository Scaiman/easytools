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

    QList<AtlasImage>::iterator it = atlasImages.begin();
    while (it != atlasImages.end()) {
        delete it->pImage;
        ++it;
    }
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
        lastDirectory = QFileInfo(fileName).absoluteDir().absolutePath();
        settings->setValue("lastDirectory", lastDirectory);

        if (!parseXML(lastDirectory, fileName))
            return;

        zoomSlider->setEnabled(true);
        zoomSpin->setEnabled(true);
        scrollArea->setEnabled(true);
        imagesListWidget->setEnabled(true);
        setWindowTitle(QString(APP_NAME " - %1").arg(fileName));
    }
}

bool MainWindow::parseXML(QString & directory, QString & fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    if (!doc.setContent(&file)) {
        file.close();
        return false;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            if (e.tagName() == "Atlas") {
                atlasWidth = e.attribute("width", "0").toInt();
                atlasHeight = e.attribute("height", "0").toInt();
                canvas->setAtlasSize(atlasWidth, atlasHeight);

                QString atlasName = e.attribute("name", "a");
                /*atlasType = e.attribute("type", "png");
                atlasMode = e.attribute("mode", "RGBA");
                atlasBorder = e.attribute("border", "1").toInt();*/

                n = e.firstChild();
                while (!n.isNull()) {
                    e = n.toElement();
                    if (e.tagName() == "image") {
                        AtlasImage image;
                        image.x = e.attribute("x", "0").toFloat();
                        image.y = e.attribute("y", "0").toFloat();
                        image.width = e.attribute("width", "0").toFloat();
                        image.height = e.attribute("height", "0").toFloat();
                        image.imagefile = e.attribute("imagefile", "unknown.png");
                        image.flipped = e.attribute("flipped", "False") == "True";
                        image.pImage = new QImage(
                            QString("%1/../textures/%2/%3")
                                .arg(directory)
                                .arg(atlasName)
                                .arg(image.imagefile)
                        );
                        atlasImages << image;
                        imagesListWidget->addItem(image.imagefile);
                    }
                    n = n.nextSibling();
                }

                canvas->setAtlasImages(&atlasImages);

                return true;
            }
        }
        n = n.nextSibling();
    }

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
