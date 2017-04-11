#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "oneshotsearchtab.h"
#include "oneshotresultstab.h"
#include "oneshotpagetab.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static unsigned int oneShotSearchTabsOpened; //Number of results that has been already opened since the launch of the software (the new results tab will take a title 'Results #'+oneShotSearchTabsOpened+1)


private:
    void build_HelpMenu();
    void import_images();
    Ui::MainWindow *ui;

public slots:
    void oneShotSearchLaunched(OneShotEventSearchFilter searchFilter); //Run when the "Search" button is pushed in the One Shot search tab, it open a results tab and launch the sql worker
    void oneShotCloseTab(int index);
    void transfertOneResultInfoSlot(OneShotEventInfo,OneShotEventInfo); //Launch the sql insert row procedure, with 2 args : the data to insert, and to old data (if edited)
    void openOneShotPageFromInfo(OneShotEventInfo); //Open a tab with One Shot information in details
    void insertRowInDBWarning(bool, QString); //Open a message box with an acquitment text for insert data in database procedure
    void openWebOfficialLink();
    void openSoftwareInfo();

};

#endif // MAINWINDOW_H
