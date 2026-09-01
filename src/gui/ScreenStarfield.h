/*
 * Copyright (C) 2025 - 2026 Alexander Busorgin
 * This file is part of BinauralBeatX (https://github.com/dualword/binauralbeatx)
 * License: GPL-3 (GPL-3.0-only)
 *
 * BinauralBeatX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BinauralBeatX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BinauralBeatX.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCREENSTARFIELD_H
#define SCREENSTARFIELD_H

#include "ScreenSaver.h"

struct star{
    qreal x, y, z, speed;
    int a, size, r, g, b;
};

class ScreenStarfield : public VideoEffect {

public:
    ScreenStarfield();
    void reset (int width, int height){w = width/2; h = height/2;};

public slots:
    void reset(star&);
    void start();
    void stop();

protected:
    virtual void paint(QPainter& painter, const QRect& r);

private:
    QBrush bg, brush;
    QPen pen;
    QList<star> list;
    int max = 500;

};

#endif // SCREENSTARFIELD_H
