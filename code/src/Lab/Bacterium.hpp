#ifndef BACTERIUM_HPP
#define BACTERIUM_HPP
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

class Bacterium : public Drawable, public Updatable
{
public:
    Bacterium();
};

#endif // BACTERIUM_HPP
