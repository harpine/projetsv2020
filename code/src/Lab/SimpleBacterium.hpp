#ifndef SIMPLEBACTERIUM_HPP
#define SIMPLEBACTERIUM_HPP

#include "Bacterium.hpp"
#include "JSON/JSON.hpp"
#include <Utility/DiffEqSolver.hpp>

class SimpleBacterium : public Bacterium, public DiffEqFunction
{
public:
    //constructeur:
    SimpleBacterium(const Vec2d& poscenter);

    //getters & setters:
    virtual j::Value& getConfig() const override;
    Vec2d getSpeedVector() const;
    //renvoie la vitesse courante (direction * une valeur)
    void setSpeedVector(const Vec2d& speed);
    //instaure une nouvelle vitesse (donc direction)

    //méthodes:
    virtual Vec2d f(Vec2d position, Vec2d speed) const override;
    //calcul de la force
    virtual void move(sf::Time dt) override;
    //permet à une bactérie de se déplacer
    virtual Bacterium* clone() const override;

};

#endif // SIMPLEBACTERIUM_HPP

