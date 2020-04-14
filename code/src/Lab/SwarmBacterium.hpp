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
    SwarmBacterium(const Vec2d& poscenter, Swarm*& swarm); //unsigned int mId); ??
    virtual ~SwarmBacterium() override;

    //Getters:
    virtual j::Value& getConfig() const override;
    //permet d'accéder aux configurations de Swarmbacterium
    Vec2d getSpeedVector() const;
    //renvoie la vitesse courante (direction * une valeur)

    //Autres méthodes:
    virtual void drawOn(sf::RenderTarget& target) const override;
    //permet de dessiner une bactérie
    virtual Bacterium* copie() override;
    //copie une bactérie
    virtual void move(sf::Time dt) override;
    //permet à une bactérie de se déplacer
    virtual Vec2d f(Vec2d position, Vec2d speed) const override;
    //modélise la force d'attraction des bactéries

private:
    //Attributs
    Swarm* swarm_;
};

#endif // SWARMBACTERIUM_HPP
