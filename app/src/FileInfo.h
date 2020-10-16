#pragma once

#include <tag.h>
#include <fileref.h>
#include <attachedpictureframe.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <QString>
#include <QPixmap>

#define defaultCoverImage "./app/src/asserts/defaultCoverImage.png"

/* FileInfo.h */
class FileInfo {


public:
    FileInfo(const QString& path, const bool &valid = true);
    FileInfo() = default;
    ~FileInfo() = default;

    QString getArtist() const;
    QString getTitle() const;
    QString getAlbum() const;
    QString getGenre() const;
    QString getFilePath() const;
    QString getLyrics() const;
    QPixmap getCover() const;

    bool isValid() const { return valid; };

    void setArtist(const QString& artist);
    void setTitle(const QString& title);
    void setAlbum(const QString& album);
    void setGenre(const QString& genre);
    void setLyrics(const QString& lyrics);
    void setCover(const QString& imagePath);
private:
    TagLib::FileRef file;
    bool valid;
    const QString filePath;
};
