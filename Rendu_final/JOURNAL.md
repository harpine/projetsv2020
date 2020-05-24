# Journal 

## Groupe 38, Aline Brunner et Helena Binková, coachées par Sébastien Gachoud

### **Semaine 1**

Nous avons mis en place l'environnement de programmation et avons pris 
la décision de travailler avec Github (nous travaillons toutes les deux
avec QtCreator sur Linux, Aline est sur sa propre machine et Helena 
travaille sur une VM.)

Nous avons créé la classe CircularBody qui permet de modéliser un 
cercle, puis répondu aux quatre questions dans le fichier REPONSES. 
Nous avons passé les tests de la semaine 1 avec succès.

### **Semaine 2**

Nous avons partagé les tâches de la manière suivante : Helena a créé les 
classes Lab et PetriDish (2.1), Aline s'est occupée de la classe
Nutriment (2.2). Actuellement, nous avons un laboratoire qui a pour 
attribut une assiette de pétri. Celle-ci hérite de la classe 
CircularBody et comporte une température. À ce stade, toutes les 
méthodes de Lab font appel aux méthodes de PetriDish. Nous ne comprenons 
pas encore l'utilité de deux classes distinctes. 

Nous avons aussi répondu aux questions dans le fichier REPONSES. Tous les 
tests sont passés avec succès.

Actuellement, nous avons donc une assiette de pétri dont nous pouvons 
changer la température et dans laquelle nous pouvons faire évoluer des 
nutriments en fonction de cette température. 

### **Semaine 3**

Cette semaine, nous nous sommes fixées l'objectif de programmer jusqu'à 
la partie 3.3. Pour ce faire, Aline a créé les classes 
NutrimentGenerator, MutableNumber et MutableColor (3.1 et 3.2). Helena 
a ensuite créé la classe Bacterium (3.3). 

Nous avons aussi répondu aux questions dans le fichier REPONSES. Les 
tests unitaires et graphiques sont passés avec succès. 

Actuellement, nous avons donc une assiette de pétri dont les nutriments 
sont générés automatiquement et évoluent selon la température. Nous 
pouvons faire apparaître des bactéries (pour le moment immobiles) qui 
interagissent avec les nutriments et qui meurent quand elles n'ont plus 
d'énergie.

Nous gardons la partie 3.4 pour la semaine prochaine. 

### **Semaine 4**

Cette semaine l'objectif était de finir la partie 3. Aline s'est occupée
du début de la partie 3.4 (déplacement rectiligne uniforme), Helena 
s'est occupée du flagelle ainsi que du Basculement et gradient et pour 
finir Aline s'est occupée de la division et de la mutation.
Par rapport aux retouches finales, nous ne comprenons pas quels
destructeurs nous devons modifier et/ou ajouter... Nous en discuterons 
la semaine prochaine avec Sébastien.

Nous avons rencontré un problème concernant les bactéries mobiles : 
certaines restent figées dans la paroi de la PetriDish. En effet, des 
imprécisions dans les pas de temps dt impliquent que la bactérie se 
retrouve constamment en train de changer de direction une fois dans la 
paroi. Un remaniement des conditions de changement de direction permet 
de résoudre le problème.

Actuellement nos bactéries simples ont passé tous les tests et elles se
déplacent vers les nutriments, avec un flagelle, mutent et meurent. 

### **Semaine 5**

Cette semaine, nous avons fait la partie 4 du projet. Helena a fait la 
partie 4.1, Aline la partie 4.2. Nous avons compris l'utilité des 
destructeurs et avons fait les modifications nécessaires. 

Aline a rencontré un problème qui nous a fait revenir sur l'ajout des 
bactéries dans PetriDish. En effet, les bactéries non contenues dans
l'assiette n'étaient en fait jamais détruites. Nous nous en sommes 
rendues compte grâce à la notion de leader et de swarm.  L'ajout d'une 
fonctionnalité permettant de tracer une droite entre les bactéries côtes
à côtes dans le vecteur swarm a permis de détecter cette erreur 
visuellement. Nous avons décidé de garder cette fonction lorsque le mode
Debug est enclenché. 

Actuellement, la partie 4 est donc finalisée et tous les tests 
graphiques se déroulent bien. Nous avons donc des bactéries à tentacule 
et des bactéries à comportement de groupe. Les bactéries simples 
marchent toujours.

### **Vacances**

Avant de rendre notre projet, nous avons relu l'intégralité de notre 
code. Nous avons donc fait plusieurs améliorations. 

