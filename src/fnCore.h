#ifndef FN_FNCORE_H // one-time include
#define FN_FNCORE_H

extern "C" {
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <libnetfilter_queue/libipq.h>
#include <linux/netfilter.h>
}

#include "fn_error.h"
#include "fnPacket.h"

// State machine states

typedef enum _CORE_PCL_STATES 
{
	PCL_DETERMINE_DIRECTION,
	PCL_INTERNAL_PACKET_RECEIVED,	// Entry state
	PCL_EXTERNAL_PACKET_RECEIVED,	// Entry state
	PCL_FIND_OUTBOUND_MAP,	// Looks up map to transform packet on way out
	PCL_FIND_INBOUND_MAP,	// Looks up map to transform packet on way back in	
	PCL_CREATE_NEW_MAP_UDP,		// Create a new map if one doesn't exist
	PCL_TRANSFORM_OUTBOUND_ICMP,	// Apply map to packet
	PCL_TRANSFORM_OUTBOUND_UDP,
	PCL_TRANSFORM_OUTBOUND_TCP,
	PCL_TRANSFORM_INBOUND_ICMP,
	PCL_TRANSFORM_INBOUND_UDP,
	PCL_TRANSFORM_INBOUND_TCP,
	PCL_UPDATE_MAP,			// Update expiry of map entry
	PCL_VERIFY_DESTINATION,	// Check to see if hairpinning rule needs apply
	PCL_SEND_PACKET,		// Send the packet
	PCL_DROP_PACKET,		// Drop the packet
	PCL_DONE,				// Done processing this packet, wait for a new one
	PCL_ERROR,				// Something bad happened
} CORE_PCL_STATES;



class fnCore
{
   public:
        static fnCore* getInstance();
        ~fnCore();
        
  		FN_STATUS initialize();
  		FN_STATUS executeNAT();
  		int processPacket(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg, struct nfq_data *nfa, void *data);

	
    protected:
    	fnCore(); ///< Protected constructor prevents creation of object my non-members
		static fnCore* s_Instance; ///< The singleton instance
		
		FN_STATUS sendPacket(fnPacket &packet);
	
	private:

};

#endif
