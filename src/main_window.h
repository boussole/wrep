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
 * \file      main_window.h
 * \copyright GNU Public License
 * \author    boussole
 * \todo      add font choose
 *****************************************************************/

#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

// Qt
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
// custom
#include "central_widget.h"

class MainWindow: public QMainWindow
{
	Q_OBJECT

public:
	/**
	 * \brief Create interface
	 */
	MainWindow(QWidget * parent = 0);

	/**
	 * \brief Destructor
	 */
	~MainWindow();

protected:
	/**
	 * \brief Create widgets and adjust them
	 */
	void createInterface();

	/**
	 * \brief Create interface actions
	 */
	void createAction();

	/**
	 * \brief Create tool bar
	 */
	void createToolBar();

protected slots:
	/**
	 * \brief Choose new words file
	 */
	void openLibrary();

	/**
	 * \brief Start repetition process
	 */
	void start();

	/**
	 * \brief Stop repetition process
	 */
	void stop();

private:
	CentralWidget *_cw;
	QToolBar *_fileToolBar, *_actionToolBar;
	QAction *_openLibAction, *_settingAction, *_startAction, *_stopAction, *_showHintAction;
	QFileDialog * _fileDialog;
};

#endif /* MAIN_WINDOW_H_ */
