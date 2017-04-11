#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "oneshoteventinfo.h"
#include "oneshoteventsearchfilter.h"
/*
* Amir Hammoutene (amir.hammoutene@gmail.com), February 2017
*
* Qt application, Qt 5.8 has been used for this project.
* 3 principal folders :
* IHM/	widgets and gui componants
* DATAMANAGEMENT/	classes that manage information
* SQLDATABASE/	communication interface
*/

int main(int argc, char *argv[])
{
	// Defines Text Codec for all the application
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
	
	// MetaType usefull for signals/slots
    qRegisterMetaType<OneShotEventInfo>();
    qRegisterMetaType< QList<OneShotEventInfo> >();
    qRegisterMetaType<OneShotEventSearchFilter>();
    qRegisterMetaType< QList<OneShotEventSearchFilter> >();    
    
	a.setWindowIcon(QIcon(":/icon.png"));
    
	MainWindow w;
    w.show();

    return a.exec();
}
