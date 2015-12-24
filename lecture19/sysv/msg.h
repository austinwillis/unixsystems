const int MAXLEN = 512;

enum msgtype { SRVMSG=1, CLIMSG };

struct message { long type; char data[MAXLEN]; };
