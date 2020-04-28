#ifndef MUTABLECOLOR_HPP
#define MUTABLECOLOR_HPP

#include "MutableNumber.hpp"
#include <array>
#include <SFML/Graphics.hpp>

class MutableColor
{
public:
    //Constructeur:
    MutableColor(j::Value const& config);

    //Getter:
    sf::Color get() const;
    //renvoie la couleur actuelle

    //Autre méthode:
    void mutate();
    //fait muter chaque couleur

private:
    //Attribut:
    std::array<MutableNumber, 4> rgba_;
};
#endif // MUTABLECOLOR_HPP
