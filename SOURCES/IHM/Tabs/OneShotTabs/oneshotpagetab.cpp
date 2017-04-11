#include "oneshotpagetab.h"
#include "ui_oneshotpagetab.h"
#include <QDomDocument>
#include <QInputDialog>
#include <QMessageBox>
#include "oneshotcreatedialog.h"
#include "oneshotpagetabtitles.h"

OneShotPageTab::OneShotPageTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OneShotPageTab)
{
    ui->setupUi(this);
    loadRandomSentences();

    QObject::connect(ui->edit_button, SIGNAL( released() ), this, SLOT( edit() ));
}

OneShotPageTab::~OneShotPageTab()
{
    delete ui;
}

void OneShotPageTab::loadRandomSentences()
{
    QDomDocument doc("headers");
    QFile file(":/oneShotPageRandomSentences.xml");
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    QString error;
    int line,column;
    if (!doc.setContent(&file,&error,&line, &column))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomNode currentNode = docElem.firstChild();

    while(!currentNode.isNull()) {
        QDomElement currentElement = currentNode.toElement();
        if(!currentElement.isNull())
        {
            QString currentVarName = currentElement.attribute("title","#noVarName");
            QDomNode currentSubNode = currentNode.firstChild();
            QStringList currentSentences;
            while(!currentSubNode.isNull())
            {
                QDomElement currentSubElement = currentSubNode.toElement();
                if(!currentSubElement.isNull())
                    currentSentences.append(currentSubElement.text());

                currentSubNode = currentSubNode.nextSibling();
            }
            auto random = qrand() % currentSentences.size();
            randomSentences.insert(currentVarName,currentSentences.at(random));

        }
        currentNode = currentNode.nextSibling();
    }
}

