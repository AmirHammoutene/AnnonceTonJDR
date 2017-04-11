#ifndef ONESHOTEVENTINFOTITLES_H
#define ONESHOTEVENTINFOTITLES_H

#include <QString>
#include <QObject>

namespace OneShotEventInfoMembersNames {
    const QString userName = QObject::tr("le nom d'utilisateur");
    const QString password = QObject::tr("le mot de passe");
    const QString realAddress = QObject::tr("le lieu");
    const QString nearCity = QObject::tr("la ville à proximité");
    const QString contact =  QObject::tr("le contact (au moins un)");
    const QString forumThreadTitle =  QObject::tr("le titre du sujet dans le forum");
    const QString eventDateTime =  QObject::tr("la date prévue pour le One Shot");

}

namespace OneShotEventInfoGameEditionTypeString {
    const QString commercial = QObject::tr("commercial");
    const QString amateur = QObject::tr("amateur");
    const QString personnal = QObject::tr("personnel");
    const QString undefined = QObject::tr("indéfini");
}


namespace OneShotEventInfoScriptSourceTypeString {
    const QString commercial = QObject::tr("du commerce");
    const QString web = QObject::tr("d'internet");
    const QString personnal = QObject::tr("personnel");
    const QString undefined = QObject::tr("indéfini");
}

namespace OneShotEventInfoPlaceTypeString {
    const QString home = QObject::tr("chez quelqu'un");
    const QString bar = QObject::tr("dans un bar/restaurant");
    const QString room = QObject::tr("dans une salle");
    const QString outside = QObject::tr("à l'extérieur");
}

#endif // ONESHOTEVENTINFOTITLES_H
