# projetsv2020

## Groupe 38, Aline Brunner et Helena Binková, coachées par Sébastien Gachoud


Notre projet contient des options sonores comme complément qui nous on 
paru intéressantes mais qui ne fonctionnent pas sur les machines 
virtuelles de l'EPFL, car ces machines ne redonnent pas le son. Merci 
donc si possible de l'exécuter sur une machine physique.

Notre simulation informatique d'une assiette de pétri avec des colonies 
de bactéries de type différent vise à modéliser leur évolution au cours 
du temps.

Les types de bactéries se différencient de part leur couleur, leur 
action et leur mode de déplacement, qui influencent leur capacité à la 
survie dans un environnement. Notre projet comprend au total 5 types de 
bactéries:
 - les batcéries simples en bleu foncé
 - les bactéries à tentacule en rouge
 - les bactéries à comportement de groupe dont la couleur marque 
 l'appartenance à un certain groupe, en vert, cyan, jaune et bordeau
 - les bactéries à poison en orange
 - les bactéries aggressives en violet

Les bactéries se nourrissent de sources de nutriments générées 
automatiquement dans l'assiette de pétri. Ces sources de nutriments sont 
consommables et permettent aux bactérie d'augmenter leur niveau 
d'énergie. On en distingue deux types, selon la couleur. Les bactéries 
connaissent un comportement différencié selon le nutriment, ce qui leur 
confère des avantages ou désavantages à la survie. La nutrition compense 
les pertes d'énergie dûes au déplacement.

Les bactéries ont des modes de déplacement qui diffèrent et qui peuvent 
donc aussi leur conférer un avantage ou désavantage selon 
l'environnement. 

L'assiette de pétri se trouve dans un laboratoire qui la contrôle. De 
nombreux paramètres comme la température où la sensibilité au gradient 
de bactéries peuvent influencer l'évolution des colonies en modifiant le
comportement des nutriments et bactéries. La totalité de l'évolution est 
limitée à l'assiette qui est en fait un cercle aux parois 
infranchissables pour toutes les entités.


## COMPILATION ET ÉXECUTION:

Ce projet utilise Cmake comme outil de compilation.

**En ligne de commande:**

- Créer un dossier build dans le dossier code //nom dossier à controler ??
- Ouvrir ce dossier dans le terminal et tapper: **cmake ../src**
*-> Cette commande construit les fichiers de compilation dans ce dossier.*
- Une fois la commande exécutée, tapper: **make application**
*-> Cette commande va compiler le code à partir de l'exécutable*
- Pour lancer le programme tapper: **./ application**
*-> Cette commande va lancer le programme avec le app.json par défaut.*
- Pour le lancer avec un autre fichier de configuration, tapper: 
**./ application nomfichierapp.json** 

**Dans QTCreator:**

Ouvrir le fichier src/CmakeLists.txt.
Choisir la cible à exécuter. 
Le programme s'exécute par défaut avec le fichier de configuration 
app.json. Pour modifier cela, dans Config.hpp, ligne 17, remplacer par 
le nom de fichier de configuration voulu.


## CIBLES PRINCIPALES:

 - application: correspond à l'application finale.
 - circularBodyTest: teste la classe CircularBody.
 - gripTest: permet de tester la tentacule des TwitchingBacteria.
 - mutableTest: teste les nombres et couleurs mutables.
 - nutrimentTest: permet de tester la modélisation des nutriments.
 - simpleBactTest: permet le test du fonctionnement des SimpleBacteria.
 - swarmTest: permet de contrôler le comportement des SwarmBacteria.
 - twitchingTest: permet la simulation des bactéries à tentacule.


## FICHIERS DE CONFIGURATION PARTICULIERS:

Ces fichiers font références au projet sans les extensions:

 - avec le fichier de configuration "simpleapp.json", nous pouvons voir 
que les simplesbacteria prennent le dessus rapidement. En effet, il n'y
a qu'une petite quantité de nutriments qui leur posent problème, mais 
assez pour empêcher la croissance des swarmbacteria. La génération est 
assez lente ce qui leur permet de se déplacer de manière ciblée et 
devancer les twitchingbacteria. Leur déplacement ne les épuise pas 
beaucoup, de sorte à leur permettre de proliférer.

 - avec le fichier de configuration "twitchingapp.json", nous pouvons 
voir que les twitchingbacteria prennent le dessus rapidement. En effet,
les deux types de nutriments sont présents à fréquence élevée leur 
permettant de proliférer au détriment des autres bactéries. Celles-ci 
sont affectées par la présence des nutriments B tandis que les 
twitchingbacteria les perçoivent comme très nutritifs.

 - avec le fichier de configuration "swarmapp.json", nous pouvons voir 
que les swarmbacteria prennent le dessus rapidement. En effet, il n'y a 
plus de nutriments nocifs pour elles, et comme les nutriments 
apparaissent lentement, les swarmbacteria sont plus aisées de se 
déplacer rapidement vers les nouvelles sources (en particulier si le 
groupe possède de nombreuses bactéries éparpillées).

 - avec le fichier de configuration "togetherapp.json", nous pouvons 
