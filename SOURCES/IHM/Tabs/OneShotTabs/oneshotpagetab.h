#ifndef ONESHOTPAGETAB_H
#define ONESHOTPAGETAB_H

#include "oneshoteventinfo.h"
#include <QWidget>
#include <QMap>

namespace Ui {
class OneShotPageTab;
}

class OneShotPageTab : public QWidget
{
    Q_OBJECT

public:
    explicit OneShotPageTab(QWidget *parent = 0);
    ~OneShotPageTab();
    void loadRandomSentences(); //Sentences are randomly choosen from the xml file

public slots:
    void fillInfo(OneShotEventInfo i_info);
    void edit();

private:
    Ui::OneShotPageTab *ui;
    QMap<QString,QString> randomSentences;
    OneShotEventInfo info;

};

#endif // ONESHOTPAGETAB_H
