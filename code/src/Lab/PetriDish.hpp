#ifndef PETRIDISH_HPP
#define PETRIDISH_HPP

#include "CircularBody.hpp"
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "Swarm.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <Utility/Vec2d.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>

class PetriDish : public CircularBody, public Drawable, public Updatable
{
public:
    //Constructeurs et destructeurs:

    //Constructeur
    PetriDish(const Vec2d& poscenter, const double radius);
    //Interdiction de copie d'une assiette de pétri
    PetriDish(const PetriDish& p) = delete;
    //Destruction de l'assiette de pétri ainsi que des nutriments et bactéries qui l'habitent
    ~PetriDish();

    //Getters et setters:
    double getTemperature() const;
    double getGradientExponent() const;
    Swarm* getSwarmWithId(const std::string& id) const;

    //Surcharges d'operateurs:

    //Interdiction d'affectation entre assiettes de pétri
    PetriDish& operator=(const PetriDish& p) = delete;

    //Ajouts:

    //Ajoute une bactérie à l'ensemble de bactéries de l'assiette
    bool addBacterium(Bacterium *bacterium);
    //Ajoute un nutriment à l'ensemble des nutriments de l'assiette
    bool addNutriment(Nutriment* nutriment);
    //ajoute un swarm à à l'ensemble des groupes (swarms) de l'assiette
    void addSwarm (Swarm* swarm);

    //Autres méthodes :

    //retourne la source de nutriment en collision avec body
    Nutriment* getNutrimentColliding(const CircularBody& body) const;
    //Fait évoluer l'assiette de pétri à chaque intervalle de temps
    void update(sf::Time dt);
    //Représentation graphique de l'assiette de pétri et de ses contenants
    void drawOn(sf::RenderTarget& targetWindow) const;
    //Supprime nutriments et bactéries de l'assiette, réinitialise la température
    void reset();

    //Pour la température:

    //Permet de modifier la température de la boîte de petri
    void increaseTemperature();
    void decreaseTemperature();
    //Réinitialise la température à sa valeur par défaut
    void resetTemperature();

    //Pour le score d'une position:

    //retourne le score associé à une position donnée
    double getPositionScore(const Vec2d& p) const;
    //Permet de modifier la température de la boîte de pétri
    void increaseGradientExponent();
    void decreaseGradientExponent();
    //Réinitialise la puissance à sa valeur par défaut
    void resetGradientExponent();

    //Pour les statistiques:
    std::unordered_map<std::string, double> fetchData(const std::string & title) const;

private:
    std::vector<Bacterium*> bacteria_;
    std::vector<Nutriment*> nutriments_;
    std::vector<Swarm*> swarms_;
    double temperature_;
    double exponent_;

};

#endif // PETRIDISH_HPP
