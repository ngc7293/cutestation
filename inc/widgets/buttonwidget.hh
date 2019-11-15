#ifndef CHART_WIDGET_HH_
#define CHART_WIDGET_HH_

#include "connection/connection.hh"
#include "widget.hh"

#include <shared/interfaces/enums.h>

class ChartWidget : public Widget {
    Q_OBJECT

private:
    QString text_;
    can_board board_;
    int message_;
    int value_;

    Connection* connection_;

public:
    ButtonWidget();
    virtual ~ButtonWidget();

    Config<ButtonWidget>* config() { return config_; }

    void setText(QString text) { text_ = text; }
    void setBoard(int board) { board_ = board; }
    void setMessage(int message) { message_ = message; }
    void setValue(intvalue) { value_ = value; }

    void setConnection()

        public slots : virtual void accept(Data& data) {};
    virtual void onClick();

signals:
    void send(radio_packet_t);
};

#endif // CHART_WIDGET_HH_
