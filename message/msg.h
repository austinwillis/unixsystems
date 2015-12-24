//Austin Willis
//CS375
//Project 6
const int MAXLEN = 256;

enum msgtype { SRVMSG=1, CLIMSG };

struct message { long type; char data[MAXLEN]; };
