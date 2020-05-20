#ifndef MUTABLECOLOR_HPP
#define MUTABLECOLOR_HPP

#include "MutableNumber.hpp"
#include <array>
#include <SFML/Graphics.hpp>

class MutableColor
{
public:
    //Constructeurs:
    MutableColor(); //initialise tous les paramètres à 0
    MutableColor(j::Value const& config);

    //Getter:

    //renvoie la couleur actuelle
    sf::Color get() const;

    //Autre méthode:

    //fait muter chaque couleur
    void mutate();

private:
    //Attribut:
    std::array<MutableNumber, 4> rgba_;
};
#endif // MUTABLECOLOR_HPP
