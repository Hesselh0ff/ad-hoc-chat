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
	
	//intitiate sequence number:
	int seq_nmr = rand(); 	//seq_nmr can now have a value between 0 and 32767	(rand_MAX)
	
	Routing();
	virtual ~Routing();
    std::vector<Packet*> received_data;
    void incrementSeq(Packet *pkt);
    bool isNew(Packet *pkt);
    
	void Extend_UDP_Header(Packet *pkt);
    QByteArray forward(Packet *pkt);
};

#endif /* ROUTING_H_ */
