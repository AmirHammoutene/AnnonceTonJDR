#ifndef GAMEEVENTINFO_H
#define GAMEEVENTINFO_H

/*
* Parent class for all games information.
* This class can not be instantiated
*/

#include <QString>
#include <QDateTime>

enum class GameType {
    ONESHOT
};

enum class Sexe {
    WOMAN,
    MAN,
    UNDEFINED

};

class GameEventInfo
{
public:
    GameEventInfo();
    virtual void initiate() = 0; // set default values. (Pure virtual)
    virtual ~GameEventInfo(){}

protected:
    QString m_userName; //The annoncer has a name
    QString m_password; //The annoncer set a password
    GameType m_gameType; //Type of the game (one-shot, campain...)
    QDateTime m_creationDateTime; //When does the annonce has been created
    unsigned int m_maximumPlayersNumber; //The game has a maximum players number
    unsigned int m_registeredPlayersNumber; //Number of people already registered in the game
    Sexe m_userSexe; //The annoncer has a sexe
    unsigned int m_userAge; //The annoncer has an age
    bool m_shareUserAge; //Does the annoncer choose to share his age in the annonce
    bool m_registeredUnderages; //Does some underages (18 years old or less) already registered
    bool m_fullGame; //Is this game full of players
    bool m_cancelledGame; //Is this a cancelled game
    QString m_realAddress; //Real address where the game takes place
    QString m_nearCity; //The game will take place to a nearest city listed
    bool m_permittedUnderages; //The game is restricted or not for underages (18 years old or less)
    QString m_phoneNumber; //Annoncer phone number
    QString m_email; //Annoncer email
    QString m_facebook; //Annoncer facebook page
    QString m_forumThreadTitle; //Thread title in the forum of the software
    bool m_considerForumThread; //Does the annoncer created a forum thread

public:
    const QString & userName() const { return m_userName; }
    void setUserName(const QString &userName) { m_userName = userName; }

    const QString & password() const { return m_password; }
    void setPassword(const QString &password) { m_password = password; }

    const QDateTime & creationDateTime() const { return m_creationDateTime; }
    void setCreationDateTime(const QDateTime &creationDateTime) { m_creationDateTime = creationDateTime; }

    unsigned int maximumPlayersNumber() const { return m_maximumPlayersNumber; }
    void setMaximumPlayersNumber(unsigned int value) { m_maximumPlayersNumber = value; }

    unsigned int registeredPlayersNumber() const { return m_registeredPlayersNumber; }
    void setRegisteredPlayersNumber(unsigned int value) { m_registeredPlayersNumber = value; }

    Sexe userSexe() const { return m_userSexe; }
    void setUserSexe(const Sexe &userSexe) { m_userSexe = userSexe; }

    unsigned int userAge() const { return m_userAge; }
    void setUserAge(unsigned int userAge) { m_userAge = userAge; }

    bool shareUserAge() const { return m_shareUserAge; }
    void setShareUserAge(bool shareUserAge) { m_shareUserAge = shareUserAge; }

    bool registeredUnderages() const { return m_registeredUnderages; }
    void setRegisteredUnderages(bool registeredUnderages) { m_registeredUnderages = registeredUnderages; }

    bool fullGame() const { return m_fullGame; }
    void setFullGame(bool fullGame) {  m_fullGame = fullGame; }

    bool cancelledGame() const { return m_cancelledGame; }
    void setCancelledGame(bool cancelledGame) {  m_cancelledGame = cancelledGame; }

    const QString & realAddress() const { return m_realAddress; }
    void setRealAddress(const QString &realAddress) { m_realAddress = realAddress; }

    const QString & nearCity() const { return m_nearCity; }
    void setNearCity(const QString &nearCity) { m_nearCity = nearCity; }

    bool permittedUnderages() const { return m_permittedUnderages; }
    void setPermittedUnderages(bool permittedUnderages) { m_permittedUnderages = permittedUnderages; }

    const QString & phoneNumber() const { return m_phoneNumber;  }
    void setPhoneNumber(const QString &phoneNumber) { m_phoneNumber = phoneNumber; }

    const QString & email() const { return m_email; }
    void setEmail(const QString &email) { m_email = email; }

    const QString & facebook() const { return m_facebook; }
    void setFacebook(const QString &facebook) { m_facebook = facebook; }

    const QString & forumThreadTitle() const { return m_forumThreadTitle; }
    void setForumThreadTitle(const QString &forumThreadTitle) { m_forumThreadTitle = forumThreadTitle; }

    bool considerForumThread() const { return m_considerForumThread; }
    void setConsiderForumThread(bool considerForumThread) { m_considerForumThread = considerForumThread; }
};

#endif // GAMEEVENTINFO_H
