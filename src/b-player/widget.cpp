#include "widget.h"
#include "ui_widget.h"

#include <QMediaPlaylist>
#include <QMouseEvent>
#include <QFileDialog>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QMediaMetaData>
#include <QScrollBar>

#include "style.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget), leftMouseButtonPressed(None)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet(Style::getWindowStyleSheet());
    this->setMouseTracking(true);

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(9);
    shadowEffect->setOffset(0);

    ui->widgetInterface->setGraphicsEffect(shadowEffect);
    ui->widgetInterface->layout()->setMargin(0);
    ui->widgetInterface->layout()->setSpacing(0);
    ui->windowTitleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->songTitleLabel->setStyleSheet("color:#c1c1c1;");
    ui->nextSongButton->setStyleSheet(Style::getNextSongButtonStyleSheet());
    ui->previousSongButton->setStyleSheet(Style::getPreviousSongButtonStyleSheet());
    ui->stopButton->setStyleSheet(Style::getStopButtonStyleSheet());
    ui->playButton->setStyleSheet(Style::getPlayButtonStyleSheet());
    ui->pauseButton->setStyleSheet(Style::getPauseButtonStyleSheet());
    ui->shuffleButton->setStyleSheet(Style::getShuffleButtonStyleSheet());
    ui->closeWindowButton->setStyleSheet(Style::getCloseWindowButtonStyleSheet());
    ui->maximizeWindowButton->setStyleSheet(Style::getMaximizeWindowButtonStyleSheet());
    ui->minimizeWindowButton->setStyleSheet(Style::getMinimizeWindowButtonStyleSheet());
    ui->removeSongButton->setStyleSheet(Style::getRemoveSongButtonStyleSheet());
    ui->addSongButton->setStyleSheet(Style::getAddSongButtonStyleSheet());
    ui->durationSlider->setStyleSheet(Style::getSliderStyleSheet());
    ui->playlistTableView->setStyleSheet(Style::getPlaylistTableViewStyleSheet());
    ui->playlistTableView->verticalScrollBar()->setStyleSheet(Style::getVerticalScrollBarStyleSheet());
    ui->playlistTableView->horizontalScrollBar()->setStyleSheet(Style::getHorizontalScrollBarStyleSheet());

    ui->addSongButton->setToolTip("Add track");
    ui->removeSongButton->setToolTip("Remove track");
    ui->nextSongButton->setToolTip("Next track");
    ui->previousSongButton->setToolTip("Previous track");
    ui->playButton->setToolTip("Play");
    ui->pauseButton->setToolTip("Pause");
    ui->stopButton->setToolTip("Stop");
    ui->shuffleButton->setToolTip("Type of payback");

    ui->nextSongButton->setCursor(Qt::PointingHandCursor);
    ui->previousSongButton->setCursor(Qt::PointingHandCursor);
    ui->playButton->setCursor(Qt::PointingHandCursor);
    ui->pauseButton->setCursor(Qt::PointingHandCursor);
    ui->stopButton->setCursor(Qt::PointingHandCursor);

    playlistModel = new QStandardItemModel(this);
    ui->playlistTableView->setModel(playlistModel);

    ui->windowControlHorizontalLayout->setSpacing(0);
    ui->playlistControlHorizontalLayout->setSpacing(0);

    ui->playlistTableView->verticalHeader()->setVisible(false);
    ui->playlistTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistTableView->horizontalHeader()->setStretchLastSection(true);

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);

    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    connect(ui->previousSongButton, &QToolButton::clicked, playlist, &QMediaPlaylist::previous);
    connect(ui->nextSongButton, &QToolButton::clicked, playlist, &QMediaPlaylist::next);
    connect(ui->playButton, &QToolButton::clicked, player, &QMediaPlayer::play);
    connect(ui->pauseButton, &QToolButton::clicked, player, &QMediaPlayer::pause);
    connect(ui->stopButton, &QToolButton::clicked, player, &QMediaPlayer::stop);
    connect(ui->removeSongButton, &QToolButton::clicked, player, &QMediaPlayer::stop);

    volumeButton = new VolumeButton(this);
    volumeButton->setToolTip(tr("Volume"));
    volumeButton->setVolume(player->volume());
    volumeButton->setStyleSheet("QToolButton::menu-indicator{image:none;}");

    connect(volumeButton, &VolumeButton::volumeChanged, player, &QMediaPlayer::setVolume);
    ui->playlistControlHorizontalLayout->addWidget(volumeButton);

    connect(player, &QMediaPlayer::positionChanged, this, &Widget::updatePosition);
    connect(player, &QMediaPlayer::durationChanged, this,&Widget:: updateDuration);
    connect(ui->durationSlider, &QAbstractSlider::valueChanged, this, &Widget::setPosition);

    connect(ui->minimizeWindowButton, &QToolButton::clicked, this, &QWidget::showMinimized);
    connect(ui->maximizeWindowButton, &QToolButton::clicked, [this]()
    {
        if (this->isMaximized())
        {
            ui->maximizeWindowButton->setStyleSheet(Style::getMaximizeWindowButtonStyleSheet());
            this->layout()->setMargin(9);
            this->showNormal();
        }
        else
        {
            ui->minimizeWindowButton->setStyleSheet(Style::getRestoreWindowButtonStyleSheet());
            this->layout()->setMargin(0);
            this->showMaximized();
        }
    });

    connect(ui->closeWindowButton, &QToolButton::clicked, this, &QWidget::close);

    connect(ui->playlistTableView, &QTableView::doubleClicked, [this](const QModelIndex &index)
    {
        playlist->setCurrentIndex(index.row());
    });

    connect(playlist, &QMediaPlaylist::currentIndexChanged, [this](int index)
    {
        ui->songTitleLabel->setText(playlistModel->data(playlistModel->index(index, 0)).toString());
    });

    connect(playlist, &QMediaPlaylist::currentIndexChanged, [this](int index)
    {
            ui->playlistTableView->selectRow(index);
    });

    ui->durationSlider->setVisible(false);
    ui->durationLabel->setVisible(false);
    ui->stopButton->setVisible(false);
    ui->nextSongButton->setVisible(false);
    ui->previousSongButton->setVisible(false);
    ui->playButton->setVisible(false);
    ui->pauseButton->setVisible(false);
    ui->shuffleButton->setVisible(false);
    ui->songTitleLabel->setText("");

