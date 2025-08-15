
#include "../../Includes/Managers/EventManager.h"

#include <iostream>


EventManager* EventManager::Instance;

EventManager::EventManager(){


    onKeyDown( GLFW_KEY_W, [](){
        std::cout << "press W\n";
    });

    onKeyUp( GLFW_KEY_A, [](){
        std::cout << "release A\n";
    });
    
    onKeyHold( GLFW_KEY_D, [](){
        std::cout << "hold D\n";
    });



    onMouseDown( 0, [](){
        std::cout << "down 0\n";
    });

    onMouseUp( 1, [](){
        std::cout << "up 1\n";
    });
        

    onMouseScrool( [](){
        std::cout << "scrool\n";
    });


    onMouseMove( [](){
        std::cout << "mouse move\n";
    });
    
}

EventManager* EventManager::GetInstance(){

    if( Instance == nullptr ) Instance = new EventManager();

    return Instance;

}



void EventManager::addEvents( GLFWwindow* winGL ){

    glfwSetWindowUserPointer(winGL, this);
    
    glfwSetKeyCallback(winGL, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto* em = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
        em->keyCallback(window, key, scancode, action, mods);
    });
    
    glfwSetMouseButtonCallback(winGL, [](GLFWwindow* window, int button, int action, int mods) {
        auto* em = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
        em->mouseButtonsCallback( window, button, action, mods );
    });
        
    glfwSetCursorPosCallback(winGL, [](GLFWwindow* window, double xpos, double ypos) {
        auto* em = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
        em->mouseMoveCallback(xpos, ypos);  // você implementa dentro do EventManager
    });

    glfwSetScrollCallback(winGL, [](GLFWwindow* window, double xoffset, double yoffset) {
        auto* em = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
        em->scrollCallback(xoffset, yoffset);
    });
    
}


void EventManager::executeKeyIfExists( int key, EventCallbacksVector callbackVector ){
    auto it = callbackVector.find( key );

    if (it != callbackVector.end()) {

        for (auto& func : it->second) {

            func();

        }

    }

}

void EventManager::processHoldKeys(){
    for (auto& [key, pressed] : keyStates) {
        if (pressed) {
            executeKeyIfExists(key, keyHoldCallbacks );
        }
    }
}



void EventManager::keyCallback( GLFWwindow* window, int key, int scancode, int action, int mods ){
    
    if (key == GLFW_KEY_UNKNOWN) return;

    if( action == GLFW_PRESS ) {
        keyStates[key] = true;
        executeKeyIfExists( key, keyDownCallbacks );
    }

    if( action == GLFW_RELEASE ) {
        keyStates[key] = false;
        executeKeyIfExists( key, keyUpCallbacks );
    }

}

void EventManager::onKeyDown( int key, EventCallback callback ){
    keyDownCallbacks[key].push_back(callback);
}

void EventManager::onKeyUp( int key, EventCallback callback ){
    keyUpCallbacks[key].push_back(callback);
}

void EventManager::onKeyHold( int key, EventCallback callback ){
    keyHoldCallbacks[key].push_back(callback);
}



void EventManager::mouseButtonsCallback( GLFWwindow* window, int button, int action, int mods  ) {
    
    if (action == GLFW_PRESS) executeKeyIfExists( button, mouseDownCallbacks );

    if (action == GLFW_RELEASE) executeKeyIfExists( button, mouseUpCallbacks );

}

void EventManager::onMouseDown( int button, EventCallback callback ){
    mouseDownCallbacks[button].push_back(callback);
}

void EventManager::onMouseUp( int button, EventCallback callback ){
    mouseUpCallbacks[button].push_back(callback);
}




void EventManager::scrollCallback( double xoffset,  double yoffset){
    for( EventCallback func : mouseScroolCallbacks ){
        func();
    }
}

void EventManager::mouseMoveCallback( double xpos, double ypos ){
    for( EventCallback func : mouseMoveCallbacks ){
        func();
    }
}


void EventManager::onMouseMove( EventCallback callback ){
    mouseMoveCallbacks.push_back( callback );
}

void EventManager::onMouseScrool( EventCallback callback ){
    mouseScroolCallbacks.push_back( callback );

}

