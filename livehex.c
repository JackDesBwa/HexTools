#include <stdio.h>
#include <unistd.h>

int main() {
	unsigned char data[512];
	size_t addr = 0;
	int iRead = 0;
	while((iRead = read(0, data, sizeof(data))) > 0) {
		int i;
		for (i = 0; i < iRead; ++i) {
			if ((addr & ((1 << 3)-1)) == 0)
				printf(" ");
			if ((addr & ((1 << 4)-1)) == 0)
				printf("\n%07x:", addr);
			printf(" %02X", data[i]);
			fflush(stdout);
			addr++;
		}	
	}
	printf("\n");
	return 0;
}
