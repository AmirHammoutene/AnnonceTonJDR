#include "onecityselectiontreewidget.h"

OneCitySelectionTreeWidget::OneCitySelectionTreeWidget(QWidget *parent):CitiesSelectionTreeWidget(parent)
{
    configureItems();
    this->resizeColumnToContents(0);
    this->resizeColumnToContents(1);

    QObject::connect(this, SIGNAL( itemChanged ( QTreeWidgetItem * , int ) ), this, SLOT(itemCheckStateToggle(QTreeWidgetItem * , int)));
}

void OneCitySelectionTreeWidget::configureItems()
{
    for(QTreeWidgetItem *item : CitiesSelectionTreeWidget::getDownLevelItemsObjectsList())
    {
        item->setCheckState(1,Qt::Unchecked);
    }
}

void OneCitySelectionTreeWidget::setCityChecked(const QString &cityName)
{
    for(QTreeWidgetItem *item : CitiesSelectionTreeWidget::getDownLevelItemsObjectsList())
    {
        if(item->text(1) == cityName)
            item->setCheckState(1,Qt::Checked);
    }
}

void OneCitySelectionTreeWidget::itemCheckStateToggle(QTreeWidgetItem *item, int column)
{
    if(item->checkState(1) == Qt::Checked)
    {
        for(QTreeWidgetItem* otherItem : CitiesSelectionTreeWidget::getDownLevelItemsObjectsList())
        {
            if(otherItem->text(1) != item->text(1))
                otherItem->setCheckState(1,Qt::Unchecked);
        }
    }
}
