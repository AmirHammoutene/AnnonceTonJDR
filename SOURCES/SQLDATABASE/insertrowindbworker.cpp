#include "insertrowindbworker.h"
#include "databaseaccess.h"
#include <QVariant>
#include <QDebug>
#include <QSqlError>

InsertRowInDBWorker::InsertRowInDBWorker() : QObject()
{
    eventInfo = OneShotEventInfo();
}

QPair<bool, QString> InsertRowInDBWorker::runQuery()
{
    QSqlQuery query(dataBase);
    query.prepare("INSERT INTO "+DatabaseAccess::tableName+" (creationDateTime, eventDateTime, userName, password, "
                  "userSexe, userAge, shareUserAge, registeredPlayersNumber, maximumPlayersNumber, registeredUnderages, "
                  "fullGame, cancelledGame, specialEvent, gameName, gameEditionType, severalGames, severalGameMasters, scriptName, "
                  "scriptEditionType, severalSessions, realAddress, nearCity, placeType, permittedUnderages, drinkFoodPermission, "
                  "alcoholPermission, smokeInsidePermission, phoneNumber, email, facebook, forumThreadTitle, considerForumThread, comments) "
                  "VALUES (:creationDateTime, :eventDateTime, :userName, :password, "
                   ":userSexe, :userAge, :shareUserAge, :registeredPlayersNumber, :maximumPlayersNumber, :registeredUnderages, "
                   ":fullGame, :cancelledGame, :specialEvent, :gameName, :gameEditionType, :severalGames, :severalGameMasters, :scriptName, "
                   ":scriptEditionType, :severalSessions, :realAddress, :nearCity, :placeType, :permittedUnderages, :drinkFoodPermission, "
                   ":alcoholPermission, :smokeInsidePermission, :phoneNumber, :email, :facebook, :forumThreadTitle, :considerForumThread, :comments)");

    query.bindValue(":creationDateTime", eventInfo.creationDateTime().toString("yyyy-MM-dd hh:mm:00") );
    query.bindValue(":eventDateTime", eventInfo.eventDateTime().toString("yyyy-MM-dd hh:mm:00"));
    query.bindValue(":userName", eventInfo.userName());
    query.bindValue(":password", eventInfo.password());
    query.bindValue(":userAge", eventInfo.userAge());
    query.bindValue(":shareUserAge", eventInfo.shareUserAge());
    query.bindValue(":registeredPlayersNumber", eventInfo.registeredPlayersNumber());
    query.bindValue(":maximumPlayersNumber", eventInfo.maximumPlayersNumber());
    query.bindValue(":registeredUnderages", eventInfo.registeredUnderages());
    query.bindValue(":fullGame", eventInfo.fullGame());
    query.bindValue(":cancelledGame", eventInfo.cancelledGame());
    query.bindValue(":specialEvent", eventInfo.specialEvent());
    query.bindValue(":gameName", eventInfo.gameName());
    query.bindValue(":severalGames", eventInfo.severalGames());
    query.bindValue(":severalGameMasters", eventInfo.severalGameMasters());
    query.bindValue(":scriptName", eventInfo.scriptName());
    query.bindValue(":severalSessions", eventInfo.severalSessions());
    query.bindValue(":realAddress", eventInfo.realAddress());
    query.bindValue(":nearCity", eventInfo.nearCity());
    query.bindValue(":permittedUnderages", eventInfo.permittedUnderages());
    query.bindValue(":phoneNumber", eventInfo.phoneNumber());
    query.bindValue(":email", eventInfo.email());
    query.bindValue(":facebook", eventInfo.facebook());
    query.bindValue(":forumThreadTitle", eventInfo.forumThreadTitle());
    query.bindValue(":considerForumThread", eventInfo.considerForumThread());
    query.bindValue(":comments", eventInfo.comments());

    unsigned int userSexeValue;
    switch (eventInfo.userSexe()) {
    case Sexe::WOMAN:
        userSexeValue = 1;
        break;
    case Sexe::MAN:
        userSexeValue = 2;
        break;
    default:
        userSexeValue = 0;
        break;
    }
    query.bindValue(":userSexe", userSexeValue);

    unsigned int gameEditionTypeValue;
    switch (eventInfo.gameEditionType()) {
    case GameEditionType::COMMERCIAL:
        gameEditionTypeValue = 1;
        break;
    case GameEditionType::AMATEUR:
        gameEditionTypeValue = 2;
        break;
    case GameEditionType::PERSONAL:
        gameEditionTypeValue = 3;
        break;
    default:
        gameEditionTypeValue = 0;
        break;
    }
    query.bindValue(":gameEditionType", gameEditionTypeValue);

    unsigned int scriptEditionTypeValue;
    switch (eventInfo.scriptSourceType()) {
    case ScriptSourceType::COMMERCIAL:
        scriptEditionTypeValue = 1;
        break;
    case ScriptSourceType::WEB:
        scriptEditionTypeValue = 2;
        break;
    case ScriptSourceType::PERSONAL:
        scriptEditionTypeValue = 3;
        break;
    default:
        scriptEditionTypeValue = 0;
        break;
    }
    query.bindValue(":scriptEditionType", scriptEditionTypeValue);

    unsigned int placeTypeValue;
    switch (eventInfo.placeType()) {
    case PlaceType::HOME:
        placeTypeValue = 1;
        break;
    case PlaceType::BAR:
        placeTypeValue = 2;
        break;
    case PlaceType::ROOM:
        placeTypeValue = 3;
        break;
    case PlaceType::OUTSIDE:
        placeTypeValue = 4;
        break;
    default:
        placeTypeValue = 0;
        break;
    }
    query.bindValue(":placeType", placeTypeValue);

    unsigned int drinkFoodPermissionValue;
    switch (eventInfo.drinkFoodPermission()) {
    case DrinkFoodPermission::NEVERMIND:
        drinkFoodPermissionValue = 1;
        break;
    case DrinkFoodPermission::BRING:
        drinkFoodPermissionValue = 2;
        break;
    default:
        drinkFoodPermissionValue = 0;
        break;
    }
    query.bindValue(":drinkFoodPermission", drinkFoodPermissionValue);

    unsigned int alcoholPermissionValue;
    switch (eventInfo.alcoholPermission()) {
    case AlcoholPermission::NEVERMIND:
        alcoholPermissionValue = 1;
        break;
    case AlcoholPermission::BRING:
        alcoholPermissionValue = 2;
        break;
    default:
        alcoholPermissionValue = 0;
        break;
    }
    query.bindValue(":alcoholPermission", alcoholPermissionValue);

    unsigned int smokeInsidePermissionValue;
    switch (eventInfo.smokeInsidePermission()) {
    case SmokeInsidePermission::PERMITTED:
        smokeInsidePermissionValue = 1;
        break;
    default:
        smokeInsidePermissionValue = 0;
        break;
    }
    query.bindValue(":smokeInsidePermission", smokeInsidePermissionValue);


    bool success = query.exec();
    QString text = query.lastError().text();

    return QPair<bool, QString>(success,text);
}

