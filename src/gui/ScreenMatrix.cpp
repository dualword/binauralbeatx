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

#include "ScreenMatrix.h"

ScreenMatrix::ScreenMatrix() : VideoEffect() {
    bg = QBrush(QColor(0, 0, 0));
    pen = QPen(Qt::black);
    pen.setWidth(1);
    font.setStyleStrategy(QFont::PreferAntialias);
    font.setPixelSize(16);
    font.setBold(true);
}

void ScreenMatrix::paint(QPainter& painter, const QRect& r) {
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(r, bg);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.setFont(font);

    for (auto &col : m_columns) {
        col.update(h);
    }

    for (auto &col : m_columns) {
        col.draw(painter, m_fontSize);
    }
}

void ScreenMatrix::start(){
    initMatrix();
}

void ScreenMatrix::stop(){
    m_columns.clear();
}
