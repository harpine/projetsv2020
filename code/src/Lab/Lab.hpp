#ifndef LAB_HPP
#define LAB_HPP
#include "CircularBody.hpp"
#include "PetriDish.hpp"
#include <SFML/Graphics.hpp>
#include "Nutriment.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "NutrimentGenerator.hpp"

class Lab : public Drawable, public Updatable
{
public:
    //Constructeurs:
    Lab();

    //Getters:
    Vec2d getCenter() const;
    Swarm* getSwarmWithId(std::string id) const; // (unsigned id) ??

    //Méthodes:
    bool contains(const CircularBody& circularbody)  const;
    //renvoie true si circularbody est dans l'assiette de petri du lab
    bool doesCollideWithDish(const CircularBody& body) const;
    //renvoie true si body est en collision avec l'assiette de petri du lab
    Nutriment* getNutrimentColliding(const CircularBody& body) const;
    //retourne la source de nutriments de l'assiette en collision avec body

    void drawOn(sf::RenderTarget& targetWindow) const;
    //Dessine Lab
    void update(sf::Time dt);
    //Fait évoluer Lab
    void reset();
    //Vide l'assiette de pétri associée à Lab et réinitialise la température

    // ajouts:
    void addNutriment(Nutriment* nutriment);
    // ajoute un nutriment à l'assiette de petri
    void addBacterium(Bacterium* bacterium);
    // ajoute un nutriment à l'assiette de petri
    void addClone(Bacterium* bacterium);
    //ajoute un clone à l'assiette de petri
    void addSwarm(Swarm* swarm);
    //ajoute un swarm à l'assiette de petri

    //pour la température:
    double getTemperature() const;
    //retourne la température de la boîte de petri
    void increaseTemperature();
    void decreaseTemperature();
    //Permet de modifier la température de la boîte de petri
    void resetTemperature();
    //Réinitialise la température avec la valeur par défaut

    //pour le score de la position:
    double getPositionScore(const Vec2d& p) const;
    //retourne le score d'une position donnée
    double getGradientExponent() const;
    void increaseGradientExponent();
    void decreaseGradientExponent();
    //Permet de modifier la température de la boîte de pétri
    void resetGradientExponent();
    //Réinitialise la puissance à sa valeur par défaut

private:
    PetriDish petridish_;
    NutrimentGenerator nutrimentGenerator_;

};

#endif // LAB_HPP
