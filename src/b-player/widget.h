#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>

#ifdef _WIN32
#include <QtWinExtras>
#endif

#include "volumebutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPoint previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

    enum MouseType {
        None = 0,
        Top,
        Bottom,
        Left,
        Right,
        Move
    };

signals:
    void previousPositionChanged(QPoint);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QPoint previousPosition() const;

public slots:
    void setPreviousPosition(QPoint);
    void togglePlayback();
    void seekForward();
    void seekBackward();

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

private:
    Ui::Widget *ui = nullptr;

    QStandardItemModel *playlistModel = nullptr;
    QMediaPlayer *player = nullptr;
    QMediaPlaylist *playlist = nullptr;

    VolumeButton *volumeButton = nullptr;

#ifdef _WIN32
    QWinTaskbarProgress *taskbarProgress = nullptr;
    QWinTaskbarButton *taskbarButton = nullptr;

    QWinThumbnailToolBar *thumbnailToolBar = nullptr;
    QWinThumbnailToolButton *playToolButton = nullptr;
    QWinThumbnailToolButton *forwardToolButton = nullptr;
    QWinThumbnailToolButton *backwardToolButton = nullptr;
#endif
    MouseType leftMouseButtonPressed;
    QPoint m_previousPosition;

    MouseType checkResizableField(QMouseEvent*);

#ifdef _WIN32
    void createTaskbar();
    void createThumbnailToolBar();
#endif

private slots:
    void on_removeSongButton_clicked();
    void on_addSongButton_clicked();
    void on_shuffleButton_clicked();
    void updatePosition(qint64);
    void updateDuration(qint64);
    void setPosition(int);

#ifdef _WIN32
    void updateTaskbar();
    void updateThumbnailToolBar();
#endif
};
#endif // WIDGET_H
