#ifndef SIMPLEBACTERIUM_HPP
#define SIMPLEBACTERIUM_HPP

#include "Bacterium.hpp"

class SimpleBacterium : public Bacterium
{
public:
    SimpleBacterium();
    virtual j::Value& getConfig() override;
};

#endif // SIMPLEBACTERIUM_HPP
