[Question Q1.1] Comment coder les trois opérateurs précédemment décrits 
en évitant toute duplication de code dans le fichier CircularBody.cpp ? 

[Réponse R1.1] Pour éviter la duplication, nous avons utilisé les 
fonctions créées auparavant (isColliding et les deux contains).

[Question Q1.2] Quelle surcharge choisissez-vous pour les opérateurs 
qu'il vous a été demandé de coder (interne ou externe) et comment 
justifiez-vous ce choix ? 

[Réponse R1.2] Pour l'opérateur =, étant donné qu'il s'agit d'une 
affectation qui touche donc directement une instance de la classe, 
nous avons décidé de la mettre à l'intérieur (surcharge interne).
Pour les autres (> (2 cercles), > (1 point 1 cercle), & (2 cercles),
comme les deux possibilités étaient envisageables, nous les avons 
sorties de la classe afin d'améliorer l'encapsulation (et de ne pas 
avoir d'erreur à cause des permissions).
 
[Question Q1.3] Quels arguments de méthodes, parmi celles qu'il vous a
été demandé de coder ci-dessus, vous semble t-il judicieux de passer par
référence constante ?

[Réponse R1.3] Nous passons par référence constante tous les arguments 
de méthodes qui ne doivent pas être modifiés et dont la copie est 
inutile (soit tous les arguments sauf ceux de type ostream que nous 
avons passé par référence et ceux de type double dont le passage par
référence constante n'apporte aucun avantage pour la mémoire; nous les
avons quand même passé en valeur cosntante car ils ne doivent pas être
modifiés).

[Question Q1.4] Quelles méthodes parmi celles que l'on vous a demandé de
coder vous semble t-il judicieux de déclarer comme const ?

[Réponse R1.4] Nous déclarons comme constantes toutes les méthodes 
qui ne modifient pas l'instance traitée (getters, cointains, 
isColliding, afficher).



