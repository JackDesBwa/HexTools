// This utility is specially designed for use with socat
// Example: socat tcp-listen:1234,reuseaddr exec:./schex,fdin=3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>

#define IN_SOCAT 3
#define OUT_SOCAT STDOUT_FILENO
#define IN_USER STDIN_FILENO
#define OUT_USER STDERR_FILENO

int main() {
	unsigned char data[512];
	char loop = 1;
	do {
		struct pollfd fds[2];
		fds[0].fd = IN_SOCAT;
		fds[0].events = POLLIN;
		fds[1].fd = IN_USER;
		fds[1].events = POLLIN;
		int timeout_msecs = 5*1e3;

		int pollres = poll(fds, 2, timeout_msecs);

		if (pollres > 0) {
			int i;
			if (fds[0].revents & POLLIN) {
				int rd = read(fds[0].fd, data, sizeof(data));
				if (rd) {
					dprintf(OUT_USER, "\e[1;36mIN:");
					for (i = 0; i < rd; ++i)
						dprintf(OUT_USER, " %02X", data[i]);
					dprintf(OUT_USER, "\e[0m\n");
				} else {
					loop = 0;
				}
			}
			if (fds[1].revents & POLLIN) {
				int rd = read(fds[1].fd, data, sizeof(data));
				if (rd) {
					dprintf(OUT_USER, "\e[1;35mOUT:", rd);
					char * pdata = data;
					char * pdataold;
					char ok;
					do {
						pdataold = pdata;
						unsigned int hex = strtoul(pdata, &pdata, 16);
						ok = (pdata != pdataold && pdata < (char*) data + rd);
						if (ok) {
							unsigned char chex = hex;
							dprintf(OUT_SOCAT, "%c", chex);
							dprintf(OUT_USER, (hex == chex) ? " %02X" : " \e[4m%02X\e[24m", chex);
						}
					} while (ok);
					dprintf(OUT_USER, "\e[0m\n");
				} else {
					loop = 0;
				}
			}
		}
	} while (loop);
	return 0;
}
