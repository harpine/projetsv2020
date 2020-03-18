#ifndef LAB_HPP
#define LAB_HPP
#include "CircularBody.hpp"
#include "PetriDish.hpp"
#include <SFML/Graphics.hpp>

class Lab
{
public:
    //Constructeurs:
    Lab();

    //Méthodes:

    /*
    bool contains(const CircularBody& circularbody);
    */

    //Dessine Lab
    void drawOn(sf::RenderTarget& targetWindow) const;
    //Fait évoluer Lab
    void update(sf::Time dt);
    //Vide l'assiette de pétri associée à Lab
    void reset();


private:
    PetriDish petridish_;

};

#endif // LAB_HPP
