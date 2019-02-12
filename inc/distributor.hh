#ifndef DISTRIBUTOR_HH_
#define DISTRIBUTOR_HH_

#include <QObject>

#include "data/data.hh"
#include "widgets/widget.hh"

class Distributor : public QObject {
    Q_OBJECT

private:
    std::vector<Widget*> widgets_;

private:
    Distributor();

public:
    static Distributor& get();
    ~Distributor();

    void add(Widget* widget) { widgets_.push_back(widget); }

public slots:
    void onData(Data* data);
};

#endif // DISTRIBUTOR_HH_