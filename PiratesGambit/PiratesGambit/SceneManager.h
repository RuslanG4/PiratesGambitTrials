#pragma once
#include"Scene.h"

class SceneManager {
private:
    Scene* currentScene = nullptr;
    static SceneManager instance;

public:
    static SceneManager& getInstance() {
        return instance;
    }

    void setScene(Scene* newScene) {
        if (currentScene) {
            delete currentScene;
        }
        currentScene = newScene;
    }

    Scene* getCurrentScene() {
        return currentScene;
    }
};