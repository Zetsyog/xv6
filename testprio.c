/*
 * Teste les priorités des processus : génère n processus.
 * Chaque processus a une priorité et effectue une boucle
 * de 500 millions d'itérations, en affichant un caractère
 * toutes les 10 millions d'itérations.
 *	testprio 2a 0b 0c
 * génère 3 processus, le premier a la priorité 2 et affiche
 * des "a", les deux autres ont la priorité 0 et affichent
 * des "b" et des "c".
 * Avec un "+", une attente est générée (1 seconde environ)
 * à la i*100-millionième itération, i étant le numéro du
 * processus.
 */

#include "types.h"
#include "user.h"
#include "prio.h"

#define	M10	(10*1000*1000)		// 10 millions

void
pig(int prio, char *c, int dosleep)
{
  int i;

  if (setprio(prio, 0) < 0) {
    printf(2, "cannot setprio %d for char %c\n", prio, *c);
    exit();
  }
  for (i = 0; i < 50*M10 ; i++) {
    if (dosleep && i == dosleep*10*M10)
	sleep (100) ;
    if (i % M10 == 0)
      write(1,c,1);
  }
  exit();
}

void
usage(void)
{
  printf(2, "Usage: testprio [+]pc [ [s]pc [ ...]] \n"
	      "\t+ : pour provoquer un sleep()\n"
	      "\tp : priorité (0...3)\n"
	      "\tc : caractère à afficher\n"
	      );
  exit();
}

int
main(int argc, char *argv[])
{
  int i, prio, pid, dosleep;
  char *p;

  // il faut se mettre dans la priorité la plus élevée, sinon on
  // n'arrivera pas à générer d'autres fils si on en a déjà généré
  // un de priorité élevée
  setprio (PRIO_RT, 0);
  if (argc < 2)
    usage();

  for (i = 1 ; i < argc; i++) {
    p = argv [i];

    dosleep = 0;
    if (*p == '+') {
	dosleep = i;
	p++;
    }

    if (*p < '0' || *p > '3')
      usage ();
    prio = *p - '0';
    p++;

    switch (pid = fork ()) {
      case -1:
	printf(2, "Cannot fork");
	exit();
      case 0:
	pig(prio, p, dosleep);
	exit();
      default:
	break;
    }
  }
  for (i = 1 ; i < argc; i++) {
    wait();
  }
  printf(1,"\n");			// affichage bien propre à la fin
  exit();
}
