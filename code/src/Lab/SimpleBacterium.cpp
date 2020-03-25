#include "SimpleBacterium.hpp"
#include "../Application.hpp"



j::Value& SimpleBacterium::getConfig() const
{
    return getAppConfig()["simple bacterium"];
}


