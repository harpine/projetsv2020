#ifndef NUTRIMENTGENERATOR_HPP
#define NUTRIMENTGENERATOR_HPP

#include "Nutriment.hpp"
#include <SFML/Graphics.hpp>
#include <Interface/Updatable.hpp>

class NutrimentGenerator: public Updatable
{
public:
    //Constructeur:
    NutrimentGenerator();

    //Autres méthodes:

    //génère des nutriments régulièrement (selon paramètres)
    virtual void update(sf::Time dt) override;
    //renvoie le nutriment à ajouter dans update (A ou B)
    Nutriment* choose();
    //réinitialise le temps à "Zero"
    void reset();

private:
    //Attribut:
    sf::Time compteur_;
};

#endif // NUTRIMENTGENERATOR_HPP
