/*
 * Routing.cpp
 *
 *  Created on: 9 apr. 2017
 *  group: 1
 */

#include "Routing.h"

Routing::Routing() {
}

Routing::~Routing() {
}

void Routing::incrementSeq(Packet *pkt){
    /* Increment sequence number of packet */
    packet_repr pkt_struct = pkt->getPacket();
    pkt_struct.seq = pkt_struct.seq+1;
    pkt->loadFromStruct(pkt_struct);
}

bool Routing::isNew(Packet *pkt){
    /* Check if a packet is new */
    packet_repr pkt_struct = pkt->getPacket();

    for(auto p: received_data){
        packet_repr temp_pkt_struct = p->getPacket();
        if(pkt_struct.msg_id == temp_pkt_struct.msg_id
                &&
           pkt_struct.seq > temp_pkt_struct.seq
        ){
            // it is an old packet
            return false;
        }
    }

    received_data.push_back(pkt);
    return true;
}

QByteArray Routing::forward(Packet *pkt){
    //will determine which nodes should get the packet that is received from the sender. This means
    //that this function should flood the packets to everyone except to the one that is was sent.
    //Beware that the sequence number should also be increased.
    incrementSeq(pkt);

//    if(isNew(pkt) == false)       // TODO
//        return QByteArray("", 0);

    MessageProto::Message message;
    pkt->getPacket(&message);
    std::string payload = message.SerializeAsString();

    QByteArray byteArray(payload.c_str(), payload.length());
    return byteArray;
}

void Routing::retransmission(Packet *pkt){
	//After a packet is lost or damaged, there should be  retransmission of that same packet.
	//This can be detected either by the PAR (positive ack with retransmission) or by the checksum.
	//So these two properties of a packet should be checked.
	
	//If the checksum is different at the receiver the the one from the sender then retransmit
	packet_repr pkt_struct = pkt->getPacket();
	packet_repr temp_pkt_struct = p->getPacket();
	if(pkt_struct.checksum != temp_pkt_struct.checksum){
		//The packet does contain a bit error and should be send again
		//unless it is an old packet
		
		//Sending again, try to call forward function?
		forward(Packet *pkt);
	}
		//The packet has no checksum errors 
	
	//Next check for the ACKs coming from the 
	return QByteArray("", 0);
}

