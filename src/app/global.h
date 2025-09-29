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

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "app/DualwordApp.h"
#include "gui/MainWindow.h"

#if defined(mApp)
#undef mApp
#endif
#define mApp (DualwordApp::instance())

#if defined(mWin)
#undef mWin
#endif
#define mWin (DualwordApp::instance()->window())

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <exception>
#include <string>

class dualword_exception: public std::runtime_error {
public:
	dualword_exception(const std::string& arg) : runtime_error(arg) {}
};

#endif /* GLOBAL_H_ */
