#include "mainwindow.h"
#include "eventfilterobj.h"
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include "settingwidget.h"
#include <QMenu>
#include <QApplication>
#include <QDebug>
#include "desktopwidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,m_centraLabel(new QLabel),curframe(0),roleModel(0),roleMood(0),settingWidget(new SettingWidget)
    ,desktopWidget(new DesktopWidget)
{
    desktopWidget->show();
    setWindowTitle("11");
    setFixedSize(200,300);

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Tool);   //设置无边框
    setAttribute(Qt::WA_TranslucentBackground);                //设置背景透明

    this->setCentralWidget(m_centraLabel);

    QTimer* updateTimer = new QTimer();
    updateTimer->callOnTimeout(this,&MainWindow::updateRoleAnimation);
    updateTimer->start(500);



    installEventFilter(new eventFilterObj(this));          //安装过滤器

    initbtn();
    initTyayIcon();

    connect(settingWidget,&SettingWidget::roleModelChanged,this,[=](int role){roleModel = role;});

    connect(settingWidget,&SettingWidget::roleMoodChanged,this,[=](int role){roleMood = role;});

    connect(settingWidget,&SettingWidget::bkImageChanged,desktopWidget,&DesktopWidget::setpixmap);
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateRoleAnimation()
{
    if(roleModel == 0)
        m_centraLabel->setStyleSheet(QString("image:url(://resource/desktopRole/summerGril/%1.png);").arg(curframe));
    else if(roleModel == 1)
        m_centraLabel->setStyleSheet(QString("image:url(://resource/desktopRole/littleBoy/%1.png);").arg(curframe));
    else
    {
        if(roleMood == 0)
            m_centraLabel->setStyleSheet(QString("image:url(://resource/desktopRole/blackGril/action1-happy/%1.png);").arg(curframe));
        else if(roleMood ==1)
            m_centraLabel->setStyleSheet(QString("image:url(://resource/desktopRole/blackGril/action2-sad/%1.png);").arg(curframe));
        else if(roleMood == 2)
            m_centraLabel->setStyleSheet(QString("image:url(://resource/desktopRole/blackGril/action3-naughty/%1.png);").arg(curframe));
        else
            m_centraLabel->setStyleSheet(QString("image:url(://resource/desktopRole/blackGril/action4-shy/%1.png);").arg(curframe));
    }
    curframe = (curframe+1) % 6;
}

void MainWindow::initbtn()
{
    closebtn = new QPushButton(this);
    setbtn = new QPushButton(this);

    closebtn->setFixedSize(20,20);
    closebtn->move(width()-40,30);
    closebtn->setObjectName("closebtn");

    setbtn->setFixedSize(20,20);
    setbtn->move(width()-40,55);
    setbtn->setObjectName("setbtn");

    this->setStyleSheet("QPushButton{border:none;background-color:rgba(205,205,205,200);}"
                        "QPushButton#closebtn{image:url(://resource/button/shut.png);}"
                        "QPushButton#setbtn{image:url(://resource/button/setting.png);}"
                        "QPushButton#closebtn:hover{background-color:rgb(232,17,35)}"
                        "QPushButton#setbtn:hover{background-color:rgb(53,169,240)}"
                        );

    connect(closebtn,&QPushButton::released,this,&MainWindow::close);

    connect(setbtn,&QPushButton::released,settingWidget,&SettingWidget::show);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        closebtn->setHidden(!closebtn->isHidden());
        setbtn->setHidden(!setbtn->isHidden());
    }
}

void MainWindow::initTyayIcon()
{
    icon = new QSystemTrayIcon(QIcon("://SuDio.ico"),this);
    QMenu* menu = new QMenu(this);
    menu->addAction("打开人物界面",this,&QMainWindow::showNormal);
    menu->addAction("最小化到托盘",this,&QMainWindow::showMinimized);
    menu->addAction("设置",settingWidget,&SettingWidget::show);
    menu->addSeparator();
    menu->addAction("退出程序",qApp,&QApplication::quit);


    icon->setContextMenu(menu);
    icon->show();

    connect(icon,&QSystemTrayIcon::activated,[=](QSystemTrayIcon::ActivationReason rea){
       if(rea == QSystemTrayIcon::ActivationReason::DoubleClick){
           if(this->windowState() & Qt::WindowState::WindowMinimized){
               this->showNormal();
           }
           else{
               this->showMinimized();
           }
       }
    });
}

