#ifndef GAMEEVENTSEARCHFILTER_H
#define GAMEEVENTSEARCHFILTER_H

/*
* Parent class for all search information.
* Those informations are used for search filters
* This class can not be instantiated
*/

#include <QString>
#include <QDateTime>


enum class SexeFilter {
    WOMAN,
    MAN,
    NEVERMIND

};

enum class PermissionUnderagesFilter {
    YES,
    NO,
    NEVERMIND

};

class GameEventSearchFilter
{
public:
    GameEventSearchFilter();
    virtual void initiate() = 0; // set default values. (Pure virtual)
    virtual ~GameEventSearchFilter(){}

protected:
    QString m_userNameFilter; //The annoncer has a name
    SexeFilter m_userSexeFilter; //The annoncer has a sexe
    unsigned int m_minimumUserAgeFilter; //The games are restricted from a minimal age
    unsigned int m_maximumUserAgeFilter; //The games are restricted to a maximum age
    PermissionUnderagesFilter m_permissionUnderagesFilter; //The games are restricted or not for underages (18 years old or less)
    bool m_showFullGameFilter; //The search will show full games or not
    bool m_showCancelledGameFilter; //The search will show cancelled games or not
    QStringList m_nearCitiesFilter; //The games will take place to a nearest city listed

public:

    const QString & userNameFilter() const{return m_userNameFilter;}
    void setUserNameFilter(const QString &userNameFilter){m_userNameFilter = userNameFilter;}

    SexeFilter userSexeFilter() const{ return m_userSexeFilter;}
    void setUserSexeFilter(const SexeFilter &userSexeFilter){m_userSexeFilter = userSexeFilter;}

    unsigned int minimumUserAgeFilter() const{return m_minimumUserAgeFilter;}
    void setMinimumUserAgeFilter(unsigned int minimumUserAgeFilter){m_minimumUserAgeFilter = minimumUserAgeFilter;}

    unsigned int maximumUserAgeFilter() const{return m_maximumUserAgeFilter;}
    void setMaximumUserAgeFilter(unsigned int maximumUserAgeFilter){m_maximumUserAgeFilter = maximumUserAgeFilter;}

    PermissionUnderagesFilter permissionUnderagesFilter() const{return m_permissionUnderagesFilter;}
    void setPermissionUnderagesFilter(const PermissionUnderagesFilter &permissionUnderagesFilter){m_permissionUnderagesFilter = permissionUnderagesFilter;}

    bool showFullGameFilter() const{return m_showFullGameFilter;}
    void setShowFullGameFilter(bool showFullGameFilter){m_showFullGameFilter = showFullGameFilter;}

    bool showCancelledGameFilter() const{return m_showCancelledGameFilter;}
    void setShowCancelledGameFilter(bool showCancelledGameFilter){m_showCancelledGameFilter = showCancelledGameFilter;}

    const QStringList & nearCitiesFilter() const{return m_nearCitiesFilter;}
    void setNearCitiesFilter(const QStringList &nearCitiesFilter){m_nearCitiesFilter = nearCitiesFilter;}
};

#endif // GAMEEVENTSEARCHFILTER_H
