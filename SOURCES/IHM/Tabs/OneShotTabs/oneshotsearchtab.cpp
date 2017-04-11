#include "oneshotsearchtab.h"
#include "ui_oneshotsearchtab.h"
#include "oneshotcreatedialog.h"

OneShotSearchTab::OneShotSearchTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OneShotSearchTab)
{
    ui->setupUi(this);

    ui->fromDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->toDateTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(3600));

    QObject::connect(ui->regionsSelectAll_button, SIGNAL( released() ), ui->citiesSelectionTreeWidget , SLOT( checkAll() ));
    QObject::connect(ui->regionsUnselectAll_button, SIGNAL( released() ), ui->citiesSelectionTreeWidget , SLOT( uncheckAll() ));
    QObject::connect(ui->createOneShot_button, SIGNAL( released() ), this, SLOT( openOneShotCreationDialog() ));
    QObject::connect(ui->customDateTime_radio, SIGNAL( toggled(bool) ), this, SLOT( customDateTimeToggled(bool) ) );
    QObject::connect(ui->search_button, SIGNAL( released() ), this, SLOT( searchPushed() ) );
}

OneShotSearchTab::~OneShotSearchTab()
{
    delete ui;
}

void OneShotSearchTab::openOneShotCreationDialog()
{
    OneShotCreateDialog::getInstance(this)->show();
}

void OneShotSearchTab::customDateTimeToggled(bool value)
{
    ui->customDateTimeSelection_widget->setEnabled(value);
}

void OneShotSearchTab::searchPushed()
{
    OneShotEventSearchFilter searchFilter;
    synchronizeWidgetWithSearchFilter(searchFilter);
    emit launchSearch(searchFilter);
}

