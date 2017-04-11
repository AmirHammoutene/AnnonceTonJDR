#ifndef INSERTROWINDBWORKER_H
#define INSERTROWINDBWORKER_H

/*
* Worker to add a row in the database
* An instance is created each time we try to add an entry, and deleted after the work is done
* It removes old entry and add another one in the case of edition
*/

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QPair>

#include "oneshoteventinfo.h"
class InsertRowInDBWorker : public QObject
{
    Q_OBJECT

private:
    OneShotEventInfo oldEventInfo;
    OneShotEventInfo eventInfo;
    QSqlDatabase dataBase;
public:
    InsertRowInDBWorker();
    ~InsertRowInDBWorker(){}
    void setEventInfo(const OneShotEventInfo & info){ eventInfo = info;}
    void setOldEventInfo(const OneShotEventInfo & oldinfo){ oldEventInfo = oldinfo;}
    QPair<bool, QString> runQuery();
    void removeOldEntry();

public slots:
    void process();

signals:
    void finished();
    void success(bool, QString);

};

#endif // INSERTROWINDBWORKER_H
