#ifndef __utils_h
#define __utils_h 1

#include <vector>
#include <string>

#include <libgen.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

class Line{
 private:
  std::vector <string> words;
 public:
  Line(const char *);
  string get_NextWord();
  string get_Word(int);
  int get_NumWords();
};

inline unsigned int uintHash(const unsigned int &val) {
  return val;
}

inline unsigned intHash(const int &val) {
  return val;
}

int connect_to_host(int *sock_in, const char * hostname, unsigned short port);
int bind_to_port(int *sock_in, unsigned short *port_in);
int get_socket_connection(int bound_socket);
int get_socket_peer(int connected_socket, char **hostname, unsigned short * port);
unsigned short get_port_from_socket(int sock);
const string getHostName(const string hostname="");    // e.g. "foo"
const string getDomainName(const string hostname="");  // "bar.net"
const string getNetworkName(const string hostname=""); // "foo.bar.net"
const string getNetworkAddr(const string hostname=""); // "127.0.0.1"

int create_Process(const string &remote_shell,
                   const string &hostName, const string &userName,
                   const string &command, const std::vector<string> &arg_list);
int remoteCommand(const string remoteExecCmd,
                  const string hostName, const string userName,
                  const string command, const std::vector<string> &arg_list);
int rshCommand(const string &hostName, const string &userName, 
               const string &command, const std::vector<string> &arg_list);
int execCmd(const string command, const std::vector<string> &args);

extern unsigned int _count;
//static char *mc_tmpfilename;
//for verbose debugging, comment first 3, uncomment next 3
//#define mc_printf(X) ;
//#define mc_printf(X) _mc_printf(X);

#include <libgen.h>
#define _mc_printf(X) \
do { \
  mc_tmpfilename=0; \
  mc_tmpfilename=strdup(__FILE__); /*basename may modify 1st arg, so copy */\
  assert(mc_tmpfilename); \
  fprintf(stderr, "***[%d]: tmp:%p &tmp:%p\n", getpid(), mc_tmpfilename, &mc_tmpfilename); \
  fprintf(stderr, "[%s:%d:%s:%d]: ", getHostName().c_str(), getpid(), basename(mc_tmpfilename), __LINE__); \
  fprintf(stderr, "***[%d]: tmp:%p &tmp:%p\n", getpid(), mc_tmpfilename, &mc_tmpfilename); \
  free(mc_tmpfilename); \
  fprintf X; fflush(stderr);       \
} while(0)

struct ltstr
{
  bool operator()(string s1, string s2) const
  {
    return (s1 < s2);
  }
};

extern pthread_key_t tsd_key;
class tsd_t{
 public:
  pthread_t thread_id;
  const char * thread_name;
  char tmp_filename[256];
};

//#define _fprintf(X)  ;
//#define _perror(X) ;
#define _fprintf(X) fprintf X ;
#define _perror(X) perror(X); 
#define MCFL  __FILE__,__LINE__  //used to call mc_printf(MCFL, ...)
int mc_printf(const char * file, int line, FILE * fp, const char * format, ...);

#endif /* __utils_h */
