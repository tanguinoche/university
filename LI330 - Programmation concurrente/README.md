#LI330 : Programmation concurrente

#Description brève l'UE :
aborder les problèmes liés à l'exécution concurrente de processus en utilisant les mécanismes fournis par le langage Ada. Ce cours offre aussi une première ouverture vers l'algorithmique répartie.

#Description de l'UE :
L'objectif de ce cours est de présenter les techniques pour la programmation concurrente à partir des besoins et des problèmes liés à la concurrence. Il sera également fait des ouvertures sur des notions de base en algorithmique répartie. Les notions vues sont:
- Le rôle du runtime dans l'exécution d'un programme,
- La notion de tâche,
- Le problème de l'accès concurrent à des données partagées,
- Les différents mécanismes de protection des données partagées,
- Les mécanismes de communication entre tâches (rendez-vous, communication asynchrone),
- La terminaison d'un programme concurrent,
- Les éléments pour la structure d'un serveur,
- Des bases d'algorithmique répartie.
Le langage Ada sera utilisé pour illustrer en TD et en TME ces notions. Ce choix se justifie par la richesses des mécanismes de gestion de la concurrence qui évite de devoir accéder directement aux routines du système d'exploitation.

#Buts pédagogiques :
Programmation événementielle et concurrente
Algorithmique répartie
Introduction aux systèmes d'exploitation
Concurrence
Introduction aux calculs répartis
Client-serveur et Web

#Bibliographie :
L. Zaffalon & P. Breguet, "Programmation Concurrente et temps-réel avec Ada95", Presses polytechniques et universitaires romandes
Michel Raynal, "Algorithmique du parallélisme - Le problème de l'exclusion mutuelle", Dunod

#Semainier :
Semaine 1 : Introduction, rappels de programmation impérative (structures de contrôle, procédures, fonctions, types, tableaux)
Semaine 2 : Structuration d'un programme et notion de runtime et de compilation séparée, tâches simples (avec discriminant), instruction bloc
Semaine 3 : Problème de cohérence de variables en cas d'accès concurrent, notion de types protégés
Semaine 4 : Communication entre tâches, points d'entrées, rendez-vous, attente multiple (select)
Semaine 5 : Exceptions, terminaison d'un programme et propagation des erreurs entre tâches, notion de flux d'exécution entre tâches et types protégés
Semaine 6 : Pointeurs et allocation dynamique
Semaine 7 : Tâches dynamiques, structure d'un serveur multi-threadé
Semaine 8 : Anneaux de tâches
Semaine 9 : Interblocage et famine: définition, détection et prévention
Semaine 10 : Notions d'algorithmique répartie: jetons, vagues
Semaine 11 : Synthèse et Conclusion
