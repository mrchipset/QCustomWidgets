#ifndef SLIDEBUTTON_H
#define SLIDEBUTTON_H

#include <QWidget>
#include <QAbstractButton>

class SlideButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit SlideButton(QWidget *parent = nullptr);

signals:

protected:
    void paintEvent(QPaintEvent *e) override;
};

#endif // SLIDEBUTTON_H
