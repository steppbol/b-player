#include "volumebutton.h"

#include <QtWidgets>

#ifdef _WIN32
#include <QtWinExtras>
#endif

#include "widget.h"
#include "style.h"

VolumeButton::VolumeButton(QWidget *parent) : QToolButton(parent)
{
    setPopupMode(QToolButton::InstantPopup);

    setIcon(QIcon(":/buttons/high_volume.png"));
    setStyleSheet("padding-left: 0px;"
                  "padding-right: 0px;"
                  "padding-top: 0px;"
                  "padding-bottom: 0px;");

    setIconSize(QSize(20,20));
    QWidget *popup = new QWidget(this);

    slider = new QSlider(Qt::Horizontal, popup);
    slider->setRange(0,100);
    slider->setStyleSheet(Style::getSliderStyleSheet());

    connect(slider, &QAbstractSlider::valueChanged, this, &VolumeButton::volumeChanged);

    label = new QLabel(popup);
    label->setAlignment(Qt::AlignCenter);
    label->setNum(100);
    label->setMinimumWidth(label->sizeHint().width());

    typedef void(QLabel::*IntSlot)(int);

    connect(slider, &QAbstractSlider::valueChanged, label, static_cast<IntSlot>(&QLabel::setNum));

    QBoxLayout *popupLayout = new QHBoxLayout(popup);
    popupLayout->setMargin(1);
    popupLayout->addWidget(slider);
    popupLayout->addWidget(label);


    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(popup);

    menu = new QMenu(this);
    menu->addAction(action);
    setMenu(menu);

    stylize();
}

void VolumeButton::increaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepAdd);
}

void VolumeButton::descreaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepSub);
}

int VolumeButton::volume() const
{
    return slider->value();
}

void VolumeButton::setVolume(int volume)
{
    slider->setValue(volume);
}

void VolumeButton::stylize()
{
#ifdef __linux__
    QString css("QMenu { border: 1px solid %1; border-radius: 1px; background: transparent; }");
    menu->setStyleSheet(css);
#elif _WIN32
    if (QtWin::isCompositionEnabled())
    {
        QtWin::enableBlurBehindWindow(menu);
        QString css("QMenu { border: 1px solid %1; border-radius: 1px; background: transparent; }");
        menu->setStyleSheet(css.arg(QtWin::realColorizationColor().name()));
    }
    else
    {
        QtWin::disableBlurBehindWindow(menu);
        QString css("QMenu { border: 1px solid black; background: %1; }");
        menu->setStyleSheet(css.arg(QtWin::realColorizationColor().name()));
    }
#endif
}
