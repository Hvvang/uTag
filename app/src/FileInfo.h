#pragma once

#include <tag.h>
#include <fileref.h>
#include <tstring.h>
#include <iostream>
#include <string>
#include <attachedpictureframe.h>
#include <asfpicture.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <QString>

#include <QPixmap>


/* FileInfo.h */
class FileInfo {


public:
    FileInfo(const QString& path);
    ~FileInfo() = default;

    QString getArtist() const;
    QString getTitle() const;
    QString getAlbum() const;
    QString getGenre() const;
    QString getFilePath() const;
    QString getLyrics() const;
    QPixmap getCover() const;

    void setArtist(const QString& artist);
    void setTitle(const QString& title);
    void setAlbum(const QString& album);
    void setGenre(const QString& genre);
    void setLyrics(const QString& lyrics);
    void setCover(const QString& imagePath);
private:
    TagLib::FileRef file;
    const QString filePath;
};
