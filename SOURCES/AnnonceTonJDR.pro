#-------------------------------------------------
#
# Project created by QtCreator 2017-01-22T22:10:16
#
#-------------------------------------------------

QT       += core gui xml sql network

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AnnonceTonJDR
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += IHM/MainWindow \
    IHM/Tabs/OneShotTabs \
    IHM/TreeWidgets \
    IHM/Dialogs \
    DATAMANAGEMENT/Info \
    DATAMANAGEMENT/Info/OneShotInfo \
    DATAMANAGEMENT/Filter \
    DATAMANAGEMENT/Filter/OneShotSearchFilter \
    SQLDATABASE


SOURCES += main.cpp\
    IHM/MainWindow/mainwindow.cpp \
    IHM/Tabs/OneShotTabs/oneshotsearchtab.cpp \
    IHM/TreeWidgets/citiesselectiontreewidget.cpp \
    IHM/Dialogs/oneshotcreatedialog.cpp \
    IHM/TreeWidgets/multicitiesselectiontreewidget.cpp \
    IHM/TreeWidgets/onecityselectiontreewidget.cpp \
    DATAMANAGEMENT/Info/gameeventinfo.cpp \
    DATAMANAGEMENT/Info/OneShotInfo/oneshoteventinfo.cpp \
    IHM/Tabs/OneShotTabs/oneshotresultstab.cpp \
    IHM/Tabs/OneShotTabs/oneshotpagetab.cpp \
    DATAMANAGEMENT/Filter/gameeventsearchfilter.cpp \
    DATAMANAGEMENT/Filter/OneShotSearchFilter/oneshoteventsearchfilter.cpp \
    SQLDATABASE/insertrowindbworker.cpp \
    SQLDATABASE/searchrowsindbworker.cpp

HEADERS  += IHM/MainWindow/mainwindow.h \
    IHM/MainWindow/mainwindowtitles.h \
    IHM/MainWindow/mainwindowimages.h \
    IHM/MainWindow/mainwindowgeometry.h \
    IHM/Tabs/OneShotTabs/oneshotsearchtab.h \
    IHM/TreeWidgets/citiesselectiontreewidget.h \
    IHM/TreeWidgets/citiesselectiontreewidgettitles.h \
    IHM/Dialogs/oneshotcreatedialog.h \
    IHM/TreeWidgets/multicitiesselectiontreewidget.h \
    IHM/TreeWidgets/onecityselectiontreewidget.h \
    DATAMANAGEMENT/Info/gameeventinfo.h \
    DATAMANAGEMENT/Info/OneShotInfo/oneshoteventinfo.h \
    DATAMANAGEMENT/Info/OneShotInfo/oneshoteventinfotitles.h \
    IHM/Dialogs/oneshotcreatedialogtitles.h \
    IHM/Tabs/OneShotTabs/oneshotresultstab.h \
    IHM/Tabs/OneShotTabs/oneshotresultstabstorage.h \
    IHM/Tabs/OneShotTabs/oneshotresultstabgeometry.h \
    IHM/Tabs/OneShotTabs/oneshotresultstabtitles.h \
    IHM/Tabs/OneShotTabs/oneshotpagetab.h \
    IHM/Tabs/OneShotTabs/oneshotpagetabtitles.h \
    DATAMANAGEMENT/Filter/gameeventsearchfilter.h \
    DATAMANAGEMENT/Filter/OneShotSearchFilter/oneshoteventsearchfilter.h \
    SQLDATABASE/insertrowindbworker.h \
    SQLDATABASE/databaseaccess.h \
    SQLDATABASE/searchrowsindbworker.h

FORMS    += IHM/MainWindow/mainwindow.ui \
    IHM/Tabs/OneShotTabs/oneshotsearchtab.ui \
    IHM/Dialogs/oneshotcreatedialog.ui \
    IHM/Tabs/OneShotTabs/oneshotresultstab.ui \
    IHM/Tabs/OneShotTabs/oneshotpagetab.ui


RESOURCES += IHM/images/resource_images.qrc \
    IHM/texts/resource_texts.qrc

RC_FILE = resource.rc

