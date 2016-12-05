L'accent a été mis sur la gestion des erreurs.
Dans le programme, celles-ci sont implémentées sous la forme "Erreur (localisation de l'erreur)" afin de cibler au mieux l'erreur ainsi que sa provenance.
Dans le programme, trois fonctions d'affichage sont utilisées :
- fprintf afin d'être sûr de récupérer l'erreur lorsque le programme est susceptible de crasher (Allocation mémoire)
- printf ou puts dans les autres cas. La fonction puts ne prend qu'une chaîne de caractère en paramètre, et est donc plus légère que printf. Néanmoins, dans le cas de notre programme, l'utilisateur ne perçoit aucune différence.
Dans le programme, certaines gestions d'erreur peuvent sembler inutiles. Celles-ci assurent l'évolutivité du programme.

L'implémentation d'une table de hachage aurait été préférable pour la recherche des points/formes, notamment si le dessin est de taille importante.
Néanmoins, le cahier des charges demandait explicitement une gestion via des ABR.

Le programme crashe ligne 234 (Segmentation fault) dans la fonction LimitesDessin si le fichier ouvert est vide. LimitesDessin est appelée par la gestion de l'interface graphique, je n'ai pas essayé de résoudre le problème, par manque de temps. Je n'ai pas repéré d'autre problème d'instabilité du programme.
Les fichiers vide.sch et bonhomme.sch sont fournis pour tester le programme.
