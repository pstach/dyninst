#if !defined(__mc_childnode_h)
#define __mc_childnode_h 1

#include <string>

#include "mrnet/src/MC_Message.h"
#include "mrnet/src/MC_RemoteNode.h"

class MC_ChildNode{
 protected:
  MC_RemoteNode * upstream_node;

 private:
  string hostname;
  unsigned short port;
  bool threaded;

 public:
  MC_ChildNode(bool, string, unsigned short);
  virtual ~MC_ChildNode(void);
  virtual int proc_PacketsFromUpStream(std::list <MC_Packet *> &)=0;
  virtual int proc_DataFromUpStream(MC_Packet *)=0;

  int recv_PacketsFromUpStream(std::list <MC_Packet *> &packet_list);
  int send_PacketUpStream(MC_Packet *packet);
  int flush_PacketsUpStream();

  string get_HostName();
  unsigned short get_Port();
};

#endif /* __mc_childnode_h */
