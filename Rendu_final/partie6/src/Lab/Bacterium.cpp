﻿#include "Bacterium.hpp"
#include "Nutriment.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "MadBacterium.hpp"
#include <Utility/Utility.hpp>
#include <Application.hpp>
#include <cmath>

//Constructeurs:
Bacterium::Bacterium(const Quantity energy, const Vec2d& poscenter,
                     const Vec2d& direction, const double radius,
                     const MutableColor& color)
    : CircularBody(poscenter, radius),
      color_(color),
      direction_(direction.normalised()),
      angle_(direction_.angle()),
      abstinence_(false),
      energy_(energy),
      score_(0)
{}

Bacterium::Bacterium(const Bacterium& other)
    : CircularBody(other),
      color_(other.color_),
      direction_(other.direction_),
      angle_(other.angle_),
      abstinence_(other.abstinence_),
      energy_(other.energy_),
      mutableParameters_(other.mutableParameters_),
      score_(other.score_)
{}

//Getters et setters:
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

Quantity Bacterium::getPoisoneffects() const
{
    return getConfig()["poison effects"].toDouble();
}

j::Value& Bacterium::getSpeedConfig() const
{
    return getConfig()[s::SPEED];
}

Vec2d Bacterium::getDirection() const
{
    return direction_;
}

void Bacterium::addProperty(const std::string& key,MutableNumber mutablenumber)
{
    //find renvoie la paire reliée à la clé
    if (mutableParameters_.find(key) != mutableParameters_.end()) {
        throw std::invalid_argument("ce paramètre existe déjà");
    }

    mutableParameters_[key] = mutablenumber;
}

MutableNumber Bacterium::getProperty(const std::string& key) const
{
    auto pair = mutableParameters_.find(key);
    //pair -> first = key, pair->second = valeur

    if (pair == mutableParameters_.end()) {
        //si key n'existe pas
        throw std::out_of_range("ce paramètre mutable n'existe pas");
    }

    return pair->second;
}

void Bacterium::setDirection(const Vec2d& direction)
{
    direction_ = direction;
}

MutableColor Bacterium::getColor() const
{
    return color_;
}

double Bacterium::getAngle() const
{
    return angle_;
}
void Bacterium::setAngle(const double angle)
{
    angle_ = angle;
}

double Bacterium::getScore() const
{
    return score_;
}

Quantity Bacterium::getEnergy() const
{
    return energy_;
}

Quantity Bacterium::getEnergyForScore() const
{
    double factor(getConfig()["bacteria gradient influence factor"].toDouble());
    return factor * getEnergy();
}

void Bacterium::setEnergy(Quantity energy)
{
    energy_ = energy;
}

sf::Time Bacterium::getMealClock() const
{
    return clock_;
}

void Bacterium::setMealClock(sf::Time newTime)
{
    clock_ = newTime;
}

bool Bacterium::getAbstinence() const
{
    return abstinence_;
}

//Autres méthodes:
void Bacterium::updateScore()
{
    score_ = getAppEnv().getPositionScore(getPosition());
}

void Bacterium::drawOn(sf::RenderTarget& target) const
{
    auto const circle = buildCircle(getPosition(), getRadius(), color_.get());
    target.draw(circle);
    //Dessine une bactérie circulaire.

    if (isDebugOn()) { //mode debug
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
    if (getAppEnv().doesCollideWithDish(*this) and
        (getPosition()-getAppEnv().getCenter()).dot(direction_)/
        ((getPosition()-getAppEnv().getCenter()).length()*direction_.length()) < 1 and
        (getPosition()-getAppEnv().getCenter()).dot(direction_)/
        ((getPosition()-getAppEnv().getCenter()).length()*direction_.length()) > 0)
        //pour améliorer les collisions en évitant le problème des bactéries blockées dans la paroi
        //la bactérie ne change pas de direction si elle est déjà dirigée vers le centre de l'assiette
    {
        direction_ *= -1;
    }
    bool isEating(eatPoison());
    eat(isEating); //si la bactérie rencontre un poison et un nutriment,
    //le poison a priorité
    updateScore();
}

void Bacterium::eat(bool isEating)
{
    if (getAppEnv().getNutrimentColliding(*this) != nullptr
        and !abstinence_
        and clock_ >= getMealDelay() and !isEating) {
        Quantity eaten(getAppEnv().getNutrimentColliding(*this)->eatenBy(*this));
        energy_ += eaten;
        isEating = true;
    }

    if (isEating) {
        clock_ = sf::Time::Zero ;
    }
}

bool Bacterium::eatPoison()
{
    bool isEating(false);
    if (getAppEnv().getPoisonColliding(*this) != nullptr and clock_ >= getMealDelay()) {
        Quantity eaten(getAppEnv().getPoisonColliding(*this)->eatenBy(*this));
        if (eaten > 0) {
            energy_ -= (eaten);
            isEating = true;
        }
    }
    return isEating;
}

Bacterium* Bacterium::clone()
{
    if (energy_ >= getDivisionEnergy()) {
        energy_/=2;
        Bacterium* nouvelle(copie());
        nouvelle->mutate();
        direction_ *= -1;
        nouvelle->updateStats();
        return nouvelle;
    }

    return nullptr;
}

bool Bacterium::isDead() const
{
    return (energy_ <= 0) ;
}

void Bacterium::consumeEnergy(const Quantity qt)
{
    energy_ -= qt;
}

void Bacterium::mutate()
{
    for (auto& pair: mutableParameters_) {
        pair.second.mutate();
    }
    color_.mutate();
}

void Bacterium::bestOfN(int n)
{
    Vec2d direction(direction_);
    Vec2d finalDirection(direction_);
    double score(score_);

    for (int i(0); i < n ; ++i) {
        direction = Vec2d::fromRandomAngle().normalised();

        if (getAppEnv().getPositionScore(getPosition()+direction) > score) {
            score = getAppEnv().getPositionScore(getPosition()+direction);
            finalDirection = direction;
        }
    }
    direction_ = finalDirection;
}

Quantity Bacterium::takeEnergy(const Quantity totake)
{
    double taken(energy_);

    if (totake <= taken) {
        taken = totake;
    }

    energy_ -= taken;
    return taken;
}

Quantity Bacterium::attackedBy(MadBacterium& madbact)
{
    return takeEnergy(madbact.getMealQuantity());
}
