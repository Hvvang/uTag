#include "FileInfo.h"

FileInfo::FileInfo(const QString& path) :
    filePath(path) {
    // TagLib::FileName fn(path.toStdString().c_str());
    // if (fn.isValid()) {
        file = TagLib::FileRef(path.toStdString().c_str());
    // }
}

QString FileInfo::getArtist() const {
    return file.tag()->artist().toCString();
}

QString FileInfo::getTitle() const {
    return file.tag()->title().toCString();
}

QString FileInfo::getAlbum() const {
    return file.tag()->album().toCString();
}

QString FileInfo::getGenre() const {
    return file.tag()->genre().toCString();
}

QString FileInfo::getFilePath() const {
    return filePath;
}

// QString FileInfo::getCover() const {
//     return filePath;
// }

void FileInfo::setArtist(const QString& artist) {
    file.tag()->setArtist(artist.toStdString());
    file.save();
}

void FileInfo::setTitle(const QString& title) {
    file.tag()->setTitle(title.toStdString());
    file.save();
}

void FileInfo::setAlbum(const QString& album) {
    file.tag()->setAlbum(album.toStdString());
    file.save();
}

void FileInfo::setGenre(const QString& genre) {
    file.tag()->setGenre(genre.toStdString());
    file.save();
}

// void FileInfo::setCover(const QString& imagePath) {
//     TagLib::MPEG::File audioFile(filePath.c_str());
//     TagLib::ID3v2::AttachedPictureFrame *pic = new TagLib::ID3v2::AttachedPictureFrame();
//     TagLib::ID3v2::Tag *tag = audioFile.ID3v2Tag(true);
//     pic->setMimeType("image/jpeg");
//     pic->setData(TagLib::ByteVector(imagePath.c_str()));
//     tag->addFrame(pic);
//     audioFile.save();
// }
