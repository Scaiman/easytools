#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
    
    bool unsavedData;

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionQuit_triggered();

private:
    void closeEvent(QCloseEvent* event);
};

#endif
