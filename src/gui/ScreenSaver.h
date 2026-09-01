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

#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QtWidgets>

class VideoEffect {
public:
    VideoEffect() {};
    virtual ~VideoEffect() = default;
    virtual void paint(QPainter& painter, const QRect& r){};
    virtual void reset (int width, int height){w = width; h = height;};
    virtual void start() {};
    virtual void stop() {};

protected:
    int w=1, h=1;
};

class ScreenSaver : public QWidget {
    Q_OBJECT

public:
    ScreenSaver(QWidget *p = nullptr);
    virtual ~ScreenSaver();
    void setEffect(VideoEffect* effect) {
        activeEffect = effect; activeEffect->reset(width(), height());  update();
    }
    virtual void start() {activeEffect->start();};
    virtual void stop() {activeEffect->stop();update();};

protected:
    void paintEvent(QPaintEvent *event) {
        QWidget::paintEvent(event);
        if (activeEffect==nullptr) return;
        QPainter p(this);
        p.setFont(font());
        p.save();
        activeEffect->paint(p, event->rect());
        p.restore();
    };
    void resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
        if (activeEffect==nullptr) return;
        activeEffect->reset(width(), height());
    };

private:
    VideoEffect* activeEffect = nullptr;
};

#endif // SCREENSAVER_H
