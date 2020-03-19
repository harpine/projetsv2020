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


[Question Q2.1] Pour pouvoir représenter graphiquement l'assiette de 
Petri et pour pouvoir permettre d'en délimiter le contour, par exemple
pour empêcher les bactéries d'en sortir, nous souhaitons voir l'assiette
comme étant un corps circulaire (qui aura une position dans 
l'environnement en deux dimensions servant de support à nos simulations 
et bien sûr).

[Réponse R2.1] Pour effectuer ceci, Petridish sera une sous-classe de 
CircularBody et va donc hériter de ses attributs (poscenter_ et radius_)
ainsi que des méthodes, ce qui permet de la représenter graphiquement 
comme un cercle, et on peut empêcher les bactéries de sortir.

[Question Q2.2] Quelles méthodes vous semble t-il judicieux de déclarer 
comme const?

[Réponse R2.2] On déclare comme const les méthodes qui ne modifient pas 
l'instance, soit la méthode PetrriDish::drawOn.

[Question Q2.3] On souhaite ne pas permettre la copie d'une PetriDish ni
l'affectation. Quelle(s) solution(s) proposeriez-vous pour satisfaire 
cette contrainte?

[Réponse R2.3] Pour ce faire, on delete explicitement le constructeur 
de copie ainsi que l'opérateur = (entre deux PetriDish).

[Question Q2.4] La question Q2.3 suggère que chaque simulation 
s'intéressera à une assiette unique disposant de son propre ensemble de 
bactéries et de nutriments. Il ne fait par ailleurs pas beaucoup de sens
de faire vivre les bactéries sans les rattacher à une assiette. Une 
PetriDish peut donc être considéré comme responsable de la durée de vie
des bactéries et des nutriments amenés à être créés dans la simulation. 
Quelle incidence cela a t-il sur la destruction d'une assiette de Petri?
La destruction peut-elle se faire en utilisant une méthode existante de 
la classe PetriDish?

[Réponse R2.4] Le destructeur de la classe PetriDish doit donc 
simultanément éliminer les nutriments et les bactéries créées dans 
l'assiette. Dans le corps du destructeur, on peut donc utiliser la 
fonction préexistante reset() qui va delete tous les pointeurs et 
tranasformer les vecteurs nutriments_ et bacteria_ en vecteurs nuls.

[Question Q2.5] Pour le moment, faire évoluer un Lab c'est simplement 
faire évoluer son assiette de Petri unique et le dessiner c'est aussi 
dessiner cette assiette de Petri. Comment proposez-vous de coder le 
corps des méthodes Lab::drawOn et Lab::update ? 

[Réponse R2.5] On code ces deux fonctions par le biais d'un appel des 
foncitons de même nom de la classe PetriDish (PetriDish::drawOn et 
PetriDish::update).

[Question Q2.7] Comme quasiment toutes les entités à modéliser, nos 
sources de nutriments seront aussi des corps circulaires. Comment 
proposez-vous d'utiliser la classe fournie CircularBody (dans le 
répertoire Lab) pour modéliser cet aspect ?

[Réponse R2.7] Nutriment va hériter de la classe CircularBody, étant
que Nutriment EST un CircularBody. Pour le niveau d'accès nous avons
décidé de mettre en "protected" au cas où il y a des sous classes à 
nutriment qui pourraient avoir besoin de cette information.

[Question Q2.8] A quoi cela peut-il bien servir d'utiliser le type 
Quantity plutôt que tout simplement un double ?

[Réponse R2.8] C'est utile au cas où nous décidons de changer le type 
des quantités sans avoir à modifier tout le code. 
(remplacer double par int par exemple)

[Question Q2.9] En examinant le code du test fourni pour cette partie 
(src/Tests/GraphicalTests/NutrimentTest.cc) quelle méthode doit-elle 
être ajoutée à la classe Lab pour permettre l'ajout de nutriments à 
l'assiette de Petri lorsque l'on appuie sur la touche 'N', une fois la 
ligne en question décommentée  ? Quelle méthode existante doit être 
modifiée pour permettre le dessin des sources de nutriments nouvellement
ajoutées? 

[Réponse R2.9] 
la méthode addNutriment(nutriment*) permettant d'ajouter un nutriment à 
l'assiette de Petri doit être ajoutée à la classe Lab.
Nous avons modifié la fonction drawOn de petridish, (car la boîte de 
petri contient les nutriments (en attribut)) en y ajoutant la méthode
drawOn de Nutriment.

[Question Q2.10] On souhaite que la classe Lab ne donne pas d'accès à sa
PetriDish via un getter. En utilisant Application::getAppEnv, comment 
permettre à Nutriment::update de connaître la température de l'assiette
de Petri ? Répondez à cette question dans le fichier REPONSES et 
programmez ce qui est nécessaire.

[Réponse R2.10] 
Nous avons une fonction getter dans la classe Lab qui accède à la 
température de sa boîte de petri. Grâce à getAppEnv().getTemperature() 
nous pouvons donc y accéder.

[Question Q2.11] Quelles méthodes de Lab et de PetriDish faut-il 
modifier et comment pour que la croissance des nutriments deviennent
visible lors de l'exécution du test graphique ?

[Réponse R2.11] Uniquement la méthode update de nutriment, car celle de
Lab fait appel à la méthode de petridish qui fait appel à celle-ci.
(on appelle setRadius(quantity_)) pour adapter le rayon à la quantité
La méthode drawOn met à jour le sprite en fonction du rayon donc il n'y
a rien à changer. 

[Question Q2.12] Quelles méthodes devez vous ajouter et dans quelles 
classes pour que appuyer sur 'PgUp' ou 'PgDn' permette respectivement 
d'augmenter ou diminuer la température de l'assiette de 
["petri dish"]["temperature"]["delta"] (un double) ? 

Quelles méthode(s) devez vous également ajouter et à quelle(s) classe(s)
pour que les touches 'R' et 'C' permettent aussi (en plus de ce 
qu'elles font) de réinitialiser l'attribut température à la valeur du 
fichier de configuration (["petri dish"]["temperature"]["default"]) 
tout en évitant toute duplication de code ?

[Réponse R2.11] Dans Application, 'PgUp/Dn' font appel à 
mLab->in/decreaseTemperature(), donc il faut ajouter 
in/decreasTemperature() à la classe Lab, et donc les ajouter dans la
classe petridish aussi. (celle de Lab fait appel à celle de PetriDish).
(car la température est un attribut de PetriDish car le laboratoire
pourrait avoir un frigo et four par exemple...)

Pour R & C, nou avons ajouté la méthode resettemperature() dans lab, qui
fait appelle à resettemperature() de petridish. Nous les avons appelées
lors de l'appel des fonctions reset() et dans le fichier application 
lorsque la touche C est appuyée.





