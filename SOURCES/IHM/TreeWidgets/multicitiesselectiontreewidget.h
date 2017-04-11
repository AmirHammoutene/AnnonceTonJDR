#ifndef MULTICITIESSELECTIONTREEWIDGET_H
#define MULTICITIESSELECTIONTREEWIDGET_H

#include "citiesselectiontreewidget.h"

class MultiCitiesSelectionTreeWidget : public CitiesSelectionTreeWidget
{
    Q_OBJECT

public:
    explicit MultiCitiesSelectionTreeWidget(QWidget *parent);
    void configureItems() override;

public slots:
    void itemCheckStateToggle(QTreeWidgetItem * item, int column);
    void checkAll();
    void uncheckAll();
};

#endif // MULTICITIESSELECTIONTREEWIDGET_H
