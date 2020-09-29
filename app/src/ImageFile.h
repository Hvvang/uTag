#include <tfile.h>

class ImageFile : public TagLib::File {
public:
    ImageFile(const char *file) :
        TagLib::File(file) {
    }

    TagLib::ByteVector data() {
        return readBlock(length());
    }


private:
    virtual TagLib::Tag *tag() const { return 0; }
    virtual TagLib::AudioProperties *audioProperties() const { return 0; }
    virtual bool save() { return false; }
};
