/*
 * Routing.h
 *  group: 1
 */

#ifndef ROUTING_H_
#define ROUTING_H_

#include <vector>
#include <iostream>
#include <QtNetwork>

#include "Packet.h"
#include "Message.pb.h"

class Routing {
public:
	Routing();
	virtual ~Routing();
    std::vector<Packet*> received_data;

private:
        void incrementSeq(Packet *pkt);
        bool isNew(Packet *pkt);
        void forward(Packet *pkt);
		void retransmission(Packet *pkt);

    void incrementSeq(Packet *pkt);
    bool isNew(Packet *pkt);
    QByteArray forward(Packet *pkt);
};

#endif /* ROUTING_H_ */
