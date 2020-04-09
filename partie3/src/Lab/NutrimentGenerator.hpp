#ifndef NUTRIMENTGENERATOR_HPP
#define NUTRIMENTGENERATOR_HPP
#include <SFML/Graphics.hpp>
#include "../Interface/Updatable.hpp"
#include "Nutriment.hpp"

class NutrimentGenerator: public Updatable
{
public:
    //Constructeurs
    NutrimentGenerator();

    //Méthodes
    virtual void update(sf::Time dt) override;
    //génère des nutriments régulièrement (selon paramètres)
    Nutriment* choose();
    //renvoie le nutriment à ajouter dans update (A ou B)
    void reset();
    //réinitialise le temps à "Zero"

private:
    sf::Time compteur_;
};

#endif // NUTRIMENTGENERATOR_HPP
