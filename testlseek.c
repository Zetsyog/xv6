#include "types.h"
#include "user.h"
#include "fcntl.h"

#define CHK(op)       \
	do {                \
		if ((op) == -1)   \
			printf(2, #op);  \
	} while (0)

#define BUF_SIZE 512

void testlseek(char *name, int o, int byte_n) {
  char buf[BUF_SIZE] = { 0 };

  int fd;
  int n;
  int a = 0;

  CHK(fd = open(name, O_RDONLY));
  CHK(lseek(fd, o, o < 0 ? SEEK_END : SEEK_SET));

  while((n = read(fd, buf, sizeof(buf))) > 0 && a < byte_n) {
    if(n < BUF_SIZE) {
      buf[n] = 0;
    }
    a += n;
    if(a > byte_n) {
      buf[byte_n % BUF_SIZE] = 0;
    } 
    
    printf(1, "%s", buf);
  }
  if(n < 0) {
    printf(2, "testlseek: read error\n");
  }
  printf(1, "\n");
}

int 
main(int argc, char *argv[]) {
  if(argc != 4) {
    printf(1, "usage: %s [file] [o(ffset)] [n(umber of byte)]\n", argv[0]);
    exit();
  }
  int o = atoi(argv[2]);
  int byte_n = atoi(argv[3]);

  testlseek(argv[1], o, byte_n);
  exit();
}