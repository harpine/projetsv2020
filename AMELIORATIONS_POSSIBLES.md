améliorations possibles:

paramètres pour la couleur du contour de la boîte de petri

cangrow() dans classe nutriment:
contrôle dépassement avant la croissance.

bactéries aggressives:
se déplace selon le gradient de bactérie et non de nutriments.
si mange bactérie toxique: perd de l'énergie
-> 1 classe
madBacterium
-> hérite de bacterium

--> drawOn avec la texture ! ---> app.json
--> valeur nutritive de la bactérie = énergie * facteur
---> facteur dans app.json, à muter
--> gradient défini par l'énergie des bactéries
--> muter la vitesse "speed" ---> app.json
--> ignore les nutriments
 

bactéries toxiques:
lâche des "crottes" à pa
compteur de "mangé", ex: tous les 100 une crotte.
-> 2 classes
poison
--> hérite de circularbody, est marron
--> addé à petridish
---> modifier dans bacterium doescollidewith(poison)

poisonousBacterium
--> hérite de bacterium
--> se nourrit avec des nutriments
-->toutes les 10 secondes, elle lâche du poison (ne perd pas d'énergie)
--> getpoisoncolliding dans petridish cd(nutrimentcolliding)
!=nullptr delete ptr mange 20

pour 
--> poison = attribut de petridish
--> attribut compteur time, lâche du poison toutes les 10 secondes
et perd 20 d'énergie 

afficher le temps qqe part

- flash UV qui fait muter toutes les batéries de l'assiette. touche F

Keyboard event F appelle getAppEnv.flash (appel petridish.flash qui 
fait muter toutes les bactéries).

