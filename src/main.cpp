#include "chatwindow.h"
#include "transceiver.h"
#include "router.h"
#include "Packet.pb.h"
#include "Message.pb.h"
#include <string>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatWindow w;
    Transceiver t;
    Router r(&t);

    w.addChat("Group Chat");
    //w.writeMessage("Group Chat", "bar", "baz");

    w.show();

    QObject::connect(&r, &Router::messageReceived,
            &w, [&w](pb::Packet p) {
                pb::Message msg = p.msg();
                w.writeMessage("Group Chat",
                        QString::fromStdString(msg.name()),
                        QString::fromStdString(msg.text()));
            });
    QObject::connect(&w, &ChatWindow::newMessage,
            &r, [&r](QString chatname, QString message) {
                pb::Packet p;
                pb::Message *msg = p.mutable_msg();
                msg->set_name(chatname.toStdString());
                msg->set_text(message.toStdString());
                p.set_message_type(pb::Packet::MESSAGE);
                r.sendMessage(p);
            });

    //t.sendMessage("Hello world");
    return a.exec();
}
