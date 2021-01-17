#include "imagetoascii.h"
#include "./ui_imagetoascii.h"



ImageToAscii::ImageToAscii(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageToAscii)
{
    ui->setupUi(this);

    myMap[12] = '_';
    myMap[11] = '.';
    myMap[10] = ',';
    myMap[9] = '-';
    myMap[8] = '~';
    myMap[7] = ':';
    myMap[6] = ';';
    myMap[5] = '=';
    myMap[4] = '!';
    myMap[3] = '*';
    myMap[2] = '#';
    myMap[1] = '$';
    myMap[0] = '@';

}

ImageToAscii::~ImageToAscii()
{
    delete ui;
}



QString previous = "";
QString output = "";
void ImageToAscii::on_btn_upload_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), previous, tr("Image Files (*.png *.jpg *.bmp *.gif *.tif)"));

    ui->label_filename->setText(fileName);
    previous = fileName;

    myImage = QImage(fileName);

    qDebug() << "" << myImage.width() << "/" << myImage.height();

    //Display images.

    QPixmap pixmap;
    pixmap.convertFromImage(myImage);
    pixmap = pixmap.scaledToHeight(100);

    ui->label_original->setPixmap(pixmap);

    //Create image icon
    QImage image2 = QImage(myImage.width()/10, myImage.height()/20, QImage::Format_RGB32);

    output = "";
    for(int y = 0; y < myImage.width(); y += 20) {
        for(int x = 0; x < myImage.height(); x += 10) {

            QColor pixel = myImage.pixel(x, y);

            float factor = (pixel.red() * 0.3f + pixel.green() * 0.59f + pixel.blue() * 0.11f) / 255;

            //CLIP DARK AND LIGHT


            auto clip = (std::max(std::min(factor, clip_light), clip_dark) - clip_dark) * (1.0f / (clip_light - clip_dark));

            factor = clip;

            //END


            int value12 = factor * 13;
            int value255 = value12 * 20;

            auto val2 = qRgb(value255, value255, value255);
            image2.setPixel(x/10, y/20, val2);

            output.append(myMap[value12]);
        }

        output.append('\n');
    }

    QPixmap pixmap2;
    pixmap2.convertFromImage(image2);

    ui->label_approx->setPixmap(pixmap2.scaledToHeight(100));


}



void ImageToAscii::setPreview()
{
    QImage image2 = QImage(myImage.width()/10, myImage.height()/20, QImage::Format_RGB32);

    output = "";
    for(int y = 0; y < myImage.width(); y += 20) {
        for(int x = 0; x < myImage.height(); x += 10) {

            QColor pixel = myImage.pixel(x, y);

            float factor = (pixel.red() * 0.3f + pixel.green() * 0.59f + pixel.blue() * 0.11f) / 255;

            //CLIP DARK AND LIGHT

            auto clip = (std::max(std::min(factor, clip_light), clip_dark) - clip_dark) * (1.0f / (clip_light - clip_dark));

            factor = clip;

            if(factor > 1.0f){
                qDebug() << factor;
            }

            //END


            int value12 = factor * 12;
            int value255 = value12 * 20;

            auto val2 = qRgb(value255, value255, value255);
            image2.setPixel(x/10, y/20, val2);

            output.append(myMap[value12]);
        }

        output.append('\n');
    }

    QPixmap pixmap2;
    pixmap2.convertFromImage(image2);

    ui->label_approx->setPixmap(pixmap2.scaledToHeight(100));


}



void ImageToAscii::on_clip_light_slider_valueChanged(int value)
{

    clip_light = ((float)value) / 100.0f;

    setPreview();

}

void ImageToAscii::on_clip_dark_slider_valueChanged(int value)
{
    clip_dark = ((float)value) / 100.0f;
    setPreview();
}

void ImageToAscii::on_btn_convert_clicked()
{
    ui->outputWidget->document()->setPlainText(output);
}
