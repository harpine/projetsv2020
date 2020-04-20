# Nos réponses
### Aline Brunner et Helena Binková, groupe 38


## Partie 1

**Question Q1.1** Comment coder les trois opérateurs précédemment décrits 
en évitant toute duplication de code dans le fichier CircularBody.cpp ? 

*Réponse R1.1* Pour éviter la duplication, nous avons utilisé les 
fonctions créées auparavant (isColliding et les deux contains).

**Question Q1.2** Quelle surcharge choisissez-vous pour les opérateurs 
qu'il vous a été demandé de coder (interne ou externe) et comment 
justifiez-vous ce choix ? 

*Réponse R1.2* Pour l'opérateur =, étant donné qu'il s'agit d'une 
affectation qui touche donc directement une instance de la classe, 
nous avons décidé de la mettre à l'intérieur (surcharge interne).
Pour les autres (> (2 cercles), > (1 point 1 cercle), & (2 cercles),
comme les deux possibilités étaient envisageables, nous les avons 
sorties de la classe afin d'améliorer l'encapsulation (et de ne pas 
avoir d'erreur à cause des permissions).
 
**Question Q1.3** Quels arguments de méthodes, parmi celles qu'il vous a
été demandé de coder ci-dessus, vous semble t-il judicieux de passer par
référence constante ?

*Réponse R1.3* Nous passons par référence constante tous les arguments 
de méthodes qui ne doivent pas être modifiés et dont la copie est 
inutile (soit tous les arguments sauf ceux de type ostream que nous 
avons passé par référence et ceux de type double dont le passage par
référence constante n'apporte aucun avantage pour la mémoire; nous les
avons quand même passé en valeur cosntante car ils ne doivent pas être
modifiés).

**Question Q1.4** Quelles méthodes parmi celles que l'on vous a demandé de
coder vous semble t-il judicieux de déclarer comme const ?

*Réponse R1.4* Nous déclarons comme constantes toutes les méthodes 
qui ne modifient pas l'instance traitée (getters, cointains, 
isColliding, afficher).


## Partie 2

**Question Q2.1** Pour pouvoir représenter graphiquement l'assiette de 
Petri et pour pouvoir permettre d'en délimiter le contour, par exemple
pour empêcher les bactéries d'en sortir, nous souhaitons voir l'assiette
comme étant un corps circulaire (qui aura une position dans 
l'environnement en deux dimensions servant de support à nos simulations 
et bien sûr).

*Réponse R2.1* Pour effectuer ceci, Petridish sera une sous-classe de 
CircularBody et va donc hériter de ses attributs (poscenter_ et radius)
ainsi que des méthodes, ce qui permet de la représenter graphiquement 
comme un cercle, et on peut empêcher les bactéries de sortir.

**Question Q2.2** Quelles méthodes vous semble t-il judicieux de déclarer 
comme const?

*Réponse R2.2* On déclare comme const les méthodes qui ne modifient pas 
l'instance, soit la méthode PetrriDish::drawOn.

**Question Q2.3** On souhaite ne pas permettre la copie d'une PetriDish ni
l'affectation. Quelle(s) solution(s) proposeriez-vous pour satisfaire 
cette contrainte?

*Réponse R2.3* Pour ce faire, on delete explicitement le constructeur 
de copie ainsi que l'opérateur = (entre deux PetriDish).

**Question Q2.4** La question Q2.3 suggère que chaque simulation 
s'intéressera à une assiette unique disposant de son propre ensemble de 
bactéries et de nutriments. Il ne fait par ailleurs pas beaucoup de sens
de faire vivre les bactéries sans les rattacher à une assiette. Une 
PetriDish peut donc être considéré comme responsable de la durée de vie
des bactéries et des nutriments amenés à être créés dans la simulation. 
Quelle incidence cela a t-il sur la destruction d'une assiette de Petri?
La destruction peut-elle se faire en utilisant une méthode existante de 
la classe PetriDish?

*Réponse R2.4* Le destructeur de la classe PetriDish doit donc 
simultanément éliminer les nutriments et les bactéries créées dans 
l'assiette. Dans le corps du destructeur, on peut donc utiliser la 
fonction préexistante reset() qui va delete tous les pointeurs et 
tranasformer les vecteurs nutriments_ et bacteria_ en vecteurs nuls.

**Question Q2.5** Pour le moment, faire évoluer un Lab c'est simplement 
faire évoluer son assiette de Petri unique et le dessiner c'est aussi 
dessiner cette assiette de Petri. Comment proposez-vous de coder le 
corps des méthodes Lab::drawOn et Lab::update ? 

*Réponse R2.5* On code ces deux fonctions par le biais d'un appel des 
foncitons de même nom de la classe PetriDish (PetriDish::drawOn et 
PetriDish::update).

**Question Q2.7** Comme quasiment toutes les entités à modéliser, nos 
sources de nutriments seront aussi des corps circulaires. Comment 
proposez-vous d'utiliser la classe fournie CircularBody (dans le 
répertoire Lab) pour modéliser cet aspect ?

