# projetsv2020

Ces fichiers font références au projet sans les nouvelles bactéries
créés par les extensions:

 - avec le fichier de configuration "simpleapp.json" nous pouvons voir 
que les simplesbacterium prennent le dessus rapidement. En effet, il n'y
a qu'une petite quantité de nutriments qui leur posent problèmes, mais 
assez pour empêcher la croissance des swarms. La génération est 
assez lente ce qui leur permet de se déplacer de manière ciblée et 
devancer les twitchingbacterium. Leur déplacement ne les épuise pas 
beaucoup, de sorte à leur permettre de proliférer.

 - avec le fichier de configuration "twitchingapp.json" nous pouvons 
voir que les twitchingbacterium prennent le dessus rapidement. En effet,
les deux types de nutriments sont présent à fréquence élevée leur 
permettant de proliférer au détriment des autres bactéries. Celles-ci 
sont affectée par la présence des nutriments B tandis que les 
twitchingbacterium les perçoivent comme très nutritifs.

 - avec le fichier de configuration "swarmapp.json" nous pouvons voir que 
les swarmbacterium prennent le dessus rapidement. En effet, il n'y a 
plus de nutriment nocif pour elle, et comme les nutriments apparaissent
lentement, les swarm sont plus aisés de se déplacer rapidement vers les
nouvelles sources (en particulier si le groupe possède de nombreuses
bactéries).

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
poison. (Si on met le "factor loss poison" à 1 cet effet est aussi
observable mais cela prend plus de temps.)

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

 - avec le fichier de configuration "together_extended.json" nous pouvons
 voir que tous les types de bactéries cohabitent harmonieusement 
(jusqu'à 2 voire 5 minutes de simulation). Nous pouvons observer que les
swarmbacterium 4 sont celles qui tiennent le plus longtemps. En effet,
c'est le groupe qui a le facteur d'attirance le plus petit, et donc les
bactéries se font moins "massacrer" par les MadBacterium étant donné
qu'elles sont moins entassées.
