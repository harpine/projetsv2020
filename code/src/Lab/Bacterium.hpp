#ifndef BACTERIUM_HPP
#define BACTERIUM_HPP

#include <SFML/Graphics.hpp>
#include "CircularBody.hpp"
#include "MutableColor.hpp"
#include "MutableNumber.hpp"
#include "../Utility/Vec2d.hpp"
#include "../Utility/Types.hpp"
#include <string>

class Bacterium : public CircularBody
{
public:

    //Construcuteurs:
    Bacterium();

    //Getters utilitaires :
    Quantity getDivisionEnergy() const;
    sf::seconds getMealDelay() const;
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
    virtual j::Value& getConfig() = 0;
    //Méthode virtuelle pure. Chaque type de bactérie crée son raccourci
    //pour atteindre ses paramètres.


private:
    MutableColor color_;
    Vec2d direction_;
    bool abstinence_;
    Quantity energy_;
    std::map<string, MutableNumber> mutableParameters_;
    sf::Clock clock_;



};

#endif // BACTERIUM_HPP
