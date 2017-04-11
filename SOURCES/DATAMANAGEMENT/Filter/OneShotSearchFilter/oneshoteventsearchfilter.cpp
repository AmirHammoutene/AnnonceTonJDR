#include "oneshoteventsearchfilter.h"
#include <QSettings>
#include <QDebug>

OneShotEventSearchFilter::OneShotEventSearchFilter()
{
    initiate();
}

OneShotEventSearchFilter::OneShotEventSearchFilter(const OneShotEventSearchFilter &other)
{
    setUserNameFilter(other.userNameFilter());
    setUserSexeFilter(other.userSexeFilter());
    setMinimumUserAgeFilter(other.minimumUserAgeFilter());
    setMaximumUserAgeFilter(other.maximumUserAgeFilter());
    setPermissionUnderagesFilter(other.permissionUnderagesFilter());
    setShowFullGameFilter(other.showFullGameFilter());
    setShowCancelledGameFilter(other.showCancelledGameFilter());
    setNearCitiesFilter(other.nearCitiesFilter());
    setFromDateTimeFilter(other.fromDateTimeFilter());
    setToDateTimeFilter(other.toDateTimeFilter());
    setDateSearchFilter(other.dateSearchFilter());
    setEventTypeFilter(other.eventTypeFilter());
    setGameNameFilter(other.gameNameFilter());
    setNumberGameMastersFilter(other.numberGameMastersFilter());
    setNumberGamesFilter(other.numberGamesFilter());
    setNumberSessionsFilter(other.numberSessionsFilter());
    setDrinkFoodPermissionFilter(other.drinkFoodPermissionFilter());
    setAlcoholPermissionFilter(other.alcoholPermissionFilter());
    setSmokeInsidePermissionFilter(other.smokeInsidePermissionFilter());
    setPlaceTypeFilter(other.placeTypeFilter());
    setShowGameCommercial(other.showGameCommercial());
    setShowGameAmateur(other.showGameAmateur());
    setShowGamePersonal(other.showGamePersonal());
    setShowScriptCommercial(other.showScriptCommercial());
    setShowScriptWeb(other.showScriptWeb());
    setShowScriptPersonal(other.showScriptPersonal());
}

void OneShotEventSearchFilter::initiate()
{
    setUserNameFilter("");
    setUserSexeFilter(SexeFilter::NEVERMIND);
    setMinimumUserAgeFilter(0);
    setMaximumUserAgeFilter(122);
    setPermissionUnderagesFilter(PermissionUnderagesFilter::NEVERMIND);
    setShowFullGameFilter(true);
    setShowCancelledGameFilter(true);
    setNearCitiesFilter(getAllCities());
    setFromDateTimeFilter(QDateTime::currentDateTime());
    setToDateTimeFilter(QDateTime::currentDateTime().addSecs(3600));
    setDateSearchFilter(DateSearchFilter::FUTUR);
    setEventTypeFilter(EventTypeFilter::NEVERMIND);
    setGameNameFilter("");
    setNumberGameMastersFilter(NumberGameMastersFilter::NEVERMIND);
    setNumberGamesFilter(NumberGamesFilter::NEVERMIND);
    setNumberSessionsFilter(NumberSessionsFilter::NEVERMIND);
    setDrinkFoodPermissionFilter(DrinkFoodPermissionFilter::NEVERMIND);
    setAlcoholPermissionFilter(AlcoholPermissionFilter::NEVERMIND);
    setSmokeInsidePermissionFilter(SmokeInsidePermissionFilter::NEVERMIND);
    setPlaceTypeFilter(PlaceTypeFilter::NEVERMIND);
    setShowGameCommercial(true);
    setShowGameAmateur(true);
    setShowGamePersonal(true);
    setShowScriptCommercial(true);
    setShowScriptWeb(true);
    setShowScriptPersonal(true);
}

QStringList OneShotEventSearchFilter::getAllCities()
{
    QStringList returnList;

    QSettings iniFile(":/listOfCities.ini", QSettings::IniFormat);
    QStringList regions = iniFile.allKeys();
    for(QString currentRegion : regions)
    {
        returnList.append(iniFile.value(currentRegion,QStringList()).toStringList());
    }
    return returnList;
}

