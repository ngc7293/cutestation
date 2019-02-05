#ifndef CONNECTION_HH
#define CONNECTION_HH

#include <QObject>

class Connection : public QObject {
    Q_OBJECT

public:
    Connection();
    virtual ~Connection();
};

#endif