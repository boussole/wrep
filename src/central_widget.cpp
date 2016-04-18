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
 * \file      central_widget.cpp
 * \copyright GNU Public License
 * \author    boussole
 *****************************************************************/

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QDateTime>
#include <QDebug>

#include "central_widget.h"

/**
 * \brief Create and adjust central widget of main window
 */
CentralWidget :: CentralWidget(QWidget * parent) :
	QWidget(parent),
	_wordIdx(-1),
	_wordCounter(0)
{
	createInterface();

	_setting = new SettingDialog(this);
	Q_ASSERT(_setting);
}

/**
 * \brief Destructor
 */
CentralWidget :: ~CentralWidget()
{
	// TODO Auto-generated destructor stub
}

/**
 * \brief Create widgets and adjust them
 */
void CentralWidget :: createInterface()
{
	QVBoxLayout * layout = new QVBoxLayout;
	Q_ASSERT(layout);

	_engGroupBox = new QGroupBox(tr("English"), this);
	Q_ASSERT(_engGroupBox);
	layout->addWidget(_engGroupBox);
	_engGroupBox->setLayout(new QHBoxLayout);
	Q_ASSERT(_engGroupBox->layout());

	_engLabel = new QLabel(_engGroupBox);
	Q_ASSERT(_engLabel);
	_engLabel->setAlignment(Qt :: AlignCenter);
	_engGroupBox->layout()->addWidget(_engLabel);

	_transGroupBox = new QGroupBox(tr("Transcription"), this);
	Q_ASSERT(_transGroupBox);
	layout->addWidget(_transGroupBox);
	_transGroupBox->setLayout(new QHBoxLayout);
	Q_ASSERT(_transGroupBox->layout());

	_transLabel = new QLabel(this);
	Q_ASSERT(_transLabel);
	_transLabel->setAlignment(Qt :: AlignCenter);
	_transGroupBox->layout()->addWidget(_transLabel);

	_rusGroupBox = new QGroupBox(tr("Russian"), this);
	Q_ASSERT(_rusGroupBox);
	layout->addWidget(_rusGroupBox);
	_rusGroupBox->setLayout(new QHBoxLayout);
	Q_ASSERT(_rusGroupBox->layout());

	_rusLabel = new QLabel(_rusGroupBox);
	Q_ASSERT(_rusLabel);
	_rusLabel->setAlignment(Qt :: AlignCenter);
	_rusGroupBox->layout()->addWidget(_rusLabel);

	_console = new QTextEdit(this);
	Q_ASSERT(_console != NULL);
	_console->setMaximumHeight(100);
	_console->setReadOnly(true);
	_console->sizePolicy().setVerticalPolicy(QSizePolicy :: Fixed);
	_console->sizePolicy().setHorizontalPolicy(QSizePolicy :: MinimumExpanding);
	layout->addWidget(_console);

	QHBoxLayout * button_layout = new QHBoxLayout;
	Q_ASSERT(button_layout);

	_nextPushButton = new QPushButton(this);
	Q_ASSERT(_nextPushButton);
	_nextPushButton->setEnabled(false);
	_nextPushButton->setIconSize(QSize(96, 96));
	_nextPushButton->setIcon(QIcon(":res/png/happy.png"));
	connect(_nextPushButton, SIGNAL(clicked()), SLOT(next()));
	button_layout->addWidget(_nextPushButton);

	_skipPushButton = new QPushButton(this);
	Q_ASSERT(_skipPushButton);
	_skipPushButton->setEnabled(false);
	_skipPushButton->setIconSize(QSize(96, 96));
	_skipPushButton->setIcon(QIcon(":res/png/sad.png"));
	connect(_skipPushButton, SIGNAL(clicked()), SLOT(skip()));
	button_layout->addWidget(_skipPushButton);

	layout->addLayout(button_layout);

	setLayout(layout);
}

/**
 * \brief  Read library file, parse it, and load data
 * \return TRUE in case of file contains as minimum 1 record
 */
bool CentralWidget :: open(const QString filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly)) {
		_console->setText(tr("Couldn't open file: ") + filename);
		return !_library.empty();
	}

	// todo do this expression as external param
//	if (file.size() > MaxFileSz) {
//		_console->setText(tr("File size more than acceptable (%1): %2").arg(MaxFileSz).arg(file.size()));
//		return !_library.empty();
//	}

	_library.clear();

	char buf[MaxLineSz];
	qint64 line_sz = -1;

	while ( (line_sz = file.readLine(buf, MaxLineSz)) != -1 ) {
		if (line_sz == MaxLineSz - 1) {
			continue;
		}

		parseLine(buf, line_sz);
	}

	if (_library.empty()) {
		_console->setText(tr("Invalid library, correct line hasn't found: ") + filename);
		return false;
	}

	return true;
}

/**
 * \brief   Parse one line of library and load data
 * \note    Current version maintains only one library format
 */