bool OneShotEventSearchFilter::matchInfo(OneShotEventInfo info)
{

    if(!userNameFilter().isEmpty())
    {
        if(!info.userName().contains(userNameFilter(),Qt::CaseInsensitive))
            return false;
    }

    if(userSexeFilter() != SexeFilter::NEVERMIND)
    {
        if(info.userSexe() != Sexe::UNDEFINED)
        {
            if(info.userSexe() == Sexe::WOMAN && userSexeFilter() != SexeFilter::WOMAN)
                return false;
            if(info.userSexe() == Sexe::MAN && userSexeFilter() != SexeFilter::MAN)
                return false;
        }
    }

    if(info.shareUserAge())
    {
        if(minimumUserAgeFilter() > info.userAge() ||  maximumUserAgeFilter() < info.userAge() )
            return false;
    }

    if(permissionUnderagesFilter() != PermissionUnderagesFilter::NEVERMIND)
    {
        if(permissionUnderagesFilter() == PermissionUnderagesFilter::YES && !info.permittedUnderages())
            return false;
        if(permissionUnderagesFilter() == PermissionUnderagesFilter::NO && info.registeredUnderages())
            return false;
    }

    if(!showFullGameFilter() && info.fullGame())
        return false;

    if(!showCancelledGameFilter() && info.cancelledGame())
        return false;

    if(!nearCitiesFilter().contains(info.nearCity()))
        return false;

    if(dateSearchFilter() == DateSearchFilter::FUTUR && info.eventDateTime() < QDateTime::currentDateTime())
        return false;

    if(dateSearchFilter() == DateSearchFilter::PAST && info.eventDateTime() > QDateTime::currentDateTime())
        return false;

    if(dateSearchFilter() == DateSearchFilter::CHOOSE)
    {
        if(info.eventDateTime() < fromDateTimeFilter() || info.eventDateTime() > toDateTimeFilter())
            return false;
    }

    if(eventTypeFilter() != EventTypeFilter::NEVERMIND)
    {
        if(info.specialEvent() && eventTypeFilter() != EventTypeFilter::SPECIAL)
                return false;
        if(!info.specialEvent() && eventTypeFilter() != EventTypeFilter::NORMAL)
                return false;
    }

    if(!gameNameFilter().isEmpty())
    {
        if(!info.gameName().contains(gameNameFilter(),Qt::CaseInsensitive))
            return false;
    }

    if(numberGameMastersFilter() != NumberGameMastersFilter::NEVERMIND)
    {
        if( !info.severalGameMasters() && numberGameMastersFilter() != NumberGameMastersFilter::ONE)
                return false;
        if(info.severalGameMasters() && numberGameMastersFilter() != NumberGameMastersFilter::SEVERAL)
                return false;
    }

    if(numberGamesFilter() != NumberGamesFilter::NEVERMIND)
    {
        if( !info.severalGames() && numberGamesFilter() != NumberGamesFilter::ONE)
                return false;
        if(info.severalGames() && numberGamesFilter() != NumberGamesFilter::SEVERAL)
                return false;
    }

    if(numberSessionsFilter() != NumberSessionsFilter::NEVERMIND)
    {
        if( !info.severalSessions() && numberSessionsFilter() != NumberSessionsFilter::ONE)
                return false;
        if(info.severalSessions() && numberSessionsFilter() != NumberSessionsFilter::SEVERAL)
                return false;
    }

    if(drinkFoodPermissionFilter() != DrinkFoodPermissionFilter::NEVERMIND)
    {
        // If Nevermind, Bring and Nevermind filters are accepted
        if(info.drinkFoodPermission() == DrinkFoodPermission::NEVERMIND && drinkFoodPermissionFilter() == DrinkFoodPermissionFilter::FORBIDDEN )
            return false;
        // If Bring, Bring and Nevermind filters are accepted
        if(info.drinkFoodPermission() == DrinkFoodPermission::BRING && drinkFoodPermissionFilter() == DrinkFoodPermissionFilter::FORBIDDEN )
            return false;
        // If Forbidden, Forbidden and Nevermind filters are accepted
        if(info.drinkFoodPermission() == DrinkFoodPermission::FORBIDDEN && drinkFoodPermissionFilter() == DrinkFoodPermissionFilter::BRING )
            return false;
    }

    if(alcoholPermissionFilter() != AlcoholPermissionFilter::NEVERMIND)
    {
        // If Nevermind, Bring and Nevermind filters are accepted
        if(info.alcoholPermission() == AlcoholPermission::NEVERMIND && alcoholPermissionFilter() == AlcoholPermissionFilter::FORBIDDEN )
            return false;
        // If Bring, Bring and Nevermind filters are accepted
        if(info.alcoholPermission() == AlcoholPermission::BRING && alcoholPermissionFilter() == AlcoholPermissionFilter::FORBIDDEN )
            return false;
        // If Forbidden, Forbidden and Nevermind filters are accepted
        if(info.alcoholPermission() == AlcoholPermission::FORBIDDEN && alcoholPermissionFilter() == AlcoholPermissionFilter::BRING )
            return false;
    }

    if(smokeInsidePermissionFilter() != SmokeInsidePermissionFilter::NEVERMIND)
    {
        // If Permitted, Nevermind and Permitted filters are accepted
        if( info.smokeInsidePermission() == SmokeInsidePermission::PERMITTED && smokeInsidePermissionFilter() == SmokeInsidePermissionFilter::FORBIDDEN)
                return false;
        // If Forbidden, Nevermind and Forbidden filters are accepted
        if( info.smokeInsidePermission() == SmokeInsidePermission::FORBIDDEN && smokeInsidePermissionFilter() == SmokeInsidePermissionFilter::PERMITTED)
                return false;
    }

    if(placeTypeFilter() != PlaceTypeFilter::NEVERMIND)
    {
        if(info.placeType() == PlaceType::HOME && placeTypeFilter() != PlaceTypeFilter::HOME)
            return false;
        if(info.placeType() == PlaceType::BAR && placeTypeFilter() != PlaceTypeFilter::BAR)
            return false;
        if(info.placeType() == PlaceType::ROOM && placeTypeFilter() != PlaceTypeFilter::ROOM)
            return false;
        if(info.placeType() == PlaceType::OUTSIDE && placeTypeFilter() != PlaceTypeFilter::OUTSIDE)
            return false;
    }

    if(!showGameCommercial() && info.gameEditionType() == GameEditionType::COMMERCIAL)
        return false;
    if(!showGameAmateur() && info.gameEditionType() == GameEditionType::AMATEUR)
        return false;
    if(!showGamePersonal() && info.gameEditionType() == GameEditionType::PERSONAL)
        return false;
    if(!showScriptCommercial() && info.scriptSourceType() == ScriptSourceType::COMMERCIAL)
        return false;
    if(!showScriptWeb() && info.scriptSourceType() == ScriptSourceType::WEB)
        return false;
    if(!showScriptPersonal() && info.scriptSourceType() == ScriptSourceType::PERSONAL)
        return false;

    return true;
}
