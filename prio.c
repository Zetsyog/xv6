/*
 * Change la priorité d'un processus existant : prio <prio> <pid>
 *   Exemple : prio 1 2
 * Exécute une commande en spécifiant sa priorité : prio <prio> <cmd> [args...]
 *   Exemple : prio 2 rm toto titi tata
 */

#include "types.h"
#include "user.h"
#include "prio.h"

int
main(int argc, char *argv[])
{
  int prio;
  int pid;

  if (argc < 3){
    printf(2, "Usage: prio <prio> cmd [args...]\n\tprio <prio> <pid>\n");
    exit();
  }
  prio = atoi(argv[1]);
  pid = atoi(argv[2]);
  if (setprio(prio, pid) == -1){
    printf(2, "cannot setprio(%d,%d)\n", prio, pid);
    exit();
  }
  if (pid == 0) {
    exec (argv[2], argv+2);
    printf(2, "cannot exec %s\n", argv[2]);
  }
  exit();
}
