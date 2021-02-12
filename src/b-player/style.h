#ifndef STYLE_H
#define STYLE_H

#include <QString>

class Style
{
public:
    static QString getWindowStyleSheet();
    static QString getLabelStyleSheet();
    static QString getCloseWindowButtonStyleSheet();
    static QString getMaximizeWindowButtonStyleSheet();
    static QString getRestoreWindowButtonStyleSheet();
    static QString getMinimizeWindowButtonStyleSheet();
    static QString getNextSongButtonStyleSheet();
    static QString getPreviousSongButtonStyleSheet();
    static QString getStopButtonStyleSheet();
    static QString getPlayButtonStyleSheet();
    static QString getShuffleButtonStyleSheet();
    static QString getSequentialButtonStyleSheet();
    static QString getPauseButtonStyleSheet();
    static QString getPlaylistTableViewStyleSheet();
    static QString getAddSongButtonStyleSheet();
    static QString getRemoveSongButtonStyleSheet();
    static QString getSliderStyleSheet();
    static QString getVerticalScrollBarStyleSheet();
    static QString getHorizontalScrollBarStyleSheet();
};

#endif // STYLE_H