void OneShotSearchTab::synchronizeWidgetWithSearchFilter(OneShotEventSearchFilter &searchFilter)
{
    searchFilter.setUserNameFilter(ui->userName_lineEdit->text());
    searchFilter.setMinimumUserAgeFilter(ui->userAgeMin_spinBox->value());
    searchFilter.setMaximumUserAgeFilter(ui->userAgeMax_spinBox->value());
    searchFilter.setShowFullGameFilter(ui->showFull_checkBox->checkState() == Qt::Checked);
    searchFilter.setShowCancelledGameFilter(ui->showCancelled_checkBox->checkState() == Qt::Checked);
    searchFilter.setNearCitiesFilter(ui->citiesSelectionTreeWidget->getCitiesChecked());
    searchFilter.setFromDateTimeFilter(ui->fromDateTimeEdit->dateTime());
    searchFilter.setToDateTimeFilter(ui->toDateTimeEdit->dateTime());
    searchFilter.setGameNameFilter(ui->gameName_lineEdit->text());
    searchFilter.setShowGameCommercial(ui->gameTypeCommercial_checkBox->checkState() == Qt::Checked);
    searchFilter.setShowGameAmateur(ui->gameTypeAmateur_checkBox->checkState() == Qt::Checked);
    searchFilter.setShowGamePersonal(ui->gameTypePersonal_checkBox->checkState() == Qt::Checked);
    searchFilter.setShowScriptCommercial(ui->scriptTypeCommercial_checkBox->checkState() == Qt::Checked);
    searchFilter.setShowScriptWeb(ui->scriptTypeWeb_checkBox->checkState() == Qt::Checked);
    searchFilter.setShowScriptPersonal(ui->scriptTypePersonal_checkBox->checkState() == Qt::Checked);


    auto placeTypeIndex = ui->placeType_comboBox->currentIndex();
    switch (placeTypeIndex) {
    case 0:
        searchFilter.setPlaceTypeFilter(PlaceTypeFilter::NEVERMIND);
        break;
    case 1:
        searchFilter.setPlaceTypeFilter(PlaceTypeFilter::HOME);
        break;
    case 2:
        searchFilter.setPlaceTypeFilter(PlaceTypeFilter::BAR);
        break;
    case 3:
        searchFilter.setPlaceTypeFilter(PlaceTypeFilter::ROOM);
        break;
    default:
        searchFilter.setPlaceTypeFilter(PlaceTypeFilter::OUTSIDE);
        break;
    }

    auto userSexeIndex = ui->userSexe_comboBox->currentIndex();
    switch (userSexeIndex) {
    case 0:
        searchFilter.setUserSexeFilter(SexeFilter::NEVERMIND);
        break;
    case 1:
        searchFilter.setUserSexeFilter(SexeFilter::WOMAN);
        break;
    default:
        searchFilter.setUserSexeFilter(SexeFilter::MAN);
        break;
    }

    auto eventTypeIndex = ui->eventType_comboBox->currentIndex();
    switch (eventTypeIndex) {
    case 0:
        searchFilter.setEventTypeFilter(EventTypeFilter::NEVERMIND);
        break;
    case 1:
        searchFilter.setEventTypeFilter(EventTypeFilter::SPECIAL);
        break;
    default:
        searchFilter.setEventTypeFilter(EventTypeFilter::NORMAL);
        break;
    }

    auto numberGameMastersIndex = ui->numberGameMasters_comboBox->currentIndex();
    switch (numberGameMastersIndex) {
    case 0:
        searchFilter.setNumberGameMastersFilter(NumberGameMastersFilter::NEVERMIND);
        break;
    case 1:
        searchFilter.setNumberGameMastersFilter(NumberGameMastersFilter::ONE);
        break;
    default:
        searchFilter.setNumberGameMastersFilter(NumberGameMastersFilter::SEVERAL);
        break;
    }

    auto numberGamesIndex = ui->numberGames_comboBox->currentIndex();
    switch (numberGamesIndex) {
    case 0:
        searchFilter.setNumberGamesFilter(NumberGamesFilter::NEVERMIND);
        break;
    case 1:
        searchFilter.setNumberGamesFilter(NumberGamesFilter::ONE);
        break;
    default:
        searchFilter.setNumberGamesFilter(NumberGamesFilter::SEVERAL);
        break;
    }

    auto numberSessionsIndex = ui->numberSessions_comboBox->currentIndex();
    switch (numberSessionsIndex) {
    case 0:
        searchFilter.setNumberSessionsFilter(NumberSessionsFilter::NEVERMIND);
        break;
    case 1:
        searchFilter.setNumberSessionsFilter(NumberSessionsFilter::ONE);
        break;
    default:
        searchFilter.setNumberSessionsFilter(NumberSessionsFilter::SEVERAL);
        break;
    }

    if(ui->searchFutur_radioButton->isChecked())
        searchFilter.setDateSearchFilter(DateSearchFilter::FUTUR);
    else if(ui->searchPast_radioButton->isChecked())
        searchFilter.setDateSearchFilter(DateSearchFilter::PAST);
    else
        searchFilter.setDateSearchFilter(DateSearchFilter::CHOOSE);

    auto underagesIndex = ui->underages_horizontalSlider->value();
    switch (underagesIndex) {
    case 0:
        searchFilter.setPermissionUnderagesFilter(PermissionUnderagesFilter::NO);
        break;
    case 1:
        searchFilter.setPermissionUnderagesFilter(PermissionUnderagesFilter::NEVERMIND);
        break;
    default:
        searchFilter.setPermissionUnderagesFilter(PermissionUnderagesFilter::YES);
        break;
    }

    auto drinkFoodIndex = ui->drinkFood_horizontalSlider->value();
    switch (drinkFoodIndex) {
    case 0:
        searchFilter.setDrinkFoodPermissionFilter(DrinkFoodPermissionFilter::FORBIDDEN);
        break;
    case 1:
        searchFilter.setDrinkFoodPermissionFilter(DrinkFoodPermissionFilter::NEVERMIND);
        break;
    default:
        searchFilter.setDrinkFoodPermissionFilter(DrinkFoodPermissionFilter::BRING);
        break;
    }

    auto alcoholIndex = ui->alcohol_horizontalSlider->value();
    switch (alcoholIndex) {
    case 0:
        searchFilter.setAlcoholPermissionFilter(AlcoholPermissionFilter::FORBIDDEN);
        break;
    case 1:
        searchFilter.setAlcoholPermissionFilter(AlcoholPermissionFilter::NEVERMIND);
        break;
    default:
        searchFilter.setAlcoholPermissionFilter(AlcoholPermissionFilter::BRING);
        break;
    }

    auto smokeIndex = ui->smoke_horizontalSlider->value();
    switch (smokeIndex) {
    case 0:
        searchFilter.setSmokeInsidePermissionFilter(SmokeInsidePermissionFilter::FORBIDDEN);
        break;
    case 1:
        searchFilter.setSmokeInsidePermissionFilter(SmokeInsidePermissionFilter::NEVERMIND);
        break;
    default:
        searchFilter.setSmokeInsidePermissionFilter(SmokeInsidePermissionFilter::PERMITTED);
        break;
    }

}
