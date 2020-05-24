**Compilation en ligne de commande:**

- Créer un dossier build dans le dossier partie6
- Ouvrir ce dossier dans le terminal et tapper: **cmake ../src**
*-> Cette commande construit les fichiers de compilation dans ce dossier.*
- Une fois la commande exécutée, tapper: **make application**
*-> Cette commande va compiler le code à partir de l'exécutable*
- Pour lancer le programme tapper: **./ application**
*-> Cette commande va lancer le programme avec le app.json par défaut.*
- Pour le lancer avec un autre fichier de configuration, tapper: 
**./ application nomfichierapp.json** 

**Qu'est-ce que nous avons fait:**

- modélisation d'une culture de bactérie dans assiette de petri			--- trouver app.json apte à simuler
- nutriments générés automatiquement -> bactérie s'en nourrissent
- 3 types bactéries imposés -> démo s-t-1-2
- ajout 2 groupes swarm (3-4)
- ajout 2 autres types (poisonousbacteria et madbacteria) -> p,m
- temps de simulation affiché 
- Spray désinfectant + son
- flash ultraviolet + son
- musique touche A
- fichiers de configurations particuliers
- statistiques (+ celles des extensions) -> tab
- commandes (extensions!) indiquées 

**Comment avons-nous procédé, choix, méthodes, organisation**

- Lecture, discussion, partage des tâches (généralement par sous partie)
- Travail si possible en amont de la séance d'exercices
- Respect du calendrier (voire avance)
- Suivre les consignes au max -> conception générale inchangée
  mais ajout améliorations
- 

**Quelles difficultés avons-nous rencontrées et comment nous les avons
traitées**

- impossibilité de travailler sur windows->machine virtelle Oracle linux
- machines virtuelles EPFL ne transmettent pas le son (pas seulement
  de notre programme!)
- aucune difficulté d'entente, implication égale de chacune
- Qqes difficultés de compréhension de l'énoncé -> discussion à 2, voire
  avec d'autres groupes
- Erreurs jamais rencontrées auparavant -> recherche google
- Programme qui crash -> utiliser le debugger

**Ce que nous avons retenu du projet**

- Utilisation de github
- Programmation en fichiers séparés, importance de séparer les classes
- Mieux gérer la mémoire des pointeurs
- Apprentissage des MAP
- Utilisation de SFML (graphique et son)
- Apprendre à modulariser
- Voir comment aborder un projet vs exercices de séries

