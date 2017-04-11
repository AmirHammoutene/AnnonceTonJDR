#include "oneshotresultstab.h"
#include "ui_oneshotresultstab.h"
#include "oneshotresultstabstorage.h"
#include "oneshotresultstabgeometry.h"
#include "oneshotresultstabtitles.h"
#include <QDomDocument>
#include <QFile>
#include <QDebug>

OneShotResultsTab::OneShotResultsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OneShotResultsTab)
{
    ui->setupUi(this);
    buildHeaders();
    ui->tableWidget->sortByColumn(0,Qt::AscendingOrder);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(OneShotResultsTabGeometry::cellsHeight);
    ui->tableWidget->setIconSize(QSize(OneShotResultsTabGeometry::cellsHeight, OneShotResultsTabGeometry::cellsHeight));
    QObject::connect(ui->tableWidget, SIGNAL( cellDoubleClicked(int,int) ), this, SLOT( openPageFromCell(int,int) ));
}

OneShotResultsTab::~OneShotResultsTab()
{
    delete ui;
}

void OneShotResultsTab::buildHeaders()
{

    QDomDocument doc("headers");
    QFile file(":/oneShotResultsHeaders.xml");
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    QString error;
    int line,column;
    if (!doc.setContent(&file,&error,&line, &column))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomNode currentNode = docElem.firstChild();

    while(!currentNode.isNull()) {
        QDomElement currentElement = currentNode.toElement();
        if(!currentElement.isNull())
        {
            auto index = ui->tableWidget->columnCount();
            ui->tableWidget->setColumnCount(index+1);
            QTableWidgetItem * headerItem = new QTableWidgetItem();
            headerItem->setText(currentElement.attribute("title","#noColumnName"));
            headerItem->setTextAlignment(Qt::AlignHCenter);

            ui->tableWidget->setHorizontalHeaderItem(index,headerItem);
            ui->tableWidget->horizontalHeader()->resizeSection(index,currentElement.attribute("size","100").toInt());

            OneShotResultsTabStorage::columnForInfoName.insert(currentElement.attribute("infoCodeName","#noInfoCodeName"),index);
        }
        currentNode = currentNode.nextSibling();
    }
}

const OneShotEventSearchFilter & OneShotResultsTab::getSearchFilter() const
{
    return searchFilter;
}

void OneShotResultsTab::setSearchFilter(const OneShotEventSearchFilter &value)
{
    searchFilter = value;
}

void OneShotResultsTab::openPageFromCell(int row, int column)
{
    QTableWidgetItem *item = ui->tableWidget->item(row,column);
    OneShotEventInfo data = qvariant_cast<OneShotEventInfo>(item->data(Qt::UserRole));
    emit openPageWithInfo(data);

}

