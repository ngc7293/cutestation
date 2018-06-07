#ifndef ATTITUDE_WIDGET
#define ATTITUDE_WIDGET

#include "inc/ui/widgets/sensorwidget.hh"

#include <QWidget>

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

class AttitudeWidget : public SensorWidget {
private:
    QWidget* scene_container_;
    Qt3DCore::QEntity* rocket_;
    Qt3DCore::QTransform* transform_;

public:
    AttitudeWidget();
    virtual ~AttitudeWidget();

    virtual void accept(Message& message);
};

#endif