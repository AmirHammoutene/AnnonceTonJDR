#ifndef ONESHOTEVENTINFO_H
#define ONESHOTEVENTINFO_H

/*
* Class for game information about One Shot.
*/

#include "gameeventinfo.h"
#include <QPair>
#include <QMetaType>

enum class GameEditionType {
    COMMERCIAL,
    AMATEUR,
    PERSONAL,
    UNDEFINED
};

enum class ScriptSourceType {
    COMMERCIAL,
    WEB,
    PERSONAL,
    UNDEFINED
};

enum class DrinkFoodPermission {
    BRING,
    FORBIDDEN,
    NEVERMIND
};

enum class AlcoholPermission {
    BRING,
    FORBIDDEN,
    NEVERMIND
};

enum class SmokeInsidePermission {
    PERMITTED,
    FORBIDDEN
};

enum class PlaceType {
    HOME,
    BAR,
    ROOM,
    OUTSIDE
};



class OneShotEventInfo : public GameEventInfo
{

protected:
    QDateTime m_eventDateTime; //When will the game take place
    bool m_specialEvent; //The game is a special event or not
    bool m_severalGameMasters; //How many persons will master the game
    GameEditionType m_gameEditionType; //What type of edition is the game
    QString m_gameName; //The game has a name
    bool m_severalGames; //One or multiple games for this annonce
    ScriptSourceType m_scriptSourceType; //Source of the script
    QString m_scriptName; //Name of the script
    bool m_severalSessions; //That game will be played in one or multiple sessions
    DrinkFoodPermission m_drinkFoodPermission; //Permissions for drink and food
    AlcoholPermission m_alcoholPermission; //Permissions for alcohol
    SmokeInsidePermission m_smokeInsidePermission; //Permissions for cigarettes
    PlaceType m_placeType; //Type of place where will be played the game
    QString m_comments; //Comments by the annoncer

public:
    OneShotEventInfo();
    OneShotEventInfo(const OneShotEventInfo &other);
    virtual ~OneShotEventInfo(){}

    void initiate() override; // set default values.
    QPair<bool,QString> verifyDataNotEmpty(); // Which data has not been correctly filled

    const QDateTime & eventDateTime() const { return m_eventDateTime; }
    void setEventDateTime(const QDateTime &eventDateTime) {  m_eventDateTime = eventDateTime; }

    bool specialEvent() const  {  return m_specialEvent; }
    void setSpecialEvent(bool specialEvent) {  m_specialEvent = specialEvent; }

    bool severalGameMasters() const { return m_severalGameMasters; }
    void setSeveralGameMasters(bool severalGameMasters) { m_severalGameMasters = severalGameMasters; }

    GameEditionType gameEditionType() const { return m_gameEditionType; }
    void setGameEditionType(const GameEditionType &gameEditionType) {  m_gameEditionType = gameEditionType; }

    const QString & gameName() const { return m_gameName; }
    void setGameName(const QString &gameName) { m_gameName = gameName;  }

    bool severalGames() const { return m_severalGames; }
    void setSeveralGames(bool severalGames) { m_severalGames = severalGames; }

    ScriptSourceType scriptSourceType() const  {  return m_scriptSourceType; }
    void setScriptSourceType(const ScriptSourceType &scriptSourceType) { m_scriptSourceType = scriptSourceType; }

    const QString &  scriptName() const { return m_scriptName; }
    void setScriptName(const QString &scriptName) { m_scriptName = scriptName; }

    bool severalSessions() const { return m_severalSessions; }
    void setSeveralSessions(bool severalSessions) { m_severalSessions = severalSessions; }

    DrinkFoodPermission drinkFoodPermission() const { return m_drinkFoodPermission; }
    void setDrinkFoodPermission(const DrinkFoodPermission &drinkFoodPermission)  { m_drinkFoodPermission = drinkFoodPermission; }

    AlcoholPermission alcoholPermission() const { return m_alcoholPermission; }
    void setAlcoholPermission(const AlcoholPermission &alcoholPermission) {  m_alcoholPermission = alcoholPermission; }

    SmokeInsidePermission smokeInsidePermission() const { return m_smokeInsidePermission; }
    void setSmokeInsidePermission(const SmokeInsidePermission &smokeInsidePermission) { m_smokeInsidePermission = smokeInsidePermission; }

    PlaceType placeType() const { return m_placeType; }
    void setPlaceType(const PlaceType &placeType) { m_placeType = placeType; }

    const QString & comments() const { return m_comments;}
    void setComments(const QString &comments){ m_comments = comments;}



    QString gameEditionTypeString();
    QString scriptSourceTypeString();
    QString placeTypeString();
};


Q_DECLARE_METATYPE(OneShotEventInfo);

#endif // ONESHOTEVENTINFO_H