void InsertRowInDBWorker::removeOldEntry()
{
    QSqlQuery selectQuery(dataBase);
    selectQuery.prepare("SELECT id FROM "+DatabaseAccess::tableName+" WHERE eventDateTime = :eventDateTime "
                        "AND userName = :userName AND gameName = :gameName AND scriptName = :scriptName");

    selectQuery.bindValue(":eventDateTime", oldEventInfo.eventDateTime().toString("yyyy-MM-dd hh:mm:00"));
    selectQuery.bindValue(":userName", oldEventInfo.userName());
    selectQuery.bindValue(":gameName", oldEventInfo.gameName());
    selectQuery.bindValue(":scriptName", oldEventInfo.scriptName());

    selectQuery.exec();

    int id = -1;

    while (selectQuery.next())
    {
        id = selectQuery.value(0).toInt();
    }

    QSqlQuery deleteQuery(dataBase);
    deleteQuery.prepare("DELETE FROM "+DatabaseAccess::tableName+" WHERE id = :id");
    deleteQuery.bindValue(":id",id);

    deleteQuery.exec();
}


void InsertRowInDBWorker::process()
{
    dataBase = QSqlDatabase::addDatabase("QMYSQL");
    dataBase.setHostName(DatabaseAccess::server);
    dataBase.setDatabaseName(DatabaseAccess::name);
    dataBase.setUserName(DatabaseAccess::username);
    dataBase.setPassword(DatabaseAccess::password);

    if(!dataBase.open())
    {
        emit success(false, dataBase.lastError().text());
        emit finished();
        return;
    }

    if(oldEventInfo.userName().size() > 0)
    {// If the old userName is not empty, it means that it has been edited before
        removeOldEntry();
    }

    QPair<bool, QString> successBoolString = runQuery();

    dataBase.close();

    emit success(successBoolString.first,successBoolString.second);
    emit finished();

}
