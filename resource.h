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
    sf::Texture p_bullet2;
    sf::Texture p_enemy2_down3;
    sf::Texture p_enemy1_down1;
    sf::Texture p_enemy3_hit;
    sf::Texture p_hero_blowup_n4;
    sf::Texture p_enemy1_down2;
    sf::Texture p_bomb;
    sf::Texture p_enemy3_n2;
    sf::Texture p_bullet1;
    sf::Texture p_game_pause_nor;
    sf::Texture p_ufo1;
    sf::Texture p_enemy2_down4;
    sf::Texture p_hero2;
    sf::Texture p_enemy2_down2;
    sf::Texture p_game_pause_pressed;
    sf::Texture p_enemy3_down2;
    sf::Texture p_enemy1;
    sf::Texture p_enemy3_down3;
    sf::Texture p_enemy3_n1;
    sf::Texture p_enemy1_down3;
    sf::Texture p_enemy3_down4;
    sf::Texture p_enemy2_down1;
    sf::Texture p_enemy1_down4;
    sf::Texture p_enemy2_hit;
    sf::Texture p_enemy3_down5;
    sf::Texture p_hero_blowup_n3;
    sf::Texture p_hero_blowup_n2;
    sf::Texture p_hero_blowup_n1;
    sf::Texture p_hero1;
    sf::Texture p_enemy3_down6;
    sf::Texture p_ufo2;
    sf::Texture p_enemy3_down1;
    sf::Texture p_enemy2;
    sf::Texture p_game_over;
    sf::SoundBuffer s_achievement;
    sf::SoundBuffer s_big_spaceship_flying;
    sf::SoundBuffer s_bullet;
    sf::SoundBuffer s_button;
    sf::SoundBuffer s_enemy1_down;
    sf::SoundBuffer s_enemy2_down;
    sf::SoundBuffer s_enemy3_down;
    sf::SoundBuffer s_game_music;
    sf::SoundBuffer s_game_over;
    sf::SoundBuffer s_get_bomb;
    sf::SoundBuffer s_get_double_laser;
    sf::SoundBuffer s_out_porp;
    sf::SoundBuffer s_use_bomb;
    } resources;

void loadResource(){
    resources.p_bullet2.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(69, 78, 9, 21));
    resources.p_enemy2_down3.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(672, 653, 69, 95));
    resources.p_enemy1_down1.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(267, 347, 57, 51));
    resources.p_enemy3_hit.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(166, 750, 169, 258));
    resources.p_hero_blowup_n4.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(432, 624, 102, 126));
    resources.p_enemy1_down2.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(873, 697, 57, 51));
    resources.p_bomb.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(810, 691, 63, 57));
    resources.p_enemy3_n2.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(504, 750, 169, 258));
    resources.p_bullet1.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(1004, 987, 9, 21));
    resources.p_game_pause_nor.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(267, 251, 60, 45));
    resources.p_ufo1.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(267, 398, 58, 88));
    resources.p_enemy2_down4.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(741, 653, 69, 95));
    resources.p_hero2.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(165, 360, 102, 126));
    resources.p_enemy2_down2.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(603, 655, 69, 95));
    resources.p_game_pause_pressed.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(810, 646, 60, 45));
    resources.p_enemy3_down2.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(0, 225, 165, 261));
    resources.p_enemy1.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(534, 612, 57, 43));
    resources.p_enemy3_down3.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(839, 748, 165, 260));
    resources.p_enemy3_n1.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(335, 750, 169, 258));
    resources.p_enemy1_down3.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(267, 296, 57, 51));
    resources.p_enemy3_down4.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(165, 486, 165, 261));
    resources.p_enemy2_down1.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(534, 655, 69, 95));
    resources.p_enemy1_down4.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(930, 697, 57, 51));
    resources.p_enemy2_hit.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(432, 525, 69, 99));
    resources.p_enemy3_down5.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(673, 748, 166, 260));
    resources.p_hero_blowup_n3.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(330, 498, 102, 126));
    resources.p_hero_blowup_n2.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(330, 624, 102, 126));
    resources.p_hero_blowup_n1.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(165, 234, 102, 126));
    resources.p_hero1.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(0, 99, 102, 126));
    resources.p_enemy3_down6.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(0, 747, 166, 261));
    resources.p_ufo2.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(102, 118, 60, 107));
    resources.p_enemy3_down1.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(0, 486, 165, 261));
    resources.p_enemy2.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/shoot.png", sf::IntRect(0, 0, 69, 99));
    resources.p_game_over.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/gameover.png");
    resources.s_achievement.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/achievement.ogg");
    resources.s_big_spaceship_flying.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/big_spaceship_flying.ogg");
    resources.s_bullet.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/bullet.ogg");
    resources.s_button.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/button.ogg");
    resources.s_enemy1_down.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/enemy1_down.ogg");
    resources.s_enemy2_down.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/enemy2_down.ogg");
    resources.s_enemy3_down.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/enemy3_down.ogg");
    resources.s_game_music.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/game_music.ogg");
    resources.s_game_over.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/game_over.ogg");
    resources.s_get_bomb.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/get_bomb.ogg");
    resources.s_get_double_laser.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/get_double_laser.ogg");
    resources.s_out_porp.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/out_porp.ogg");
    resources.s_use_bomb.loadFromFile("/home/pan/repo/pandada8/flight/resources/sound/use_bomb.ogg");
    }


#endif //FLIGHT_RESOURCE_H