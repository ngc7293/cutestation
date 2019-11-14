#ifndef SERIES_HH_
#define SERIES_HH_

#include <QObject>

#include <vector>

class Series : public QObject {
    Q_OBJECT

private:
    std::vector<float> data_;
    int length_;

public:
    Series();
    ~Series();

    void add(float data);
    void clear();

signals:
    void dataChanged();
};

#endif /* SERIES_HH_ */