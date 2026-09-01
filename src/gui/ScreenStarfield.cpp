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

#include "ScreenStarfield.h"

ScreenStarfield::ScreenStarfield() : VideoEffect() {
    bg = QBrush(QColor(0, 0, 0));
    pen = QPen(Qt::black);
    pen.setWidth(1);
}

void ScreenStarfield::reset(star& s) {
    s.x = QRandomGenerator::global()->bounded(-w, w);
    s.y = QRandomGenerator::global()->bounded(-h, h);
    s.z = QRandomGenerator::global()->bounded(w);
    std::uniform_real_distribution<> dist(1, 2.5);
    s.speed = dist(*QRandomGenerator::global());
    s.size = QRandomGenerator::global()->bounded(2, 5);
    s.r = QRandomGenerator::global()->bounded(200, 256);
    s.g = QRandomGenerator::global()->bounded(200, 256);
    s.b = QRandomGenerator::global()->bounded(200, 256);
    s.a = 0;
}

void ScreenStarfield::paint(QPainter& painter, const QRect& r) {
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(r, bg);
    painter.setBrush(brush);
    painter.setPen(pen);

    for (int i =0; i < list.size(); i++) {
        list[i].z -= list[i].speed;
        float x = list[i].x / list[i].z * 100 + w;
        float y = list[i].y / list[i].z * 100 + h;
        if(list[i].a < 255) list[i].a++;
        if (qIsNaN(x) || qIsNaN(y)) continue;

        painter.setBrush(QBrush(QColor(list[i].r, list[i].g, list[i].b, list[i].a)));
        painter.drawEllipse(QRectF(x , y, list[i].size, list[i].size));
        if(list[i].z < 0) reset(list[i]);
    }
}
void ScreenStarfield::start(){
    list.clear();
    for (int i = 0; i < max; i++){
        star s;
        reset(s);
        list.append(s);
    }
}

void ScreenStarfield::stop(){
    list.clear();
}
