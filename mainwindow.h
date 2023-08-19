#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSystemTrayIcon>
class QLabel;
class QPushButton;
class SettingWidget;
class DesktopWidget;
class QSystemTrayIcon;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void  updateRoleAnimation();
    void initbtn();
    void mousePressEvent(QMouseEvent* event) override;

    void initTyayIcon();
private:
    QLabel* m_centraLabel;
    qint8 curframe;     //当前帧
    qint8 roleModel;    //角色模型
    qint8 roleMood;     //角色心情

    QPushButton* closebtn;
    QPushButton* setbtn;
    SettingWidget* settingWidget;
    DesktopWidget* desktopWidget;
    QSystemTrayIcon* icon;
};
#endif // MAINWINDOW_H
