#include "searchrowsindbworker.h"
#include "databaseaccess.h"

#include <QDebug>

SearchRowsInDBWorker::SearchRowsInDBWorker() : QObject()
{
    searchFilter = OneShotEventSearchFilter();

}

OneShotEventInfo SearchRowsInDBWorker::getEventInfoFromQuery(const QSqlQuery &query)
{
    OneShotEventInfo info;
    info.setCreationDateTime(query.value(1).toDateTime());
    info.setEventDateTime(query.value(2).toDateTime());
    info.setUserName(query.value(3).toString());
    info.setPassword(query.value(4).toString());
    info.setUserAge(query.value(6).toInt());
    info.setShareUserAge(query.value(7).toBool());
    info.setRegisteredPlayersNumber(query.value(8).toInt());
    info.setMaximumPlayersNumber(query.value(9).toInt());
    info.setRegisteredUnderages(query.value(10).toBool());
    info.setFullGame(query.value(11).toBool());
    info.setCancelledGame(query.value(12).toBool());
    info.setSpecialEvent(query.value(13).toBool());
    info.setGameName(query.value(14).toString());
    info.setSeveralGames(query.value(16).toBool());
    info.setSeveralGameMasters(query.value(17).toBool());
    info.setScriptName(query.value(18).toString());
    info.setSeveralSessions(query.value(20).toBool());
    info.setRealAddress(query.value(21).toString());
    info.setNearCity(query.value(22).toString());
    info.setPermittedUnderages(query.value(24).toBool());
    info.setPhoneNumber(query.value(28).toString());
    info.setEmail(query.value(29).toString());
    info.setFacebook(query.value(30).toString());
    info.setForumThreadTitle(query.value(31).toString());
    info.setConsiderForumThread(query.value(32).toBool());
    info.setComments(query.value(33).toString());

    switch (query.value(5).toInt()) {
    case 0:
        info.setUserSexe(Sexe::UNDEFINED);
        break;
    case 1:
        info.setUserSexe(Sexe::WOMAN);
        break;
    default:
        info.setUserSexe(Sexe::MAN);
        break;
    }

    switch (query.value(15).toInt()) {
    case 0:
        info.setGameEditionType(GameEditionType::UNDEFINED);
        break;
    case 1:
        info.setGameEditionType(GameEditionType::COMMERCIAL);
        break;
    case 2:
        info.setGameEditionType(GameEditionType::AMATEUR);
        break;
    default:
        info.setGameEditionType(GameEditionType::PERSONAL);
        break;
    }

    switch (query.value(19).toInt()) {
    case 0:
        info.setScriptSourceType(ScriptSourceType::UNDEFINED);
        break;
    case 1:
        info.setScriptSourceType(ScriptSourceType::COMMERCIAL);
        break;
    case 2:
        info.setScriptSourceType(ScriptSourceType::WEB);
        break;
    default:
        info.setScriptSourceType(ScriptSourceType::PERSONAL);
        break;
    }

    switch (query.value(25).toInt()) {
    case 0:
        info.setDrinkFoodPermission(DrinkFoodPermission::FORBIDDEN);
        break;
    case 1:
        info.setDrinkFoodPermission(DrinkFoodPermission::NEVERMIND);
        break;
    default:
        info.setDrinkFoodPermission(DrinkFoodPermission::BRING);
        break;
    }

    switch (query.value(26).toInt()) {
    case 0:
        info.setAlcoholPermission(AlcoholPermission::FORBIDDEN);
        break;
    case 1:
        info.setAlcoholPermission(AlcoholPermission::NEVERMIND);
        break;
    default:
        info.setAlcoholPermission(AlcoholPermission::BRING);
        break;
    }

    switch (query.value(27).toInt()) {
    case 0:
        info.setSmokeInsidePermission(SmokeInsidePermission::FORBIDDEN);
        break;
    default:
        info.setSmokeInsidePermission(SmokeInsidePermission::PERMITTED);
        break;
    }

    switch (query.value(23).toInt()) {
    case 1:
        info.setPlaceType(PlaceType::HOME);
        break;
    case 2:
        info.setPlaceType(PlaceType::BAR);
        break;
    case 3:
        info.setPlaceType(PlaceType::ROOM);
        break;
    case 4:
        info.setPlaceType(PlaceType::OUTSIDE);
        break;
    default:
        info.setPlaceType(PlaceType::HOME);
        break;
    }

    return info;
}

void SearchRowsInDBWorker::process()
{
    dataBase = QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName(DatabaseAccess::server);
    dataBase.setDatabaseName(DatabaseAccess::name);
    dataBase.setUserName(DatabaseAccess::username);
    dataBase.setPassword(DatabaseAccess::password);

    if(!dataBase.open())
    {
        emit finished();
        return;
    }

    QSqlQuery selectQuery(dataBase);
    selectQuery.prepare("SELECT * FROM "+DatabaseAccess::tableName);
    selectQuery.exec();

    while (selectQuery.next())
    {
        OneShotEventInfo oneEventInfo = getEventInfoFromQuery(selectQuery);

        if(searchFilter.matchInfo(oneEventInfo))
        {
            emit sendInfo(oneEventInfo);
        }
    }

    dataBase.close();

    emit finished();
}
