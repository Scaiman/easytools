#include "canvas.h"

Canvas::Canvas(QWidget* parent)
    : QWidget(parent)
{
    zoom = 100;
}

Canvas::~Canvas()
{
}

void Canvas::setZoom(int zoom)
{
    this->zoom = zoom;
}
