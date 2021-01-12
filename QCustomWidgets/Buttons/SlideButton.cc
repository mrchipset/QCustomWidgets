#include "SlideButton.h"

#include <chrono>
#include <thread>

#include <QMouseEvent>
#include <QTimerEvent>

#include <QPainter>
#include <QPainterPath>

#include <QDebug>

SlideButton::SlideButton(QWidget *parent) : QAbstractButton(parent),
    mTimerId(-1),
    mBtnXOffset(0)
{
    resize(sizeHint());
    setSizeIncrement(QSize(8, 4));
    setContentsMargins(5, 5, 5, 5);

    setBackgroundBrush(QBrush(Qt::gray));
    setForegroundBrush(QBrush(Qt::green));
    setForegroundPen(QPen(Qt::black));
    setBackgroundPen(QPen(Qt::black));

    setCheckable(true);
}

void SlideButton::setForegroundBrush(const QBrush &brush)
{
    mPainterCfg.fgBrush = brush;
}

void SlideButton::setBackgroundBrush(const QBrush &brush)
{
    mPainterCfg.bgBrush = brush;
}

void SlideButton::setForegroundPen(const QPen &pen)
{
    mPainterCfg.fgPen = pen;
}

void SlideButton::setBackgroundPen(const QPen &pen)
{
    mPainterCfg.bgPen = pen;
}

QBrush SlideButton::foregroundBrush() const
{
    return mPainterCfg.fgBrush;
}

QBrush SlideButton::backgroundBrush() const
{
    return mPainterCfg.bgBrush;
}

QPen SlideButton::foregroundPen() const
{
    return mPainterCfg.fgPen;
}

QPen SlideButton::backgroundPen() const
{
    return mPainterCfg.bgPen;
}

QSize SlideButton::sizeHint() const
{
    return minimumSizeHint();
}

QSize SlideButton::minimumSizeHint() const
{
    constexpr int _h = 32;
    constexpr int _w = 64;
    return QSize(_w, _h);
}

void SlideButton::startSlideAnimation()
{

    constexpr int blockTime = 100;
    if (mTimerId != -1)
    {
        killTimer(mTimerId);
        mTimerId = -1;
        mBtnXOffset = 0;
        repaint();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    const int margin = contentsMargins().left();
    const int radius = height() / 2 - margin;
    mBtnXOffset = width() - margin * 2 - radius * 2;
    mBtnXOffsetSpeed = mBtnXOffset / blockTime;
    mBtnXOffsetSpeed = mBtnXOffsetSpeed == 0 ? 1 : mBtnXOffsetSpeed;
    mTimerId = startTimer(std::chrono::milliseconds(5));

}

void SlideButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setPen(Qt::NoPen);
    QBrush bgBrush(Qt::gray);
    QBrush fgBrush(Qt::white);
    QPen fgPen(mPainterCfg.fgPen);
    QPen bgPen(mPainterCfg.bgPen);

    const double opacity = 0.67;
    const int margin = contentsMargins().left();
    const int radius = height() / 2 - margin;
    const int btnPosX = isChecked() ? width() - margin - radius * 2 - mBtnXOffset: margin + mBtnXOffset;
    const int btnPosY = margin / 2;
    const int innerRadius = radius - margin > margin ? radius - margin : margin;

    // draw small ellipse
    if (isChecked() && mBtnXOffset == 0)
    {
        bgBrush = mPainterCfg.bgBrush;
    }

    // draw rounded background
    painter.setPen(bgPen);
    painter.setBrush(bgBrush);
    painter.setOpacity(opacity);
    painter.drawRoundedRect(QRectF(margin, margin, width() - 2 * margin, height() - 2 * margin), radius, radius);

    // draw slide circle button
    painter.setPen(fgPen);
    painter.setBrush(fgBrush);
    painter.setOpacity(1.0);
    painter.drawEllipse(QRectF(btnPosX, btnPosY, 2 * radius + margin, 2 * radius + margin));

    if (isChecked() && mBtnXOffset == 0)
    {
        fgBrush = mPainterCfg.fgBrush;
        //draw slide circle button
        painter.setPen(fgPen);
        painter.setBrush(fgBrush);
        painter.setOpacity(0.8);
        painter.drawEllipse(QRectF(btnPosX + (radius - innerRadius), btnPosY + (radius - innerRadius), 2 * innerRadius + margin, 2 * innerRadius + margin));
    }



}

void SlideButton::mouseReleaseEvent(QMouseEvent *e)
{
    constexpr int blockTime = 100;
    if (mBlockElapsedTimer.elapsed() > blockTime)
    {
        mBlockElapsedTimer.restart();
        startSlideAnimation();
        QAbstractButton::mouseReleaseEvent(e);
        e->accept();
    }
}

void SlideButton::timerEvent(QTimerEvent *e)
{
    if (e->timerId() != mTimerId)
    {
        QAbstractButton::timerEvent(e);
        return;
    }

    mBtnXOffset -= mBtnXOffsetSpeed;
    if (mBtnXOffset <= 0)
    {
        mBtnXOffset = 0;
        killTimer(mTimerId);
        mTimerId = -1;
    }
    update();
//    e->accept();
}
