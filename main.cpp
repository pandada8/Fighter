#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "easylogging++.h"
#include "resource.h"
#include <string>
#include <vector>
#include <thread>
#include <random>

using namespace std;

#define PUT_CENTER(obj, height) obj.setPosition((this->window.getSize().x - obj.getLocalBounds().width) / 2, height); this->window.draw(obj);

#define BOTTOM(obj) (obj.getGlobalBounds().height + obj.getGlobalBounds().top)

INITIALIZE_EASYLOGGINGPP

int randomChoice(int start, int end){
    static default_random_engine generator;
    uniform_int_distribution<int> distribution(start, end);
    return distribution(generator);
}


struct {
    sf::Texture* bullets[2] = {
            &resources.p_bullet1,
            &resources.p_bullet2
    };
    sf::Texture* enemy1[5] = {
            &resources.p_enemy1,
            &resources.p_enemy1_down1,
            &resources.p_enemy1_down2,
            &resources.p_enemy1_down3,
            &resources.p_enemy1_down4,
    };
    sf::Texture* enemy2[5] = {
            &resources.p_enemy2,
            &resources.p_enemy2_down1,
            &resources.p_enemy2_down2,
            &resources.p_enemy2_down3,
            &resources.p_enemy2_down4,
    };
    sf::Texture* enemy3[9] = {
            &resources.p_enemy3_n1,
            &resources.p_enemy3_n2,
            &resources.p_enemy3_down1,
            &resources.p_enemy3_down2,
            &resources.p_enemy3_down3,
            &resources.p_enemy3_down4,
            &resources.p_enemy3_down5,
            &resources.p_enemy3_down6,
            &resources.p_enemy3_hit,
    };
} skins;



class Bullet : public sf::Sprite{
public:
    Bullet(float base_x, float base_y, bool self = false) : sf::Sprite(), send_by_self(self) {
        if(self){
            this->setTexture(*skins.bullets[0]);
        }else{
            this->setTexture(*skins.bullets[1]);
        }
        this->setPosition(base_x, base_y);
    };
    void autoMove(){
        if(send_by_self){
            this->move(0, -2.0);
        }else{
            this->move(0, 2.0);
        }
    }
    const bool send_by_self;
};

class Enemy : public sf::Sprite{
public:
    Enemy(float width) : sf::Sprite(), life(30) {
        if (randomChoice(0, 1)){
            this->skins = ::skins.enemy1;
        }else{
            this->skins = ::skins.enemy2;
        }
        this->setTexture(*this->skins[0]);
        this->setPosition(randomChoice(0, width - this->getLocalBounds().width), - this->getLocalBounds().top + 1);
    }
    void paint(){
        if(this->life > 0){
            this->move(0, 1);
        }else{
            if(count == 0){
                last_animate.restart();
            }
            if(count <= 4){
                if(last_animate.getElapsedTime().asMilliseconds() > 125){
                    last_animate.restart();
                    this->setTexture(*this->skins[count++]);
                }
            }else{
                this->animated = true;
            }
        }
    }
    void hited(){
        this->life -= 10;
    }
    void shot(vector<shared_ptr<Bullet>>& bullet_pool){
        if(this->last_shot.getElapsedTime().asMilliseconds() > 1000){
            bullet_pool.push_back(make_shared<Bullet>(this->getPosition().x + this->getLocalBounds().width / 2, \
            this->getPosition().y + this->getGlobalBounds().height, false));
            this->last_shot.restart();
        }
    }
    bool should_remove(){
        return this->life <= 0 && this->animated;
    }
    int life;
private:
    sf::Texture** skins;
    bool animated=false;
    int count = 1;
    sf::Clock last_animate;
    sf::Clock last_shot;
};


