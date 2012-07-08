#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT

    int zoom;

public:
    Canvas(QWidget* parent = 0);
    ~Canvas();

public slots:
    void setZoom(int zoom);
};

#endif
