#ifndef MUTABLECOLOR_HPP
#define MUTABLECOLOR_HPP
#include "MutableNumber.hpp"
#include <array>
#include <SFML/Graphics.hpp>
class MutableColor
{
public:
    //constructeurs:
    MutableColor(j::Value const& config);

    //getters:
    sf::Color get() const;

    //méthodes:
    void mutate();
    //fait muter chaque couleur
private:
    std::array<MutableNumber, 4> rgba_;
};

#endif // MUTABLECOLOR_HPP
