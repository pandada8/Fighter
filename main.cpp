#include <iostream>
#include <SFML/Graphics.hpp>
#include "easylogging++.h"
#include "resource.h"
#include <string>
#include <iostream>

using namespace std;

#define PUT_CENTER(obj, height) obj.setPosition((this->window.getSize().x - title.getLocalBounds().width) / 2, height); this->window.draw(obj);

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
        title.setPosition((this->window.getSize().x - title.getLocalBounds().width) / 2, 100);
        this->window.draw(title);
        sf::Text sub_title(L"载入中", this->font, 20);
        sub_title.setPosition((this->window.getSize().x - sub_title.getLocalBounds().width) / 2,  100 + title.getLocalBounds().height + 300);
        this->window.draw(sub_title);
    }
    void finishLoading(){
        LOG(DEBUG) << "The main menu";
        this->window.clear();
        this->drawBackground();
        sf::Text title("Flighter", this->font, 50);
        title.setPosition((this->window.getSize().x - title.getLocalBounds().width) / 2, 100);
        this->window.draw(title);
        sf::Text sub_title(L"按下空格开始", this->font, 20);
        sub_title.setPosition((this->window.getSize().x - sub_title.getLocalBounds().width) / 2,  100 + title.getLocalBounds().height + 200);
        this->window.draw(sub_title);
        sf::Sprite plant(resources.p_hero1);
        plant.setPosition((this->window.getSize().x - plant.getLocalBounds().width) / 2, sub_title.getGlobalBounds().top + sub_title.getGlobalBounds().height + 100);
        this->window.draw(plant);
    };
    void wait_for_space(){
        sf::Event event;
        while(this->window.waitEvent(event)) {
            switch (event.type){
                case sf::Event::KeyPressed:
                    if (event.key.code == 57){
                        // we could start the game
                        LOG(INFO) << "We start the game!";
                        goto finish;
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
//
//int main(int argc, char* argv[]) {
//    START_EASYLOGGINGPP(argc, argv);
//    el::Configurations conf;
//    conf.setToDefault();
//    conf.set(el::Level::Global, el::ConfigurationType::Format, "%datetime %level: %msg");
//    el::Loggers::reconfigureLogger("default", conf);
//
//
//    sf::RenderWindow window(sf::VideoMode(480, 800), "Test");
//    LOG(INFO) << "The program started";
//    // show the entry windows
//    LOG(DEBUG) << "Start loading the background";
//    auto background = loadTexture("/home/pan/ClionProjects/Flight/resources/image/background.png");  //todo: replace the path.
//    window.draw(sf::Sprite(*background));
//    LOG(DEBUG) << "Start loading the Font";
//    auto font = loadFont("/home/pan/ClionProjects/Flight/resources/font/STHeiti Light.ttc");
//    auto title = sf::Text("Flighter", *font, 50);
//    auto size = window.getSize();
//    title.setPosition((size.x - title.getLocalBounds().width) / 2, 100);
//    auto sub_title = sf::Text(L"载入中", *font, 20);
//    sub_title.setPosition((size.x - sub_title.getLocalBounds().width) / 2, 100 + title.getLocalBounds().height + 200);
//    window.draw(title);
//    window.draw(sub_title);
//    window.display();
//
//
//
//    LOG(DEBUG) << "Start to loading the resource pack";
//    loadResource();
//    LOG(INFO) << "Finish loading the resource pack";
//
//    // show a
//    while(window.isOpen()) {
//        sf::Event event;
//        while(window.pollEvent(event)) {
//            switch (event.type){
//                case sf::Event::Closed:
//                    // Do Some clean stuff
//
//                    window.close();
//                    break;
//                case sf::Event::KeyPressed:
//                    if (event.key.code == 57){
//                        // we could start the game
//                        cout << "DEBUG: Starting the game" << endl;
//                        break;
//                    }
//            }
//        }
//        // go the game scene
//    }
//    return 0;
//}