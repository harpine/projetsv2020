#pragma once
#include "Utility/Vec2d.hpp"
#include <iostream>

class CircularBody
{
public:
    //constructeurs:
    CircularBody(const Vec2d& poscenter, const double radius);
    CircularBody(const CircularBody& other);

    //getters/setters:
    Vec2d getPosition() const;
    double getRadius() const;
    void setPosition(const Vec2d& poscenter);
    void setRadius(const double radius);

    //autres méthodes:
    void move(const Vec2d& v);
    //déplace le centre du cercle de la "distance" v
    bool contains(const CircularBody& other) const;
    //retourne true si other est dans le cercle, false autrement
    bool contains(const Vec2d& v) const;
    //retourne true si le point v est dans le cercle, false autrement
    bool isColliding(const CircularBody& other) const;

    //surcharge d'opérateurs:
    CircularBody& operator=(const CircularBody& circle);
    //dans la classe car il travaille sur l'objet

    void afficher(std::ostream& out) const; //pour simplifier la surcharge <<

private:
    //attributs:
    Vec2d poscenter_;
    double radius_;


};

bool operator>(const CircularBody& c1, const CircularBody& c2); // 2 cercles
bool operator>(const CircularBody& c, const Vec2d& v); //point - cercle
bool operator&(const CircularBody& c1, const CircularBody& c2);
std::ostream& operator<<(std::ostream& out, const CircularBody& c);
