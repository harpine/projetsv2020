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

    //Getters:
    //permet d'accéder aux configurations de Swarmbacterium
    virtual j::Value& getConfig() const override;
    //renvoie la vitesse courante (direction * une valeur)
    Vec2d getSpeedVector() const;

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
};

#endif // SWARMBACTERIUM_HPP
