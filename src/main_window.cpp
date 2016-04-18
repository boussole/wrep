/*****************************************************************
 * Copyright (c) 2016 boussole (x dotty conquistador dotty at gmail com)
 * All rights reserved.
 *
 * This file is part of wrep.
 *
 * Wrep is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * https://github.com/boussole/wrep
 *
 * \file      main_window.cpp
 * \copyright GNU Public License
 * \author    boussole
 * \todo      add font choose
 *****************************************************************/

// Qt
#include <QFileDialog>
// custom
#include "main_window.h"

/**
 * \brief Create interface
 */
MainWindow :: MainWindow(QWidget * parent) :
	QMainWindow(parent)
{
	_cw = new CentralWidget(this);
	Q_ASSERT(_cw);
	setCentralWidget(_cw);

	createInterface();

	connect(_cw, SIGNAL(done()), SLOT(stop()));
}

/**
 * \brief Destructor
 */
MainWindow :: ~MainWindow()
{
	// TODO Auto-generated destructor stub
}

/**
 * \brief Create widgets and adjust them
 */
void MainWindow :: createInterface()
{
	_openLibAction = new QAction(tr("Open library"), this);
	Q_ASSERT(_openLibAction);

	createAction();
	createToolBar();
}

/**
 * \brief Create interface actions
 */
void MainWindow :: createAction()
{
	_openLibAction = new QAction(tr("Open library"), this);
	Q_ASSERT(_openLibAction);
	_openLibAction->setIcon(QIcon(":res/png/folder.png"));
	_openLibAction->setCheckable(false);
	connect(_openLibAction, SIGNAL(triggered()), SLOT(openLibrary()));

	_settingAction = new QAction(tr("Setting"), this);
	Q_ASSERT(_settingAction);
	_settingAction->setIcon(QIcon(":res/png/gear.png"));
	_settingAction->setCheckable(false);
	connect(_settingAction, SIGNAL(triggered()), _cw, SLOT(setting()));

	_startAction = new QAction(tr("Start"), this);
	Q_ASSERT(_startAction);
	_startAction->setIcon(QIcon(":res/png/play.png"));
	_startAction->setDisabled(true);
	connect(_startAction, SIGNAL(triggered()), SLOT(start()));

	_stopAction = new QAction(tr("Stop"), this);
	Q_ASSERT(_stopAction);
	_stopAction->setIcon(QIcon(":res/png/stop.png"));
	_stopAction->setDisabled(true);
	connect(_stopAction, SIGNAL(triggered()), SLOT(stop()));

	_showHintAction = new QAction(tr("Hint"), this);
	Q_ASSERT(_showHintAction);
	_showHintAction->setIcon(QIcon(":res/png/hint.png"));
	_showHintAction->setDisabled(true);
	connect(_showHintAction, SIGNAL(triggered()), _cw, SLOT(hint()));

	_fileDialog = new QFileDialog(this, Qt::Window | Qt::WindowStaysOnTopHint);
	Q_ASSERT(_fileDialog);
	_fileDialog->setWindowTitle(tr("Choose library"));
	_fileDialog->setWindowState(Qt::WindowFullScreen);
}

/**
 * \brief Create tool bar
 */
void MainWindow :: createToolBar()
{
	_fileToolBar = addToolBar("");
	Q_ASSERT(_fileToolBar);
	_fileToolBar->setMovable(false);
	_fileToolBar->setFocusPolicy(Qt::NoFocus);
	_fileToolBar->setMinimumHeight(96);
	_fileToolBar->setIconSize(QSize(96, 96));

	_fileToolBar->addAction(_openLibAction);
	_fileToolBar->addAction(_settingAction);

	_actionToolBar = addToolBar("");
	Q_ASSERT(_actionToolBar);
	_actionToolBar->setMovable(false);
	_actionToolBar->setFocusPolicy(Qt::NoFocus);
	_actionToolBar->setMinimumHeight(96);
	_actionToolBar->setIconSize(QSize(96, 96));

	_actionToolBar->addAction(_startAction);
	_actionToolBar->addAction(_stopAction);
	_actionToolBar->addAction(_showHintAction);
}

/**
 * \brief Choose new words file
 */
void MainWindow :: openLibrary()
{
	if (!_fileDialog->exec()) {
		return;
	}

	QString filename = _fileDialog->selectedFiles().first();

	if (!filename.isEmpty()) {
		if (_cw->open(filename)) {
			stop();
		}
	}
}

/**
 * \brief Start repetition process
 */
void MainWindow :: start()
{
	_startAction->setDisabled(true);
	_stopAction->setEnabled(true);
	_showHintAction->setEnabled(true);
	_cw->start();
}

/**
 * \brief Stop repetition process
 */
void MainWindow :: stop()
{
	_startAction->setEnabled(true);
	_stopAction->setDisabled(true);
	_showHintAction->setDisabled(true);
	_cw->stop();
}

