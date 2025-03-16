#define MAXNAMELEN 256
#define MAXPKTLEN  2048
#define MAXMSGLEN  1024
#define QUIT_STRING "close"
#define WELCOME_MSG    0
#define USER_NAME     1
#define EMAIL_MSG_TO_SERVER    2
#define EMAIL_MSG_TO_CLIENT 3
#define CLOSE_CON 4
#define SERVER_ERROR 5

typedef struct _packet {


	uint8_t     type;

	
	uint32_t      lent;

	// packet text
	char *    text;

} Packet;

extern int startserver();
extern Packet *recvpkt(int sd);
extern int sendpkt(int sd, uint8_t typ, uint32_t len, char *buf);
extern void freepkt(Packet *msg);