- Pour la méthode clone : dans PetriDish, nous avions créé un attribut 
tableau de clones où l'on rajoutait les clones créés lors d'un update 
de Bacterium, car nous ne voyions pas d'autre solution. Cependant, d'un 
point de vue conceptuel, cela n'avait aucun sens. Nous avons donc décidé
de plutôt créer une variable locale à la fonction PetriDish::update. 

- Nous avons aussi amélioré le basculement des SimpleBacterium et le 
changement de direction du leader des Swarms. Pour ce faire, nous avons 
ajouté une fonction bestOfN(int n) dans Bacterium changeant la direction
de la bactérie en fonction du meilleur score entre n possibilités. Cela 
permet une meilleure modularisation dans les sous-classe. De plus, dans 
SimpleBacterium, le nombre de possibilités n s'adapte en fonction du 
fichier app.json. 

*Jusqu'à présent, toutes les parties semblent fonctionnelles.*

### **Semaine 6**

Nous avions fini la partie 4 avant les vacances et la partie 5 n'est pas
encore sortie, donc nous faisons une petite pause de programmation
cette semaine. :)

### **Semaine 7**

Helena s'est occupée de la partie 5.1 et Aline a fait le début de la
partie 5.2 (test 18). Helena a commencé la suite et nous nous sommes
rejoint pour finaliser les statistiques.
Une fois les tests 17 à 19 passés, et donc la partie obligatoire 
terminée, nous nous sommes attaqués à la partie bonus, où nous avons 
fait des statistiques sur la vitesse des bactéries, les probabilités 
de basculement (tumble) des simple bacterium et la vitesse et longueur
des tentacules des twitching bacterium.

Le test 20 est passé avec succès, ce qui fait que nous avons terminé la 
partie de programmation de l'étape 5! Nous allons faire quelques essais
de simulation la semaine prochaine.

Actuellement, nous avons donc une boîte de Petri capable d'accueillir
3 sortes de bactérie et 2 sortes de nutriment. Les statistiques sont
tracées dans la fenêtre de simulation sous forme de graph.

### **Semaine 8**

Cette semaine nous avons codé 2 nouvelles classes de bactérie: 
PoisonousBacterium et MadBacterium. Aline s'est occupée de la classe
PoisonousBacterium (et de Poison qui l'accompagne) et Helena a codé
MadBacterium. 
Nos MadBacterium sont caractérisées comme suit:
Elles se nourrissent de bactéries et non de nutriments, se déplacent 
donc selon le gradient de bactéries.
Chaque type de bactérie donne une quantité différente d'énergie à la 
MadBacterium (paramétrable dans le fichier app.json)
Cette classe hérite de Bacterium et possède la vitesse comme paramètres
mutables, ainsi que tumble worse et tumble better. (tous ajoutés aux 
statistiques)

Nos PoisonousBacterium sont caractérisées comme suit:
Elles se nourrissent de nutriment (de la même manière que les 
SimpleBacterium) et déposent du poison sur l'assiette de Petri toutes 
les x secondes (configurable sous "poison delay"). La quantité du poison 
est configurable sous "poison" "quantity" dans le app.json, et sa taille
en tant que facteur de la quantité "factor size division".
La bactérie perd de l'énergie lorsqu'elle dépose du poison (elle perd la
quantité déposée multipliée par un facteur, mais n'est pa suicidaire -> 
il faut qu'elle ait au minimum l'énergie correspondant à la quantité de 
poison qu'elle va déposer (+10)). Cette quantité perdue est paramétrable 
en tant que facteur sous "factor loss poison" dans le app.json.
La classe poison hérite de circularbody. Les pointeurs sur ses instances
sont stockées dans un vecteur, attribut de petridish.
La classe poisonousBacterium hérite de bacterium et possède comme 
paramètres mutables la vitesse, ainsi que tumble worse et better, 
ajoutés auxstatistiques.

### **Semaine 9**

Nous avons ajouté l'affichage du temps en format mm:ss sur la simulation
et avons ajouté 2 autres types de swarm. Nous avons réglé quelques 
problèmes mineurs et amélioré la modularisation de notre code.
Nous allons nous attaquer au fichier README tout prochainement.

### **Semaine 10**

Nous avons ajouté un spray désinfectant éliminant toutes les entités 
entrant en contact avec le liquide. Nous avons aussi ajouté un flash UV
faisant muter toutes les bactéries de l'assiette.
Nous avons accompagné le spray et le flash par un effet sonore et
ajouté une musique de fond à la simulation.
Nous avons finalisé le readme, contrôlé que le code compile sur la VM, 
(bien que le son n'est pas rediffusé). 
Nous avons fixé quelques problèmes mineurs. Nous préparons actuellement
les fichiers à rendre sous format zip.
