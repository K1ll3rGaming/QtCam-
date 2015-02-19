#include "camera.h"
#include "ui_camera.h"
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QTimer>
#include <QDebug>
Q_DECLARE_METATYPE(QCameraInfo)
Camera::Camera(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Camera),
    camera(0),
    imageCapture(0),
    isCapturingImage(false)
{
    ui->setupUi(this);
    setCamera(QCameraInfo::defaultCamera());
}
Camera::~Camera()
{
    delete imageCapture;
    delete camera;
}
void Camera::setCamera(const QCameraInfo &cameraInfo)
{
    delete imageCapture;
    delete camera;
    camera = new QCamera(cameraInfo);
    imageCapture = new QCameraImageCapture(camera);
    camera->setViewfinder(ui->viewfinder);
    connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(processCapturedImage(int,QImage)));
    connect(imageCapture, SIGNAL(imageSaved(int,QString)), this, SLOT(imageSaved(int,QString)));
    camera->start();
}
int i=0,j=0;
void Camera::processCapturedImage(int requestId, const QImage& img)
{
    Q_UNUSED(requestId);
    QImage scaledImage = img.scaled(ui->viewfinder->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));
    // Display captured image for 3 seconds.
    displayCapturedImage();
    QTimer::singleShot(3000, this, SLOT(displayViewfinder()));
    const QString slikca = "C:/Users/Trinet/Desktop/slika"+QString::number(i)+".png";
    img.save(slikca, "png", 50);
    i++;
}
void Camera::takeImage()
{
    isCapturingImage = true;
    imageCapture->capture();
    isCapturingImage = false;
}
void Camera::displayViewfinder()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void Camera::displayCapturedImage()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void Camera::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    Q_UNUSED(fileName);
    isCapturingImage = false;
    if(j<5){
        Camera::takeImage();
        j++;
    }
    else if(j==5)
        j=1;
}
