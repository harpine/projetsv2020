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
    //retourne la bacterie de l'assiette en collision avec body
    Bacterium* getBacteriumColliding(const CircularBody& body) const;
    //retourne le poison de l'assiette en collision avec le body
    Poison* getPoisonColliding(const CircularBody& body) const;
    //met à jour le temps;
    void addTime(const sf::Time toAdd);

    //dessine Lab
    void drawOn(sf::RenderTarget& targetWindow) const;
    //fait évoluer Lab
    void update(sf::Time dt);
    //vide l'assiette de pétri associée à Lab et réinitialise la température
    void reset();
    //réinitialise la température et la puissance du gradient
    void resetControls();
    //irradie les bactérie de l'assiette et les fait muter par un flash UV
    void flash();

    //Ajouts/retranchements:

    //ajoute un nutriment à l'assiette de petri
    void addNutriment(Nutriment* nutriment);
    //ajoute une bactérie à l'assiette de petri
    void addBacterium(Bacterium* bacterium);
    //ajoute un swarm à l'assiette de petri
    void addSwarm(Swarm* swarm);
    //ajoute un poison à l'assiette de petri
    void addPoison(Poison* poison);
    //ajoute un spray à l'assiette de petri
    void addSpray(Spray* spray);

    //Pour la température:

    //retourne la température de la boîte de petri
    double getTemperature() const;
    //permet de modifier la température de la boîte de petri
    void increaseTemperature();
    void decreaseTemperature();
    //réinitialise la température avec la valeur par défaut
    void resetTemperature();

    //Pour le score de la position:

    //retourne le score d'une position donnée
    double getPositionScore(const Vec2d& p) const;
    //retourne le score de bactéries d'une position donnée
    double getPositionBacteriaScore(const Vec2d& p) const;
    double getGradientExponent() const;
    //permet de modifier la température de la boîte de pétri
    void increaseGradientExponent();
    void decreaseGradientExponent();
    //réinitialise la puissance à sa valeur par défaut
    void resetGradientExponent();

    //Pour les statistiques:

    //renvoie les nouvelles données pour un graphe donné
    std::unordered_map<std::string, double> fetchData(const std::string & title) const;

private:
    //Attributs:
    PetriDish petridish_;
    NutrimentGenerator nutrimentGenerator_;
    sf::Time time_; //temps écoulé dans la simulation

    //Méthodes:
    //inscrit le temps écoulé depuis le début de la simulation
    void drawOnTime(sf::RenderTarget& targetWindow) const;

};

#endif // LAB_HPP
