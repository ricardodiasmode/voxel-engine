#include <iostream>
#include <chrono>

float calculateFPS() {
    static auto lastTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float elapsedTime = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastTime).count();

    lastTime = currentTime; // Update lastTime for the next frame

    if (elapsedTime < 0.001f) { // Prevent division by near-zero (e.g., < 1 microsecond)
        elapsedTime = 0.001f;   // Cap at 1000 FPS
    }

    return 1000.f / elapsedTime; // FPS = 1000 ms / frame time in ms
}