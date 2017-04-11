#ifndef SEARCHROWSINDBWORKER_H
#define SEARCHROWSINDBWORKER_H

/*
* Worker to search entries in the database
* An instance is created each time we try to search, and deleted after the work is done
*/

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "oneshoteventsearchfilter.h"
#include "oneshoteventinfo.h"

class SearchRowsInDBWorker : public QObject
{
    Q_OBJECT

private:
    OneShotEventSearchFilter searchFilter;
    QSqlDatabase dataBase;
public:
    SearchRowsInDBWorker();
    ~SearchRowsInDBWorker(){}
    void setSearchFilter(const OneShotEventSearchFilter & filter){ searchFilter = filter;}
    OneShotEventInfo getEventInfoFromQuery(const QSqlQuery & query);

signals:
    void finished();
    void sendInfo(OneShotEventInfo);

public slots:
    void process();
};

#endif // SEARCHROWSINDBWORKER_H
