#ifndef MAINWINDOWTITLES_H
#define MAINWINDOWTITLES_H

namespace MainWindowTitle {
    const QString helpButton_title = QObject::tr("Aide");
    const QString weblinkHelpButton_title = QObject::tr("Lien vers le Site Web et le Forum");
    const QString aboutHelpButton_title = QObject::tr("A propos");

    const QString searchTabName_OneShot = QObject::tr("Rechercher un One Shot");
    const QString resultsTabName_OneShot = QObject::tr("Résultats");

    const QString lastRequestFailedPopupTitle = QObject::tr("Echec de la requête");
    const QString lastRequestFailedPopupMessage = QObject::tr("La dernière requête a échouée.\nVoici le message d'erreur reçu : \n");
    const QString lastRequestSuccessPopupTitle = QObject::tr("Succès de la requête");
    const QString lastRequestSuccessPopupMessage = QObject::tr("La dernière requête a réussi.");

    const QString softwareInfo = QObject::tr("Logiciel de recherche d'annonces de jeux de rôle.\nVersion 1.1.0 développé en février 2017 par Amir Hammoutene.");
}

#endif // MAINWINDOWTITLES_H