class Application{
public:
    Application(): window(sf::VideoMode(480, 800), "Game"), point(100){
        LOG(INFO) << "Init the program";
    };
    void loadPreSource(){
        this->font.loadFromFile("/home/pan/repo/pandada8/flight/resources/font/STHeiti Light.ttc");
        this->background.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/background.png");
    }
    void loadExtraResource(){
        loadResource();
        this->effect.setBuffer(resources.s_enemy1_down);
    }
    void flush(){
        this->window.display();
    }
    void drawBackground(){
        sf::Sprite background(this->background);
        background.scale(this->window.getSize().x / background.getLocalBounds().width, 1);
        this->window.clear();
        this->window.draw(background);
    }
    void drawFirstScreen(){
        LOG(DEBUG) << "The first screen";
        this->drawBackground();
        sf::Text title(L"打飞机", this->font, 50);
        PUT_CENTER(title, 100)
        sf::Text sub_title(L"载入中", this->font, 20);
        PUT_CENTER(sub_title, BOTTOM(title) + 300)
    }
    void finishLoading(){
        LOG(DEBUG) << "The main menu";
        this->drawBackground();
        sf::Text title(L"打飞机", this->font, 50);
        PUT_CENTER(title, 100)
        sf::Text sub_title(L"按下空格开始", this->font, 20);
        PUT_CENTER(sub_title, BOTTOM(title) + 300);
        this->window.draw(sub_title);
        sf::Sprite plant(resources.p_hero1);
        PUT_CENTER(plant, BOTTOM(sub_title) + 50)
    };
    void play_bgm(){
        this->background_music.setBuffer(resources.s_game_music);
        this->background_music.setLoop(true);
        this->background_music.play();
    }
    void wait_for_space(){
        sf::Event event;
        while(this->window.waitEvent(event)) {
            switch (event.type){
                case sf::Event::KeyPressed:
                    if (event.key.code == 57 || event.key.code == 16 || event.key.code == 36){
                        // we could start the game
                        LOG(INFO) << "We start the game!";
                        goto finish;
                    }else{
                        LOG(DEBUG) << event.key.code;
                    }
            }
        };
        finish:
            return;
    }
    void close(){
        LOG(INFO) << "Goodbye!";
        this->window.close();
    }
    bool start_game(){
        this->window.setKeyRepeatEnabled(true);
        LOG(INFO) << "Start game";
        this->drawBackground();
        this->flight.setTexture(resources.p_hero1);
        PUT_CENTER(this->flight, this->window.getSize().y - 120)
        this->flush();
        sf::Event event;


        // we should render all the things in one thread and just pass the information from the main thread to the target.
        LOG(INFO) << "Start render thread";
        sf::Clock tick;
        sf::Text fps_text("FPS", this->font, 20);
        LOG(INFO) << "Enter event loop ";
        float move = 0.0;
        sf::Clock last_shot;
        while (this->window.hasFocus()) {
            this->drawBackground();

            for (auto i : bullets_pool){
                i->autoMove();
            }
            // if we are hit
            bullets_pool.erase(remove_if(bullets_pool.begin(), bullets_pool.end(), [this](shared_ptr<Bullet> x){
                if(this->flight.getGlobalBounds().contains(x->getPosition())){
                    this->point -= 10;
                    return true;
                }else{
                    return (x->getPosition().y < 0 || x->getPosition().y > window.getSize().y);
                }
            }), bullets_pool.end());

            // gen the new enemy
            if(this->enemy_pool.size() < 5 && randomChoice(0, 10000) < 50) {
                auto ptr = make_shared<Enemy>(window.getSize().x);
                this->enemy_pool.push_back(ptr);
            }
            for(auto flight : enemy_pool){
                flight->shot(bullets_pool);
            }

            for(auto i : enemy_pool){
                i->paint();
            }
            // check if we hit you
            for(auto flight : enemy_pool){
                for(auto i = bullets_pool.begin(); i!=bullets_pool.end();){
                    if(flight->getGlobalBounds().contains(i->get()->getPosition()) && i->get()->send_by_self){
                        //wow the flight was hit
                        LOG(DEBUG) << "A Flight got hit";
                        flight->hited();
                        effect.play();
                    }else{
                        i++;
                    }
                }
            }
            // check if we are killed
            for(auto enemy : enemy_pool){
                if(this->flight.getGlobalBounds().contains(enemy->getPosition())){
                    // ok we crashed and died;
                    this->point -= 10;
                    enemy->life = 0;
                }
            }
            // A quite LONG Lambda function :/
            enemy_pool.erase(remove_if(enemy_pool.begin(), enemy_pool.end(), [this](shared_ptr<Enemy> x){
                if(this->flight.getGlobalBounds().contains(x->getPosition())){
                    this->point -= 10;
                    return true;
                }else{
                    return x->getPosition().y - x->getLocalBounds().height > window.getSize().y || x->should_remove();
                }
            }), enemy_pool.end());
            for(auto i : enemy_pool){
                window.draw(*i);
            }

            for (auto i : bullets_pool){
                window.draw(*(i.get()));
            }

            this->window.draw(this->flight);

            int passed = tick.getElapsedTime().asMilliseconds();
            passed = passed==0 ? 1 : passed ;
            float fps = 1000 / passed;
            fps_text.setString("FPS: "+to_string(fps) + " Enemy:" + to_string(enemy_pool.size()) + " Life:" + to_string(this->point));
            tick.restart();
            this->window.draw(fps_text);
            this->flush();


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                if(this->flight.getPosition().x - 10 > 0){
                    this->flight.move(-4.0, 0);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                if(window.getSize().x - this->flight.getLocalBounds().width - this->flight.getPosition().x > 10){
                    this->flight.move(4.0, 0);
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && last_shot.getElapsedTime().asMilliseconds() > 300){
                auto ptr = make_shared<Bullet>(flight.getPosition().x + flight.getLocalBounds().width / 2, flight.getPosition().y, true);
                bullets_pool.push_back(ptr);
                last_shot.restart();
            }

            // if we die?
            if(this->point <= 0){
                LOG(INFO) << "Oh WE have to say goobye";
                return false;
            }


            int delta = 20 - tick.getElapsedTime().asMilliseconds();

            if(delta > 0){
                sf::sleep(sf::milliseconds(delta));
            }

        }
        return true;
    }
    void fail_page(){
        sf::Sprite mask(resources.p_game_over);
        this->window.draw(mask);
        sf::Text fail(L"按空格退出", this->font);
        PUT_CENTER(fail, 300);
        this->flush();

    }
private:
    sf::RenderWindow window;
    sf::Texture background;
    sf::Font font;
    sf::Sound background_music;
    sf::Sound effect;
    int point = 100;
    sf::Sprite flight;
    vector<shared_ptr<Bullet>> bullets_pool;
    vector<shared_ptr<Enemy>> enemy_pool;
};
int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    el::Configurations conf;
    conf.setToDefault();
    conf.set(el::Level::Global, el::ConfigurationType::Format, "%datetime %level: %msg");
    el::Loggers::reconfigureLogger("default", conf);

    Application app;
    app.loadPreSource();
    app.drawFirstScreen();
    app.flush();
    app.loadExtraResource();
    app.finishLoading();
//    app.play_bgm();
    app.flush();
    app.wait_for_space();
    // start game

    if(!app.start_game()){
        // we lose
        app.fail_page();
        app.wait_for_space();
    };

    app.close();
    return 0;
}