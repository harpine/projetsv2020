#ifndef PETRIDISH_HPP
#define PETRIDISH_HPP

#include "CircularBody.hpp"
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "Swarm.hpp"
#include "Poison.hpp"
#include "Spray.hpp"
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
    bool addBacterium(Bacterium* bacterium);
    //Ajoute un nutriment à l'ensemble des nutriments de l'assiette
    bool addNutriment(Nutriment* nutriment);
    //ajoute un swarm à à l'ensemble des groupes (swarms) de l'assiette
    void addSwarm (Swarm* swarm);
    //ajoute un poison à l'ensemble de poisons de l'assiette
    void addPoison(Poison* poison);
    //ajoute un spray à l'ensemble de sprays de l'assiette
    void addSpray(Spray* spray);

    //Autres méthodes :

    //retourne la source de nutriment en collision avec body
    Nutriment* getNutrimentColliding(const CircularBody& body) const;
    //retourne la bactérie en collision avec body
    Bacterium* getBacteriumColliding(const CircularBody& body) const;
    //retourne la source de poison en collision avec body
    Poison* getPoisonColliding(const CircularBody& body) const;
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
    //retourne le score pour le gradient de bactérie. La sensibilité du score à une
    //bactérie peut varier polymorphiquement
    double getPositionBacteriaScore(const Vec2d& p) const;
    //Permet de modifier la température de la boîte de pétri
    void increaseGradientExponent();
    void decreaseGradientExponent();
    //Réinitialise la puissance à sa valeur par défaut
    void resetGradientExponent();

    //Pour les statistiques:
    std::unordered_map<std::string, double> fetchData(const std::string & title) const;

private:
    //Attributs:
    std::vector<Bacterium*> bacteria_;
    std::vector<Nutriment*> nutriments_;
    std::vector<Swarm*> swarms_;
    std::vector<Poison*> poisons_;
    std::vector<Spray*> sprays_;
    double temperature_;
    double exponent_;
    double bacteriaExponent_;

    //Méthodes privées:
    std::unordered_map<std::string, double> fetchGeneralData() const;
    std::unordered_map<std::string, double> fetchNutrimentQuantityData() const;
    std::unordered_map<std::string, double> fetchSimpleBacteriaData() const;
    std::unordered_map<std::string, double> fetchPoisonousBacteriaData() const;
    std::unordered_map<std::string, double> fetchMadBacteriaData() const;
    std::unordered_map<std::string, double> fetchTwitchingBacteriaData() const;
    std::unordered_map<std::string, double> fetchBacteriaData() const;
};

#endif // PETRIDISH_HPP
