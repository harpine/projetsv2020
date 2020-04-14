#ifndef BACTERIUM_HPP
#define BACTERIUM_HPP
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Vec2d.hpp>
#include <Utility/Types.hpp>
#include <string>
#include "CircularBody.hpp"
#include "../Utility/MutableColor.hpp"
#include "../Utility/MutableNumber.hpp"

class Bacterium : public CircularBody, public Drawable, public Updatable

{
public:

    //Construcuteurs:
    Bacterium(const Quantity energy, const Vec2d& poscenter,
              const Vec2d& direction, const double radius,
              const MutableColor color);
    Bacterium(const Bacterium& other);

    virtual ~Bacterium() = default;

    //Getters utilitaires et setters:
    Quantity getDivisionEnergy() const;
    //renvoie l'energie nécessaire à la division
    sf::Time getMealDelay() const;
    //renvoie le "meal" "delay"
    Quantity getDisplacementEnergy() const;
    //renvoie le "consumption factor"
    Quantity getMealQuantity() const;
    //renvoie le "meal" "max"
    virtual j::Value& getSpeedConfig() const;
    //renvoie la vitesse polymorphique pour une bactérie
    Vec2d getDirection() const;
    //renvoie la direction de la bactérie
    virtual void addProperty(const std::string& key, MutableNumber mutablenumber);
    //ajouter un paramètre mutable
    virtual MutableNumber getProperty(const std::string& key) const;
    //Permet de retrouver une valeur mutable associée à une clé donnée
    void setDirection(const Vec2d& direction);
    //met à jour la direction de la bactérie
    MutableColor getColor() const;
    //renvoie la couleur de la bactérie
    double getAngle() const;
    //renvoie l'angle de la direction de la bactérie
    void setAngle(const double angle);
    //met à jour l'angle de direction de la bactérie

    //Méthodes:
    virtual void drawOn(sf::RenderTarget& target) const;
    //Permet de représenter graphiquement un bactérie. Méthode virtuelle.
    virtual void update(sf::Time dt);
    //Calcule l'évolution d'une bactérie après un pas de temps.
    //Méthode virtuelle.
    virtual void move(sf::Time dt) = 0;
    //Calcule le dépplacement d'une bactérie après un pas de temps.
    //Méthode virtuelle pure.
    void eat();
    //Permet à la bactérie de se nourrir si possible dans l'assiette
    virtual Bacterium* clone();
    //Division de la bactérie en deux bactéries identiques.
    bool death() const;
    //Indique si la bactérie est morte ou non, c'est-à-dire si son niveau
    //d'energie (energy_) est nul ou inférieur à 0.
    virtual j::Value& getConfig() const = 0;
    //Méthode virtuelle pure. Chaque type de bactérie crée son raccourci
    //pour atteindre ses paramètres.
    void consumeEnergy(const Quantity qt);
    //Décrémente l'energie de la bactérie d'une quantité donnée
    virtual void mutate(); //est-ce vraiment virtuel??
    //Mute la bactérie.
    virtual Bacterium* copie() = 0;
    //permet de copier une bactérie

private:
    MutableColor color_;
    Vec2d direction_;
    double angle_; //indique l'angle de direction (en degré) d'une bactérie
    bool abstinence_;
    Quantity energy_;
    std::map<std::string, MutableNumber> mutableParameters_;
    sf::Time clock_;



};

#endif // BACTERIUM_HPP
