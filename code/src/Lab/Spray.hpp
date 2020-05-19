#ifndef SPRAY_HPP
#define SPRAY_HPP
#include "CircularBody.hpp"
#include "Interface/Drawable.hpp"
#include <Utility/Vec2d.hpp>


class Spray : public CircularBody, public Drawable
{
public:
    //Constructeurs et destructeurs:
    Spray(const Vec2d& poscenter);
    ~Spray();
    Spray(const Spray& other);

    //Getters et setters:
    j::Value& getConfig() const;

    //Autres méthodes:
    void drawOn(sf::RenderTarget& target) const override;
    bool hasFaded() const;

private :
    sf::Clock clock_;
};

#endif // SPRAY_HPP