observer une coexistance des bactéries. La quantité de nutriments bleus
générés est minime, ce qui diminue ses effets néfastes. Les nutriments 
sont générés suffisamment rapidement pour permettre la survie à tous. 
Le swarm 3 notamment est bien adapté parmis les swarms. Les twitching 
sont très résistantes car assez stationnaires : elles peuvent donc
attendre la génération d'un nutriment à leur côté et être les premières
à les atteindre. On remarque l'évolution globale des mutations vers des 
vitesses les plus basses possibles. Cela s'explique par le fait que 
moins d'énergie est consommée dans ces conditions, mais les nutriments 
sont toujours générés à la même vitesse et sont donc accessibles.

Ces fichiers font références au projet avec les extensions:

 - avec le fichier de configuration "poisonousapp.json" nous pouvons 
voir que les poisonousbacteria prennent le dessus rapidement. En effet,
lâcher peu de poison mais régulièrement leur offre un net avantage sur 
les madbacteria, car celles-ci sont d'abord affectées par le poison
avant de pouvoir manger la bactérie. Elles prennent ensuite le dessus 
car toutes les autres bactéries sont affectées par ce poison et elles ne
le sont pas. Elles ne perdent que très peu d'énergie en déposant ce 
poison.

 - avec le fichier de configuration "madapp.json", nous pouvons voir que 
les madbacteria prennent le dessus rapidement. En effet, les bactéries 
sont en compétition pour les nutriments, mais la madbacterium n'a pour 
ennemi que la poisonousbacterium dont le poison est certes puissant, 
mais trop tardif face à la multiplication des madbacteria. Les 
nutriments ne sont pas générés assez rapidement pour créer un équilibre 
entre la consommation par les bactéries et l'attaque des madbacteria. 
On remarque cependant que les madbacterium meurent après que toutes les 
bactéries des alentours sont consommées. Toute la culture de l'assiette 
de pétri disparaît.

 - avec le fichier de configuration "togetherextendedapp.json" nous 
pouvons voir que tous les types de bactéries cohabitent harmonieusement 
(jusqu'à 2 voire 5 minutes de simulation). Nous pouvons observer que 
parmi les swarmbacteria, ce sont les swarmbacteria 3 qui tiennent le 
plus longtemps. En effet, c'est le groupe qui a le facteur d'attirance 
le plus petit, et donc les bactéries se font moins "massacrer" par les 
madbacteria étant donné qu'elles sont moins entassées.


## COMMANDES:

Les commandes disponibles pour une cible particulière sont décrites sur 
la droite de la simulation.
 - La touche S permet d'ajouter une SimpleBacterium à l'assiette.
 - La touche T permet d'ajouter une TwitchingBacterium.
 - Les touches 1, 2, 3, 4 permettent d'ajouter des Swarmbacteria 
 appartenant aux Swarms 1, 2, 3, 4 respectivement. 
 - La touche P permet d'ajouter une PoisonousBacterium.
 - La touche M permet d'ajouter une MadBacterium.
 - La touche H permet d'ajouter une bactérie au hasard parmis toutes les
 bactéries.
 - La touche K permet de sprayer un peu de désinfectant dans une zone de
 l'assiette, ce qui tue (kill) la totalité des objets en contact.
 - la touche F permet d'irradier les bactéries et les faire muter par un
 flash de radiations UV.
 - La touche Space permet de mettre la simulation en pause.
 - La touche D enclenche le mode Debug.
 - La touche R permet de réinitialiser la simulation.
 - La molette de la souris permet de Zoomer.
 - La touche Esc permet de fermer la simulation.
 - La touche C permet d'adapter la simulation aux configurations 
 nouvellement modifiées. 
 - Les flèches permettent de bouger la simulation.
 - La touche A lance ou met la musique d'ambiance en pause.
 - La touche Tab permet de changer de pannel de contrôle.
 - Les touches PageUp et PageDown permettent d'augmenter ou diminuer
 le contenu du pannel de contrôle courant.


## MODIFICATIONS DE CONCEPTION:

Le code suit, à quelques exceptions mineures près, les instructions 
données dans l'énoncé.


## EXTENSIONS:

Nous avons mis en place dans notre assiette de pétri deux mécanismes 
extérieurs pouvant influencer l'évolution des bactéries:
 - un spray de désinfectant peut être appliqué dans l'assiette : il 
 neutralise toutes les entités qui rentrent en contact avec le liquide.
 Il est accompagné d'un son "pschitt".
 - une autre touche peut aussi provoquer un flash de radiations UV qui 
 fait muter les bactéries présentent sur l'assiette. Il est accompagné 
 d'un effet visuel et d'un effet sonore.

Nous avons aussi mis en place un compteur sur l'écran qui affiche le 
temps écoulé dans la simulation, s'adaptant aux pauses ou autres 
manipulations dans app.json (time factor).

Nous avons introduit deux types supplémentaires de bactéries:
 - les PoisonousBacteria : elles se nourrissent de nutriment (de la 
 même manière que les SimpleBacteria) et déposent du poison sur 
 l'assiette de Petri toutes les x secondes (configurable sous "poison 
 delay"). La bactérie perd de l'énergie lorsqu'elle dépose du poison 
 (elle perd la quantité déposée multipliée par un facteur configurable).
 - les MadBacteria : elles se nourrissent de bactéries et non de 
 nutriments, se déplacent donc selon le gradient de bactéries. Chaque 
 type de bactérie donne une quantité différente d'énergie à la 
 MadBacterium (paramétrable dans le fichier app.json).


