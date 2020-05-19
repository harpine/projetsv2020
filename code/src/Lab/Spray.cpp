#include "Spray.hpp"
#include <Application.hpp>

Spray::Spray(const Vec2d& poscenter)
    :CircularBody(poscenter, getConfig()["size"].toDouble())
{}

j::Value &Spray::getConfig() const
{
    return getAppConfig()["spray"];
}

