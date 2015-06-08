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

class Object{
public:
    Object(){};
    void draw(){};
    void setPosition(float, float){};
    void move(){};
private:
    sf::Sprite drawable;
};

class Bullet : public Object{
public:
    Bullet(bool self = false){
        if(self){
            this->drawable = sf::Sprite(*skins.bullets[0]);
        }else{
            this->drawable = sf::Sprite(*skins.bullets[1]);
        }
    };
    void setPosition(float x, float y){
        this->drawable.setPosition(x, y);
    };
    void move(float x, float y){
        this->drawable.move(x, y);
    }
private:
    sf::Sprite drawable;
};

class Enemy : public Object{
    Enemy(char type='A'){
        if (type == 'A') {
            this->skins = ::skins.enemy1;
        }else{
            this->skins = ::skins.enemy2;
        }
        this->drawable = sf::Sprite(*this->skins[0]);
    }
    void move(){

    }
    void draw(sf::RenderWindow window, bool boom=false){
        static int frame = 0;
        if(this->point <= 0){
            // loser, go to the death


        }else{
            window.draw(this->drawable);
        }

    };
private:
    sf::Texture** skins;
    sf::Sprite drawable;
    int point = 100;
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
    void render(){
        // paint the fps on the left top corner
        sf::Clock tick;
        sf::Text fps_text("FPS", this->font, 20);
        while (true ){
            this->drawBackground();
//            // draw other things here
//
            int passed = tick.getElapsedTime().asMilliseconds();
            passed = passed==0 ? 1 : passed ;
            float fps = 1000 / passed;
            fps_text.setString("FPS: "+to_string(fps));
            this->window.draw(fps_text);
            this->flush();
            int delta = 5 - tick.getElapsedTime().asMilliseconds();
            tick.restart();

            if(delta > 0){
                sf::sleep(sf::milliseconds(delta));
            }
        }
    }
    void start_game(){
        LOG(INFO) << "Start game";
        this->drawBackground();
        sf::Sprite flight(resources.p_hero1);
        PUT_CENTER(flight, this->window.getSize().y - 120)
        this->window.draw(flight);
        this->flush();
        sf::Event event;
        LOG(INFO) << "Enter event loop ";

        // we should render all the things in one thread and just pass the information from the main thread to the target.
        sf::Thread render(&Application::render, this);
        render.launch();
        render.wait();
//        while (!this->isGameOver() && this->window.hasFocus()) {
//            while (this->window.pollEvent(event)){
//                float move = 0.0;
//                switch(event.type){
//                    case sf::Event::KeyPressed:
//                        if (event.key.code == sf::Keyboard::Left){
//                            flight.move(-5.0, 0);
//                        }else if (event.key.code == sf::Keyboard::Right){
//                            flight.move(5.0, 0);
//                        }else if (event.key.code == sf::Keyboard::Space){
//                            LOG(DEBUG) << "Bullet";
//                        }
//                        this->window.clear();
//                        this->drawBackground();
//                        this->window.draw(flight);
//                        this->flush();
//                    default:;
//                }
//
//            }
//        }
    }
    bool isGameOver(){
        return false;
    }
private:
    sf::RenderWindow window;
    sf::Texture background;
    sf::Font font;
    sf::Sound background_music;
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