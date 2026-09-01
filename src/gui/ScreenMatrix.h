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

#ifndef SCREENMATRIX_H
#define SCREENMATRIX_H

#include "ScreenSaver.h"

class Drop {
public:
    Drop(char character, int y, int speed, int alpha, bool isHead = false) :
        m_char(character), m_y(y), m_speed(speed), m_alpha(alpha), m_head(isHead) {
    };
    void update(int maxHeight){
        m_y += m_speed;
        if (m_y > maxHeight) {
            m_y = 0;
        }
    };
    void speed(int s){m_speed = s;};
    void draw(QPainter &painter, int x, int fontSize){
        if (m_head) {
            painter.setPen(QColor(200, 255, 200, m_alpha));
        } else {
            painter.setPen(QColor(0, 255, 70, m_alpha));
        }
        painter.drawText(x, m_y, m_char);
    };

    int getY() const { return m_y; }
    void setCharacter(const QString& c) { m_char = c; }

private:
    QString m_char;
    int m_y;
    int m_speed;
    int m_alpha;
    bool m_head;
};

class DropColumn {
public:
    DropColumn() : m_x(0), m_speed(0) {

    };
    void init(int x, int maxHeight){
        m_x = x;
        m_speed = QRandomGenerator::global()->bounded(5, 10);
        int length = QRandomGenerator::global()->bounded(10, 30);
        int startY = QRandomGenerator::global()->bounded(-500, 0);

        for (int i = 0; i < length; ++i) {
            char c = QRandomGenerator::global()->bounded(33, 126);
            int alpha = 255 - (i * (255 / length));
            if (alpha < 0) alpha = 0;
            m_drops.append(Drop(c, startY - (i * 20), m_speed, alpha, i == 0));
        }
    };
    void update(int maxHeight){
        for (auto &drop : m_drops) {
            drop.update(maxHeight);
            if (QRandomGenerator::global()->bounded(0, 100) < 3) {
                drop.setCharacter(getRandomChar());
            }
        }
    };
    void draw(QPainter &painter, int fontSize){
        for (auto &drop : m_drops) {
            drop.draw(painter, m_x, fontSize);
        }
    };
    QChar getRandomChar() {
        int type = QRandomGenerator::global()->bounded(4);
        if (type == 0) {
            return QChar(QRandomGenerator::global()->bounded(0x30A0, 0x30FF));
        }else if(type == 1){
             return QChar('A' + QRandomGenerator::global()->bounded(26));
        }else if(type == 2){
            return QChar('0' + QRandomGenerator::global()->bounded(10));
        }else if (type == 3){
            return ru.at(QRandomGenerator::global()->bounded(rulen));
        }
    }

private:
    inline static const QString ru = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    inline static const int rulen = ru.length();
    int m_x;
    int m_speed;
    int m_inc;
    QVector<Drop> m_drops;
};

class ScreenMatrix : public VideoEffect {
public:
    ScreenMatrix();
    void reset (int width, int height){w = width; h = height; initMatrix();};

public slots:
    void start();
    void stop();

protected:
    virtual void paint(QPainter& painter, const QRect& r);

private:
    inline static QFont font = QFont("Monospace", 16, QFont::Bold);
    QBrush bg, brush;
    QPen pen;
    QVector<DropColumn> m_columns;
    int m_fontSize = 16;
    int m_columnWidth = 16;

    void initializeColumns();
    void updateRain();

    void initMatrix() {
        m_columns.clear();
        int numColumns = w / m_fontSize;
        m_columns.resize(numColumns);
        for (int i = 0; i < numColumns; ++i) {
            m_columns[i].init(i * m_fontSize, h);
        }
    }

};

#endif // SCREENMATRIX_H
