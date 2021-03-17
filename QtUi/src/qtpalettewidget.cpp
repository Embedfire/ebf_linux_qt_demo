/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtpalettewidget.cpp --- QtPaletteWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/13
*******************************************************************/
#include "qtpalettewidget.h"
#include <QPainter>
#include <QMouseEvent>

QtPaletteWidget::QtPaletteWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    m_nBaseWidth = 436;
    m_nBaseWidth = 432;

    m_nFontSize = 18;
    m_currentColor = QColor("#000000");
    m_nIndex = 0;
    m_bColorPanel = false;

    m_strColors = QStringList() << "#000000" << "#333333" << "#555555" << "#7f7f7f" << "#aaaaaa" << "#d7d7d7" << "#f2f2f2" << "#ffffff"
                                << "#ec808d" << "#facd91" << "#ffff80" << "#caf982" << "#80ffff" << "#81d3f8" << "#8080ff" << "#c280ff"
                                << "#d9001b" << "#f59a23" << "#ffff00" << "#95f204" << "#00ffff" << "#02a7f0" << "#0000ff" << "#8400ff"
                                << "#a30014" << "#b8741a" << "#bfbf00" << "#70b603" << "#00bfbf" << "#027db4" << "#0000bf" << "#6300bf"
                                << "#6d000e" << "#7b4d12" << "#808000" << "#4b7902" << "#008080" << "#015478" << "#000080" << "#420080";
    InitValues();
}

QtPaletteWidget::~QtPaletteWidget()
{

}

void QtPaletteWidget::CreatePanel(QRect rect)
{
    int width = rect.width();
    int height = rect.height();

    //首次显示记住当前背景截图,用于获取颜色值
    m_colorPanel = QPixmap(width, height);
    m_colorPanel.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&m_colorPanel);

    QColor colorStart, colorCenter, colorEnd;
    for(int i = 0; i < width; i++) {
        colorStart.setHslF(i / double(width), 1, 0);
        colorCenter.setHslF(i / double(width), 1, 0.5);
        colorEnd.setHslF(i / double(width), 1, 1);

        QLinearGradient linearGradient;
        linearGradient.setStart(QPointF(i, -height));
        linearGradient.setFinalStop(QPointF(i, height));
        linearGradient.setColorAt(0.0, colorStart);
        linearGradient.setColorAt(0.5, colorCenter);
        linearGradient.setColorAt(1.0, colorEnd);

        painter.setPen(QPen(linearGradient, 1));
        painter.drawLine(QPointF(i, 0), QPointF(i, height));
    }

    painter.end();
}

void QtPaletteWidget::ColorPanelClicked(QPoint pos)
{
    int x = pos.x() - m_rectPanel.left();
    int y = pos.y() - m_rectPanel.top();

    //获取当前坐标处的颜色值
    m_currentColor = m_colorPanel.toImage().pixel(x, y);
    emit signalColorChanged(m_currentColor);
    this->update();
}

void QtPaletteWidget::InitValues()
{
    m_rectPanel = QRect(20, 90, m_nBaseWidth - 35, m_nBaseHeight - 175);
    // 创建颜色面板
    CreatePanel(m_rectPanel);

    int nRow = 5;
    int nCol = 8;
    int nSpace = 1;
    qreal nW = (m_rectPanel.width() - nSpace * (nCol + 1)) / nCol;
    qreal nH = (m_rectPanel.height() - nSpace * (nRow + 1)) / nRow;
    for (int i = 0; i < m_strColors.size(); i++) {
        QRect rectColor(m_rectPanel.left() + (i % nCol) * (nSpace + nW) + nSpace, m_rectPanel.top() + (i / nCol) * (nH + nSpace) + nSpace, nW, nH);
        m_colorRects.insert(i, ColorRole(i, QColor(m_strColors.at(i)), rectColor));
    }
}

void QtPaletteWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.drawPixmap(this->rect(), QPixmap(":/images/ebook/ic_palette.png"));
    painter.scale(m_scaleX, m_scaleY);
    drawFontConfig(&painter);
    drawColorBoard(&painter);
}

