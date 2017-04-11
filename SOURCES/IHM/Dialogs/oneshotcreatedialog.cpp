#include "oneshotcreatedialog.h"
#include "ui_oneshotcreatedialog.h"
#include "oneshotcreatedialogtitles.h"
#include <QMessageBox>

OneShotCreateDialog* OneShotCreateDialog::m_instance = 0;


OneShotCreateDialog::OneShotCreateDialog(QWidget *parent, const OneShotEventInfo &oldInfo) :
    QDialog(parent),
    ui(new Ui::OneShotCreateDialog)
{
    ui->setupUi(this);
    m_oldEventInfo = oldInfo;
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    synchronizeWidgetWithOldEventInfo();

    QObject::connect(ui->showPassword_button, SIGNAL( pressed() ) , this ,SLOT( showPasswordClicked() ));
    QObject::connect(ui->showPassword_button, SIGNAL( released() ) , this ,SLOT( showPasswordReleased() ));
    QObject::connect(ui->hideAge_checkbox, SIGNAL( toggled(bool) ), this, SLOT( hideAge_toggled(bool)) );
    QObject::connect(ui->markFull_checkBox, SIGNAL( toggled(bool) ), this, SLOT( markFullChecked(bool)) );
    QObject::connect(ui->markCancel_checkBox, SIGNAL( toggled(bool) ), this, SLOT( markCancelChecked(bool)) );
    QObject::connect(ui->forumTitle_checkbox, SIGNAL( toggled(bool) ), this, SLOT( promiseToCreateForumThreadChecked(bool) ));
    QObject::connect(ui->createEdit_pushButton, SIGNAL ( released() ), this, SLOT( sendRequest()) );
}

OneShotCreateDialog::~OneShotCreateDialog()
{
    delete ui;
}

OneShotCreateDialog* OneShotCreateDialog::getInstance(QWidget *parent, const OneShotEventInfo & oldInfo)
{
    if ( !m_instance) {
        m_instance = new OneShotCreateDialog(parent,oldInfo);
    }
    return m_instance;
}

OneShotEventInfo OneShotCreateDialog::synchronizeInfoWithWidget(OneShotEventInfo &info)
{
    info.setCreationDateTime(QDateTime::currentDateTime());
    info.setUserName(ui->userName_lineEdit->text());
    info.setPassword(ui->password_lineEdit->text());
    info.setMaximumPlayersNumber(ui->maximumPlayersNumber_spinBox->value());
    info.setRegisteredPlayersNumber(ui->registeredPlayersNumber_spinBox->value());
    info.setShareUserAge( ui->hideAge_checkbox->checkState() == Qt::Unchecked ? true : false );
    info.setUserAge(ui->age_spinbox->value());
    info.setRegisteredUnderages( ui->registeredUnderages_checkBox->checkState() == Qt::Checked ? true : false);
    info.setFullGame( ui->markFull_checkBox->checkState() == Qt::Checked ? true : false );
    info.setCancelledGame(ui->markCancel_checkBox->checkState() == Qt::Checked ? true : false);
    info.setRealAddress(ui->realAddress_lineEdit->text());
    info.setPermittedUnderages( ui->permittedUnderages_comboBox->currentIndex() == 0 ? true : false);
    info.setPhoneNumber(ui->phoneNumber_lineEdit->text());
    info.setEmail(ui->email_lineEdit->text());
    info.setFacebook(ui->facebook_lineEdit->text());
    if(ui->forumTitle_checkbox->checkState() == Qt::Checked)
        info.setForumThreadTitle(ui->forumTitle_lineEdit->text());
    else
        info.setForumThreadTitle("");
    info.setConsiderForumThread( ui->forumTitle_checkbox->checkState() == Qt::Checked ? true : false );
    info.setEventDateTime(ui->dateTimeEdit->dateTime());
    info.setSpecialEvent( ui->specialEvent_checkBox->checkState() == Qt::Checked ? true : false );
    info.setSeveralGameMasters( ui->severalGameMasters_checkBox->checkState() == Qt::Checked ? true : false );
    info.setGameName(ui->gameName_lineEdit->text());
    info.setSeveralGames(ui->severalGames_checkBox->checkState() == Qt::Checked ? true : false );
    info.setScriptName(ui->scriptName_lineEdit->text());
    info.setSeveralSessions(ui->severalSessions_checkBox->checkState() == Qt::Checked ? true : false );
    info.setSmokeInsidePermission( ui->smokeInsidePermission_comboBox->currentIndex() == 0 ? SmokeInsidePermission::FORBIDDEN : SmokeInsidePermission::PERMITTED );
    info.setComments(ui->comments_lineEdit->text());

    QStringList cityChecked = ui->nearCity_customTreeWidget->getCitiesChecked();
    info.setNearCity( cityChecked.isEmpty() ? "" : cityChecked.first() );

    switch (ui->userSexe_comboBox->currentIndex()) {
    case 0:
        info.setUserSexe(Sexe::WOMAN);
        break;
    case 1:
        info.setUserSexe(Sexe::MAN);
        break;
    default:
        info.setUserSexe(Sexe::UNDEFINED);
        break;
    }

    switch (ui->gameEditionType_comboBox->currentIndex()) {
    case 0:
        info.setGameEditionType(GameEditionType::COMMERCIAL);
        break;
    case 1:
        info.setGameEditionType(GameEditionType::AMATEUR);
        break;
    case 2:
        info.setGameEditionType(GameEditionType::PERSONAL);
        break;
    default:
        info.setGameEditionType(GameEditionType::UNDEFINED);
        break;
    }

    switch (ui->scriptSourceType_comboBox->currentIndex()) {
    case 0:
        info.setScriptSourceType(ScriptSourceType::COMMERCIAL);
        break;
    case 1:
        info.setScriptSourceType(ScriptSourceType::WEB);
        break;
    case 2:
        info.setScriptSourceType(ScriptSourceType::PERSONAL);
        break;
    default:
        info.setScriptSourceType(ScriptSourceType::UNDEFINED);
        break;
    }

    switch (ui->drinkFoodPermission_comboBox->currentIndex()) {
    case 0:
        info.setDrinkFoodPermission(DrinkFoodPermission::NEVERMIND);
        break;
    case 1:
        info.setDrinkFoodPermission(DrinkFoodPermission::BRING);
        break;
    default:
        info.setDrinkFoodPermission(DrinkFoodPermission::FORBIDDEN);
        break;
    }

    switch (ui->alcoholPermission_comboBox->currentIndex()) {
    case 0:
        info.setAlcoholPermission(AlcoholPermission::NEVERMIND);
        break;
    case 1:
        info.setAlcoholPermission(AlcoholPermission::BRING);
        break;
    default:
        info.setAlcoholPermission(AlcoholPermission::FORBIDDEN);
        break;
    }

    switch (ui->placeType_comboBox->currentIndex()) {
    case 0:
        info.setPlaceType(PlaceType::HOME);
        break;
    case 1:
        info.setPlaceType(PlaceType::BAR);
        break;
    case 2:
        info.setPlaceType(PlaceType::ROOM);
        break;
    default:
        info.setPlaceType(PlaceType::OUTSIDE);
        break;
    }
    return info;
}

