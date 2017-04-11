#include "oneshoteventinfo.h"
#include "oneshoteventinfotitles.h"

OneShotEventInfo::OneShotEventInfo():GameEventInfo()
{
    m_gameType = GameType::ONESHOT;
    initiate();
}

OneShotEventInfo::OneShotEventInfo(const OneShotEventInfo &other)
{
    setCreationDateTime(other.creationDateTime());
    setUserName(other.userName());
    setPassword(other.password());
    setMaximumPlayersNumber(other.maximumPlayersNumber());
    setRegisteredPlayersNumber(other.registeredPlayersNumber());
    setUserSexe(other.userSexe());
    setShareUserAge(other.shareUserAge());
    setUserAge(other.userAge());
    setRegisteredUnderages(other.registeredUnderages());
    setFullGame(other.fullGame());
    setCancelledGame(other.cancelledGame());
    setRealAddress(other.realAddress());
    setNearCity(other.nearCity());
    setPermittedUnderages(other.permittedUnderages());
    setPhoneNumber(other.phoneNumber());
    setEmail(other.email());
    setFacebook(other.facebook());
    setForumThreadTitle(other.forumThreadTitle());
    setConsiderForumThread(other.considerForumThread());
    setEventDateTime(other.eventDateTime());
    setSpecialEvent(other.specialEvent());
    setSeveralGameMasters(other.severalGameMasters());
    setGameEditionType(other.gameEditionType());
    setGameName(other.gameName());
    setSeveralGames(other.severalGames());
    setScriptSourceType(other.scriptSourceType());
    setScriptName(other.scriptName());
    setSeveralSessions(other.severalSessions());
    setDrinkFoodPermission(other.drinkFoodPermission());
    setAlcoholPermission(other.alcoholPermission());
    setSmokeInsidePermission(other.smokeInsidePermission());
    setPlaceType(other.placeType());
    setComments(other.comments());
}

void OneShotEventInfo::initiate()
{
    // Members are initiated as the Qt widget values are at first print
    // See IHM/Dialogs/oneshotcreatedialog.ui

    setCreationDateTime(QDateTime::currentDateTime());
    setUserName("");
    setPassword("");
    setMaximumPlayersNumber(5);
    setRegisteredPlayersNumber(0);
    setUserSexe(Sexe::WOMAN);
    setShareUserAge(true);
    setUserAge(42);
    setRegisteredUnderages(false);
    setFullGame(false);
    setCancelledGame(false);
    setRealAddress("");
    setNearCity("");
    setPermittedUnderages(true);
    setPhoneNumber("");
    setEmail("");
    setFacebook("");
    setForumThreadTitle("");
    setConsiderForumThread(false);
    setEventDateTime(QDateTime::currentDateTime());
    setSpecialEvent(false);
    setSeveralGameMasters(false);
    setGameEditionType(GameEditionType::COMMERCIAL);
    setGameName("");
    setSeveralGames(false);
    setScriptSourceType(ScriptSourceType::COMMERCIAL);
    setScriptName("");
    setSeveralSessions(false);
    setDrinkFoodPermission(DrinkFoodPermission::NEVERMIND);
    setAlcoholPermission(AlcoholPermission::NEVERMIND);
    setSmokeInsidePermission(SmokeInsidePermission::FORBIDDEN);
    setPlaceType(PlaceType::HOME);
    setComments("");
}

QPair<bool, QString> OneShotEventInfo::verifyDataNotEmpty()
{
    if(userName().isEmpty())
        return QPair<bool, QString>(false, OneShotEventInfoMembersNames::userName);

    if(password().size() < 2)
        return QPair<bool, QString>(false, OneShotEventInfoMembersNames::password);

    if(realAddress().isEmpty())
        return QPair<bool, QString>(false, OneShotEventInfoMembersNames::realAddress);

    if(nearCity().isEmpty())
        return QPair<bool, QString>(false, OneShotEventInfoMembersNames::nearCity);

    if(phoneNumber().isEmpty() && email().isEmpty() && facebook().isEmpty() && considerForumThread() == false)
        return QPair<bool, QString>(false, OneShotEventInfoMembersNames::contact);

    if(considerForumThread() == true && forumThreadTitle().isEmpty())
        return QPair<bool, QString>(false, OneShotEventInfoMembersNames::forumThreadTitle);

    if(eventDateTime() <= QDateTime::currentDateTime())
        return QPair<bool, QString>(false, OneShotEventInfoMembersNames::eventDateTime);

    return QPair<bool, QString>(true, "");
}

QString OneShotEventInfo::gameEditionTypeString()
{
    switch (gameEditionType()) {
    case GameEditionType::COMMERCIAL:
            return OneShotEventInfoGameEditionTypeString::commercial;
        break;
    case GameEditionType::AMATEUR:
            return OneShotEventInfoGameEditionTypeString::amateur;
        break;
    case GameEditionType::PERSONAL:
            return OneShotEventInfoGameEditionTypeString::personnal;
        break;
    default:
        return OneShotEventInfoGameEditionTypeString::undefined;
        break;
    }
}

QString OneShotEventInfo::scriptSourceTypeString()
{
    switch (scriptSourceType()) {
    case ScriptSourceType::COMMERCIAL:
            return OneShotEventInfoScriptSourceTypeString::commercial;
        break;
    case ScriptSourceType::WEB:
            return OneShotEventInfoScriptSourceTypeString::web;
        break;
    case ScriptSourceType::PERSONAL:
            return OneShotEventInfoScriptSourceTypeString::personnal;
        break;
    default:
        return OneShotEventInfoScriptSourceTypeString::undefined;
        break;
    }
}

QString OneShotEventInfo::placeTypeString()
{
    switch (placeType()) {
    case PlaceType::HOME:
            return OneShotEventInfoPlaceTypeString::home;
        break;
    case PlaceType::BAR:
            return OneShotEventInfoPlaceTypeString::bar;
        break;
    case PlaceType::ROOM:
            return OneShotEventInfoPlaceTypeString::room;
        break;
    default:
        return OneShotEventInfoPlaceTypeString::outside;
        break;
    }
}
























