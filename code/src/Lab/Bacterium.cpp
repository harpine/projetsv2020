#include "Bacterium.hpp"
#include "../Utility/Utility.hpp"
#include "../Application.hpp"
#include "Nutriment.hpp"
#include <iostream> //à enlever

//Constructeurs:
Bacterium::Bacterium(const Quantity energy, const Vec2d& poscenter,
                     const Vec2d& direction, const double radius,
                     const MutableColor color)
    : CircularBody(poscenter, radius),
      color_(color),
      direction_(direction),
      abstinence_(false),
      energy_(energy)
    //mutableParameters_();
{
    //std::map<std::string, MutableNumber> mutableParameters_;
    //Pour Helena: Constructeur par défaut = vide si on l'appelle pas
    //dans le constructeur de bactérie
}


//Getters utilitaires :
Quantity Bacterium::getDivisionEnergy() const
{
    return getConfig()["energy"]["division"].toDouble();
}

sf::Time Bacterium::getMealDelay() const
{
    return sf::seconds(getConfig()["meal"]["delay"].toDouble());
}

Quantity Bacterium::getDisplacementEnergy() const
{
    return getConfig()["energy"]["consumption factor"].toDouble();
}

Quantity Bacterium::getMealQuantity() const
{
    return getConfig()["meal"]["max"].toDouble();
}

Vec2d Bacterium::getDirection() const
{
    return direction_;
}

void Bacterium::setDirection(const Vec2d& speed)
{
    direction_ = speed;
}


//Méthodes:
void Bacterium::drawOn(sf::RenderTarget& target) const
{
    auto const circle = buildCircle(getPosition(), getRadius(), color_.get());
    target.draw(circle);
    //Dessine une bactérie circulaire.

    if (isDebugOn()) //mode debug
    {
        sf::Text const texte = buildText(std::to_string(int(energy_)),
                            Vec2d(getPosition().x - 5, getPosition().y + getRadius() + 10),
                                         getAppFont(), 15, sf::Color::Black);
        target.draw(texte);
    }
}

void Bacterium::update(sf::Time dt)
{
    clock_ += dt;
    move(dt);
    if (getAppEnv().doesCollideWithDish(*this))
    {
        direction_ *= -1;
    }
    eat();
}

void Bacterium::eat()   //VOIR SI POLYMORPHISME FONCTIONNE ET SI DT DOIT ETRE AJOUTE
{
    if (getAppEnv().getNutrimentColliding(*this) != nullptr
            and !abstinence_
            and clock_ >= getMealDelay())
    {
        energy_ += getAppEnv().getNutrimentColliding(*this)->takeQuantity(getMealQuantity());
        clock_ = sf::Time::Zero ;
    }
}

/*
void Bacterium::mutate()
{

} */

/*
Bacterium* Bacterium::clone() const
{
    Bacterium* cloned(new Bacterium);
    *cloned = *this;
    return cloned;
} */

bool Bacterium::death() const
{
   return (energy_ <= 0) ;
}

void Bacterium::consumeEnergy(const Quantity qt)
{
    energy_ -= qt;
}
