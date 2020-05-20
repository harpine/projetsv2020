# projetsv2020

Notre simulation informatique d'une assiette de pétri avec des colonies 
de bactéries de type différent vise à modéliser leur évolution au cours 
du temps.

Les types de bactéries se différencient de part leur couleur, leur 
action et leur mode de déplacement, qui influencent leur capacités à la 
survie dans un environnement. Notre projet comprend au total 5 types de 
bactéries :
 - les batcéries simples en bleu foncé
 - les bactéries à tentacules en rouge
 - les bactéries à comportement de groupe dont la couleur marque 
 l'appartenance à un certain groupe, en vert, cyan, jaune et bordeau
 - les bactéries à poison en orange
 - les bactéries aggressives en violet

Les bactéries se nourrissent de source de nutriments générés 
automatiquements dans l'assiette de pétri. Ces sources de nutriment sont 
consommables et permettent aux bactérie d'augmenter leur niveau 
d'énergie. On en distingue deux type, selon la couleur. Les bactéries 
connaissent un comportement différencié selon le nutriment, ce qui leur 
confère des avantages ou désavantages à la survie. La nutrition compense 
les pertes d'énergie dûes au déplacement.

Les bactéries ont des modes de déplacement qui diffèrent et qui peuvent 
donc aussi leur conférer un avantage ou désavantage selon 
l'environnement. 

L'assiette de pétri se trouve dans un laboratoire cabale de la 
coordonner. De nombreux paramètres comme la température où la 
sensibilité au gradient de bactéries peuvent influencer l'évolution des 
colonies en modifiant le comportement des nutriments et bactéries. La 
totalité de l'évolutio

 




Ces fichiers font références au projet sans les nouvelles bactéries
créés par les extensions:

##COMPILATION:

**En ligne de commande:**
Créer un dossier build dans le dossier code //nom dossier à controler ??
Ouvrir ce dossier dans le terminal et tapper: **cmake ../src**
*-> Cette commande construit les fichiers de compilation dans ce dossier.*
Une fois la commande exécutée, tapper: **make application**
*-> Cette commande va compiler le code à partir de l'exécutable*
Pour lancer le programme tapper: **./ application**
*-> Cette commande va lancer le programme avec le app.json par défaut.*
Pour le lancer avec un autre fichier de configuration, tapper: 
**./ application nomfichierapp.json** 

**Dans QTCreator:**
Ouvrir 


 - avec le fichier de configuration "simpleapp.json" nous pouvons voir 
que les simplesbacterium prennent le dessus rapidement. En effet, il n'y
a qu'une petite quantité de nutriments qui leur posent problèmes, mais 
assez pour empêcher la croissance des swarms. La génération est 
assez lente ce qui leur permet de se déplacer de manière ciblée et 
devancer les twitchingbacterium. Leur déplacement ne les épuise pas 
beaucoup, de sorte à leur permettre de proliférer.

 - avec le fichier de configuration "twitchingapp.json" nous pouvons 
voir que les twitchingbacterium prennent le dessus rapidement. En effet,
les deux types de nutriments sont présents à fréquence élevée leur 
permettant de proliférer au détriment des autres bactéries. Celles-ci 
sont affectées par la présence des nutriments B tandis que les 
twitchingbacterium les perçoivent comme très nutritifs.

 - avec le fichier de configuration "swarmapp.json" nous pouvons voir que 
les swarmbacterium prennent le dessus rapidement. En effet, il n'y a 
plus de nutriment nocif pour elle, et comme les nutriments apparaissent
lentement, les swarmbacteria sont plus aisées de se déplacer rapidement 
vers les nouvelles sources (en particulier si le groupe possède de 
nombreuses bactéries).

 - avec le fichier de configuration "together.json", nous pouvons 
observer une coexistance des bactéries. La quantité de nutriment bleus
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
voir que les poisonousbacterium prennent le dessus rapidement. En effet,
lâcher peu de poison mais régulièrement leur offre un net avantage sur 
les madbacterium, car celles si sont d'abord affectées par le poison
avant de pouvoir manger la bactérie. Elles prennent ensuite le dessus 
car toutes les autres bactéries sont affectées par ce poison et elles
le sont pas. Elles ne perdent que très peu d'énergie en déposant ce 
poison.

 - avec le fichier de configuration "madapp.json" nous pouvons voir que 
les madbacterium prennent le dessus rapidement. En effet, les bactéries 
sont en compétition pour les nutriments, mais la madbacterium n'a pour 
enemi que la poisonous bacterium dont le poison est certes puissant, 
mais trop tardif face à la multiplication des madbacterium. Les 
nutriments ne sont pas générés assez rapidement pour crééer un équilibre 
entre la consommation par les bactéries et l'attaque des madbacteria. 
On remarque cependant que les madbacterium meurent après que toutes les 
bactéries des alentours sont consommées. Toute la culture de l'assiette 
de pétri périt.

 - avec le fichier de configuration "together_extended.json" nous 
pouvons voir que tous les types de bactéries cohabitent harmonieusement 
(jusqu'à 2 voire 5 minutes de simulation). Nous pouvons observer que les
swarmbacterium 3 sont celles qui tiennent le plus longtemps. En effet,
c'est le groupe qui a le facteur d'attirance le plus petit, et donc les
bactéries se font moins "massacrer" par les MadBacterium étant donné
qu'elles sont moins entassées.
