#ifndef ONESHOTRESULTSTAB_H
#define ONESHOTRESULTSTAB_H

#include <QWidget>
#include "oneshoteventinfo.h"
#include "oneshoteventsearchfilter.h"

namespace Ui {
class OneShotResultsTab;
}

class OneShotResultsTab : public QWidget
{
    Q_OBJECT

public:
    explicit OneShotResultsTab(QWidget *parent = 0);
    ~OneShotResultsTab();
    void buildHeaders();
    OneShotEventSearchFilter searchFilter;

    const OneShotEventSearchFilter & getSearchFilter() const;
    void setSearchFilter(const OneShotEventSearchFilter &value);

public slots:
    void openPageFromCell(int row, int column);
    void insertInfo(OneShotEventInfo info); //Insert one row from the database search results
private:
    Ui::OneShotResultsTab *ui;

signals:
    void openPageWithInfo(OneShotEventInfo);
};

#endif // ONESHOTRESULTSTAB_H
