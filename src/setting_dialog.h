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
 * \file      setting_dialog.h
 * \copyright GNU Public License
 * \author    boussole
 *****************************************************************/

#ifndef SETTING_DIALOG_H_
#define SETTING_DIALOG_H_

#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QCheckBox>

struct Setting {
	enum Direction {
		ENG_RUS_DIRECTION = 0,
		RUS_ENG_DIRECTION
	};

	enum SelectPolicy {
		DIRECT_SELECT_POLICY = 0,
		RANDOM_SELECT_POLICY
	};

	enum Duration {
		ENDING_DURATION = 0,
		ENDLESS_DURATION
	};

	Setting() :
		_duration(ENDING_DURATION),
		_direction(RUS_ENG_DIRECTION),
		_selectPolicy(RANDOM_SELECT_POLICY),
		_showTranscription(false) {}

	Duration _duration;
	Direction _direction;
	SelectPolicy _selectPolicy;
	bool _showTranscription;
};

class SettingDialog : public Setting, private QDialog
{
public:
	/**
	 * \brief Create dialog UI
	 */
	SettingDialog(QWidget * parent = 0);

	/**
	 * \brief Destructor
	 */
	~SettingDialog();

	/**
	 * \brief Custom executor of dialog
	 */
	int exec();

//	/**
//	 * \brief Lock not runtime settings
//	 * \note  Isn't used yet
//	 */
//	void lock();
//
//	/**
//	 * \brief Unlock not runtime settings
//	 * \note  Isn't used yet
//	 */
//	void unlock();

protected:
	/**
	 * \brief Create widgets and adjust them
	 */
	void createInterface();

	/**
	 * \brief Save settings before call in case of CANCEL
	 */
	void backup();

	/**
	 * \brief Restore settings in case of CANCEL
	 */
	void restore();

private:
	QGroupBox *_directionGroupBox, *_selectPolicyGroupBox, *_duration;
	QRadioButton *_englishRadioButton, *_russianRadioButton, *_directSelectPolicy, *_randomSelectPolicy;
	QCheckBox * _showTranscriptionCheckBox;
	QDialogButtonBox * _buttons;
};

#endif /* SETTING_DIALOG_H_ */
