#include "ui/widgets/attitudewidget.hh"

#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>

#include "messages/gyromessage.hh"
#include "messages/message_defs.h"

using namespace Qt3DCore;
using namespace Qt3DExtras;

AttitudeWidget::AttitudeWidget()
    : SensorWidget("Attitude")
{
    Qt3DWindow* view = new Qt3DWindow();
    scene_container_ = QWidget::createWindowContainer(view);
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xff00ff)));

    QEntity* root = new QEntity();
    QCylinderMesh* cylinder = new QCylinderMesh();
    Qt3DExtras::QPhongMaterial* cylinderMaterial = new Qt3DExtras::QPhongMaterial();
    cylinderMaterial->setDiffuse(QColor(QRgb(0x928327)));
    transform_ = new Qt3DCore::QTransform();
    transform_->setTranslation(QVector3D(0.0f, 4.0f, -1.5));
    rocket_ = new QEntity(root);
    rocket_->addComponent(cylinder);
    rocket_->addComponent(cylinderMaterial);
    rocket_->addComponent(transform_);

    Qt3DRender::QCamera* cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity* lightEntity = new Qt3DCore::QEntity(root);
    Qt3DRender::QPointLight* light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform* lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    view->setRootEntity(root);
    layout_->addWidget(scene_container_);
    setMinimumHeight(600);
}

AttitudeWidget::~AttitudeWidget()
{
}

void AttitudeWidget::accept(Message& msg)
{
    if (msg.id() != MSG_ID_GYRO) {
        return;
    }

    GyroMessage& message = (GyroMessage&)msg;
    transform_->setRotation(QQuaternion(QVector4D(message.q1(), message.q2(), message.q3(), message.q4())));
}