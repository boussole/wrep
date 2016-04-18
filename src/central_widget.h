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
 * \file      central_widget.h
 * \copyright GNU Public License
 * \author    boussole
 *****************************************************************/

#ifndef CENTRAL_WIDGET_H_
#define CENTRAL_WIDGET_H_

// Qt
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
// custom
#include "setting_dialog.h"

class CentralWidget: public QWidget
{
	Q_OBJECT

	struct LibraryUnit {
		LibraryUnit() :
			passed(false) {}

		QString english, transcription, speech;
		QStringList russian;
		bool passed;
	};

	static const qint64 MaxFileSz = 2048;
	static const qint64 MaxLineSz = 300;

	enum LibIndex {
		ENGLISH_LIB_INDEX = 0,
		TRANSCRIPTION_LIB_INDEX,
		SPEECH_LIB_INDEX,
		RUSSIAN_INDEX,
		__MAX_LIB_INDEX
	};

public:
	/**
	 * \brief Create and adjust central widget of main window
	 */
	CentralWidget(QWidget * parent = 0);

	/**
	 * \brief Destructor
	 */
	~CentralWidget();

signals:
	/**
	 * \brief Signal of exercise finishing
	 */
	void done();

public slots:
	/**
	 * \brief  Read library file, parse it, and load data
	 * \return TRUE in case of file contains as minimum 1 record
	 */
	bool open(const QString filename);

	/**
	 * \brief Call settings dialog
	 */
	void setting();

	/**
	 * \brief Start exercise
	 */
	void start();

	/**
	 * \brief Force stop exercise
	 */
	void stop();

	/**
	 * \brief Show hint
	 */
	void hint();

protected slots:
	/**
	 * \brief Show next word
	 */
	void next();

	/**
	 * \brief Skip word
	 */
	void skip();

protected:
	/**
	 * \brief   Parse one line of library and load data
	 * \note    Current version maintains only one library format
	 */
	void parseLine(char * buf, qint64 sz);

	/**
	 * \brief Create widgets and adjust them
	 */
	void createInterface();

	/**
	 * \brief Show word
	 */
	void printWord(const LibraryUnit & unit);

	/**
	 * \brief Choose next word
	 */
	void loadWord();

	/**
	 * \brief Choose next word using DIRECT strategy
	 */
	void loadDirectWord();

	/**
	 * \brief Choose next word using RANDOM strategy
	 */
	void loadRandomWord();

	/**
	 * \brief Remove all data from UI
	 */
	void clearBoard();

private:
	QPushButton *_nextPushButton, *_skipPushButton;
	QGroupBox *_engGroupBox, *_transGroupBox, *_rusGroupBox;
	QLabel *_engLabel, *_transLabel, *_rusLabel;
	QTextEdit *_console;
	QVector<LibraryUnit> _library;
	int _wordIdx, _wordCounter;
	SettingDialog *_setting;
};

#endif /* CENTRAL_WIDGET_H_ */