void OneShotCreateDialog::synchronizeWidgetWithOldEventInfo()
{
    ui->userName_lineEdit->setText(m_oldEventInfo.userName());
    ui->password_lineEdit->setText(m_oldEventInfo.password());
    ui->maximumPlayersNumber_spinBox->setValue(m_oldEventInfo.maximumPlayersNumber());
    ui->registeredPlayersNumber_spinBox->setValue(m_oldEventInfo.registeredPlayersNumber());
    ui->hideAge_checkbox->setChecked(!m_oldEventInfo.shareUserAge());
    ui->age_spinbox->setValue(m_oldEventInfo.userAge());
    ui->registeredUnderages_checkBox->setChecked(m_oldEventInfo.registeredUnderages());
    ui->markFull_checkBox->setChecked(m_oldEventInfo.fullGame());
    ui->markCancel_checkBox->setChecked(m_oldEventInfo.cancelledGame());
    ui->realAddress_lineEdit->setText(m_oldEventInfo.realAddress());
    ui->permittedUnderages_comboBox->setCurrentIndex( m_oldEventInfo.permittedUnderages() == true ? 0 : 1 );
    ui->phoneNumber_lineEdit->setText(m_oldEventInfo.phoneNumber());
    ui->email_lineEdit->setText(m_oldEventInfo.email());
    ui->facebook_lineEdit->setText(m_oldEventInfo.facebook());
    ui->forumTitle_checkbox->setChecked(m_oldEventInfo.considerForumThread());
    ui->forumTitle_lineEdit->setText(m_oldEventInfo.forumThreadTitle());
    ui->dateTimeEdit->setDateTime(m_oldEventInfo.eventDateTime());
    ui->specialEvent_checkBox->setChecked(m_oldEventInfo.specialEvent());
    ui->severalGameMasters_checkBox->setChecked(m_oldEventInfo.severalGameMasters());
    ui->gameName_lineEdit->setText(m_oldEventInfo.gameName());
    ui->severalGames_checkBox->setChecked(m_oldEventInfo.severalGames());
    ui->scriptName_lineEdit->setText(m_oldEventInfo.scriptName());
    ui->severalSessions_checkBox->setChecked(m_oldEventInfo.severalSessions());
    ui->smokeInsidePermission_comboBox->setCurrentIndex( m_oldEventInfo.smokeInsidePermission() == SmokeInsidePermission::FORBIDDEN ? 0 : 1 );
    ui->nearCity_customTreeWidget->setCityChecked(m_oldEventInfo.nearCity());
    ui->comments_lineEdit->setText(m_oldEventInfo.comments());

    switch (m_oldEventInfo.userSexe()) {
    case Sexe::WOMAN:
        ui->userSexe_comboBox->setCurrentIndex(0);
        break;
    case Sexe::MAN:
        ui->userSexe_comboBox->setCurrentIndex(1);
        break;
    default:
        ui->userSexe_comboBox->setCurrentIndex(2);
        break;
    }

    switch (m_oldEventInfo.gameEditionType()) {
    case GameEditionType::COMMERCIAL:
        ui->gameEditionType_comboBox->setCurrentIndex(0);
        break;
    case GameEditionType::AMATEUR:
        ui->gameEditionType_comboBox->setCurrentIndex(1);
        break;
    default:
        ui->gameEditionType_comboBox->setCurrentIndex(2);
        break;
    }

    switch (m_oldEventInfo.scriptSourceType()) {
    case ScriptSourceType::COMMERCIAL:
        ui->scriptSourceType_comboBox->setCurrentIndex(0);
        break;
    case ScriptSourceType::WEB:
        ui->scriptSourceType_comboBox->setCurrentIndex(1);
        break;
    default:
        ui->scriptSourceType_comboBox->setCurrentIndex(2);
        break;
    }

    switch (m_oldEventInfo.drinkFoodPermission()) {
    case DrinkFoodPermission::NEVERMIND:
        ui->drinkFoodPermission_comboBox->setCurrentIndex(0);
        break;
    case DrinkFoodPermission::BRING:
        ui->drinkFoodPermission_comboBox->setCurrentIndex(1);
        break;
    default:
        ui->drinkFoodPermission_comboBox->setCurrentIndex(2);
        break;
    }

    switch (m_oldEventInfo.alcoholPermission()) {
    case AlcoholPermission::NEVERMIND:
        ui->alcoholPermission_comboBox->setCurrentIndex(0);
        break;
    case AlcoholPermission::BRING:
        ui->alcoholPermission_comboBox->setCurrentIndex(1);
        break;
    default:
        ui->alcoholPermission_comboBox->setCurrentIndex(2);
        break;
    }

    switch (m_oldEventInfo.placeType()) {
    case PlaceType::HOME:
        ui->placeType_comboBox->setCurrentIndex(0);
        break;
    case PlaceType::BAR:
        ui->placeType_comboBox->setCurrentIndex(1);
        break;
    case PlaceType::ROOM:
        ui->placeType_comboBox->setCurrentIndex(2);
        break;
    default:
        ui->placeType_comboBox->setCurrentIndex(3);
        break;
    }
}

