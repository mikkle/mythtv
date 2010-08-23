#ifndef SUBTITLEREADER_H
#define SUBTITLEREADER_H

#include <QMutex>

extern "C" {
#include "libavcodec/avcodec.h"
}

#include "mythdeque.h"
#include "textsubtitleparser.h"

class AVSubtitles
{
  public:
    MythDeque<AVSubtitle> buffers;
    QMutex lock;
};

class RawTextSubs
{
  public:
    QStringList buffers;
    uint64_t    duration;
    QMutex      lock;
};

class SubtitleReader
{
  public:
    SubtitleReader();
    ~SubtitleReader();

    void EnableAVSubtitles(bool enable);
    void EnableTextSubtitles(bool enable);
    void EnableRawTextSubtitles(bool enable);

    AVSubtitles* GetAVSubtitles(void) { return &m_AVSubtitles; }
    void AddAVSubtitle(const AVSubtitle& subtitle);
    void ClearAVSubtitles(void);
    void FreeAVSubtitle(const AVSubtitle &sub);

    TextSubtitles* GetTextSubtitles(void) { return &m_TextSubtitles; }
    bool HasTextSubtitles(void);
    bool LoadExternalSubtitles(const QString &videoFile);

    QStringList GetRawTextSubtitles(uint64_t &duration);
    void AddRawTextSubtitle(QStringList list, uint64_t duration);
    void ClearRawTextSubtitles(void);

  private:
    AVSubtitles   m_AVSubtitles;
    bool          m_AVSubtitlesEnabled;
    TextSubtitles m_TextSubtitles;
    bool          m_TextSubtitlesEnabled;
    RawTextSubs   m_RawTextSubtitles;
    bool          m_RawTextSubtitlesEnabled;
};

#endif // SUBTITLEREADER_H