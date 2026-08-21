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

#ifndef DUALWORDAPP_H
#define DUALWORDAPP_H

#include <QApplication>
#include "gui/MainWindow.h"

class DualwordApp : public QApplication {
    Q_OBJECT

public:
    DualwordApp() = delete;
    DualwordApp(const DualwordApp&) = delete;
    DualwordApp& operator=(const DualwordApp&) = delete;
    DualwordApp(int &argc, char **argv);
    virtual ~DualwordApp();
    static DualwordApp* instance() {
        return (static_cast<DualwordApp *>(QCoreApplication::instance()));
    };
    MainWindow* window() {return w;};


public slots:
    void start();
    void setValue(const QString&, const QVariant&);
    QVariant value(const QString&, const QVariant &v = QVariant());

private:
    MainWindow* w;

};

#endif // DUALWORDAPP_H
