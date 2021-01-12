#ifndef SLIDEBUTTON_H
#define SLIDEBUTTON_H

#include <QWidget>
#include <QAbstractButton>
#include <QElapsedTimer>
#include <QPen>
#include <QBrush>

class SlideButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit SlideButton(QWidget *parent = nullptr);


    void setForegroundBrush(const QBrush& brush);
    void setBackgroundBrush(const QBrush& brush);
    void setForegroundPen(const QPen& pen);
    void setBackgroundPen(const QPen& pen);

    QBrush foregroundBrush() const;
    QBrush backgroundBrush() const;
    QPen foregroundPen() const;
    QPen backgroundPen() const;

    virtual QSize sizeHint() const override;
    virtual QSize minimumSizeHint() const override;
private:
    struct {
        QPen fgPen;
        QPen bgPen;
        QBrush fgBrush;
        QBrush bgBrush;
    } mPainterCfg;
    int mTimerId;
    int mBtnXOffset;
    int mBtnXOffsetSpeed;
    QElapsedTimer mBlockElapsedTimer;

    Q_SLOT void startSlideAnimation();

protected:
    virtual void paintEvent(QPaintEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent* e) override;
    virtual void timerEvent(QTimerEvent* e) override;
};

#endif // SLIDEBUTTON_H
