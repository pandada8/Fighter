//
// Created by pan on 5/17/15.
//

#ifndef FLIGHT_RESOURCE_H
#define FLIGHT_RESOURCE_H

// load resource

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

struct {
    sf::Texture enemy3_down1;
    sf::Texture enemy3_down4;
    sf::Texture ufo1;
    sf::Texture hero_blowup_n1;
    sf::Texture game_pause_nor;
    sf::Texture hero_blowup_n3;
    sf::Texture enemy2_down1;
    sf::Texture enemy2_down4;
    sf::Texture bullet2;
    sf::Texture enemy1;
    sf::Texture hero_blowup_n2;
    sf::Texture enemy3_n1;
    sf::Texture enemy3_down6;
    sf::Texture enemy1_down3;
    sf::Texture enemy3_down2;
    sf::Texture hero_blowup_n4;
    sf::Texture hero1;
    sf::Texture hero2;
    sf::Texture enemy3_down5;
    sf::Texture enemy2_hit;
    sf::Texture enemy3_n2;
    sf::Texture enemy1_down2;
    sf::Texture enemy1_down4;
    sf::Texture enemy2_down3;
    sf::Texture enemy2;
    sf::Texture enemy3_down3;
    sf::Texture enemy1_down1;
    sf::Texture bullet1;
    sf::Texture enemy3_hit;
    sf::Texture enemy2_down2;
    sf::Texture game_pause_pressed;
    sf::Texture bomb;
    sf::Texture ufo2;
    sf::Texture gameover;
    sf::SoundBuffer achievement;
    sf::SoundBuffer big_spaceship_flying;
    sf::SoundBuffer bullet;
    sf::SoundBuffer button;
    sf::SoundBuffer enemy1_down;
    sf::SoundBuffer enemy2_down;
    sf::SoundBuffer enemy3_down;
    sf::SoundBuffer game_music;
    sf::SoundBuffer game_over;
    sf::SoundBuffer get_bomb;
    sf::SoundBuffer get_double_laser;
    sf::SoundBuffer out_porp;
    sf::SoundBuffer use_bomb;
    } resources;

void loadResource(){
    resources.enemy3_down1.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(0, 486, 165, 261));
    resources.enemy3_down4.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(165, 486, 165, 261));
    resources.ufo1.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(267, 398, 58, 88));
    resources.hero_blowup_n1.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(165, 234, 102, 126));
    resources.game_pause_nor.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(267, 251, 60, 45));
    resources.hero_blowup_n3.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(330, 498, 102, 126));
    resources.enemy2_down1.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(534, 655, 69, 95));
    resources.enemy2_down4.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(741, 653, 69, 95));
    resources.bullet2.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(69, 78, 9, 21));
    resources.enemy1.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(534, 612, 57, 43));
    resources.hero_blowup_n2.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(330, 624, 102, 126));
    resources.enemy3_n1.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(335, 750, 169, 258));
    resources.enemy3_down6.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(0, 747, 166, 261));
    resources.enemy1_down3.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(267, 296, 57, 51));
    resources.enemy3_down2.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(0, 225, 165, 261));
    resources.hero_blowup_n4.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(432, 624, 102, 126));
    resources.hero1.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(0, 99, 102, 126));
    resources.hero2.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(165, 360, 102, 126));
    resources.enemy3_down5.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(673, 748, 166, 260));
    resources.enemy2_hit.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(432, 525, 69, 99));
    resources.enemy3_n2.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(504, 750, 169, 258));
    resources.enemy1_down2.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(873, 697, 57, 51));
    resources.enemy1_down4.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(930, 697, 57, 51));
    resources.enemy2_down3.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(672, 653, 69, 95));
    resources.enemy2.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(0, 0, 69, 99));
    resources.enemy3_down3.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(839, 748, 165, 260));
    resources.enemy1_down1.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(267, 347, 57, 51));
    resources.bullet1.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(1004, 987, 9, 21));
    resources.enemy3_hit.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(166, 750, 169, 258));
    resources.enemy2_down2.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(603, 655, 69, 95));
    resources.game_pause_pressed.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(810, 646, 60, 45));
    resources.bomb.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(810, 691, 63, 57));
    resources.ufo2.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/shoot.png", sf::IntRect(102, 118, 60, 107));
    resources.gameover.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/gameover.png");
    resources.achievement.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/achievement.ogg");
    resources.big_spaceship_flying.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/big_spaceship_flying.ogg");
    resources.bullet.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/bullet.ogg");
    resources.button.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/button.ogg");
    resources.enemy1_down.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/enemy1_down.ogg");
    resources.enemy2_down.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/enemy2_down.ogg");
    resources.enemy3_down.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/enemy3_down.ogg");
    resources.game_music.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/game_music.ogg");
    resources.game_over.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/game_over.ogg");
    resources.get_bomb.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/get_bomb.ogg");
    resources.get_double_laser.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/get_double_laser.ogg");
    resources.out_porp.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/out_porp.ogg");
    resources.use_bomb.loadFromFile("/home/pan/ClionProjects/Flight/resources/sound/use_bomb.ogg");
    }


#endif //FLIGHT_RESOURCE_H