#ifndef IMAGETOASCII_H
#define IMAGETOASCII_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMap>
#include <QBitmap>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageToAscii; }
QT_END_NAMESPACE

class ImageToAscii : public QMainWindow
{
    Q_OBJECT

public:
    ImageToAscii(QWidget *parent = nullptr);
    ~ImageToAscii();

private slots:
    void on_btn_upload_clicked();

    void on_clip_light_slider_valueChanged(int value);

    void on_clip_dark_slider_valueChanged(int value);

    void on_btn_convert_clicked();

private:
    Ui::ImageToAscii *ui;
    QMap<int, QString> myMap;
    QImage myImage;

    void setPreview();

    float clip_light = 1.0f;
    float clip_dark = 0.0f;

};
#endif // IMAGETOASCII_H
