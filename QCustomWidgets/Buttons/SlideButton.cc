#include "SlideButton.h"
#include <QPainter>
#include <QDebug>

SlideButton::SlideButton(QWidget *parent) : QAbstractButton(parent)
{
    setCheckable(true);

    qDebug() << rect();
    connect(this, &SlideButton::clicked, [=](bool b){
        qDebug() << isChecked() << b;
    });
}

void SlideButton::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen bgPen(Qt::gray);
    QBrush bgBrush(Qt::gray);
    const int height = rect().height();
    const int bgWidth = rect().width() - height;
    painter.setPen(bgPen);
    painter.setBrush(bgBrush);
    QRect bgRect(height / 2, 0, bgWidth, height);
    painter.drawRect(bgRect);
    painter.drawEllipse(height / 2 - bgWidth / 2, 0, height, height);

}
