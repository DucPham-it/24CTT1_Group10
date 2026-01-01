#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::instance() {
    static SoundManager inst;
    return inst;
}

void SoundManager::loadSound(const std::string& name, const std::string& path) {
    sf::SoundBuffer buf;
    if (!buf.loadFromFile(path)) {
        std::cout << "[SOUND] Load failed: " << path << "\n";
        return;
    }
    _buffers[name] = buf;
}

void SoundManager::playSound(const std::string& name) {
    if (_buffers.find(name) == _buffers.end()) return;
    _sound.setBuffer(_buffers[name]);
    _sound.play();
}

void SoundManager::playMusic(const std::string& path, bool loop) {
    if (!_music.openFromFile(path)) {
        std::cout << "[MUSIC] Load failed: " << path << "\n";
        return;
    }
    _music.setLoop(loop);
    _music.play();
}

void SoundManager::stopMusic() {
    _music.stop();
}
