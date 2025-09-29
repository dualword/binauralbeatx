/*
 * Copyright (C) 2025 Alexander Busorgin
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

#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QtWidgets>

struct star{
    qreal x, y, z, speed;
    int a, size, r, g, b;
};

class ScreenSaver : public QWidget {
    Q_OBJECT

public:
    ScreenSaver(QWidget *);

public slots:
    void reset(star&);
    void start();
    void stop();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *);

private:
    QBrush bg, brush;
    QPen pen;
    int w, h;
    QList<star> list;
    int max = 500;
};

#endif // SCREENSAVER_H
