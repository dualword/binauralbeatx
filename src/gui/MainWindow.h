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

#ifndef GUI_MAINWINDOW_H_
#define GUI_MAINWINDOW_H_

#include "ui_MainWindow.h"

#include <QtWidgets>

class Generator;

class MainWindow : public QMainWindow, private Ui::MainWindow {
  Q_OBJECT

public:
	MainWindow(QWidget *p = nullptr);
	virtual ~MainWindow();
	void init();
	bool askYesNo(QWidget*, const QString&);
    
protected:
    void closeEvent(QCloseEvent *);
    void resizeEvent(QResizeEvent *);

public slots:

private slots:
	void showAbout();

private:
    QScopedPointer<Generator> m_generator;
    QScopedPointer<QTimer> timer;

};

#endif /* GUI_MAINWINDOW_H_ */
