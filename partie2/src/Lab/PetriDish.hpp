#ifndef PETRIDISH_HPP
#define PETRIDISH_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "CircularBody.hpp"
#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "Utility/Vec2d.hpp"

class PetriDish : public CircularBody
{
public:

    //Constructeurs et destructeurs:
    PetriDish(const Vec2d& poscenter, const double radius);
    //Constructeur :
    PetriDish(const PetriDish& p) = delete;
    //Interdiction de copie d'une assiette de pétri
    ~PetriDish();
    //Destruction de l'assiette de pétri ainsi que des nutriments et bactéries qui l'habitent

    //getters et setters:
    double getTemperature();

    //Surcharges d'operateurs :
    PetriDish& operator=(const PetriDish& p) = delete;
    //Interdiction d'affectation entre assiettes de pétri


    //Methodes :
    bool addBacterium(Bacterium* bacterium);
    //Ajoute une bactérie à l'ensemble de bactéries de l'assiette
    bool addNutriment(Nutriment* nutriment);
    //Ajoute un nutriment à l'ensemble des nutriments de l'assiette
    void update(sf::Time dt);
    //Fait évoluer l'assiette de pétri à chaque intervalle de temps
    void drawOn(sf::RenderTarget& targetWindow) const;
    //Représentation graphique de l'assiette de pétri et de ses contenants
    void reset();
    //Supprime nutriments et bactéries de l'assiette, réinitialise la température
    void increaseTemperature();
    void decreaseTemperature();
    //Permet de modifier la température de la boîte de petri
    void resetTemperature();
    //Réinitialise la température à sa valeur par défaut



private:
    std::vector<Bacterium*> bacteria_;
    std::vector<Nutriment*> nutriments_;
    double temperature_;

};

#endif // PETRIDISH_HPP
