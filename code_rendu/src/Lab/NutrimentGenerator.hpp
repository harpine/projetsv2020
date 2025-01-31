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
    virtual void update(sf::Time dt) override;
    //génère des nutriments régulièrement (selon paramètres)
    Nutriment* choose();
    //renvoie le nutriment à ajouter dans update (A ou B)
    void reset();
    //réinitialise le temps à "Zero"

private:
    //Attribut:
    sf::Time compteur_;
};

#endif // NUTRIMENTGENERATOR_HPP
