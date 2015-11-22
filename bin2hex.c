#include <stdio.h>
#include <unistd.h>

int main() {
	unsigned char data[512];
	size_t addr = 0;
	int iRead = 0;
	while((iRead = read(0, data, sizeof(data))) > 0) {
		int i;
		for (i = 0; i < iRead; ++i) {
			printf(" %02X", data[i]);
			addr++;
		}
		printf("\n");
		fflush(stdout);
	}
	return 0;
}
