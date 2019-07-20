#pragma once
#include "Border.h"

class NullBorder : public Border {
    public:
        NullBorder();
        virtual ~NullBorder();
        virtual void drawBorder(Graphics& g, short left, short top, short width, short height);
};
