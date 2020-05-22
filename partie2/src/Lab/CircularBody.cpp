#include "CircularBody.hpp"

CircularBody::CircularBody(const Vec2d& poscenter, const double radius)
    :poscenter_(poscenter),
     radius_(radius)
{}

CircularBody::CircularBody(const CircularBody& other)
    :poscenter_(other.poscenter_),
     radius_(other.radius_)
{}

Vec2d CircularBody::getPosition() const
{
    return poscenter_;
}

double CircularBody::getRadius() const
{
    return radius_;
}

void CircularBody::setPosition(const Vec2d& poscenter)
{
    poscenter_ = poscenter;
}

void CircularBody::setRadius(const double radius)
{
    radius_ = radius;
}

CircularBody& CircularBody::operator=(const CircularBody& circle)
{
    poscenter_ = circle.poscenter_;
    radius_ = circle.radius_;
    return *this;
}

void CircularBody::move(const Vec2d& v)
{
    poscenter_ += v;
}

bool CircularBody::contains(const CircularBody& other) const
{
    return (other.radius_ <= radius_ and
            distance(poscenter_, other.poscenter_) <= std::abs(radius_ - other.radius_));
}

bool CircularBody::isColliding(const CircularBody& other) const
{
    return (distance(poscenter_, other.poscenter_) <= (radius_ + other.radius_));
}

bool CircularBody::contains(const Vec2d& v) const
{
    return (distance(v, poscenter_) <= radius_);
}

void CircularBody::afficher(std::ostream& out) const
{
    out << "CircularBody: position = (" << poscenter_.x  << "," << poscenter_.y
        << ") radius = " << radius_ << std::endl;
}

// hors classe
bool operator>(const CircularBody& c1, const CircularBody& c2) //2 cercles
{
    return c1.contains(c2);
}

bool operator>(const CircularBody& c, const Vec2d& v) //point - cercle
{
    return c.contains(v);
}

bool operator&(const CircularBody& c1, const CircularBody& c2) // 2 cercles
{
    return c1.isColliding(c2);
}

std::ostream& operator<<(std::ostream& out, const CircularBody& c)
{
    c.afficher(out);
    return out;
}







