#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>


class EventManager {
    EventManager();
    
    using EventCallback = std::function<void()>;
    using EventCallbacksVector = std::unordered_map<int, std::vector<EventCallback>>;
    
    std::unordered_map<int, bool> keyStates;
    
    EventCallbacksVector keyDownCallbacks;
    EventCallbacksVector keyUpCallbacks;
    EventCallbacksVector keyHoldCallbacks;

    EventCallbacksVector mouseDownCallbacks;
    EventCallbacksVector mouseUpCallbacks;

    std::vector<EventCallback> mouseScroolCallbacks;
    std::vector<EventCallback> mouseMoveCallbacks;


    void executeKeyIfExists( int key, EventCallbacksVector callbackVector );
    
    

    public:
    static EventManager* Instance;
    static EventManager* GetInstance();


    void keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods ); 
    void mouseButtonsCallback( GLFWwindow* window, int button, int action, int mods );
    void mouseMoveCallback( double xpos, double ypos );
    void scrollCallback( double xoffset,  double yoffset);
    
    void processHoldKeys();


    void onKeyDown( int button, EventCallback callback );
    void onKeyUp( int key, EventCallback callback );
    void onKeyHold( int key, EventCallback callback );

    void onMouseUp ( int button, EventCallback callback );
    void onMouseDown ( int button, EventCallback callback );

    void onMouseMove( EventCallback callback );
    void onMouseScrool( EventCallback callback );
   
};