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


class Bacterium : public CircularBody, public Drawable, public Updatable

{
public:

    //Construcuteurs:
    Bacterium(const Quantity energy, const Vec2d& poscenter,
              const Vec2d& direction, const double radius,
              const MutableColor color);
    Bacterium(const Bacterium& other);

    virtual ~Bacterium() = default;

    //Getters et setters:

    //renvoie l'energie nécessaire à la division
    Quantity getDivisionEnergy() const;
    //renvoie le "meal" "delay"
    sf::Time getMealDelay() const;
    //renvoie le "consumption factor"
    Quantity getDisplacementEnergy() const;
    //renvoie le "meal" "max"
    Quantity getMealQuantity() const;
    //renvoie la vitesse polymorphique pour une bactérie
    virtual j::Value& getSpeedConfig() const;
    //renvoie la direction de la bactérie
    Vec2d getDirection() const;
    //ajouter un paramètre mutable
    virtual void addProperty(const std::string& key, MutableNumber mutablenumber);
    //Permet de retrouver une valeur mutable associée à une clé donnée
    virtual MutableNumber getProperty(const std::string& key) const;
    //met à jour la direction de la bactérie
    void setDirection(const Vec2d& direction);
    //renvoie la couleur de la bactérie
    MutableColor getColor() const;
    //renvoie l'angle de la direction de la bactérie
    double getAngle() const;
    //met à jour l'angle de direction de la bactérie
    void setAngle(const double angle);
    //Méthode virtuelle pure. Chaque type de bactérie crée son raccourci
    //pour atteindre ses paramètres.
    virtual j::Value& getConfig() const = 0;
    //renovie le score de la position de la bactérie
    double getScore() const;

    //Autres méthodes:

    //mets à jour le score à partir de la position de la bactérie
    void updateScore();
    //Permet de représenter graphiquement un bactérie. Méthode virtuelle.
    virtual void drawOn(sf::RenderTarget& target) const;
    //Calcule l'évolution d'une bactérie après un pas de temps.
    //Méthode virtuelle.
    virtual void update(sf::Time dt);
    //Calcule le dépplacement d'une bactérie après un pas de temps.
    //Méthode virtuelle pure.
    virtual void move(sf::Time dt) = 0;
    //Permet à la bactérie de se nourrir si possible dans l'assiette
    void eat();
    //Division de la bactérie en deux bactéries identiques.
    virtual Bacterium* clone();
    //Indique si la bactérie est morte ou non, c'est-à-dire si son niveau
    //d'energie (energy_) est nul ou inférieur à 0.
    bool isDead() const;
    //Décrémente l'energie de la bactérie d'une quantité donnée
    void consumeEnergy(const Quantity qt);
    //Mute la bactérie.
    void mutate();
    //permet de copier une bactérie
    virtual Bacterium* copie() = 0;
    //modifie la direction que prend la bactérie en fonction
    //du score de N possibilités
    void bestOfN(int n);

private:
    MutableColor color_;
    Vec2d direction_;
    double angle_; //indique l'angle de direction (en degré) d'une bactérie
    bool abstinence_;
    Quantity energy_;
    std::map<std::string, MutableNumber> mutableParameters_;
    sf::Time clock_;
    double score_; //représente le gradient lié à la position de la bactérie
};

#endif // BACTERIUM_HPP
