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

/* FileInfo.h */
class FileInfo {
public:
    FileInfo(const std::string& path);
    ~FileInfo() = default;

    std::string getArtist() const;
    std::string getTitle() const;
    std::string getAlbum() const;
    std::string getGenre() const;
    std::string getFilePath() const;

    void setArtist(const std::string& artist);
    void setTitle(const std::string& title);
    void setAlbum(const std::string& album);
    void setGenre(const std::string& genre);
    void setCover(const std::string& imagePath);

private:
    TagLib::FileRef file;
    const std::string filePath;
};
