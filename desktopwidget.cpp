#include "desktopwidget.h"
#include "finddesktophwnd.h"
DesktopWidget::DesktopWidget(QWidget *parent) : QLabel(parent)
{

    showFullScreen();
    setpixmap(":/resource/wallpaper/1.jpg");
    FindDektopHwnd::SetParent(this,nullptr);
}

void DesktopWidget::setpixmap(const QString &filename)
{
    if(QPixmap(filename).isNull()){
        return ;
    }
    this->setPixmap(filename);
}
