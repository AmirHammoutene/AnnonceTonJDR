#include "citiesselectiontreewidget.h"
#include "citiesselectiontreewidgettitles.h"

#include <QSettings>
#include <QDebug>

CitiesSelectionTreeWidget::CitiesSelectionTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    setHeaderHidden(true);
    setColumnCount(2);
    fillCitiesNamesMap();
    addCitiesInTree();


}

void CitiesSelectionTreeWidget::fillCitiesNamesMap()
{
    QSettings iniFile(":/listOfCities.ini", QSettings::IniFormat);
    QStringList regions = iniFile.allKeys();
    for(QString currentRegion : regions)
    {
        QStringList currentCities = iniFile.value(currentRegion,QStringList()).toStringList();
        if(!currentCities.isEmpty())
        {
            CitiesSelectionTreeWidgetTitles::mapOfCitiesNames.insert(currentRegion,currentCities);
        }

    }

}

void CitiesSelectionTreeWidget::addCitiesInTree()
{
    QStringList regions = CitiesSelectionTreeWidgetTitles::mapOfCitiesNames.keys();
    for(QString currentRegion : regions)
    {
        QStringList currentCities = CitiesSelectionTreeWidgetTitles::mapOfCitiesNames.value(currentRegion,QStringList());
        if(!currentCities.isEmpty())
        {
            QTreeWidgetItem *currentRegionItem = new QTreeWidgetItem(this,QStringList(currentRegion));
            for(QString currentCity : currentCities)
            {
                QStringList columnsText = {"", currentCity};
                QTreeWidgetItem *currentCityItem = new QTreeWidgetItem(currentRegionItem, columnsText);
                currentRegionItem->addChild(currentCityItem);
            }
            this->addTopLevelItem(currentRegionItem);
        }
    }
}

QList<QTreeWidgetItem *> CitiesSelectionTreeWidget::getItemsObjectsList()
{
    QList<QTreeWidgetItem *> resultList;

    for(int i = 0 ; i < topLevelItemCount() ; i++)
    {
        QTreeWidgetItem *topItem = topLevelItem(i);
        resultList.append(topItem);
        for(int j = 0 ; j < topItem->childCount() ; j++)
        {
            resultList.append(topItem->child(j));
        }
    }

    return resultList;
}

QList<QTreeWidgetItem *> CitiesSelectionTreeWidget::getTopLevelItemsObjectsList()
{
    QList<QTreeWidgetItem *> resultList;

    for(int i = 0 ; i < topLevelItemCount() ; i++)
    {
        QTreeWidgetItem *topItem = topLevelItem(i);
        resultList.append(topItem);
    }

    return resultList;
}

QList<QTreeWidgetItem *> CitiesSelectionTreeWidget::getDownLevelItemsObjectsList()
{
    QList<QTreeWidgetItem *> resultList;

    for(int i = 0 ; i < topLevelItemCount() ; i++)
    {
        QTreeWidgetItem *topItem = topLevelItem(i);
        for(int j = 0 ; j < topItem->childCount() ; j++)
        {
            resultList.append(topItem->child(j));
        }
    }

    return resultList;
}

QStringList CitiesSelectionTreeWidget::getCitiesChecked()
{
    QStringList resultList;

    for(QTreeWidgetItem * topItem : getTopLevelItemsObjectsList())
    {
        for(int i = 0 ; i < topItem->childCount() ; i++)
        {
            if(topItem->child(i)->checkState(1) == Qt::Checked)
                resultList.append(topItem->child(i)->text(1));
        }
    }
    return resultList;
}