void CentralWidget :: parseLine(char * buf, qint64 sz)
{
	QStringList list = QString :: fromUtf8(buf, sz).split('|');

	if (list.size() == __MAX_LIB_INDEX) {
		LibraryUnit unit;
		unit.english = list.at(ENGLISH_LIB_INDEX).trimmed();
		unit.transcription = list.at(TRANSCRIPTION_LIB_INDEX).trimmed();
		unit.speech = list.at(SPEECH_LIB_INDEX).trimmed();

		unit.russian.append(list.at(RUSSIAN_INDEX).trimmed()); /**< first version stub */

		if (!unit.english.isEmpty() && !unit.russian.first().isEmpty()) {
			if (unit.transcription.isEmpty()) {
				unit.transcription = tr("unavailable");
			}

			_library.push_back(unit);
		}
	}
}

/**
 * \brief Call settings dialog
 */
void CentralWidget :: setting()
{
	_setting->exec();

	if (!_engLabel->text().isEmpty()) {
		_transLabel->setText(
			_setting->_showTranscription ?
				_library[_wordIdx].transcription : QString()
		);
	}
}

/**
 * \brief Start exercise
 */
void CentralWidget :: start()
{
	Q_ASSERT(_library.count() > 0);

	stop();

	_nextPushButton->setEnabled(true);
	_skipPushButton->setEnabled(true);

	_wordCounter = 0;

	_console->setText(tr("Completed: %1 of %2").arg(_wordCounter).arg(_library.count()));

	qsrand(QDateTime :: currentMSecsSinceEpoch());

	loadWord();
}

/**
 * \brief Force stop exercise
 */
void CentralWidget :: stop()
{
	_nextPushButton->setDisabled(true);
	_skipPushButton->setDisabled(true);

	for (QVector<LibraryUnit> :: Iterator it = _library.begin();
	     it != _library.end();
	     it++)
	{
		it->passed = false;
	}

	_console->setText(tr("Library size = %1 word (s)").arg(_library.size()));

	_wordIdx = -1;

	_wordCounter = 0;

	clearBoard();
}

/**
 * \brief Show next word
 */
void CentralWidget :: next()
{
	Q_ASSERT(_wordCounter < _library.size());

	_wordCounter++;

	_console->setText(tr("Completed: %1 of %2").arg(_wordCounter).arg(_library.count()));

	if (_wordCounter < _library.size()) {
		_library[_wordIdx].passed = true;
		loadWord();
	}
	else {
		clearBoard();
		_console->setText(tr("Exercise has been completed: %1 of %1").arg(_library.count()));
		emit done();
	}
}

/**
 * \brief Skip word
 */
void CentralWidget :: skip()
{
	loadWord();
}

/**
 * \brief Show hint
 */
void CentralWidget :: hint()
{
	Q_ASSERT(_wordIdx >= 0);
	Q_ASSERT(_wordCounter < _library.size());

	const LibraryUnit & unit = _library[_wordIdx];

	switch(_setting->_direction) {
		case(Setting :: RUS_ENG_DIRECTION): {
			_engLabel->setText(unit.english);

			if (_setting->_showTranscription) {
				_transLabel->setText(unit.transcription);
			}

			break;
		}

		case(Setting :: ENG_RUS_DIRECTION): {
			_rusLabel->setText(unit.russian.first());
			break;
		}

		default: break;
	}
}

/**
 * \brief Show word
 */
void CentralWidget :: printWord(const LibraryUnit & unit)
{
	switch(_setting->_direction) {
		case(Setting :: ENG_RUS_DIRECTION): {
			_engLabel->setText(unit.english);

			if (_setting->_showTranscription) {
				_transLabel->setText(unit.transcription);
			}

			break;
		}

		case(Setting :: RUS_ENG_DIRECTION): {
			_rusLabel->setText(unit.russian.first());
			break;
		}

		default: break;
	}
}

/**
 * \brief Choose next word using DIRECT strategy
 */
void CentralWidget :: loadDirectWord()
{
	Q_ASSERT(_wordCounter < _library.size());
	Q_ASSERT(_library[_wordCounter].passed == false);

	clearBoard();

	_wordIdx = (_wordIdx + 1) % _library.size();
	while (_library[_wordIdx].passed) {
		_wordIdx = (_wordIdx + 1) % _library.size();
	}

	printWord(_library[_wordIdx]);
}

/**
 * \brief Choose next word using RANDOM strategy
 */
void CentralWidget :: loadRandomWord()
{
	clearBoard();

	if (_wordCounter == (_library.size() - 1)) {
		_wordIdx = 0;

		while (_wordIdx < _library.count()) {
			if (!_library[_wordIdx].passed) {
				break;
			}

			_wordIdx++;
		}
	}
	else {
		int new_idx = qrand() % _library.count();
		/** exclude previous word too */
		while (_library[new_idx].passed || (new_idx == _wordIdx)) {
			new_idx = (new_idx + 1) % _library.count();
		}

		_wordIdx = new_idx;
	}

	printWord(_library[_wordIdx]);
}

/**
 * \brief Choose next word
 */
void CentralWidget :: loadWord()
{
	switch(_setting->_selectPolicy) {
		case(Setting :: DIRECT_SELECT_POLICY): loadDirectWord(); break;
		case(Setting :: RANDOM_SELECT_POLICY): loadRandomWord(); break;
		default: break;
	}
}

/**
 * \brief Remove all data from UI
 */
void CentralWidget :: clearBoard()
{
	_engLabel->clear();
	_transLabel->clear();
	_rusLabel->clear();
}