void OneShotPageTab::fillInfo(OneShotEventInfo i_info)
{
    info=i_info;

    ui->userName->setText(info.userName());

    QString userSentence = randomSentences.value("userName",tr("Bonjour, je m'appelle $$ ."));
    QStringList userSentenceSplitted = userSentence.split("$$");
    if(userSentenceSplitted.size() == 2)
    {
        ui->userNamePretext->setText(userSentenceSplitted.at(0));
        ui->userNamePosttext->setText(userSentenceSplitted.at(1));
    }

    if(!info.shareUserAge())
    {
        ui->userAgeWidget->setVisible(false);

    }
    else
    {
        ui->userAge->setText(QString::number(info.userAge()));
        QString ageSentence = randomSentences.value("userAge",tr("J'ai $$ ans."));
        QStringList ageSentenceSplitted = ageSentence.split("$$");
        if(ageSentenceSplitted.size() == 2)
        {
            ui->userAgePretext->setText(ageSentenceSplitted.at(0));
            ui->userAgePosttext->setText(ageSentenceSplitted.at(1));
        }
    }

    if(info.userSexe() == Sexe::WOMAN)
    {
        ui->userSexe->setText(tr("une femme"));
        QString sexeSentence = randomSentences.value("userSexeWoman",tr("Je suis $$ ."));
        QStringList sexeSentenceSplitted = sexeSentence.split("$$");
        if(sexeSentenceSplitted.size() == 2)
        {
            ui->userSexePretext->setText(sexeSentenceSplitted.at(0));
            ui->userSexePosttext->setText(sexeSentenceSplitted.at(1));
        }
    }
    else if(info.userSexe() == Sexe::MAN)
    {
        ui->userSexe->setText(tr("un homme"));
        QString sexeSentence = randomSentences.value("userSexeMan",tr("Je suis $$ ."));
        QStringList sexeSentenceSplitted = sexeSentence.split("$$");
        if(sexeSentenceSplitted.size() == 2)
        {
            ui->userSexePretext->setText(sexeSentenceSplitted.at(0));
            ui->userSexePosttext->setText(sexeSentenceSplitted.at(1));
        }
    }
    else
    {
        ui->userSexeWidget->setVisible(false);
    }

    if(!info.cancelledGame() && !info.fullGame())
    {
        ui->fullOrCancelledGameWidget->setVisible(false);

        ui->searchedPlayersNumber->setText(QString::number(info.maximumPlayersNumber()-info.registeredPlayersNumber()));
        ui->regPlayersNumber->setText(QString::number(info.registeredPlayersNumber()));
        ui->maxPlayersNumber->setText(QString::number(info.maximumPlayersNumber()));

        QString searchedPlayersNumber = randomSentences.value("searchedPlayersNumber",tr("Je cherche $$ joueurs."));
        QStringList searchedPlayersNumberSplitted = searchedPlayersNumber.split("$$");
        if(searchedPlayersNumberSplitted.size() == 2)
        {
            ui->searchedPlayersNumberPretext->setText(searchedPlayersNumberSplitted.at(0));
            ui->searchedPlayersNumberPosttext->setText(searchedPlayersNumberSplitted.at(1));
        }

        QString regPlayersNumber = randomSentences.value("regPlayersNumber",tr("Il y a déjà $$ joueurs inscrits."));
        QStringList regPlayersNumberSplitted = regPlayersNumber.split("$$");
        if(regPlayersNumberSplitted.size() == 2)
        {
            ui->regPlayersNumberPretext->setText(regPlayersNumberSplitted.at(0));
            ui->regPlayersNumberPosttext->setText(regPlayersNumberSplitted.at(1));
        }

        QString maxPlayersNumber = randomSentences.value("maxPlayersNumber",tr("Nous serons au maximum $$ joueurs autour de la table."));
        QStringList maxPlayersNumberSplitted = maxPlayersNumber.split("$$");
        if(maxPlayersNumberSplitted.size() == 2)
        {
            ui->maxPlayersNumberPretext->setText(maxPlayersNumberSplitted.at(0));
            ui->maxPlayersNumberPosttext->setText(maxPlayersNumberSplitted.at(1));
        }
    }
    else
    {
        ui->searchedPlayersNumberWidget->setVisible(false);
        ui->regPlayersNumberWidget->setVisible(false);
        ui->maxPlayersNumberWidget->setVisible(false);

         if(info.cancelledGame())
            ui->fullOrCancelledGameText->setText(randomSentences.value("cancelledGame",tr("Malheureusement, la partie est annulée.")));
         else
            ui->fullOrCancelledGameText->setText(randomSentences.value("fullGame",tr("Malheureusement, la partie est pleine.")));
    }

    if(info.specialEvent())
        ui->specialEventText->setText(randomSentences.value("specialEvent",tr("Il s'agit d'un évènement spécial (Salon, convention, rencontre,...).")));
    else
        ui->specialEventWidget->setVisible(false);

    if(!info.gameName().isEmpty())
    {
        ui->gameNamePretext->setText(randomSentences.value("gameName",tr("Ce sera une partie de ce JDR : ")));
        ui->gameName->setText(info.gameName());
    }
    else
    {
        ui->gameNameWidget->setVisible(false);
    }

    if(info.severalGameMasters())
        ui->severalGameMastersText->setText(randomSentences.value("severalGameMasters",tr("Plusieurs maîtres de jeu seront présents.")));
    else
        ui->severalGameMastersWidget->setVisible(false);

    if(info.severalGames())
        ui->severalGamesText->setText(randomSentences.value("severalGames",tr("Il y aura plusieurs jeux maîtrisés.")));
    else
        ui->severalGamesWidget->setVisible(false);

    ui->gameTypePretext->setText(randomSentences.value("gameType",tr("Le type d'édition du jeu est ")));
    ui->gameType->setText(info.gameEditionTypeString());

    if(!info.scriptName().isEmpty())
    {
        ui->scriptNamePretext->setText(randomSentences.value("scriptName",tr("Le scénario s'intitule ")));
        ui->scriptName->setText(info.scriptName());
    }
    else
    {
        ui->scriptNameWidget->setVisible(false);
    }

    if(info.severalSessions())
        ui->severalSessionsText->setText(randomSentences.value("severalSessions",tr("Ce scénario est prévu pour être joué en plusieurs parties.")));
    else
        ui->severalSessionsWidget->setVisible(false);

    ui->scriptTypePretext->setText(randomSentences.value("scriptType",tr("Ce scénario est de source ")));
    ui->scriptTypeText->setText(info.scriptSourceTypeString());

    ui->eventDateTimePretext->setText(randomSentences.value("dateTime",tr("Rendez-vous le ")));
    ui->eventDateTime->setText(info.eventDateTime().toString("d MMMM yyyy à h:mm"));

    ui->realAddressPretext->setText(randomSentences.value("realAddress",tr("Voici le lieu : ")));
    ui->realAddress->setText(info.realAddress());

    ui->nearCityPretext->setText(randomSentences.value("nearCity",tr("Cela se trouve proche de ")));
    ui->nearCity->setText(info.nearCity());

    ui->placeTypePretext->setText(randomSentences.value("placeType",tr("Cela se jouera ")));
    ui->placeType->setText(info.placeTypeString());

    ui->moreInfoText->setText(randomSentences.value("moreInfo",tr("Voici plus d'informations : ")));

    if(info.permittedUnderages())
        ui->permittedUnderagesText->setText(randomSentences.value("permittedUnderagesYes",tr("Les mineurs peuvent s'inscrire.")));
    else
        ui->permittedUnderagesText->setText(randomSentences.value("permittedUnderagesNo",tr("Les mineurs ne peuvent pas s'inscrire.")));

    if(info.registeredUnderages())
        ui->registredUnderagesText->setText(randomSentences.value("registredUnderages",tr("Il y a déjà des mineurs inscrits.")));
    else
        ui->registredUnderagesWidget->setVisible(false);

    if(info.drinkFoodPermission() == DrinkFoodPermission::BRING)
        ui->drinkFoodPermissionText->setText(randomSentences.value("drinkFoodPermissionBring",tr("Veuillez amener à boire et à manger.")));
    else if(info.drinkFoodPermission() == DrinkFoodPermission::NEVERMIND)
        ui->drinkFoodPermissionText->setText(randomSentences.value("drinkFoodPermissionOk",tr("Vous pouvez, si vous le souhaitez, amener à boire et à manger.")));
    else
        ui->drinkFoodPermissionText->setText(randomSentences.value("drinkFoodPermissionNo",tr("Evitez d'amener à boire et à manger.")));

    if(info.alcoholPermission() == AlcoholPermission::BRING)
        ui->alcoholPermissionText->setText(randomSentences.value("alcoholPermissionBring",tr("Veuillez amener de l'alcool.")));
    else if(info.alcoholPermission() == AlcoholPermission::NEVERMIND)
        ui->alcoholPermissionText->setText(randomSentences.value("alcoholPermissionOk",tr("Vous pouvez, si vous le souhaitez, amener de l'alcool.")));
    else
        ui->alcoholPermissionText->setText(randomSentences.value("alcoholPermissionNo",tr("Evitez d'amener de l'alcool.")));

    if(info.smokeInsidePermission() == SmokeInsidePermission::PERMITTED)
        ui->smokePermissionText->setText(randomSentences.value("smokePermissionYes",tr("Il est possible de fumer à l'intérieur.")));
    else
        ui->smokePermissionText->setText(randomSentences.value("smokePermissionNo",tr("Il ne sera pas possible de fumer à l'intérieur.")));

    if(!info.phoneNumber().isEmpty())
        ui->phoneNumber->setText(info.phoneNumber());
    else
        ui->phoneNumberWidget->setVisible(false);

    if(!info.email().isEmpty())
        ui->email->setText(info.email());
    else
        ui->emailWidget->setVisible(false);

    if(!info.facebook().isEmpty())
        ui->facebook->setText(info.facebook());
    else
        ui->facebookWidget->setVisible(false);

    if(info.considerForumThread())
        ui->forumThread->setText(info.forumThreadTitle());
    else
        ui->forumThreadWidget->setVisible(false);

    ui->commentsPretext->setText(randomSentences.value("comments",tr("Voici quelques commentaires")));
    ui->comments->setPlainText(info.comments());
}

void OneShotPageTab::edit()
{
    bool ok;
    QString enteredPassword = QInputDialog::getText(this,OneShotPageTabTitles::editInputDialogTitle,OneShotPageTabTitles::editInputDialogText,QLineEdit::Password,"",&ok);
    if(!ok)
        return;

    if(enteredPassword!=info.password())
        QMessageBox::warning(this,OneShotPageTabTitles::editWarningPasswordTitle,OneShotPageTabTitles::editWarningPasswordText);
    else
    {
        OneShotCreateDialog::getInstance(this,info)->show();
        OneShotCreateDialog::getInstance(this,info)->setOldEventInfo(info);
    }
}

















