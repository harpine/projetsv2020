#ifndef LAB_HPP
#define LAB_HPP

#include "CircularBody.hpp"
#include "PetriDish.hpp"
#include "Nutriment.hpp"
#include "NutrimentGenerator.hpp"
#include <SFML/Graphics.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>

class Lab : public Drawable, public Updatable
{
public:
    //Constructeurs:
    Lab();

    //Getters:
    Vec2d getCenter() const;
    Swarm* getSwarmWithId(std::string id) const;

    //Autres méthodes:

    //renvoie true si circularbody est dans l'assiette de petri du lab
    bool contains(const CircularBody& circularbody)  const;
    //renvoie true si body est en collision avec l'assiette de petri du lab
    bool doesCollideWithDish(const CircularBody& body) const;
    //retourne la source de nutriments de l'assiette en collision avec body
    Nutriment* getNutrimentColliding(const CircularBody& body) const;

    //Dessine Lab
    void drawOn(sf::RenderTarget& targetWindow) const;
    //Fait évoluer Lab
    void update(sf::Time dt);
    //Vide l'assiette de pétri associée à Lab et réinitialise la température
    void reset();
    //Réinitialise la température et la puissance du gradient
    void resetControls();

    //Ajouts/retranchements:


    //ajoute un nutriment à l'assiette de petri
    void addNutriment(Nutriment* nutriment);
    //ajoute un nutriment à l'assiette de petri
    void addBacterium(Bacterium* bacterium);
    //ajoute un swarm à l'assiette de petri
    void addSwarm(Swarm* swarm);

    //Pour la température:

    //retourne la température de la boîte de petri
    double getTemperature() const;
    //Permet de modifier la température de la boîte de petri
    void increaseTemperature();
    void decreaseTemperature();
    //Réinitialise la température avec la valeur par défaut
    void resetTemperature();

    //Pour le score de la position:

    //retourne le score d'une position donnée
    double getPositionScore(const Vec2d& p) const;
    double getGradientExponent() const;
    //Permet de modifier la température de la boîte de pétri
    void increaseGradientExponent();
    void decreaseGradientExponent();
    //Réinitialise la puissance à sa valeur par défaut
    void resetGradientExponent();

    //Pour les statistiques:

    //Renvoie les nouvelles données pour un graphe donné
    std::unordered_map<std::string, double> fetchData(const std::string & title) const;

private:
    PetriDish petridish_;
    NutrimentGenerator nutrimentGenerator_;

};

#endif // LAB_HPP
