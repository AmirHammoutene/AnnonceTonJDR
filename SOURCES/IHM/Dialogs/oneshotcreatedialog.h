#ifndef ONESHOTCREATEDIALOG_H
#define ONESHOTCREATEDIALOG_H

/*
 * Dialog widget used to  create or edit a One Shot Game
 * Only one object of this class may exists, we use singleton pattern.
 *
*/

#include <QDialog>
#include <QPair>
#include "oneshoteventinfo.h"

namespace Ui {
class OneShotCreateDialog;
}



class OneShotCreateDialog : public QDialog
{
    Q_OBJECT

private:
    OneShotCreateDialog(QWidget *parent = 0, const OneShotEventInfo & oldInfo = OneShotEventInfo());
    ~OneShotCreateDialog();

    Ui::OneShotCreateDialog *ui;

    static OneShotCreateDialog* m_instance;
    OneShotEventInfo m_oldEventInfo;

    OneShotCreateDialog& operator= (const OneShotCreateDialog&) = delete;
    OneShotCreateDialog (const OneShotCreateDialog&) = delete;

public:
    static OneShotCreateDialog *getInstance(QWidget *parent = 0, const OneShotEventInfo & oldInfo = OneShotEventInfo());
    OneShotEventInfo synchronizeInfoWithWidget(OneShotEventInfo &info); //Data are set to the widget parameters
    void synchronizeWidgetWithOldEventInfo(); //Set the widget parameters to the 'old data' = data we load in the widget in case of editing
    void setOldEventInfo(const OneShotEventInfo & oldInfo = OneShotEventInfo());

public slots:
    void sendRequest();
    void showPasswordClicked();
    void showPasswordReleased();
    void hideAge_toggled(bool value);
    void markFullChecked(bool value);
    void markCancelChecked(bool value);
    void promiseToCreateForumThreadChecked(bool value);

signals:
    void transfertCreateInfoSignal(OneShotEventInfo,OneShotEventInfo);
};

#endif // ONESHOTCREATEDIALOG_H
