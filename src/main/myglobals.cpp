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

#include "myglobals.h"

#include <QApplication>

QMap<QString, QIcon> &
Icons::GetCache()
{
    static QMap<QString, QIcon> cache;
    static auto conn = QObject::connect(qApp,
                                        &QCoreApplication::aboutToQuit,
                                        [&]{
        cache.clear();
    });
    return cache;
}