#ifdef _WIN32
    createTaskbar();
    createThumbnailToolBar();
#endif

    setWindowTitle("B-Player");
}

Widget::~Widget()
{
    delete ui;
    delete playlistModel;
    delete playlist;
    delete player;
}

void Widget::on_addSongButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this,tr("Open files"), QString(), tr("Audio Files(*.wav *.mp3)"));

    foreach (QString filePath, files)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));

        playlistModel->appendRow(items);
        playlist->addMedia(QUrl(filePath));
    };

    ui->durationSlider->setVisible(true);
    ui->durationLabel->setVisible(true);
    ui->stopButton->setVisible(true);
    ui->pauseButton->setVisible(true);
    ui->playButton->setVisible(true);
    ui->nextSongButton->setVisible(true);
    ui->previousSongButton->setVisible(true);
    ui->shuffleButton->setVisible(true);

    playlistModel->setHorizontalHeaderLabels(QStringList()  << tr("AUDIO TRACK") << tr("FILE PATH"));
}

void Widget::on_removeSongButton_clicked()
{
    playlist->removeMedia(ui->playlistTableView->currentIndex().row());
    playlistModel->removeRow(ui->playlistTableView->currentIndex().row());
    ui->songTitleLabel->setText("");
}

void Widget::on_shuffleButton_clicked()
{
    static int check=4;

    if(check%2==0)
    {
        ui->shuffleButton->setStyleSheet(Style::getSequentialButtonStyleSheet());
        playlist->setPlaybackMode(QMediaPlaylist::Random);
    }
    else
    {
        ui->shuffleButton->setStyleSheet(Style::getShuffleButtonStyleSheet());
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    }
    check++;
}

QPoint Widget::previousPosition() const
{
    return m_previousPosition;
}

void Widget::setPreviousPosition(QPoint previousPosition)
{
    if (m_previousPosition == previousPosition)
    {
        return;
    }

    m_previousPosition = previousPosition;
    emit previousPositionChanged(previousPosition);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton )
    {
        leftMouseButtonPressed = checkResizableField(event);
        setPreviousPosition(event->pos());
    }
    return QWidget::mousePressEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftMouseButtonPressed = None;
    }

    return QWidget::mouseReleaseEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    switch (leftMouseButtonPressed) {
    case Move:
    {
        if (isMaximized())
        {
            ui->maximizeWindowButton->setStyleSheet(Style::getMaximizeWindowButtonStyleSheet());
            this->layout()->setMargin(9);
            auto part = event->screenPos().x() / width();
            this->showNormal();
            auto offsetX = width() * part;
            setGeometry(event->screenPos().x() - offsetX, 0, width(), height());
            setPreviousPosition(QPoint(offsetX, event->y()));
        }
        else
        {
            auto dx = event->x() - m_previousPosition.x();
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x() + dx, y() + dy, width(), height());
        }

        break;
    }
    case Top:
    {
        if (!isMaximized())
        {
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x(), y() + dy, width(), height() - dy);
        }

        break;
    }
    case Bottom:
    {
        if (!isMaximized())
        {
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x(), y(), width(), height() + dy);
            setPreviousPosition(event->pos());
        }

        break;
    }
    case Left:
    {
        if (!isMaximized())
        {
            auto dx = event->x() - m_previousPosition.x();
            setGeometry(x() + dx, y(), width() - dx, height());
        }

        break;
    }
    case Right:
    {
        if (!isMaximized())
        {
            auto dx = event->x() - m_previousPosition.x();
            setGeometry(x(), y(), width() + dx, height());
            setPreviousPosition(event->pos());
        }

        break;
    }
    default:
        checkResizableField(event);
        break;
    }
    return QWidget::mouseMoveEvent(event);
}

