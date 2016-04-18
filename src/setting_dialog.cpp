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
 * \file      setting_dialog.cpp
 * \copyright GNU Public License
 * \author    boussole
 *****************************************************************/

// Qt
#include <QVBoxLayout>
// custom
#include "setting_dialog.h"

/**
 * \brief Create dialog UI
 */
SettingDialog :: SettingDialog(QWidget * parent) :
	QDialog(parent)
{
	createInterface();

	setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
	setWindowState(Qt::WindowFullScreen);
}

/**
 * \brief Destructor
 */
SettingDialog :: ~SettingDialog()
{
	// TODO Auto-generated destructor stub
}

/**
 * \brief Custom executor of dialog
 */
int SettingDialog :: exec()
{
	restore();

	int result = QDialog :: exec();

	(result == QDialog :: Accepted) ? backup() : restore();

	return result;
}

/**
 * \brief Create widgets and adjust them
 */
void SettingDialog :: createInterface()
{
	QVBoxLayout * layout = new QVBoxLayout;
	Q_ASSERT(layout);

	_directionGroupBox = new QGroupBox(tr("Direction"), this);
	Q_ASSERT(_directionGroupBox);
	_directionGroupBox->setLayout(new QVBoxLayout);
	Q_ASSERT(_directionGroupBox->layout());

	_russianRadioButton = new QRadioButton(tr("Russian"), _directionGroupBox);
	Q_ASSERT(_russianRadioButton);
	_directionGroupBox->layout()->addWidget(_russianRadioButton);

	_englishRadioButton = new QRadioButton(tr("English"), _directionGroupBox);
	Q_ASSERT(_englishRadioButton);
	_directionGroupBox->layout()->addWidget(_englishRadioButton);

	layout->addWidget(_directionGroupBox);

	_selectPolicyGroupBox = new QGroupBox(tr("Select policy"), this);
	Q_ASSERT(_selectPolicyGroupBox);
	_selectPolicyGroupBox->setLayout(new QVBoxLayout);
	Q_ASSERT(_selectPolicyGroupBox->layout());

	_randomSelectPolicy = new QRadioButton(tr("Random"), _selectPolicyGroupBox);
	Q_ASSERT(_randomSelectPolicy);
	_selectPolicyGroupBox->layout()->addWidget(_randomSelectPolicy);

	_directSelectPolicy = new QRadioButton(tr("Direct"), _selectPolicyGroupBox);
	Q_ASSERT(_directSelectPolicy);
	_selectPolicyGroupBox->layout()->addWidget(_directSelectPolicy);

	layout->addWidget(_selectPolicyGroupBox);

	_showTranscriptionCheckBox = new QCheckBox(tr("Show transcription"), this);
	Q_ASSERT(_showTranscriptionCheckBox);
	layout->addWidget(_showTranscriptionCheckBox);

	layout->addStretch();

	_buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
	                                Qt::Horizontal, this);
	Q_ASSERT(_buttons);

	connect(_buttons, SIGNAL(accepted()), SLOT(accept()));
	connect(_buttons, SIGNAL(rejected()), SLOT(reject()));

	layout->addWidget(_buttons);

	setLayout(layout);
}

/**
 * \brief Save settings before call in case of CANCEL
 */
void SettingDialog :: backup()
{
	_direction = _englishRadioButton->isChecked() ? ENG_RUS_DIRECTION : RUS_ENG_DIRECTION;
	_selectPolicy = _randomSelectPolicy->isChecked() ? RANDOM_SELECT_POLICY : DIRECT_SELECT_POLICY;
	_showTranscription = _showTranscriptionCheckBox->isChecked();
}

/**
 * \brief Restore settings in case of CANCEL
 */
void SettingDialog :: restore()
{
	switch(_direction) {
		case(ENG_RUS_DIRECTION): _englishRadioButton->setChecked(true); break;
		case(RUS_ENG_DIRECTION): _russianRadioButton->setChecked(true); break;
	};

	switch(_selectPolicy) {
		case(RANDOM_SELECT_POLICY): _randomSelectPolicy->setChecked(true); break;
		case(DIRECT_SELECT_POLICY): _directSelectPolicy->setChecked(true); break;
	}

	_showTranscriptionCheckBox->setChecked(_showTranscription);
}

///**
// * \brief Lock not runtime settings
// * \note  Isn't used yet
// */
//void SettingDialog :: lock()
//{
//
//}
//
///**
// * \brief Unlock not runtime settings
// * \note  Isn't used yet
// */
//void SettingDialog :: unlock()
//{
//
//}
