#ifndef CUTE_APP_Hh_
#define CUTE_APP_HH_

#include <QObject>

#include <memory>

namespace cute {

class App : public QObject {
    Q_OBJECT

public:
    App();
    ~App();

    void show();

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif