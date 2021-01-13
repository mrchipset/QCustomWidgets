# HoldButton class

The HoldButton Button is inherited from QAbstractButton to provide basic long hold event handling.

The *paintEvent* hsen't been overrided. So it could not be created as an instance. 

A singleshot *QTimer* is used to timing the long hold period.
When the button is pressed, timer is started. And when user release the button, it will stop.

if the period is not reached, it will emit a *clicked* signal.
Otherwise, the *longPressed* signal will be emitted. And there won't be a *clicked* signal;