void QtPaletteWidget::drawFontConfig(QPainter *painter)
{
    painter->save();
    QFont font = painter->font();
    font.setPixelSize(18);
    painter->setFont(font);
    QString strTitle = QString("设置字体大小");
    int nTW = painter->fontMetrics().width(strTitle);
    QRect rectTitle(15, 15, m_nBaseWidth / 2 + nTW / 2, 40);
    painter->setPen(QColor("#5fbae2"));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(rectTitle, 2, 2);

    m_rectAdd = QRect(rectTitle.left() + nTW + 5, rectTitle.top(), 60, rectTitle.height());
    painter->fillRect(m_rectAdd, QColor("#1173d6"));

    QRect rectFont(m_rectAdd.right(), rectTitle.top(), 40, rectTitle.height());
    painter->setPen(QColor("#333333"));
    painter->drawText(rectFont, Qt::AlignCenter, QString::number(m_nFontSize));
    painter->drawText(rectTitle, Qt::AlignVCenter, strTitle);

    m_rectMinus = QRect(rectFont.right(), rectTitle.top(), 60, rectTitle.height());
    painter->fillRect(m_rectMinus, QColor("#1173d6"));

    painter->setPen(QColor("#ffffff"));
    painter->drawText(m_rectAdd, Qt::AlignCenter, "A");
    painter->drawText(m_rectAdd.center().x() + 5, m_rectAdd.top() + 20,  "+");
    painter->drawText(m_rectMinus, Qt::AlignCenter, "A");
    painter->drawText(m_rectMinus.center().x() + 5, m_rectAdd.top() + 20,  "-");
    painter->restore();
}

void QtPaletteWidget::drawColorBoard(QPainter *painter)
{
    painter->save();
    painter->setClipRect(10, 60, m_nBaseWidth - 20, m_nBaseHeight - 80);
    painter->setPen(QColor("#5fbae2"));
    painter->setBrush(Qt::NoBrush);
    QFont font = painter->font();
    font.setPixelSize(18);
    painter->setFont(font);
    QString strTitle = QString("设置字体颜色");

    QPainterPath path;
    int nTW = painter->fontMetrics().width(strTitle);
    int nTH = painter->fontMetrics().height();
    QRect rectTitle((m_nBaseWidth - nTW) / 2, 60, nTW, nTH);
    path.addRoundedRect(rectTitle, 2, 2);
    path.moveTo(10, rectTitle.bottom());

    QRect rectCenter(15, rectTitle.bottom(), m_nBaseWidth, m_nBaseHeight - 80 - nTH);
    path.addRoundedRect(rectCenter, 2, 2);
    painter->drawPath(path);
    painter->setPen(QColor("#333333"));
    painter->drawText(rectTitle, strTitle);

    if (m_bColorPanel && !m_colorPanel.isNull()) {
        painter->drawPixmap(rectCenter.left() + 5, rectCenter.top() + 5, m_colorPanel);
        painter->setPen(QColor("#ffffff"));
        int nXOffset = painter->fontMetrics().width("+");
        int nYOffset = painter->fontMetrics().height();
        painter->drawText(m_selectPos.x() - nXOffset / 2, m_selectPos.y() - nYOffset / 2,
                          nXOffset, nYOffset, Qt::AlignCenter, QString("+"));
    }
    else {
        foreach (ColorRole color, m_colorRects) {
            if (m_nIndex == color.m_nId) {
                painter->setPen(QPen(QColor("#ff0000"), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            } else painter->setPen(Qt::NoPen);
            painter->setBrush(color.m_color);
            painter->drawRect(color.m_rect);
        }
    }

    QRect rectBottom(rectCenter.left() + 5, rectCenter.bottom() - 55, rectCenter.width() - 10, 50);
    painter->setPen(QColor("#9e979e"));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(rectBottom, 2, 2);

    m_rectOther = QRect(rectBottom.left() + 5, rectBottom.top() + 5, rectBottom.height() - 10, rectBottom.height() - 10);
    painter->fillRect(m_rectOther, m_currentColor);
    painter->setPen(QColor("#333333"));
    painter->drawText(m_rectOther.right() + 10, m_rectOther.top(), rectBottom.width() - m_rectOther.width(), m_rectOther.height(),
                      Qt::AlignVCenter, tr("选择其他颜色"));
    painter->restore();
}

void QtPaletteWidget::mousePressEvent(QMouseEvent *e)
{
    QRect rect;
    ScaleRect(rect, m_rectMinus);
    if (rect.contains(e->pos())) {
        m_nFontSize -= 1;
        emit signalFontChanged(m_nFontSize);
        this->update();
        return;
    }

    ScaleRect(rect, m_rectAdd);
    if (rect.contains(e->pos())) {
        m_nFontSize += 1;
        emit signalFontChanged(m_nFontSize);
        this->update();
        return;
    }

    ScaleRect(rect, m_rectOther);
    if (rect.contains(e->pos())) {
        m_bColorPanel = !m_bColorPanel;
        this->update();
        return;
    }

    if (m_bColorPanel) {
        ScaleRect(rect, m_rectPanel);
        if (rect.contains(e->pos())) {
            m_selectPos = QPoint(e->x() / m_scaleX, e->y() / m_scaleY);
            ColorPanelClicked(m_selectPos);
        }
    }
    else {
        foreach (ColorRole color, m_colorRects) {
            ScaleRect(rect, color.m_rect);
            if (rect.contains(e->pos())) {
                m_nIndex = color.m_nId;
                m_currentColor = color.m_color;
                this->update();
                emit signalColorChanged(m_currentColor);
                break;
            }
        }
    }
}
