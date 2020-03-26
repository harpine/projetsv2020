#include "MutableColor.hpp"
#include "MutableNumber.hpp"
MutableColor::MutableColor(j::Value const& config)
    :rgba_{MutableNumber(config["r"]), MutableNumber(config["g"]),
      MutableNumber(config["b"]), MutableNumber(config["a"])}

{}

void MutableColor::mutate()
{
    for (auto color: rgba_)
    {
        color.mutate();
    }
}

sf::Color MutableColor::get() const
{
    return { static_cast<sf::Uint8>(rgba_[0].get() * 255),
              static_cast<sf::Uint8>(rgba_[1].get() * 255),
              static_cast<sf::Uint8>(rgba_[2].get() * 255),
              static_cast<sf::Uint8>(rgba_[3].get() * 255) };
}
