#ifndef ONESHOTSEARCHTAB_H
#define ONESHOTSEARCHTAB_H

#include <QWidget>

#include "citiesselectiontreewidget.h"
#include "oneshoteventinfo.h"
#include "oneshoteventsearchfilter.h"

namespace Ui {
class OneShotSearchTab;
}

class OneShotSearchTab : public QWidget
{
    Q_OBJECT

public:
    explicit OneShotSearchTab(QWidget *parent = 0);
    ~OneShotSearchTab();

public slots:
    void openOneShotCreationDialog();
    void customDateTimeToggled(bool value);
    void searchPushed();
    void synchronizeWidgetWithSearchFilter(OneShotEventSearchFilter & searchFilter); //Filter data are set to the widget parameters

signals:
    void launchSearch(OneShotEventSearchFilter);

private:
    Ui::OneShotSearchTab *ui;
};

#endif // ONESHOTSEARCHTAB_H
