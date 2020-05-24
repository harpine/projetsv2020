#ifndef BACTERIUM_HPP
#define BACTERIUM_HPP

#include "CircularBody.hpp"
#include "../Utility/MutableColor.hpp"
#include "../Utility/MutableNumber.hpp"
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Types.hpp>
#include <string>

class Nutriment;
class NutrimentA;
class NutrimentB;
class Poison;
class MadBacterium;

class Bacterium : public CircularBody, public Drawable, public Updatable

{
public:

    //Construcuteurs:
    Bacterium(const Quantity energy, const Vec2d& poscenter,
              const Vec2d& direction, const double radius,
              const MutableColor& color);
    Bacterium(const Bacterium& other);

    virtual ~Bacterium() = default;

    //fonction à polymorphisme induit permettant de mettre les statistiques
    //à jour après que la mutation soit effectuée
    virtual void updateStats() = 0;

    //Getters et setters:

    //renvoie l'énergie nécessaire à la division
    Quantity getDivisionEnergy() const;
    //renvoie le "meal" "delay"
    sf::Time getMealDelay() const;
    //renvoie le "consumption factor"
    Quantity getDisplacementEnergy() const;
    //renvoie le "meal" "max"
    Quantity getMealQuantity() const;
    //renvoie le "poison effects" (qui est un facteur)
    double getPoisoneffects() const;
    //renvoie la vitesse polymorphique pour une bactérie
    virtual j::Value& getSpeedConfig() const;
    //renvoie la direction de la bactérie
    Vec2d getDirection() const;
    //ajoute un paramètre mutable
    virtual void addProperty(const std::string& key, MutableNumber mutablenumber);
    //permet de retrouver une valeur mutable associée à une clé donnée
    virtual MutableNumber getProperty(const std::string& key) const;
    //met à jour la direction de la bactérie
    void setDirection(const Vec2d& direction);
    //renvoie la couleur de la bactérie
    MutableColor getColor() const;
    //renvoie l'angle de la direction de la bactérie
    double getAngle() const;
    //met à jour l'angle de direction de la bactérie
    void setAngle(const double angle);
    //méthode virtuelle pure. Chaque type de bactérie crée son raccourci
    //pour atteindre ses paramètres.
    virtual j::Value& getConfig() const = 0;
    //renvoie le score de la position de la bactérie
    double getScore() const;
    //renvoie l'énergie d'une bactérie
    Quantity getEnergy() const;
    //renvoie l'énergie d'une bactérie selon son influence sur le gradient de bactérie.
    //méthode qui s'adapte à la bactérie en question en fonction de app.json
    Quantity getEnergyForScore() const;
    //met à jour l'énergie
    void setEnergy(Quantity energy);
    //renvoie le temps écoulé depuis le dernier repas
    sf::Time getMealClock() const;
    //met à jour le temps écoulé depuis le dernier repas
    void setMealClock(sf::Time newTime);
    //renvoie l'état d'abstinence
    bool getAbstinence() const;

    //Autres méthodes:

    //met à jour le score à partir de la position de la bactérie
    void updateScore();
    //permet de représenter graphiquement un bactérie
    virtual void drawOn(sf::RenderTarget& target) const;
    //calcule l'évolution d'une bactérie après un pas de temps
    virtual void update(sf::Time dt);
    //calcule le déplacement d'une bactérie après un pas de temps
    virtual void move(sf::Time dt) = 0;
    //permet à la bactérie de se nourrir si possible dans l'assiette
    //le bool permet de prendre le poison en compte devant le nutriment en cas de conflit
    virtual void eat(bool isEating);
    //permet à la bactérie de manger du poison
    bool eatPoison();
    //division de la bactérie en deux bactéries identiques.
    virtual Bacterium* clone();
    //indique si la bactérie est morte ou non, c'est-à-dire si son niveau
    //d'energie (energy_) est nul ou inférieur à 0.
    bool isDead() const;
    //décrémente l'energie de la bactérie d'une quantité donnée
    void consumeEnergy(const Quantity qt);
    //mute la bactérie.
    void mutate();
    //permet de copier une bactérie
    virtual Bacterium* copie() = 0;
    //modifie la direction que prend la bactérie en fonction
    //du score de N possibilités
    virtual void bestOfN(int n);
    //permet de mimer un polymorphisme sur les bacteries dans les Nutriment.
    //renvoie la quantité prélevée au nutriment selon le type de bactérie.
    virtual Quantity eatableQuantity(NutrimentA& nutriment) = 0;
    virtual Quantity eatableQuantity(NutrimentB& nutriment) = 0;
    //permet de diminuer l'énergie de la bactérie et renvoie la quantité
    //effectivement disponible
    Quantity takeEnergy(const Quantity totake);
    //permet un comportement différencié d'attaque des MadBActeria vis-à-vis
    //du type de bactérie attaqué
    virtual Quantity attackedBy(MadBacterium& madbact);
    //renvoie les effets du poison sur les bactéries selon leur type
    virtual Quantity eatablePoison(Poison& poison) = 0;

private:
    MutableColor color_;
    Vec2d direction_;
    double angle_; //indique l'angle de direction (en degré) d'une bactérie
    bool abstinence_;
    Quantity energy_;
    std::map<std::string, MutableNumber> mutableParameters_;
    sf::Time clock_;
    double score_; //représente le gradient de nutriments lié à la position de la bactérie
};

#endif // BACTERIUM_HPP
