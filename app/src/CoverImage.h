#ifndef COVERIMAGE_H
#define COVERIMAGE_H


class CoverImage : public QPushButton {
    Q_OBJECT

public:
    CoverImage(QString imagePath, QWidget *parent = nullptr);
    ~CoverImage();

protected:
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);

// private:

};

#endif // COVERIMAGE_H
