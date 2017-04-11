#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindowtitles.h"
#include "mainwindowimages.h"
#include "mainwindowgeometry.h"
#include "oneshotcreatedialog.h"
#include "insertrowindbworker.h"
#include "searchrowsindbworker.h"
#include <QThread>
#include <QMessageBox>
#include <QDesktopServices>


unsigned int MainWindow::oneShotSearchTabsOpened = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    import_images();
    build_HelpMenu();

    // By default, in the designer of QtCreator, two tabs appear when we create a QTabWidget
    // Since it's much more easier to manipulate tabs via the designer, we used it and now delete the 2nd tab for the main tabWidget,
    // and all tabs for sub tabWidgets
    ui->mainTabWidget->removeTab(1);
    ui->oneshot_tabWidget->removeTab(1);
    ui->oneshot_tabWidget->removeTab(0);

    auto *oneShotSearchTab = new OneShotSearchTab(this);
    auto oneShotSearchTabIndex = ui->oneshot_tabWidget->addTab(oneShotSearchTab,MainWindowTitle::searchTabName_OneShot);
    // Setting the search tab not closable
    ui->oneshot_tabWidget->tabBar()->tabButton(oneShotSearchTabIndex, QTabBar::RightSide)->resize(0, 0);

    MainWindow::oneShotSearchTabsOpened = 0;


    QObject::connect(ui->oneshot_tabWidget, SIGNAL( tabCloseRequested(int) ), this, SLOT( oneShotCloseTab(int) ) );
    QObject::connect(oneShotSearchTab, SIGNAL( launchSearch(OneShotEventSearchFilter) ), this, SLOT( oneShotSearchLaunched(OneShotEventSearchFilter) ) );
    QObject::connect(OneShotCreateDialog::getInstance(this), SIGNAL( transfertCreateInfoSignal(OneShotEventInfo,OneShotEventInfo) ), this, SLOT( transfertOneResultInfoSlot(OneShotEventInfo,OneShotEventInfo) ) );

    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::build_HelpMenu()
{
    ui->helpButton->setMinimumSize(MainWindowImageSize::helpIcon_width,MainWindowImageSize::helpIcon_height);
    ui->helpButton->setIcon(MainWindowIcon::interrogationPoint);
    ui->helpButton->setIconSize(QSize(MainWindowImageSize::helpIcon_width,MainWindowImageSize::helpIcon_height));

    QMenu* helpMenu = new QMenu(ui->helpButton);
    QAction* weblink_helpMenuAction = helpMenu->addAction(MainWindowTitle::weblinkHelpButton_title);
    QAction* about_helpMenuAction = helpMenu->addAction(MainWindowTitle::aboutHelpButton_title);

    connect(weblink_helpMenuAction, SIGNAL( triggered(bool) ), this, SLOT( openWebOfficialLink() ));
    connect(about_helpMenuAction, SIGNAL( triggered(bool) ), this, SLOT( openSoftwareInfo() ));

    ui->helpButton->setMenu(helpMenu);
}

void MainWindow::import_images()
{
    MainWindowIcon::interrogationPoint.addFile(":/interrogationPoint.png");
}

void MainWindow::oneShotSearchLaunched(OneShotEventSearchFilter searchFilter)
{
    MainWindow::oneShotSearchTabsOpened += 1;

    OneShotResultsTab *newResultsTab = new OneShotResultsTab(this);
    newResultsTab->setSearchFilter(searchFilter);

    QString title = MainWindowTitle::resultsTabName_OneShot+" #"+QString::number(MainWindow::oneShotSearchTabsOpened);

    int newTabIndex = ui->oneshot_tabWidget->addTab(newResultsTab,title);

	//Connect the click to a row of the results to the detail page opening procedure
    QObject::connect(newResultsTab, SIGNAL( openPageWithInfo(OneShotEventInfo) ),this, SLOT( openOneShotPageFromInfo(OneShotEventInfo) ));

    //Search in database worker is created, assign to a thread, and connected to delete procedure
    QThread* thread = new QThread;
    SearchRowsInDBWorker* searchRowsWorker = new SearchRowsInDBWorker();
    searchRowsWorker->setSearchFilter(searchFilter);
    searchRowsWorker->moveToThread(thread);
    connect(thread, SIGNAL( started() ), searchRowsWorker, SLOT( process() ));
    QObject::connect(searchRowsWorker, SIGNAL( sendInfo(OneShotEventInfo) ),newResultsTab, SLOT( insertInfo(OneShotEventInfo) ));
    connect(searchRowsWorker, SIGNAL( finished() ), thread, SLOT( quit() ));
    connect(searchRowsWorker, SIGNAL( finished() ), searchRowsWorker, SLOT( deleteLater() ));
    connect(thread, SIGNAL( finished() ), thread, SLOT( deleteLater() ));
    thread->start();

    //Swap to the result page view
    ui->oneshot_tabWidget->setCurrentIndex(newTabIndex);

}

void MainWindow::oneShotCloseTab(int index)
{
    ui->oneshot_tabWidget->removeTab(index);
}

void MainWindow::transfertOneResultInfoSlot(OneShotEventInfo info, OneShotEventInfo oldInfo)
{
    //Insert data in database worker is created, assign to a thread, and connected to delete procedure
    QThread* thread = new QThread;
    InsertRowInDBWorker* insertRowWorker = new InsertRowInDBWorker();
    insertRowWorker->setEventInfo(info);
    insertRowWorker->setOldEventInfo(oldInfo);
    insertRowWorker->moveToThread(thread);
    connect(insertRowWorker, SIGNAL( success(bool,QString) ), this, SLOT( insertRowInDBWarning(bool, QString) ));
    connect(thread, SIGNAL( started() ), insertRowWorker, SLOT( process() ));
    connect(insertRowWorker, SIGNAL( finished() ), thread, SLOT( quit() ));
    connect(insertRowWorker, SIGNAL( finished() ), insertRowWorker, SLOT( deleteLater() ));
    connect(thread, SIGNAL( finished() ), thread, SLOT( deleteLater() ));
    thread->start();

}

void MainWindow::openOneShotPageFromInfo(OneShotEventInfo info)
{
    OneShotPageTab *newPageTab = new OneShotPageTab(this);
    QString pageTitle = info.userName()+" - "+info.eventDateTime().toString("d MMM h:mm");

    int newTabIndex = ui->oneshot_tabWidget->addTab(newPageTab,pageTitle);
    newPageTab->fillInfo(info);

    //Swap to the detail info page view
    ui->oneshot_tabWidget->setCurrentIndex(newTabIndex);
}

void MainWindow::insertRowInDBWarning(bool success, QString text)
{
    if(success)
    {
        QMessageBox::information(this,MainWindowTitle::lastRequestSuccessPopupTitle,MainWindowTitle::lastRequestSuccessPopupMessage);
    }
    else
    {
        QMessageBox::critical(this,MainWindowTitle::lastRequestFailedPopupTitle,MainWindowTitle::lastRequestFailedPopupMessage+text);
    }
}

void MainWindow::openWebOfficialLink()
{
    QDesktopServices::openUrl(QUrl("http://www.annoncetonjdr.fr"));
}

void MainWindow::openSoftwareInfo()
{
    QMessageBox::information(this,this->windowTitle(),MainWindowTitle::softwareInfo);
}
