#ifndef ATLASIMAGE_H
#define ATLASIMAGE_H

struct AtlasImage {
    float x;
    float y;
    float width;
    float height;
    QString imagefile;
    bool flipped;
    QImage* pImage;
};

#endif
