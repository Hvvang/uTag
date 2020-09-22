#include "FileInfo.h"

FileInfo::FileInfo(const std::string& path) :
    filePath(path) {
    file = TagLib::FileRef(path.c_str());
}

std::string FileInfo::getArtist() const {
    return file.tag()->artist().toCString();
}

std::string FileInfo::getTitle() const {
    return file.tag()->title().toCString();
}

std::string FileInfo::getAlbum() const {
    return file.tag()->album().toCString();
}

std::string FileInfo::getGenre() const {
    return file.tag()->genre().toCString();
}

std::string FileInfo::getFilePath() const {
    return filePath;
}

// std::string FileInfo::getCover() const {
//     return filePath;
// }

void FileInfo::setArtist(const std::string& artist) {
    file.tag()->setArtist(artist);
    file.save();
}

void FileInfo::setTitle(const std::string& title) {
    file.tag()->setTitle(title);
    file.save();
}

void FileInfo::setAlbum(const std::string& album) {
    file.tag()->setAlbum(album);
    file.save();
}

void FileInfo::setGenre(const std::string& genre) {
    file.tag()->setGenre(genre);
    file.save();
}

void FileInfo::setCover(const std::string& imagePath) {
    TagLib::MPEG::File audioFile(filePath.c_str());
    TagLib::ID3v2::AttachedPictureFrame *pic = new TagLib::ID3v2::AttachedPictureFrame();
    TagLib::ID3v2::Tag *tag = audioFile.ID3v2Tag(true);
    pic->setMimeType("image/jpeg");
    pic->setData(TagLib::ByteVector(imagePath.c_str()));
    tag->addFrame(pic);
    audioFile.save();
}
