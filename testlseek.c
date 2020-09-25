#include "types.h"
#include "user.h"
#include "fcntl.h"

#define CHK(op)       \
	do {                \
		if ((op) == -1)   \
			printf(2, #op);  \
	} while (0)

#define BUF_SIZE 512

int 
main(int argc, char *argv[]) {
  if(argc != 4) {
    printf(1, "usage: %s [file] [o(ffset)] [n(umber of byte)]", argv[0]);
    exit();
  }
  int o = atoi(argv[2]);
  int byte_n = atoi(argv[3]);

  char buf[BUF_SIZE] = { 0 };

  int fd;
  int n;
  int a = 0;

  CHK(fd = open(argv[1], O_RDONLY));
  CHK(lseek(fd, o, o < 0 ? SEEK_END : SEEK_SET));

  while((n = read(fd, buf, sizeof(buf))) > 0 && a < byte_n) {
    a += n;
    printf(1, buf);
  }
  if(n < 0) {
    printf(2, "testlseek: read error\n");
  }
  printf(1, "\n");
  exit();
}