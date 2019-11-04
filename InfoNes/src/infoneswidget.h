/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : infoneswidget.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/19
*******************************************************************/
#ifndef INFONESWIDGET_H
#define INFONESWIDGET_H

#include "qtwidgetbase.h"
#include "gamewidgetpannel.h"

class QtListWidgetItem;
class InfoNesWidget : public QtAnimationWidget
{
    Q_OBJECT

public:
    InfoNesWidget(QWidget *parent = 0);
    ~InfoNesWidget();

private:
    void InitWidget();

private slots:
    void SltItemClicked(QtListWidgetItem *item);

private:
    GameWidgetPannel *m_gamePannel;

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // INFONESWIDGET_H