*Réponse R2.7* Nutriment va hériter de la classe CircularBody, étant
donné que Nutriment EST un CircularBody. Pour le niveau d'accès nous 
avons décidé de mettre en "public" pour que l'extérieur puisse aussi
percevoir Nutriment comme un CircularBody.

**Question Q2.8** A quoi cela peut-il bien servir d'utiliser le type 
Quantity plutôt que tout simplement un double ?

*Réponse R2.8* C'est utile au cas où nous décidons de changer le type 
des quantités sans avoir à modifier tout le code. 
(remplacer double par int par exemple)

**Question Q2.9** En examinant le code du test fourni pour cette partie 
(src/Tests/GraphicalTests/NutrimentTest.cc) quelle méthode doit-elle 
être ajoutée à la classe Lab pour permettre l'ajout de nutriments à 
l'assiette de Petri lorsque l'on appuie sur la touche 'N', une fois la 
ligne en question décommentée  ? Quelle méthode existante doit être 
modifiée pour permettre le dessin des sources de nutriments nouvellement
ajoutées? 

*Réponse R2.9* La méthode addNutriment(nutriment*) permettant d'ajouter 
un nutriment à l'assiette de Petri doit être ajoutée à la classe Lab.
Nous avons modifié la fonction drawOn de petridish, (car la boîte de 
petri contient les nutriments (en attribut)) en y ajoutant la méthode
drawOn de Nutriment.

**Question Q2.10** On souhaite que la classe Lab ne donne pas d'accès à sa
PetriDish via un getter. En utilisant Application::getAppEnv, comment 
permettre à Nutriment::update de connaître la température de l'assiette
de Petri ? Répondez à cette question dans le fichier REPONSES et 
programmez ce qui est nécessaire.

*Réponse R2.10* Nous avons une fonction getter dans la classe Lab qui 
accède à la température de sa boîte de petri. Grâce à 
getAppEnv().getTemperature() nous pouvons donc y accéder.

**Question Q2.11** Quelles méthodes de Lab et de PetriDish faut-il 
modifier et comment pour que la croissance des nutriments deviennent
visible lors de l'exécution du test graphique ?

*Réponse R2.11* Uniquement la méthode update de nutriment, car celle de
Lab fait appel à la méthode de petridish qui fait appel à celle-ci.
(on appelle setRadius(quantity_)) pour adapter le rayon à la quantité
La méthode drawOn met à jour le sprite en fonction du rayon donc il n'y
a rien à changer. 

**Question Q2.12** Quelles méthodes devez vous ajouter et dans quelles 
classes pour que appuyer sur 'PgUp' ou 'PgDn' permette respectivement 
d'augmenter ou diminuer la température de l'assiette de 
["petri dish"]["temperature"]["delta"] (un double) ? 

