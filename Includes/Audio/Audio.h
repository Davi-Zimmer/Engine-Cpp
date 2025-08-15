#pragma once

#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>

class Audio {
    public:

    sf::SoundBuffer buffer;
    sf::Sound sound;
    Audio( const char* path );

};