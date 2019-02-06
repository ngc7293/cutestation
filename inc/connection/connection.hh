#ifndef CONNECTION_HH_
#define CONNECTION_HH_

#include <QObject>

class Connection : public QObject {
    Q_OBJECT

public:
    Connection();
    virtual ~Connection();
};

#endif // CONNECTION_HH_