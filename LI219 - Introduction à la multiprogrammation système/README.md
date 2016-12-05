#LI219 : Introduction à la multiprogrammation système

#Description brève l'UE :
introduire les concepts de base des syst�mes d'exploitation et de la multiprogrammation. L'accent sera mis sur les notions de processus et d'acc�s concurrent aux ressources critiques (m�moire, fichiers).

#Description de l'UE :
Le premier contact d'un utilisateur avec l'environnement Unix est la connexion, phase durant laquelle il est demandé à l'usager un identifiant, login, et un mot de passe. Après authentification de ce couple par le système, l'utilisateur est connecté et a accès à des informations et applications partagées avec les autres utilisateurs ainsi qu'à des données propres. Plusieurs utilisateurs peuvent se connecter en même temps sans pour autant que les actions de l'un ne perturbent les autres utilisateurs. Les fonctionnalités rendant cela possible sont assurées par le système d'exploitation avec lequel l'utilisateur peut interagir pour gérer ses données et les programmes qu'il souhaite exécuter.
Ce cours est une première initiation aux systèmes d'exploitation (Unix en particulier) et a pour but d'expliquer :
- comment plusieurs utilisateurs peuvent se connecter en même temps sans pour autant se �gêner�,
- à quoi correspond l'exécution d'un programme,
- comment interagir avec le système d'exploitation,
- comment plusieurs programmes peuvent s'exécuter en même temps et les problèmes que cela pose,
- comment transmettre de l'information entre programmes qui s'exécutent.
Ces notions seront vues dans un premier temps en ne considérant que des programmes qui s'exécutent sur un seul ordinateur, nous verrons ensuite un modèle d'interaction entre processus, le modèle clients-serveurs. Nous nous intéresserons en fin de cours aux liens qui existent entre les systèmes d'exploitation et le réseau.


#Buts pédagogiques :
Introduction aux systèmes d'exploitation
Principes des systèmes d'exploitation
Ordonnancement
Gestion mémoire
Systèmes de fichiers
Réseaux et communication
Client-serveur et Web

#Bibliographie :
Unix Guide de l'étudiant. Harley Hahn, Editeur Dunod
Unix le tout en poche. David Taylor, Editeur Eyrolles
Pour ceux qui veulent aller plus loin : Systèmes d'exploitation. Andrew Tanenbaum. Pearson Education, 2003

#Semainier :
Semaine 1 : Introduction
Semaine 2 : Gestion des fichiers
Semaine 3 : Processus : hiérarchie, environnement d'exécution
Semaine 4 : Partage du processeur, processus en arrière plan
Semaine 5 : Partage de la mémoire
Semaine 6 : Signaux
Semaine 7 : Partage des ressources : sections critiques
Semaine 8 : Synchronisation
Semaine 9 : Modèle Client-Serveur (Internet)
Semaine 10 : Lien système-réseau (adresse IP, serveur DNS)
Semaine 11 : Synthèse et conclusion
