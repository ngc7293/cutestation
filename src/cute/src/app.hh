#ifndef CUTE_APP_Hh_
#define CUTE_APP_HH_

#include <QObject>

#include <filesystem>
#include <memory>

namespace cute {

class App : public QObject {
    Q_OBJECT

public:
    App(const std::filesystem::path& config_path);
    ~App();

    void show();

private:
    struct priv;
    std::unique_ptr<priv> _d;
};

}

#endif