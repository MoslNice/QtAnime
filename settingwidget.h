#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();
    void signalsAndslots();
signals:
    void roleModelChanged(int model);
    void roleMoodChanged(int mood);
    void bkImageChanged(const QString& filename);

private slots:
    void on_closeBtn_clicked();

    void on_setBtn_clicked();

    void on_role1Btn_clicked();

    void on_role2Btn_clicked();

    void on_role3Btn_clicked();

    void on_pushButton_clicked();

private:
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
