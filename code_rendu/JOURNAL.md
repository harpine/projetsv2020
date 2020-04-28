# Journal 

## Groupe 38, Aline Brunner et Helena Binková, coachées par Sébastien 
Gachoud

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
