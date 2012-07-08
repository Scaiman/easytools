#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QList>
#include "atlasimage.h"

class Canvas : public QWidget
{
    Q_OBJECT

    int zoom;
    QList<AtlasImage>* atlasImages;
    int atlasWidth;
    int atlasHeight;

public:
    Canvas(QWidget* parent = 0);
    ~Canvas();
    void setAtlasSize(int width, int height);
    void setAtlasImages(QList<AtlasImage>* atlasImages);

public slots:
    void setZoom(int zoom);

protected:
    void paintEvent(QPaintEvent* event);
};

#endif
