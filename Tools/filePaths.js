module.exports = {
    files: [],
    folders: {
        source: {
            folders: {

                Audio: {
                    files: [
                        "Audio.cpp"
                    ]
                },

                Core: {
                    files: [
                        "Engine.cpp",
                        "Main.cpp",
                        "Window.cpp",
                    ]
                },

                Graphics: {
                    files: [
                        "Canvas2D.cpp",
                        "Image.cpp"
                    ]
                },

                Math: {
                    files: [
                        "Matrix.cpp"
                    ]
                },

                Utils: {
                    files: [
                        "utils.cpp",
                        "Interpreter.cpp",
                        "Logger.cpp"
                    ]
                }
            }
        },
    }
}

/*
g++ 
source/Audio/Audio.cpp
source/Core/Engine.cpp
source/Core/Main.cpp
source/Core/Window.cpp
source/Graphics/Canvas2D.cpp
source/Graphics/Image.cpp
source/Math/Matrix.cpp
source/Utils/utils.cpp
source/Utils/Interpreter.cpp
source/Utils/Logger.cpp
-std=c++17
-pthread

*/