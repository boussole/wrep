######################################################################
# Copyright (c) 2016 boussole (x dotty conquistador dotty at gmail com)
# All rights reserved.
#
# This file is part of wrep.
#
# Wrep is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>
#
# https://github.com/boussole/wrep
#
# \file      Qt project
# \copyright GNU Public License
# \author    boussole
######################################################################

QT += core gui
TEMPLATE = app
TARGET = wrep
INCLUDEPATH += .
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#CONFIG += debug

# Input
HEADERS += central_widget.h main_window.h setting_dialog.h
SOURCES += central_widget.cpp main.cpp main_window.cpp setting_dialog.cpp

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
    
RESOURCES += wrep.qrc
