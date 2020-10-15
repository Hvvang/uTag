#include "FileInfo.h"
#include "ImageFile.h"

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

QString FileInfo::getLyrics() const {
    return file.tag()->comment().toCString();
}

QString FileInfo::getFilePath() const {
    return filePath;
}

QPixmap FileInfo::getCover() const {
    TagLib::MPEG::File audioFile(filePath.toStdString().c_str());
    TagLib::ID3v2::Tag *tag = audioFile.ID3v2Tag();
    TagLib::ID3v2::FrameList frames = tag->frameList("APIC");

    if (frames.isEmpty()) {
        QPixmap pix(defaultCoverImage);
        return pix;
    }
    TagLib::ID3v2::AttachedPictureFrame *coverImage =
        static_cast<TagLib::ID3v2::AttachedPictureFrame *>(frames.front());
    QImage cover;
    cover.loadFromData((const uchar *)coverImage->picture().data(), coverImage->picture().size());
    QPixmap pix = QPixmap::fromImage(cover);
    return pix;
}

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

void FileInfo::setLyrics(const QString& lyrics) {
    file.tag()->setComment(lyrics.toStdString());
    file.save();
}

void FileInfo::setCover(const QString& imagePath) {
    TagLib::MPEG::File audioFile(filePath.toStdString().c_str());
    TagLib::ID3v2::Tag *tag = audioFile.ID3v2Tag();
    TagLib::ID3v2::FrameList frames = tag->frameList("APIC");

    TagLib::ID3v2::AttachedPictureFrame *frame = 0;
    if (frames.isEmpty()) {
        frame = new TagLib::ID3v2::AttachedPictureFrame;
        tag->addFrame(frame);
    } else {
        frame = dynamic_cast<TagLib::ID3v2::AttachedPictureFrame *>(frames.front());
    }
    ImageFile image(imagePath.toStdString().c_str());
    TagLib::ByteVector imageData = image.data();
    frame->setMimeType("image/jpeg");
    frame->setPicture(imageData);
    audioFile.save();
}
