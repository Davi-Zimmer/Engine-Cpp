// #include "headers/Audio.h"
#include "../../Includes/Audio/Audio.h"
#include "../../Includes/Utils/Utils.h"



Audio::Audio( const char* path ){
   
    if (!buffer.loadFromFile( path )) return;
    
    sound.setBuffer(buffer);
    sound.setVolume(80.f);
    sound.setLoop(false);
    
}