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
    Bullet(float base_x, float base_y, bool self = false) : sf::Sprite() {
        this-> to_self = self;
        if(self){
            this->setTexture(*skins.bullets[0]);
        }else{
            this->setTexture(*skins.bullets[1]);
        }
        this->setPosition(base_x, base_y);
    };
    void autoMove(){
        if(to_self){
            this->move(0, -2.0);
        }else{
            this->move(0, 2.0);
        }
    }
private:
    bool to_self;
};


class Application{
public:
    Application(): window(sf::VideoMode(480, 800), "Game"){
        LOG(INFO) << "Init the program";
    };
    void loadPreSource(){
        this->font.loadFromFile("/home/pan/repo/pandada8/flight/resources/font/STHeiti Light.ttc");
        this->background.loadFromFile("/home/pan/repo/pandada8/flight/resources/image/background.png");
    }
    void loadExtraResource(){
        loadResource();
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
    void update_frame(vector<sf::Drawable>){

    }
    void start_game(){
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
        auto ptr = make_shared<Bullet>(flight.getPosition().x + flight.getLocalBounds().width / 2, flight.getPosition().y, true);
        bullets_pool.push_back(ptr);
        while (!this->isGameOver() && this->window.hasFocus()) {
            this->drawBackground();

            // we move first
            for (auto i : bullets_pool){
                i->autoMove();
            }
            bullets_pool.erase(remove_if(bullets_pool.begin(), bullets_pool.end(), [this](shared_ptr<Bullet> x){
                return x->getPosition().y < 0 || x->getPosition().y > window.getPosition().y;
            }), bullets_pool.end());
            // then we check if we have same position?

            // ok we cound draw
            for (auto i : bullets_pool){
                window.draw(*i);
            }

            this->window.draw(this->flight);

            int passed = tick.getElapsedTime().asMilliseconds();
            passed = passed==0 ? 1 : passed ;
            float fps = 1000 / passed;
            fps_text.setString("FPS: "+to_string(fps));
            tick.restart();
            this->window.draw(fps_text);
            this->flush();



            while (this->window.pollEvent(event)){
                switch(event.type){
                    case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Left){
                            this->flight.move(-5.0, 0);
                        }else if (event.key.code == sf::Keyboard::Right){
                            this->flight.move(5.0, 0);
                        }else if (event.key.code == sf::Keyboard::Space){

                        }
                    default:;
                }

            }

            int delta = 5 - tick.getElapsedTime().asMilliseconds();

            if(delta > 0){
                sf::sleep(sf::milliseconds(delta));
            }
        }

    }
    bool isGameOver(){
        return false;
    }
private:
    sf::RenderWindow window;
    sf::Texture background;
    sf::Font font;
    sf::Sound background_music;
    sf::Sprite flight;
    vector<shared_ptr<Bullet>> bullets_pool;
//    vector<Object*> enemy_pool;

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

    app.start_game();
    app.close();
    return 0;
}