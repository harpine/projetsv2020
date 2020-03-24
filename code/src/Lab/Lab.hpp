#ifndef LAB_HPP
#define LAB_HPP
#include "CircularBody.hpp"
#include "PetriDish.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "NutrimentGenerator.hpp"

class Lab : public Drawable, public Updatable
{
public:
    //Constructeurs:
    Lab();

    //Méthodes:
    bool contains(const CircularBody& circularbody)  const;
    //renvoie true si circularbody est dans l'assiette de petri du lab
    void drawOn(sf::RenderTarget& targetWindow) const;
    //Dessine Lab
    void update(sf::Time dt);
    //Fait évoluer Lab
    void reset();
    //Vide l'assiette de pétri associée à Lab et réinitialise la température
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
    NutrimentGenerator nutrimentGenerator_;

};

#endif // LAB_HPP
