#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "common.h"

#define MAXNAMELEN 256

void printpkt(Packet *);

// prepare server to accept requests
// returns file descriptor of socket
// returns -1 on error

int startserver() {
	// fprintf(stderr, "Method Entry: startserver()\n");

	int sd;

	char * servhost;
	ushort servport;

	// create a TCP socket using socket()
	sd = socket(PF_INET, SOCK_STREAM, 0);

	// bind the socket to some port using bind()
	// let the system choose a port

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(5945);

	// Set this so that no issues if port already blocked.
	int optval = 1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optval,
				sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}

	bind(sd, (struct sockaddr *) &server_address, sizeof(server_address));

	// we are ready to receive connections
	listen(sd, 5);

	// figure out the full local host name (servhost)
	// use gethostname() and gethostbyname()
	// full host name is zeus.ite.gmu.edu instead of just zeus

	char hostname[MAXNAMELEN];

	if (gethostname(hostname, sizeof hostname) != 0)
		perror("gethostname");

	struct hostent* h;
	h = gethostbyname(hostname);

	// figure out the port assigned to this server (servport)
	// use getsockname()

	int len = sizeof(struct sockaddr);

	getsockname(sd, (struct sockaddr *) &server_address, &len);

	servhost = h->h_name;
	servport = ntohs(server_address.sin_port);

	// ready to accept requests
	fprintf(stderr,
			"Welcome to Santosh's E-mail Server running on host %s, port %hu\n",
			servhost, servport);
	return (sd);
}

int hooktoserver(char* user, char* servhost, ushort servport) {

	int sd;

	// create a TCP socket using socket()

	sd = socket(AF_INET, SOCK_STREAM, 0);

	

	// struct hostent *hostinfo;
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(servport);
	inet_pton(AF_INET, servhost, &address.sin_addr);


	if (connect(sd, (struct sockaddr *) &address, sizeof(address)) < 0) {
		perror("connecting");
		exit(1);
	}


	return (sd);
}


int readn(int sd, char *buf, size_t n) {
	
	size_t toberead = n;
	char * ptr = buf;

	while (toberead > 0) {

		int errno_save = 0;

		

		ssize_t  byteread = read(sd, ptr, toberead);
		errno_save = errno;

		

		if (byteread <= 0) {
		
			if (byteread == -1)
			{
				perror("read");
				errno = errno_save;
			}
			return (0);
		}

		toberead -= byteread;
		ptr += byteread;
	}

	
	return (1);
}

// receives a packet on the given socket.
Packet *recvpkt(int sd)
{
	// printf("Recvpkt via utils.\n");
	Packet *pkt;

	// allocate space for the pkt
	pkt = (Packet *) calloc(1, sizeof(Packet));
	if (!pkt) {
		fprintf(stderr, "error : unable to calloc\n");
		return(NULL);
	}

	// read the message type
	if (!readn(sd, (char *) &pkt->type, sizeof(pkt->type))) {
		free(pkt);
		return(NULL);
	}

	// read the message length
	if (!readn(sd, (char *) &pkt->lent, sizeof(pkt->lent))) {
		free(pkt);
		return(NULL);
	}
	pkt->lent = ntohl(pkt->lent);

	// allocate space for message text
	if (pkt->lent > 0) {
		pkt->text = (char *) malloc(pkt->lent + 1);
		if (!pkt) {
			fprintf(stderr, "error : unable to malloc\n");
			return(NULL);
		}

		// read the message text
		if (!readn(sd, pkt->text, pkt->lent)) {
			freepkt(pkt);
			return(NULL);
		}

		pkt->text[pkt->lent] = '\0';
	}

	// fprintf(stderr, "Reading packet complete succesfully. %s\n", pkt->text);
	// printpkt(pkt);

	return(pkt);
}

// Sends a packet on given socket with given type, length and data.
int sendpkt(int sd, uint8_t typ, uint32_t len, char *buf)
{
	//fprintf(stderr, "Send packet via utils. sd: %d, typ: %u, len: %lu, buf: %s\n", sd, typ, len, buf);
	char tmp[8];
	uint32_t siz;

	// write type and lent
	bcopy(&typ, tmp, sizeof(typ));
	siz = htonl(len);
	bcopy((uint32_t *) &siz, tmp+sizeof(typ), sizeof(len));
	write(sd, tmp, sizeof(typ) + sizeof(len));

	//* write message text
	if (len > 0)
		write(sd, buf, len);
	return(1);
}

// free memory of a given packet.
void freepkt(Packet *pkt)
{
	// fprintf(stderr, "Freeing packet.\n");
	free(pkt->text);
	free(pkt);
}

// display data in the given packet.
void printpkt(Packet *pkt)
{
	fprintf(stderr, "Printing packet.\n");
	fprintf(stderr, "pkt -> type: %u\n", pkt->type);
	fprintf(stderr, "pkt -> len: %d\n", pkt->lent);
	fprintf(stderr, "pkt -> text: %s\n", pkt->text);
}
