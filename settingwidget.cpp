#include "settingwidget.h"
#include "ui_settingwidget.h"
#include <QButtonGroup>
#include "eventfilterobj.h"
#include <QFileDialog>
SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    signalsAndslots();

    installEventFilter(new eventFilterObj);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::signalsAndslots()
{
    QButtonGroup* roleCheckboxGroup = new QButtonGroup(this);    //选项组  不能同时选中
    roleCheckboxGroup->addButton(ui->role1checkBox);
    roleCheckboxGroup->addButton(ui->role2checkBox);
    roleCheckboxGroup->addButton(ui->role3checkBox);
    roleCheckboxGroup->setExclusive(true);
    //人物模型选择
    connect(roleCheckboxGroup,QOverload<QAbstractButton*,bool>::of(&QButtonGroup::buttonToggled),this,[=](QAbstractButton* btn,bool checked){
        if(btn == ui->role1checkBox){
            emit roleModelChanged(0);
        }
        else if(btn == ui->role2checkBox){
            emit roleModelChanged(1);
        }
        else if(btn == ui->role3checkBox){
            emit roleModelChanged(2);
        }
    });
    ui->role1checkBox->setChecked(true);

    //人物心情选择
    connect(ui->radioButton_1,&QRadioButton::toggled,this,[=](){
        emit roleMoodChanged(0);
    });
    connect(ui->radioButton_2,&QRadioButton::toggled,this,[=](){
        emit roleMoodChanged(1);
    });
    connect(ui->radioButton_3,&QRadioButton::toggled,this,[=](){
        emit roleMoodChanged(2);
    });
    connect(ui->radioButton_4,&QRadioButton::toggled,this,[=](){
        emit roleMoodChanged(3);
    });

    ui->radioButton_1->setChecked(true);



}

void SettingWidget::on_closeBtn_clicked()
{
    this->hide();
}

void SettingWidget::on_setBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void SettingWidget::on_role1Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void SettingWidget::on_role2Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void SettingWidget::on_role3Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void SettingWidget::on_pushButton_clicked()
{
    const QString& filename = QFileDialog::getOpenFileName(this,"选择背景","./","Image (*.png *.jpg)");
    if(filename.isEmpty()){
        qWarning("请选择壁纸");
    }
    emit bkImageChanged(filename);
}