void OneShotCreateDialog::setOldEventInfo(const OneShotEventInfo &oldInfo)
{
    m_oldEventInfo = oldInfo;
    synchronizeWidgetWithOldEventInfo();
}

void OneShotCreateDialog::sendRequest()
{
    OneShotEventInfo eventInfo;
    synchronizeInfoWithWidget(eventInfo);

    // Verify that all data are correctly entered
    QPair<bool,QString> dataVerification = eventInfo.verifyDataNotEmpty();

    if(dataVerification.first == false)
    {
        QMessageBox::critical(this,OneShotCreateDialogTitles::formErrorPopupTitle,OneShotCreateDialogTitles::formErrorPopupMessage+dataVerification.second);
    }
    else
    {
        emit transfertCreateInfoSignal(eventInfo,m_oldEventInfo);
        close();
    }
}


void OneShotCreateDialog::showPasswordClicked()
{
    ui->password_lineEdit->setEchoMode(QLineEdit::Normal);
}

void OneShotCreateDialog::showPasswordReleased()
{
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
}

void OneShotCreateDialog::hideAge_toggled(bool value)
{
    ui->age_spinbox->setDisabled(value);
}

void OneShotCreateDialog::markFullChecked(bool value)
{
    if(value)
        ui->markCancel_checkBox->setChecked(false);
}

void OneShotCreateDialog::markCancelChecked(bool value)
{
    if(value)
        ui->markFull_checkBox->setChecked(false);
}

void OneShotCreateDialog::promiseToCreateForumThreadChecked(bool value)
{
    ui->forumTitle_lineEdit->setEnabled(value);

    if(value)
    {
        QString generatedThreadTitle;
        generatedThreadTitle+=ui->userName_lineEdit->text();
        if(!ui->gameName_lineEdit->text().isEmpty())
            generatedThreadTitle+=" ["+ui->gameName_lineEdit->text()+"]";
        if(!ui->scriptName_lineEdit->text().isEmpty())
            generatedThreadTitle+=" \""+ui->scriptName_lineEdit->text()+"\"";
        generatedThreadTitle+=" "+ui->dateTimeEdit->dateTime().toString("dd/MM/yy");
        if(ui->nearCity_customTreeWidget->getCitiesChecked().size() == 1)
        generatedThreadTitle+=" - "+ui->nearCity_customTreeWidget->getCitiesChecked().at(0);

        ui->forumTitle_lineEdit->setText(generatedThreadTitle);
    }
    else
    {
        ui->forumTitle_lineEdit->setText("");
    }
}