void OneShotResultsTab::insertInfo(OneShotEventInfo info)
{
    if(!searchFilter.matchInfo(info))
        return;

    ui->tableWidget->setSortingEnabled(false);

    auto rowNumber = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowNumber);

    QMap<QString, int>::iterator i;
    for (i = OneShotResultsTabStorage::columnForInfoName.begin(); i != OneShotResultsTabStorage::columnForInfoName.end(); ++i)
    {
        QTableWidgetItem * widgetItem = new QTableWidgetItem();

        if(i.key() == "eventDateTime")
        {
            widgetItem->setText(info.eventDateTime().toString("yyyy/MM(MMMM)/dd hh:mm"));
        }
        else if(i.key() == "nearCity")
        {
            widgetItem->setText(info.nearCity());
            widgetItem->setTextAlignment(Qt::AlignCenter);
            QFont font;
            font.setBold(true);
            widgetItem->setFont(font);
        }
        else if(i.key() == "realAddress")
        {
            widgetItem->setText(info.realAddress());
            widgetItem->setTextAlignment(Qt::AlignCenter);
        }
        else if(i.key() == "userName")
        {
            widgetItem->setText(info.userName());
            widgetItem->setTextAlignment(Qt::AlignCenter);
            QFont font;
            font.setBold(true);
            widgetItem->setFont(font);
            QColor color(0,0,0);
            switch(info.userSexe())
            {
            case Sexe::WOMAN:
                color.setNamedColor("hotpink");
                break;
            case Sexe::MAN:
                color.setNamedColor("blue");
                break;
            default:
                break;
            }
            widgetItem->setTextColor(color);
        }
        else if(i.key() == "userAge")
        {
            if(info.shareUserAge())
                widgetItem->setText(QString::number(info.userAge()));
            else
            {
                widgetItem->setSizeHint(QSize(OneShotResultsTabGeometry::cellsHeight, OneShotResultsTabGeometry::cellsHeight));
                widgetItem->setIcon(QIcon(":/interrogationPoint.png"));
                widgetItem->setToolTip(OneShotResultsTabTooltips::ageNotShared);
            }

            widgetItem->setTextAlignment(Qt::AlignCenter);
        }
        else if(i.key() == "specialEvent")
        {
            if(info.specialEvent())
            {
                widgetItem->setSizeHint(QSize(OneShotResultsTabGeometry::cellsHeight, OneShotResultsTabGeometry::cellsHeight));
                widgetItem->setIcon(QIcon(":/star.png"));
                widgetItem->setTextAlignment(Qt::AlignCenter);
                widgetItem->setToolTip(OneShotResultsTabTooltips::specialEvent);
            }

        }
        else if(i.key() == "gameName")
        {
            widgetItem->setText(info.gameName());
        }
        else if(i.key() == "scriptName")
        {
            widgetItem->setText(info.scriptName());
        }
        else if(i.key() == "playersNumberRatio")
        {

            QColor color(0,0,0);
            if(info.cancelledGame())
            {
                widgetItem->setText("[ANNULE]");
                color = QColor(166,0,0);
            }
            else if(info.fullGame())
            {
                widgetItem->setText("[COMPLET]");
                color = QColor(166,0,0);
            }
            else
            {
                widgetItem->setText(QString::number(info.registeredPlayersNumber())+" / "+QString::number(info.maximumPlayersNumber()));
            }

            QFont font;
            font.setBold(true);
            widgetItem->setFont(font);
            widgetItem->setTextColor(color);
            widgetItem->setTextAlignment(Qt::AlignCenter);
        }
        else if(i.key() == "registeredUnderages")
        {
            if(info.registeredUnderages())
            {
                widgetItem->setText("oui");
                widgetItem->setToolTip(OneShotResultsTabTooltips::registeredUnderages);
            }
            else
            {
                widgetItem->setText("non");
                widgetItem->setToolTip(OneShotResultsTabTooltips::noRegisteredUnderages);
            }
            widgetItem->setTextAlignment(Qt::AlignCenter);

        }
        else if(i.key() == "permittedUnderages")
        {
            if(info.permittedUnderages())
            {
                widgetItem->setText("oui");
                widgetItem->setToolTip(OneShotResultsTabTooltips::permittedUnderages);
            }
            else
            {
                widgetItem->setText("non");
                widgetItem->setToolTip(OneShotResultsTabTooltips::notPermittedUnderages);
            }

            widgetItem->setTextAlignment(Qt::AlignCenter);

        }
        else if(i.key() == "drinkFoodPermission")
        {
            widgetItem->setSizeHint(QSize(OneShotResultsTabGeometry::cellsHeight, OneShotResultsTabGeometry::cellsHeight));
            if(info.drinkFoodPermission() == DrinkFoodPermission::BRING)
            {
                widgetItem->setIcon(QIcon(":/drinkFoodBring.png"));
                widgetItem->setToolTip(OneShotResultsTabTooltips::drinkFoodBring);
            }
            else if(info.drinkFoodPermission() == DrinkFoodPermission::NEVERMIND)
            {
                widgetItem->setIcon(QIcon(":/drinkFoodOK.png"));
                widgetItem->setToolTip(OneShotResultsTabTooltips::drinkFoodOk);
            }
            else
            {
                widgetItem->setIcon(QIcon(":/drinkFoodNo.png"));
                widgetItem->setToolTip(OneShotResultsTabTooltips::drinkFoodNo);
            }

            widgetItem->setTextAlignment(Qt::AlignCenter);
        }
        else if(i.key() == "alcoholPermission")
        {
            widgetItem->setSizeHint(QSize(OneShotResultsTabGeometry::cellsHeight, OneShotResultsTabGeometry::cellsHeight));
            if(info.alcoholPermission() == AlcoholPermission::BRING)
            {
                widgetItem->setIcon(QIcon(":/alcoholBring.png"));
                widgetItem->setToolTip(OneShotResultsTabTooltips::alcoholBring);
            }
            else if(info.alcoholPermission() == AlcoholPermission::NEVERMIND)
            {
                widgetItem->setIcon(QIcon(":/alcoholOK.png"));
                widgetItem->setToolTip(OneShotResultsTabTooltips::alcoholOk);
            }
            else
            {
                widgetItem->setIcon(QIcon(":/alcoholNo.png"));
                widgetItem->setToolTip(OneShotResultsTabTooltips::alcoholNo);
            }

            widgetItem->setTextAlignment(Qt::AlignCenter);
        }
        else if(i.key() == "smokeInsidePermission")
        {
            widgetItem->setSizeHint(QSize(OneShotResultsTabGeometry::cellsHeight, OneShotResultsTabGeometry::cellsHeight));
            if(info.smokeInsidePermission() == SmokeInsidePermission::PERMITTED)
            {
                widgetItem->setIcon(QIcon(":/smokeYes.png"));
                widgetItem->setToolTip(OneShotResultsTabTooltips::smokeYes);
            }
            else
            {
                widgetItem->setIcon(QIcon(":/smokeNo.png"));
                widgetItem->setToolTip(OneShotResultsTabTooltips::smokeNo);
            }

            widgetItem->setTextAlignment(Qt::AlignCenter);
        }

        //On each item of the row, we set a user role data
        widgetItem->setData(Qt::UserRole, QVariant::fromValue(info));

        ui->tableWidget->setItem(rowNumber, i.value(), widgetItem);
    }


    ui->tableWidget->setSortingEnabled(true);
}

















