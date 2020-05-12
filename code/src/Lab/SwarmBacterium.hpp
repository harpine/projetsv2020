#ifndef SWARMBACTERIUM_HPP
#define SWARMBACTERIUM_HPP

#include "Bacterium.hpp"
#include "Swarm.hpp"
#include <SFML/Graphics.hpp>
#include <Utility/DiffEqSolver.hpp>

class SwarmBacterium: public Bacterium, public DiffEqFunction
{
public:
    //Constructeur et destructeur:
    SwarmBacterium(const Vec2d& poscenter, Swarm*& swarm);
    virtual ~SwarmBacterium() override;
    SwarmBacterium(const SwarmBacterium& other);
    //fonction à polymorphisme induit permettant de mettre les statistiques
    //à jour après que la mutation soit effectuée
    void updateStats() override;

    //Getters:
    //permet d'accéder aux configurations de Swarmbacterium
    virtual j::Value& getConfig() const override;
    //renvoie la vitesse courante (direction * une valeur)
    Vec2d getSpeedVector() const;
    //renvoie le nombre d'instances existantes
    static int getCompteur();
    //renvoie la somme des vitesses des swarmbacteriums existantes
    static double getTotalSpeed();
    //Renvoie les effets du poison sur les bactéries selon leur type
    virtual Quantity eatablePoison(Poison& poison) override;

    //Autres méthodes:

    //permet de dessiner une bactérie
    virtual void drawOn(sf::RenderTarget& target) const override;
    //copie une bactérie
    virtual Bacterium* copie() override;
    //permet à une bactérie de se déplacer
    virtual void move(sf::Time dt) override;
    //modélise la force d'attraction des bactéries
    virtual Vec2d f(Vec2d position, Vec2d speed) const override;
    //renvoie la quantité de nutriment consommée en fonction du nutriment
    virtual Quantity eatableQuantity(NutrimentA& nutriment) override;
    virtual Quantity eatableQuantity(NutrimentB& nutriment) override;

private:
    //Attributs
    Swarm* swarm_;
    static int compteur_;
    static double totalspeed_;
};

#endif // SWARMBACTERIUM_HPP
