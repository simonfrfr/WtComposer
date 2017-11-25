// Copyright (c) 2018 TSASPC
//
// This file is part of WtComposer
//
// WtComposer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// WtComposer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WtComposer.  If not, see <http://www.gnu.org/licenses/>.

// Qt Includes
#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPixmap>
#include <QSplashScreen>
#include <QSettings>


int main(int argc, char *argv[])
{
	// create qt application
	QApplication a(argc, argv);

#ifdef Q_OS_UNIX
    QApplication::addLibraryPath("./plugins");
#endif

	// show splash screen
	QPixmap pixmap(":/logo_loading"); // NOTE : had to convert text to path in inkscape for text to show
	QSplashScreen splash(pixmap);
	splash.show();

	// configure company and appname
    QCoreApplication::setOrganizationName("TSASPC");
    QCoreApplication::setOrganizationDomain("tsaspc.com");
    QCoreApplication::setApplicationName("WtComposer");

    // set CSS Theme
    //First we need to see the current saved theme...
    auto m_sSettingsFile = QApplication::applicationDirPath().left(1) + ":/settings.ini";
    QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
    QString sText = settings.value("Theme", "Light").toString();

    //We will default to no theme...
    if (sText == "Dark") {
        QFile f(":qdarkstyle/style.qss");
        if (!f.exists())
        {
            qDebug() << "[ERROR] Unable to set stylesheet, file not found.";
        }
        else
        {
            f.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&f);
            a.setStyleSheet(ts.readAll());
        }
    }
    else if (sText == "Light"){}
    else {
        QStringList extraThemes = settings.value("ExtraWtComposerThemes").value<QStringList>();
        Q_FOREACH(const QString theme, extraThemes){
            if (sText == theme){
                   QString temp = QApplication::applicationDirPath().left(1) + ":"+sText+"/.qss";
                   QFile f(temp);
                   if (!f.exists())
                   {
                       qDebug() << "[ERROR] Unable to set stylesheet, file not found.";
                   }
                   else
                   {
                       f.open(QFile::ReadOnly | QFile::Text);
                       QTextStream ts(&f);
                       a.setStyleSheet(ts.readAll());
                   }
            }
        }
    }

	// create main window and show it
	MainWindow w(argc, argv);
	w.show();
	// found this bug in debug mode when remove and then undo main.css file : https://bugreports.qt.io/browse/QTBUG-35663
	// close splash screen
	splash.finish(&w);
	// start qts event loop
	return a.exec();
}
