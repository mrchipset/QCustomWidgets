#include "HoldButton.h"

HoldButton::HoldButton(QWidget *parent) : QAbstractButton(parent), /*QPushButton(parent),*/
    mLongPressThreshold(1000)
{
    setAutoRepeat(false);

    mLongPressTimer.setInterval(mLongPressThreshold);
    mLongPressTimer.setSingleShot(true);
    connect(&mLongPressTimer, &QTimer::timeout, this, &HoldButton::longPressed, Qt::DirectConnection);
}

void HoldButton::setLongPressThreshold(uint64_t threshold)
{
    mLongPressThreshold = threshold;
}

uint64_t HoldButton::longPressThreshold() const
{
    return mLongPressThreshold;
}

void HoldButton::mousePressEvent(QMouseEvent *e)
{
//    mElapsedTimer.restart();
    mLongPressTimer.start();
    QAbstractButton::mousePressEvent(e);
}

void HoldButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (!mLongPressTimer.isActive())
    {
        Q_EMIT released();
        blockSignals(true);
    } else
    {
        mLongPressTimer.stop();
    }

    QAbstractButton::mouseReleaseEvent(e);
    blockSignals(false);

}

