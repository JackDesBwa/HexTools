#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	unsigned char data[512 + 1];
	size_t addr = 0;
	int iRead = 0;
	while((iRead = read(0, data, sizeof(data) - 1)) > 0) {
		int hex, iScanned, ok;
		char * pdata = data, * pdata_old;
		data[iRead] = 0; // Add a null character at end of read data
		do {
			pdata_old = pdata;
			hex = strtol(pdata, &pdata, 16);
			ok = (pdata != pdataold && pdata < (char*) data + rd);
			if (ok) {
				unsigned char uchhex = hex;
				printf("%c", uchhex);
				if (uchhex != hex) fprintf(stderr, "%x truncated to %x\n", hex, uchhex);
			}
		} while (ok);
		fflush(stdout);
	}
	return 0;
}
