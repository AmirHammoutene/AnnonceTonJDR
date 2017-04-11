#ifndef ONESHOTEVENTSEARCHFILTER_H
#define ONESHOTEVENTSEARCHFILTER_H

/*
* Class for all search information about One Shot Games.
* Those informations are used for search filters
*/

#include "gameeventsearchfilter.h"
#include "oneshoteventinfo.h"

#include <QMetaType>

enum class EventTypeFilter {
    NORMAL,
    SPECIAL,
    NEVERMIND
};

enum class NumberGameMastersFilter {
    ONE,
    SEVERAL,
    NEVERMIND
};


enum class NumberGamesFilter {
    ONE,
    SEVERAL,
    NEVERMIND
};

enum class NumberSessionsFilter {
    ONE,
    SEVERAL,
    NEVERMIND
};

enum class DrinkFoodPermissionFilter {
    BRING,
    FORBIDDEN,
    NEVERMIND
};

enum class AlcoholPermissionFilter {
    BRING,
    FORBIDDEN,
    NEVERMIND
};

enum class SmokeInsidePermissionFilter {
    PERMITTED,
    FORBIDDEN,
    NEVERMIND
};

enum class PlaceTypeFilter {
    HOME,
    BAR,
    ROOM,
    OUTSIDE,
    NEVERMIND
};

enum class DateSearchFilter {
    PAST,
    FUTUR,
    CHOOSE
};

class OneShotEventSearchFilter : public GameEventSearchFilter
{
protected:
    QDateTime m_fromDateTimeFilter; //The search will be limited to a beginning date
    QDateTime m_toDateTimeFilter; //The search will be limited to a last date
    DateSearchFilter m_dateSearchFilter; //The search will use from and to dateTimeFilters or will simply look in the past or the future from now
    EventTypeFilter m_eventTypeFilter; //The game is a special event or not
    QString m_gameNameFilter; //The game has a name
    NumberGameMastersFilter m_numberGameMastersFilter; //How many persons will master the game
    NumberGamesFilter m_numberGamesFilter; //One or multiple games
    NumberSessionsFilter m_numberSessionsFilter; //That game will be played in one or multiple sessions
    DrinkFoodPermissionFilter m_drinkFoodPermissionFilter; //Permissions for drink and food
    AlcoholPermissionFilter m_alcoholPermissionFilter; //Permissions for alcohol
    SmokeInsidePermissionFilter m_smokeInsidePermissionFilter; //Permissions for cigarettes
    PlaceTypeFilter m_placeTypeFilter; //Type of place where will be played the game
    bool m_showGameCommercial; //Show commercial games
    bool m_showGameAmateur; //Show amateur games
    bool m_showGamePersonal; //Show personnal games
    bool m_showScriptCommercial; //Show commercial scripts
    bool m_showScriptWeb; //Show web scripts
    bool m_showScriptPersonal; //Show personnal scripts

public:
    OneShotEventSearchFilter();
    OneShotEventSearchFilter(const OneShotEventSearchFilter &other);
    virtual ~OneShotEventSearchFilter(){}

    void initiate() override; // set default values.
    QStringList getAllCities(); // returns the list of cities written in the ini file

    const QDateTime & fromDateTimeFilter() const { return m_fromDateTimeFilter; }
    void setFromDateTimeFilter(const QDateTime &fromDateTimeFilter) { m_fromDateTimeFilter = fromDateTimeFilter; }

    const QDateTime & toDateTimeFilter() const { return m_toDateTimeFilter; }
    void setToDateTimeFilter(const QDateTime &toDateTimeFilter) { m_toDateTimeFilter = toDateTimeFilter; }

    DateSearchFilter dateSearchFilter() const { return m_dateSearchFilter; }
    void setDateSearchFilter(const DateSearchFilter &dateSearchFilter) { m_dateSearchFilter = dateSearchFilter; }

    EventTypeFilter eventTypeFilter() const { return m_eventTypeFilter; }
    void setEventTypeFilter(const EventTypeFilter &eventTypeFilter) { m_eventTypeFilter = eventTypeFilter; }

    const QString & gameNameFilter() const { return m_gameNameFilter; }
    void setGameNameFilter(const QString &gameNameFilter) { m_gameNameFilter = gameNameFilter; }

    NumberGameMastersFilter numberGameMastersFilter() const { return m_numberGameMastersFilter; }
    void setNumberGameMastersFilter(const NumberGameMastersFilter &numberGameMastersFilter) { m_numberGameMastersFilter = numberGameMastersFilter; }

    NumberGamesFilter numberGamesFilter() const { return m_numberGamesFilter; }
    void setNumberGamesFilter(const NumberGamesFilter &numberGamesFilter) { m_numberGamesFilter = numberGamesFilter; }

    NumberSessionsFilter numberSessionsFilter() const { return m_numberSessionsFilter; }
    void setNumberSessionsFilter(const NumberSessionsFilter &numberSessionsFilter) { m_numberSessionsFilter = numberSessionsFilter; }

    DrinkFoodPermissionFilter drinkFoodPermissionFilter() const { return m_drinkFoodPermissionFilter; }
    void setDrinkFoodPermissionFilter(const DrinkFoodPermissionFilter &drinkFoodPermissionFilter) { m_drinkFoodPermissionFilter = drinkFoodPermissionFilter; }

    AlcoholPermissionFilter alcoholPermissionFilter() const { return m_alcoholPermissionFilter; }
    void setAlcoholPermissionFilter(const AlcoholPermissionFilter &alcoholPermissionFilter) { m_alcoholPermissionFilter = alcoholPermissionFilter; }

    SmokeInsidePermissionFilter smokeInsidePermissionFilter() const { return m_smokeInsidePermissionFilter; }
    void setSmokeInsidePermissionFilter(const SmokeInsidePermissionFilter &smokeInsidePermissionFilter) { m_smokeInsidePermissionFilter = smokeInsidePermissionFilter; }

    PlaceTypeFilter placeTypeFilter() const { return m_placeTypeFilter; }
    void setPlaceTypeFilter(const PlaceTypeFilter &placeTypeFilter) { m_placeTypeFilter = placeTypeFilter; }

    bool showGameCommercial() const { return m_showGameCommercial; }
    void setShowGameCommercial(bool showGameCommercial) { m_showGameCommercial = showGameCommercial; }

    bool showGameAmateur() const { return m_showGameAmateur; }
    void setShowGameAmateur(bool showGameAmateur) { m_showGameAmateur = showGameAmateur; }

    bool showGamePersonal() const { return m_showGamePersonal; }
    void setShowGamePersonal(bool showGamePersonal) { m_showGamePersonal = showGamePersonal; }

    bool showScriptCommercial() const { return m_showScriptCommercial; }
    void setShowScriptCommercial(bool showScriptCommercial) { m_showScriptCommercial = showScriptCommercial; }

    bool showScriptWeb() const { return m_showScriptWeb; }
    void setShowScriptWeb(bool showScriptWeb) { m_showScriptWeb = showScriptWeb; }

    bool showScriptPersonal() const { return m_showScriptPersonal; }
    void setShowScriptPersonal(bool showScriptPersonal) { m_showScriptPersonal = showScriptPersonal; }

    bool matchInfo(OneShotEventInfo info); //Does the filters of that search matches with some game information
};

Q_DECLARE_METATYPE(OneShotEventSearchFilter);

#endif // ONESHOTEVENTSEARCHFILTER_H
