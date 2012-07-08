#include "canvas.h"
#include <QPainter>

Canvas::Canvas(QWidget* parent)
    : QWidget(parent)
{
    zoom = 100;
    atlasImages = 0;
}

Canvas::~Canvas()
{
}

void Canvas::setAtlasSize(int width, int height)
{
    atlasWidth = width;
    atlasHeight = height;
}

void Canvas::setAtlasImages(QList<AtlasImage>* atlasImages)
{
    this->atlasImages = atlasImages;
}

void Canvas::setZoom(int zoom)
{
    this->zoom = zoom;
}

void Canvas::paintEvent(QPaintEvent* event)
{
    if (atlasImages == 0)
        return;

    int w = (zoom * atlasWidth) / 100;
    int h = (zoom * atlasHeight) / 100;
    setFixedSize(w, h);

    QPainter p(this);
    qreal z = (qreal)zoom / 100.0f;
    p.scale(z, z);

    QList<AtlasImage>::iterator it = atlasImages->begin();
    while (it != atlasImages->end()) {
        p.drawImage(it->x * (float)atlasWidth,
                    it->y * (float)atlasHeight,
                    *(it->pImage));
        it++;
    }
}
