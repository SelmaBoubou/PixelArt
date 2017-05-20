#include "pixel.h"

Px::Px(int x, int y, int size, int red, int green, int blue) {

    this->setRect(x, y, size, size);
    this->setBrush(QColor(red, green, blue));

}
