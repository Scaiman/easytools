#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>
#include <QSettings>
#include <QtXml/QDomDocument>
#include <QList>
#include <QImage>
#include "atlasimage.h"

#define APP_NAME "SpriteVertexForm"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
    
    bool unsavedData;
    QSettings* settings;

    QDomDocument doc;

    QList<AtlasImage> atlasImages;
    int atlasWidth;
    int atlasHeight;

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

    bool parseXML(QString & directory, QString & fileName);

public slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionQuit_triggered();

private:
    void closeEvent(QCloseEvent* event);
};

#endif
