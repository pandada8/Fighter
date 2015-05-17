#include <iostream>
#include <SFML/Graphics.hpp>
#include "easylogging++.h"
#include "resource.h"
#include <string>
#include <iostream>

using namespace std;

#define PUT_CENTER(obj, height) obj.setPosition((this->window.getSize().x - obj.getLocalBounds().width) / 2, height); this->window.draw(obj);

#define BOTTOM(obj) (obj.getGlobalBounds().height + obj.getGlobalBounds().top)

INITIALIZE_EASYLOGGINGPP


class Application{
public:
    Application(): window(sf::VideoMode(480, 800), "Game"){
        LOG(INFO) << "Init the program";
    };
    void loadPreSource(){
        this->font.loadFromFile("/home/pan/ClionProjects/Flight/resources/font/STHeiti Light.ttc");
        this->background.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/background.png");
    }
    void loadExtraResource(){
        loadResource();
    }
    void flush(){
        this->window.display();
    }
    void drawBackground(){
        sf::Sprite background(this->background);
        this->window.draw(background);
    }
    void drawFirstScreen(){
        LOG(DEBUG) << "The first screen";
        this->window.clear();
        this->drawBackground();
        sf::Text title(L"打飞机", this->font, 50);
        PUT_CENTER(title, 100)
        sf::Text sub_title(L"载入中", this->font, 20);
        PUT_CENTER(sub_title, BOTTOM(title) + 300)
    }
    void finishLoading(){
        LOG(DEBUG) << "The main menu";
        this->window.clear();
        this->drawBackground();
        sf::Text title(L"打飞机", this->font, 50);
        PUT_CENTER(title, 100)
        sf::Text sub_title(L"按下空格开始", this->font, 20);
        PUT_CENTER(sub_title, BOTTOM(title) + 300);
        this->window.draw(sub_title);
        sf::Sprite plant(resources.p_hero1);
        PUT_CENTER(plant, BOTTOM(sub_title) + 50)
    };
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
private:
    sf::RenderWindow window;
    sf::Texture background;
    sf::Font font;
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
    app.flush();
    app.wait_for_space();
    app.close();
    return 0;
}