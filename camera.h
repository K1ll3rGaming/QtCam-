#ifndef CAMERA_H
#define CAMERA_H
#include <QCamera>
#include <QCameraImageCapture>
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class Camera; }
QT_END_NAMESPACE
class Camera : public QMainWindow
{
    Q_OBJECT
public:
    Camera(QWidget *parent = 0);
    ~Camera();
private slots:
    void setCamera(const QCameraInfo &cameraInfo);
    void takeImage();
    void processCapturedImage(int requestId, const QImage &img);
    void displayViewfinder();
    void displayCapturedImage();
    void imageSaved(int id, const QString &fileName);

private:
    Ui::Camera *ui;
    QCamera *camera;
    QCameraImageCapture *imageCapture;
    bool isCapturingImage;
};
#endif
