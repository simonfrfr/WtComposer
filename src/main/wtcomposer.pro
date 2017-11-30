# Copyright (c) 2016 Juan Gonzalez Burgos
# 
# This file is part of WtDesigner.
# 
# WtDesigner is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# WtDesigner is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with WtDesigner.  If not, see <http://www.gnu.org/licenses/>.


#win32 {
# For compiling with Qt Creator
 TEMPLATE     = app
# For compiling with Visual Studio
#TEMPLATE      = vcapp
#RC_ICONS      = ./../../rec/WtDesigner_logo.ico
#}
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14
#linux-g++ {

#}


TARGET        = WtComposer

#CONFIG       -= flat
#CONFIG       += no_batch
#CONFIG       += debug_and_release

QT           += core xml widgets gui svg xmlpatterns
QT += webenginewidgets webchannel
QT += KCompletion KTextEditor
#QT           += webkitwidgets
#DEFINES      += QT_DLL QT_WEBKITWIDGETS_LIB QT_WIDGETS_LIB QT_XML_LIB

#DESTDIR       = ../../bin/WtComposer/
DEFINES      += QT_NO_KEYWORDS WT_NO_SLOT_MACROS
INCLUDEPATH  += ./wtwithqtlib

#win32 {
#include(../wtconfig.pri)
#}

#linux-g++ {
#include(../wtconfig_nix.pri)
INCLUDEPATH  += /usr/local/include/
LIBS         += -L/usr/local/lib/
#LIBS += -L/usr/lib/x86_64-linux-gnu/
        LIBS += -lboost_system \
                -lboost_thread \
             #   -lwttest       \
                -lwt           \
             #   -lwtdbo        \
             #   -lwtdbopostgres\
             #   -lwtdbosqlite3 \
                -lwthttp \
                -lboost_signals
#}

HEADERS      += ./myglobals.h                                   \			
                ./mainpage.h                                    \
                ./mainwindow.h                                  \
                ./mixedclasses.h                                \
                ./myundocommands.h                              \                
                ./mywebview.h                                   \
                ./helperfunctions.h                             \
                ./wtwithqtlib/DispatchThread.h                  \
                ./wtwithqtlib/WQApplication.h                   \
                ./modelview/mytreeview.h                        \
		./modelview/mytreemodel.h                       \
		./modelview/mypropertymodel.h                   \
		./modelview/mypropertyview.h                    \
		./modelview/mypropertydelegate.h                \
		./modelview/mywidgetmodel.h                     \
		./modelview/mywidgetview.h                      \
		./modelview/mysignalslotsmodel.h                \
		./modelview/mysignalslotsview.h                 \                      
                ./modelview/mysignalslotsdelegate.h             \
                ./modelview/myfilesystemview.h                  \
		./dialogs/dialogconfig/dialogconfig.h           \
		./dialogs/dialogprojselect/dialogprojselect.h   \ 	
		./dialogs/dialogprojsave/dialogprojsave.h       \ 
                ./dialogs/dialogabout/dialogabout.h
               
SOURCES      += ./main.cpp                                      \
                ./mainpage.cpp                                  \
                ./mainwindow.cpp                                \
		./mixedclasses.cpp                              \
                ./myglobals.cpp                                 \
		./myundocommands.cpp                            \				
                ./mywebview.cpp                                 \
                ./helperfunctions.cpp                           \
                ./wtwithqtlib/DispatchThread.cpp                \
                ./wtwithqtlib/WQApplication.cpp                 \
                ./modelview/mytreeview.cpp                      \
                ./modelview/mytreemodel.cpp                     \
		./modelview/mypropertymodel.cpp                 \
		./modelview/mypropertyview.cpp                  \
		./modelview/mypropertydelegate.cpp              \
		./modelview/mywidgetmodel.cpp                   \
		./modelview/mywidgetview.cpp                    \
		./modelview/mysignalslotsmodel.cpp              \
		./modelview/mysignalslotsview.cpp               \       
                ./modelview/mysignalslotsdelegate.cpp           \
                ./modelview/myfilesystemview.cpp                \   
		./dialogs/dialogconfig/dialogconfig.cpp         \
		./dialogs/dialogprojselect/dialogprojselect.cpp \
		./dialogs/dialogprojsave/dialogprojsave.cpp     \
                ./dialogs/dialogabout/dialogabout.cpp
             
FORMS        += ./mainwindow.ui                                 \
                ./dialogs/dialogconfig/dialogconfig.ui          \
                ./dialogs/dialogprojselect/dialogprojselect.ui  \
                ./dialogs/dialogprojsave/dialogprojsave.ui      \
                ./dialogs/dialogabout/dialogabout.ui            \


RESOURCES     = ./../../rec/qtresources.qrc \
    jsfiles.qrc \
    default/default_resources.qrc \
    widgets/widgets.qrc
RESOURCES    += ./../../rec/styles/qdarkstyle/style.qrc


