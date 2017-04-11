#ifndef ONECITYSELECTIONTREEWIDGET_H
#define ONECITYSELECTIONTREEWIDGET_H

#include "citiesselectiontreewidget.h"

class OneCitySelectionTreeWidget : public CitiesSelectionTreeWidget
{
    Q_OBJECT

public:
    explicit OneCitySelectionTreeWidget(QWidget *parent);
    void configureItems() override;
    void setCityChecked(const QString & cityName);

public slots:
    void itemCheckStateToggle(QTreeWidgetItem * item, int column);
};

#endif // ONECITYSELECTIONTREEWIDGET_H
