#ifndef BACTERIUM_HPP
#define BACTERIUM_HPP
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

#include <SFML/Graphics.hpp>
#include "CircularBody.hpp"
#include "../Utility/MutableColor.hpp"
#include "../Utility/MutableNumber.hpp"
#include "../Utility/Vec2d.hpp"
#include "../Utility/Types.hpp"
#include <string>

class Bacterium : public CircularBody, public Drawable, public Updatable

{
public:

    //Construcuteurs:
    Bacterium(const Quantity energy, const Vec2d& poscenter,
              const Vec2d& direction, const double radius,
              const MutableColor color);

    //Getters utilitaires :
    Quantity getDivisionEnergy() const;
    sf::Time getMealDelay() const;
    Quantity getDisplacementEnergy() const;
    Quantity getMealQuantity() const;


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
    void mutate();
    //Mute la bactérie.
    Bacterium* clone() const;
    //Division de la bactérie en deux bactéries identiques.
    bool death() const;
    //Indique si la bactérie est morte ou non, c'est-à-dire si son niveau
    //d'energie (energy_) est nul ou inférieur à 0.
    virtual j::Value& getConfig() const = 0;
    //Méthode virtuelle pure. Chaque type de bactérie crée son raccourci
    //pour atteindre ses paramètres.
    void consumeEnergy(const Quantity qt);
    //Décrémente l'energie de la bactérie d'une quantité donnée


private:
    MutableColor color_;
    Vec2d direction_;
    bool abstinence_;
    Quantity energy_;
    std::map<std::string, MutableNumber> mutableParameters_;
    sf::Time clock_;




};

#endif // BACTERIUM_HPP
