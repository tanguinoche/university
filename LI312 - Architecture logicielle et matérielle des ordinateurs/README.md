#LI312 : Architecture logicielle et matérielle des ordinateurs

#Description brève l'UE :
présenter l'architecture générale et les principes de fonctionnement d'un ordinateur de type PC, en insistant sur l'interface matériel/logiciel : gestionnaire d'interruptions, appels systèmes, traitement des exceptions, et la communication entre le processeur, la mémoire, les disques, et les périphériques.

#Description de l'UE :
La première partie est un rappel de l'architecture externe (jeu d'instructions) du processeur MIPS32, qui a été présentée au niveau L2 dans le cadre du module "Machine et représentation". On vise à préciser et à approfondir les points délicats de l'interface matériel/logiciel : gestionnaire d'interruptions, appels systèmes et exceptions. La seconde partie porte sur l'architecture générale d'un ordinateur de type PC, en introduisant les notions fondamentales nécessaires à la compréhension des architectures multi-cores actuelles : hiérarchie mémoire et mémoires caches, bus système, contrôleurs d'entrées/sorties sur disque, mécanismes de communication entre le processeur et les périphériques. On insiste sur les interactions entre le matériel et le système d'exploitation, et on analyse en détail les techniques de virtualisation permettant à plusieurs tâches de s'exécuter en pseudo-parallélisme, en partageant le processeur. On analyse enfin le support matériel aux techniques de mémoire virtuelle permettant à plusieurs programmes de cohabiter sur la même machine.

#Buts pédagogiques :
Multiprocesseurs et autres architectures

#Bibliographie :
Architecture des ordinateurs : Interface matériel / logiciel John Hennessy & David Patterson

#Semainier :
Semaine 1 : Architecture générale d'un ordinateur. Interface matériel/logiciel. Langage machine et jeu d'instructions du processeur MIPS32.
Semaine 2 : Mécanisme général d'exécution des programmes. Conventions concernant les appels de fonction et la gestion de la pile.
Semaine 3 : Génération du code binaire à partir du code C. Chaîne de compilation GCC.
Semaine 4 : Edition de lien et segmentation de la mémoire. L'éditeur de lien LD et le fichier LDSCRIPT.
Semaine 5 : Hiérarchie mémoire : caches L1 et L2. Evaluation de l'impact des caches sur les performances (temps d'exécution).
Semaine 6 : Interruptions, Exceptions et appels système. Mode "Utilisateur" et mode "Noyau". Analyse détaillé d'un gestionnaire d'Interruptions, exceptions et trappes.
Semaine 7 : Architectures multi-processeurs à mémoire partagée. Rôle du bus système.
Semaine 8 : Communication entre un processeur et ses périphériques. Contrôleur d'interruption vectorisé. Périphériques orientés "caractères" : exemple
Semaine 9 : Périphériques orientés blocs : contrôleurs de disque et contrôleurs réseau. Fonctionnalité DMA.
Semaine 10 : Virtualisation du processeur: principe de la multiprogrammation et mécanisme de commutation de tâches.
Semaine 11 : Principe de la mémoire virtuelle. Pagination et segmentation.
Semaine 12 : Programmation parallèle multi-tâches. Communication et de synchronisation entre processus. Problème de cohérence des caches.