Quelles méthode(s) devez vous également ajouter et à quelle(s) classe(s)
pour que les touches 'R' et 'C' permettent aussi (en plus de ce 
qu'elles font) de réinitialiser l'attribut température à la valeur du 
fichier de configuration (["petri dish"]["temperature"]["default"]) 
tout en évitant toute duplication de code ?

*Réponse R2.11* Dans Application, 'PgUp/Dn' font appel à 
mLab->in/decreaseTemperature(), donc il faut ajouter 
in/decreasTemperature() à la classe Lab, et donc les ajouter dans la
classe petridish aussi. (celle de Lab fait appel à celle de PetriDish).
(car la température est un attribut de PetriDish car le laboratoire
pourrait avoir un frigo et four par exemple...)

Pour R & C, nou avons ajouté la méthode resettemperature() dans lab, qui
fait appelle à resettemperature() de petridish. Nous les avons appelées
lors de l'appel des fonctions reset() et dans le fichier application 
lorsque la touche C est appuyée.


## Partie 3

**Question Q3.1** : les classes fournies dans le répertoire Interface, à 
savoir Drawable et Updatable, fournissent deux méthodes polymorphiques 
drawOn et update. Quelles classes de votre conception actuelle serait-il
bon de faire hériter de ces sous-classes ? Quel plus cela amène t-il à 
la conception ? 

*Réponse R3.1* Toutes les classes qui ont besoin d'avoir un affichage 
graphique et/ou qui évoluent au fil du temps.
(Lab, Petridish, Nutriment, Bactérie)
Une meilleure conception de la hiérarchie ainsi que des fonctions des
classes. De plus, suivant comment on peut généraliser les méthodes et
avoir un meilleur contrôle sur les instances réellement visées.

**Question Q3.2** : Qu'implique cette contrainte au niveau des définitions
de drawOn et update?

*Réponse R3.2* Elles doivent être définies comme virtuelles dans la 
classe Nutriment (et donc en "override" dans NutrimentA et NutrimentB).

**Question Q3.3** : Comment doit-être codée la méthode getConfig dans la 
hiérarchie de classes pour satisfaire cette contrainte ? 

*Réponse R3.3* Elle doit être définie comme virtuelle pure dans 
Nutriment (=0 dans le  prototype), puis redéfinie en override dans les 
sous classes NutrimentA/B.

**Question Q3.4** : Qu'est-ce qui fait que sans modifier les méthodes 
drawOn et update dans les sous-classes, l'affichage graphique peut 
faire usage de textures différentes (les couleurs pour NutrimentA et 
NutrimentB ne sont pas les mêmes) et la croissance dépend de conditions 
différentes ? 

*Réponse R3.4* L'affichage graphique peut faire usage de textures 
différentes sans modifier les méthodes drawOn et update, car c'est la 
méthode GetConfig() qui leur fournit les valeurs nécessaires à la 
paramétrisations.

**Question Q3.5** Quelle modification doit être faite dans Lab et dans 
quelle méthode pour permettre au générateur d'effectivement générer des 
sources de nutriments dans l'assiette de Petri qui lui est associée ?

*Réponse R3.5* Nous devons modifier la méthode update de lab, en y 
ajoutant un appel à la méthode update de NutrimentGenerator (au début).

**Question Q3.6** Quelles méthodes parmi celles suggérées pour un 
MutableNumber devront procéder au plafonnage de la valeur entre la borne
inférieure et la borne supérieure ? Comment éviter les duplications de 
code si ce traitement est amené à se répéter à plusieurs endroits ? 

*Réponse R3.6* Nous avons créé une fonction "controlvalue" qui renvoie
la valeur à inscrire (valeur minimum si la valeur donnée est en dessous
de celle-ci, maximum ci en dessus, et valeur originale si celle-ci est 
comprise à l'intérieur des bornes. Ceci permet d'éviter les duplicatats.
Nous avons donc ajouté cette méthode aux méthodes mutate et set() ainsi 
qu'aux deux constructeurs.

**Question Q3.7** Comment faut-il procéder pour que ces méthodes puissent 
être invoquées sans passer par la création d'une instance de 
MutableNumber ? 

*Réponse R3.7* En déclarant ces méthodes comme static, il n'y aura pas
besoin de créer d'instance pour pouvoir les utiliser.

**Question Q3.8** Au vu de ce qui précède, comment proposez-vous de 
modéliser la classe Bacterium (héritage, attributs, méthodes , ...) ?

*Réponse R3.8* La classe Bacterium peut être modélisée comme sous-classe
de CircularBody, de niveau d'accès publique pour qu'elle soit perçue 
comme tel à l'extérieur (notamment dans Lab). En plus de ses attributs
hérités, elle admet les attributs spécifiques de couleur (MutableColor 
color_), de direction de mouvement (Vec2d direction_), un booléen 
indiquant son état d'abstinence (bool abstinence_), son énergie 
(Qunatity energy_) et un ensemble de paramètre mutables 
(std::map<string, MutableNumber> mutableParameters_). On crée aussi des 
méthodes spécifiques : le constructeur ainsi que drawOn, update, move,
mutate, clone et death.

**Question Q3.9** Quelles méthodes parmi celles suggérées pour une 
Bacterium devront vraisemblablement être virtuelles/virtuelles pures ? 

*Réponse R3.9* Les méthodes qui vont être redéfinies spécifiquement à 
chaque bactérie et qui doivent donc être virtuelles sont 
Bacterium::drawOn ainsi que Bacterium::update. La méthode 
Bacterium::move doit est quant à elle virtuelle pure car elle ne peut 
pas être définie de manière générique pour toutes les bactéries. 

**Question Q3.10** La méthode getConfig est-elle virtuelle pure selon 
vous ?

*Réponse R3.10* La méthode getConfig est virtuelle pure d'après nous 
car elle ne peut être définie de manière générique pour toutes les 
bactéries. En effet, elle doit justement rediriger le choix des 
paramètres vers ceux spécifiques à un type de bactéries précis. On ne 
peut donc pas écrire de corps de fonction général. De plus, nous 
souhaitons forcer la redéfinition de cette méthode dans les sous-classes
ce qui est rendu possible avec une méthode virtuelle pure.

**Question Q3.11** Comment retrouvez-vous la couleur SFML de la bactérie
à partir de son attribut de type MutableColor ? 

*Réponse R3.11* L'attribut color_ de la bactérie est de type 
MutableColor, classe que nous avons prédéfinie auparavant. Or cette 
classe est munie d'une méthode get() qui retourne la couleur associée 
sous un format que SFML reconnait (de type sf::Color). Ainsi, on peut 
utiliser cette méthode. 

**Question Q3.12** Le fait qu'aucune méthode de déplacement concrète 
n'existe encore est-elle un frein à l'écriture de la méthode update ?

*Réponse R3.12* La méthode update peut tout de même être écrite car elle
utilise uniquement ce que fait move, mais n'a pas besoin de comprendre
comment move foncitonne. En fonction de la sous-classe de bactérie, 
move sera implémentée différemment la position étant stockée dans les 
attributs, update peut continuer ses tests sans s'en préoccuper. 

**Question Q3.13** La classe PetriDish ne donne pas d'accès à sa 
collection de nutriments, comment procéder dans ce cas pour coder 
Lab::getNutrimentColliding(CircularBody const& body) ? 

*Réponse R3.12* On peut faire appel à une fonction de même nom de 
la classe PetriDish qui peut alors accéder à l'ensemble des nutrmients
via son attribut nutriments_.

**Question Q3.14** Quelle méthode de la classe PetriDish doit être 
modifiée pour permettre la simulation de l'évolution des bactéries ? 
Comment doit-elle être modifiée ?  

*Réponse R3.14* La méthode qui doit être modifiée est PetriDish::update 
qui doit non seulement faire évoluer les nutriments, mais aussi prendre 
en compte l'évolution des bactéries par l'appel de Bacterium::update sur
les bactéries de l'assiette.

**Question Q3.15** Que devez-vous modifier et dans quelle classe pour 
faire en sorte que les bactéries et sources de nutriments de votre 
simulation meurent/disparaissent si leur énergie/quantité devient 
nulle ? 

*Réponse R3.15* Grâce à la méthode Bacterium::death, on peut identifier 
les bactéries mortes, dont l'énergie est inférieure ou égale à 0. Dans 
la classe PetriDish, il faut donc faire disparaître bactéries et 
nutriments des vectors nutirments_ et bacteria_. La méthode PetriDish::
update doit donc également comprendre la transformation des nutriments 
épuisés et des bactéries mortes et nullptr puis les faire disparaître. 

**Question Q3.16** La classe DiffEqFunction (aussi contenue dans le 
fichier Utility/DiffEqSolver.hpp) permet justement de modéliser une 
force f à évaluer en fonction d'une position et d'une vitesse. Expliquez
dans votre fichier REPONSES comment vous proposez d'utiliser cette 
classe pour doter une bactérie simple d'une méthode qui calcule la force
f régissant son déplacement ? (indication : utilise t-on la composition 
ou l'héritage ?) 

*Réponse R3.16* Nous nous sommes tournées vers l'héritage de sorte à 
pouvoir utiliser les fonction déclarées dans la classe diffEqusolver. De
plus, les fonctions de cette classe sont déclarées virtuelles, donc nous
aurons besoin de les redéfinir pour pouvoir les utiliser.
Pour confirmation, dans la classe DiffEquSolver il nous est indiqué que 
nous devons hériter de cette classe.

**Question Q3.17** Où déclarer et initialiser le temps t ?

*Réponse R3.17* Le temps t peut être déclaré comme attribut de la classe
TwitchingBacterium et initialisé dans le constructeur à une valeur 
uniformément distribuée entre 0 et PI.

**Question Q3.18** Comment mémoriser l'angle de direction et à quel 
endroit du code l'initialiser et le mettre à jour si l'on considère que
toutes les bactéries ont une direction et un angle de direction? 

*Réponse R3.18* Pour mémoriser la direction d'une bactérie, nous le 
déclarons attribut de la super-classe Bacterium. Nous l'initialisons 
donc dans le constructeur de Bacterium. Nous la mettons à jour dans les 
sous-classes en fonction du déplacement spécifique au type de bactérie.
Ainsi cela se fait dans la méthode move grâce à un setter. 

**Question Q3.19** Comment devez-vous modifier PetriDish pour mettre en 
oeuvre cette fonctionnalité ?

*Réponse R3.19* Il faut ajouter la méthode getPositionScore(const 
Vec2d&) dans PetriDish qui sera applée dans Lab dans la fonction de même
nom. Il faut aussi ajouter l'attribut exposant (et l'initialiser à 
"Gradient exponent") dans Petridish.

**Question Q3.20** Quel(s) attributs suggérez-vous d'ajouter à la 
représentation des bactéries (simples ou "tout court") pour permettre 
la mise en oeuvre cet algorithme ? Comment initialiser ces attributs et 
à quels endroits devez-vous les mettre à jour ? 

*Réponse Q3.20* Pour mettre en oeuvre l'algorithme, on ajoute un 
attribut score à Bacterium ainsi qu'un attribut servant de compteur 
contentant le temps écoulé depuis le dernier basculement à 
SimpleBacterium. Leur initialisation se fait dans les constructeurs 
respectifs et ils sont mis à jour après chaque pas de temps, soit dans 
la méthode Bacterium::update (appelée aprèsla méthode move).

**Question Q3.21** Dans quelle classe proposez-vous d'ajouter la méthode 
de mutation ?

*Réponse Q3.21* Dans Bacterium car toutes les bactéries vont muter et 
les sous classes héritent de bactérie. Si elles n'ont pas de paramètres
mutables, cette liste sera donc vide et cela ne posera aucun problème
aux sous classes.

**Question Q3.22** Dans quelle classe proposez-vous d'ajouter ces 
méthodes ?

*Réponse Q3.22* Dans la classe Bacterium car les paramètres mutables
sont un attribut de Bacterium.

**Question Q3.23** Où choisissez-vous de placer la méthode de division 
d'une bactérie ?

*Réponse Q3.23* La procédure de division étant la même pour toutes les
bactéries, nous avons décider d'avoir une méthode clone dans bacterium,
qui fait appelle à une méthode virtuelle pure "copie()", qui fonctionne
de façon polymorphique.


## Partie 4

**Question Q4.1** Quel(s) lien(s) d'héritage proposez-vous de mettre en 
place pour intégrer les TwitchingBacteria à l'architecture existante ?

*Réponse R4.1* TwitchingBacterium sera une classe héritant de Bacterium
car elle est aussi une bactérie et a besoin de méthodes préexistantes 
de Bacterium ainsi que de ses attributs.

**Question Q4.2** En vous inspirant de ce que vous avez fait pour les 
bactéries simples, et en observant le contenu du fichier de 
configuration app.json, comment proposez-vous d'accéder aux paramètres 
caractérisant ce type de bactéries (comme la longueur maximale de son 
tentacule ou sa vitesse d'extension) ? 

*Réponse R4.2* Pour accéder aux paramètres en général, nous avons déjà 
une méthode getConfig à redéfinir car elle est virtuelle pure dans la 
classe Bacterium. De plus, on peut construire certains getters 
utilitaires pratiques pour accéder aux paramètres caractéristiques.

**Question Q4.3** Quelles méthodes déjà présentes dans la hiérarchie de 
classes des bactéries devrez-vous impérativement redéfinir dans 
TwitchingBacterium ?

*Réponse R4.3* Nous devons impérativement redéfinir les méthodes 
virtuelles pures, c'est-à-dire getConfig, move et copie. 

**Question Q4.4** Les facteurs de déperdition d'énergie permettant le 
calcul de la perte d'énergie dans chaque cas sont donnés par les valeurs
associées à ["energy"]["consumption factor"]["move"] et 
["energy"]["consumption factor"]["tentacle"] dans le fichier de 
configuration. Quel «getters» proposez-vous d'ajouter/redéfinir à/dans 
votre classe pour retrouver ces valeurs lorsque nécessaires ? 

*Réponse R4.4* Il faut créer un nouveau getter pour l'énergie consommée
lors du déploiment du tentacule. Nous devons aussi redéfinir le getter 
pour l'énergie consommée lors du mouvement.

**Question Q4.5** Un type énuméré peut être une bonne solution pour 
répertorier les différents états cités plus haut. Comment proposeriez-
vous d'en utiliser un pour mettre en oeuvre l'algorithme de mouvement ?

*Réponse R4.5* On peut créer avec enum un nouveau type contenant tous 
les états que la TwitchignBcterium peut prendre. On ajouterait ensuite
un nouvel attribut à la classe prenant l'état dans lequel se trouve la 
bactérie, ce qui permet de lui faire faire des actions en fonction de 
l'état dans lequel elle se trouve.

**Question Q4.6** Une assiette de Petri contiendra désormais aussi des 
Swarm qu'elle doit faire évoluer. Sachant que nous souhaitons disposer 
d'une fonctionnalité addSwarm ajoutant un Swarm (vide de bactéries) à 
l'assiette et invocable comme suit:

getEnv().addSwarm(new Swarm(id));//id est l'entier identifiant du groupe

Quelle(s) modification(s) faites-vous et à quelle(s) classe(s) pour 
intégrer cela ? 

*Réponse Q4.6* Nous ajoutons un attribut swarms à l'assiette de pétri et
des méthodes addSwarm à Petridish et à Lab.

**Question Q4.7** Une SwarmBacterium doit disposer d'une force régissant
son déplacement, exactement comme les bactéries simples. Quels liens 
mettez-vous en place pour modéliser cette force ? 

*Réponse Q4.7* Étant donné que nous avons utilisé le lien d'héritage
pour Simplebacterium, nous allons utiliser le même lien ici.

**Question Q4.8** Au vu de ce qui précède, quelles méthodes déjà présentes
dans la hiérarchie de classes des bactéries devrez-vous impérativement 
redéfinir dans SwarmBacterium ? 

*Réponse Q4.8* getConfig(), move() et copie() (car ces 3 méthodes sont 
virtuelles pures)

**Question Q4.9** Si vous examinez la méthode onEvent dans l'exemple de 
programme précédent, vous verrez que le placement d'une SwarmBacterium 
nécessite de recourir à l'appel getEnv().getSwarmWithId(id);. 
Que devez-vous ajouter à votre code et où pour mettre en place cette 
fonctionnalité ? 

*Réponse Q4.9* Il faut ajouter la méthode getSwarmWithId(id) dans Lab et
dans PetriDish (celle de Lab appelant celle de PetriDish).

**Question Q4.10** Une SwarmBacterium est donc ajoutée à l'assiette comme 
toutes les autres (elle fait partie de la collection de bactéries de 
l'assiette). Le destructeur de Swarm doit-il faire quelque chose 
selon vous ? 

*Réponse Q4.10* Il doit détruire toutes les bactéries appartenant à son
groupe.

**Question Q4.11** Lorsqu'une SwarmBacterium meurt, elle ne doit plus être
recensée dans son Swarm. Que devez-vous ajoutez à votre code et où pour 
que cette contrainte soit respectée ? 

*Réponse Q4.11* On doit enlever la bactérie de son swarm (méthode
removeSwarmBacterium) lors de la destruction de la SwarmBacterium (il
faut donc redéfinir le constructeur de SwarmBaterium).
