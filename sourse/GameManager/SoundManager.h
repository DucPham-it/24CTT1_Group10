#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class SoundManager {
public:
    static SoundManager& instance();

    void loadSound(const std::string& name, const std::string& path);
    void playSound(const std::string& name);

    void playMusic(const std::string& path, bool loop = true);
    void stopMusic();

private:
    SoundManager() = default;
    std::unordered_map<std::string, sf::SoundBuffer> _buffers;
    sf::Sound _sound;
    sf::Music _music;
};
