#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	unsigned char data[512 + 1];
	size_t addr = 0;
	int iRead = 0;
	while((iRead = read(0, data, sizeof(data) - 1)) > 0) {
		int hex, iScanned;
		char * pdata = data, * pdata_old;
		data[iRead] = 0; // Add a null character at end of read data
		while (1) {
			static i;
			i++;
			if (i==20) break;
			pdata_old = pdata;
			hex = strtol(pdata, &pdata, 16);
			if (pdata != pdata_old) {
				unsigned char uchhex = hex;
				printf("%c", uchhex);
				if (uchhex != hex) fprintf(stderr, "%x truncated to %x\n", hex, uchhex);
			} else {
				break;
			}
		}
		fflush(stdout);
	}
	return 0;
}