Widget::MouseType Widget::checkResizableField(QMouseEvent *event)
{
    QPointF position = event->screenPos();
    qreal x = this->x();
    qreal y = this->y();
    qreal width = this->width();
    qreal height = this->height();

    QRectF rectTop(x + 9, y, width - 18, 7);
    QRectF rectBottom(x + 9, y + height - 7, width - 18, 7);
    QRectF rectLeft(x, y + 9, 7, height - 18);
    QRectF rectRight(x + width - 7, y + 9, 7, height - 18);
    QRectF rectInterface(x + 9, y + 9, width - 18, height - 18);

    if (rectTop.contains(position))
    {
        setCursor(Qt::SizeVerCursor);
        return Top;
    }
    else if (rectBottom.contains(position))
    {
        setCursor(Qt::SizeVerCursor);
        return Bottom;
    }
    else if (rectLeft.contains(position))
    {
        setCursor(Qt::SizeHorCursor);
        return Left;
    }
    else if (rectRight.contains(position))
    {
        setCursor(Qt::SizeHorCursor);
        return Right;
    }
    else if (rectInterface.contains(position)) {
        setCursor(QCursor());
        return Move;
    }
    else
    {
        setCursor(QCursor());
        return None;
    }
}

void Widget::togglePlayback()
{
    if (player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();
    }
    else
    {
        player->play();
    }
}

void Widget::seekForward()
{
    ui->durationSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void Widget::seekBackward()
{
    ui->durationSlider->triggerAction(QSlider::SliderPageStepSub);
}

static QString formatTime(qint64 timeMilliSeconds)
{
    qint64 seconds = timeMilliSeconds / 1000;
    const qint64 minutes = seconds / 60;
    seconds -= minutes * 60;

    return QStringLiteral("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
}

void Widget::updatePosition(qint64 position)
{
    ui->durationSlider->setValue(position);
    ui->durationLabel->setText(formatTime(position));
}

void Widget::updateDuration(qint64 duration)
{
    ui->durationSlider->setRange(0, duration);
    ui->durationSlider->setEnabled(duration > 0);
    ui->durationSlider->setPageStep(duration / 10);
}

void Widget::setPosition(int position)
{
    if (qAbs(player->position() - position) > 99)
    {
        player->setPosition(position);
    }
}

#ifdef _WIN32
void Widget::createTaskbar()
{
    taskbarButton = new QWinTaskbarButton(this);
    taskbarButton->setWindow(windowHandle());

    taskbarProgress = taskbarButton->progress();
    connect(ui->durationSlider, &QAbstractSlider::valueChanged, taskbarProgress, &QWinTaskbarProgress::setValue);
    connect(ui->durationSlider, &QAbstractSlider::rangeChanged, taskbarProgress, &QWinTaskbarProgress::setRange);

    connect(player, &QMediaPlayer::stateChanged, this, &Widget::updateTaskbar);
}

void Widget::updateTaskbar()
{
    switch (player->state())
    {
    case QMediaPlayer::PlayingState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        taskbarProgress->show();
        taskbarProgress->resume();
        break;
    case QMediaPlayer::PausedState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaPause));
        taskbarProgress->show();
        taskbarProgress->pause();
        break;
    case QMediaPlayer::StoppedState:
        taskbarButton->setOverlayIcon(style()->standardIcon(QStyle::SP_MediaStop));
        taskbarProgress->hide();
        break;
    }
}

void Widget::createThumbnailToolBar()
{
    thumbnailToolBar = new QWinThumbnailToolBar(this);
    thumbnailToolBar->setWindow(windowHandle());

    playToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    playToolButton->setEnabled(false);
    playToolButton->setToolTip(tr("Play"));
    playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playToolButton, &QWinThumbnailToolButton::clicked, this, &Widget::togglePlayback);

    forwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    forwardToolButton->setEnabled(false);
    forwardToolButton->setToolTip(tr("Fast forward"));
    forwardToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    connect(forwardToolButton, &QWinThumbnailToolButton::clicked, this, &Widget::seekForward);

    backwardToolButton = new QWinThumbnailToolButton(thumbnailToolBar);
    backwardToolButton->setEnabled(false);
    backwardToolButton->setToolTip(tr("Rewind"));
    backwardToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    connect(backwardToolButton, &QWinThumbnailToolButton::clicked, this, &Widget::seekBackward);

    thumbnailToolBar->addButton(backwardToolButton);
    thumbnailToolBar->addButton(playToolButton);
    thumbnailToolBar->addButton(forwardToolButton);

    connect(player, &QMediaPlayer::positionChanged, this, &Widget::updateThumbnailToolBar);
    connect(player, &QMediaPlayer::durationChanged, this, &Widget::updateThumbnailToolBar);
    connect(player, &QMediaPlayer::stateChanged, this, &Widget::updateThumbnailToolBar);
}

void Widget::updateThumbnailToolBar()
{
    playToolButton->setEnabled(player->duration() > 0);
    backwardToolButton->setEnabled(player->position() > 0);
    forwardToolButton->setEnabled(player->position() < player->duration());

    if (player->state() == QMediaPlayer::PlayingState)
    {
        playToolButton->setToolTip(tr("Pause"));
        playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        playToolButton->setToolTip(tr("Play"));
        playToolButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}
#endif
