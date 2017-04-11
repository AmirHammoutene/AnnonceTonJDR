#include "multicitiesselectiontreewidget.h"

MultiCitiesSelectionTreeWidget::MultiCitiesSelectionTreeWidget(QWidget *parent):CitiesSelectionTreeWidget(parent)
{
    configureItems();
    this->resizeColumnToContents(0);
    this->resizeColumnToContents(1);

    QObject::connect(this, SIGNAL( itemChanged ( QTreeWidgetItem * , int ) ), this, SLOT(itemCheckStateToggle(QTreeWidgetItem * , int)));
}

void MultiCitiesSelectionTreeWidget::configureItems()
{
    for(QTreeWidgetItem *item : CitiesSelectionTreeWidget::getItemsObjectsList())
    {
        if(item->text(0) == "")
            item->setCheckState(1,Qt::Checked);
        else
            item->setCheckState(0,Qt::Checked);
    }
}

void MultiCitiesSelectionTreeWidget::itemCheckStateToggle(QTreeWidgetItem *item, int column)
{
    if(column == 0)
    {
        for(int i = 0 ; i < item->childCount() ; i++)
        {
            item->child(i)->setCheckState(1,item->checkState(0));
        }
    }
}

void MultiCitiesSelectionTreeWidget::checkAll()
{
    for(QTreeWidgetItem * topItem : CitiesSelectionTreeWidget::getTopLevelItemsObjectsList())
    {
        topItem->setCheckState(0,Qt::Unchecked);
        topItem->setCheckState(0,Qt::Checked);
    }
}

void MultiCitiesSelectionTreeWidget::uncheckAll()
{
    for(QTreeWidgetItem * topItem : CitiesSelectionTreeWidget::getTopLevelItemsObjectsList())
    {
        topItem->setCheckState(0,Qt::Checked);
        topItem->setCheckState(0,Qt::Unchecked);
    }
}
