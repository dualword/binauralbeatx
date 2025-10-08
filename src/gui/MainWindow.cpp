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

#include "app/global.h"
#include "ScreenSaver.h"
#include "Generator.h"

#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *p) : QMainWindow(p) {
	setupUi(this);
    setWindowTitle(QApplication::applicationName());
    txtL->setAlignment(Qt::AlignHCenter);
    txtR->setAlignment(Qt::AlignHCenter);
    setAttribute(Qt::WA_DeleteOnClose, true);
    restoreGeometry(mApp->value("geom").toByteArray());
    gView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(gView, QOverload<const QPoint&>::of(&QWidget::customContextMenuRequested), this,
            [this](const QPoint& p){
        QMenu menu(this);
        auto a = new QAction(tr("About"), this);
        menu.addAction(a);
        connect(a,SIGNAL(triggered()),this,SLOT(showAbout()));
        menu.exec(QCursor::pos());
    });
}

MainWindow::~MainWindow() {

}

void MainWindow::init(){

    connect(btnG, &QPushButton::clicked, [this] {
        if (m_generator.isNull() || m_generator->output()->state() == QAudio::StoppedState) {
            m_generator.reset(new Generator(txtL->text().toFloat(), txtR->text().toFloat()));
            m_generator->noise(chkNoise->checkState());

            m_generator->start();            
            sldV->setValue(sldV->value());

            btnG->setText("Stop");
            gView->start();
            timer.reset(new QTimer());
            QObject::connect( timer.get(), SIGNAL( timeout() ), gView, SLOT( repaint() ) );
            timer->start(35);
        } else {
            gView->stop();
            m_generator->stop();
            btnG->setText("Play");
            timer->stop();
        }
    });

    connect(sldV, &QSlider::valueChanged, [this](int val) {
        if (!m_generator.isNull()) m_generator->output()->setVolume(QAudio::convertVolume(val / qreal(100.0),
            QAudio::LogarithmicVolumeScale, QAudio::LinearVolumeScale));
    });

    connect(chkNoise, &QCheckBox::stateChanged, [this](int val) {

    });
}

void MainWindow::closeEvent(QCloseEvent *event) {
    mApp->setValue("geom", saveGeometry());
	event->accept();
}

void MainWindow::showAbout() {
	QString str;
	str.append(qApp->applicationName());
	str.append(" ").append(qApp->applicationVersion()).append("<br>");
    str.append("License: GPL-3 (GPL-3.0-only)<br/>");
    str.append("<a href='https://github.com/dualword/binauralbeatx'>https://github.com/dualword/binauralbeatx</a><br/>");
    str.append("&copy; 2025 Alexander Busorgin <br/>");
	QMessageBox::about(this, tr("About"), str );
}

bool MainWindow::askYesNo(QWidget* p, const QString& str){
	bool yes = false;
	QMessageBox::StandardButton r;
	r = QMessageBox::question(p, tr(""),str, QMessageBox::Yes | QMessageBox::No);
	if (r == QMessageBox::Yes) yes = true;
	return yes;
}

void MainWindow::resizeEvent(QResizeEvent *event){

}

