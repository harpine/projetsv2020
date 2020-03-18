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
    bool contains(const CircularBody& circularbody)  const;
    //renvoie true si circularbody est dans l'assiette de petri du lab
    //Dessine Lab
    void drawOn(sf::RenderTarget& targetWindow) const;
    //Fait évoluer Lab
    void update(sf::Time dt);
    //Vide l'assiette de pétri associée à Lab et réinitialise la température
    void reset();
    void addNutriment(Nutriment* nutriment);
    // ajoute un nutriment à l'assiette de petri
    double getTemperature();
    //retourne la température de la boîte de petri
    void increaseTemperature();
    void decreaseTemperature();
    //Permet de modifier la température de la boîte de petri
    void resetTemperature();
    //Réinitialise la température avec la valeur par défaut

private:
    PetriDish petridish_;

};

#endif // LAB_HPP
