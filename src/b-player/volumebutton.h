#ifndef VOLUMEBUTTON_H
#define VOLUMEBUTTON_H

#include <QToolButton>

QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSlider)

class VolumeButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)

private:
    QMenu *menu = nullptr;
    QLabel *label = nullptr;
    QSlider *slider = nullptr;

public:
   explicit VolumeButton(QWidget *parent = nullptr);
    int volume() const;

public slots:
    void increaseVolume();
    void descreaseVolume();
    void setVolume(int);
    void stylize();

signals:
    void volumeChanged(int);
};

#endif // VOLUMEBUTTON_H
