#ifndef CITIESSELECTIONTREEWIDGET_H
#define CITIESSELECTIONTREEWIDGET_H

/*
 * Parent class widget, only children are used
 * Those tree widgets are used to select one or several cities listed in the ini file
 * This class can not be instantiated
 */

#include <QObject>
#include <QList>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class CitiesSelectionTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    CitiesSelectionTreeWidget(QWidget *parent);
    void fillCitiesNamesMap();
    void addCitiesInTree();
    virtual void configureItems() = 0; //Set the check state of each row
    QList<QTreeWidgetItem *> getItemsObjectsList(); //Returns all the items of the tree
    QList<QTreeWidgetItem *> getTopLevelItemsObjectsList(); //Returns all the regions items
    QList<QTreeWidgetItem *> getDownLevelItemsObjectsList(); //Return all the cities items
    QStringList getCitiesChecked();



};

#endif // CITIESSELECTIONTREEWIDGET_H
