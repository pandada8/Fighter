#include <iostream>
#include <SFML/Graphics.hpp>
#include "easylogging++.h"
#include "resource.h"
#include <string>
#include <iostream>

using namespace std;

INITIALIZE_EASYLOGGINGPP


class Application{
public:
    Application(){
        LOG(INFO) << "Init the program";
    };
    void loadPreSource(){
        this->font.loadFromFile("/home/pan/ClionProjects/Flight/resources/font/STHeiti Light.ttc");
        this->background.loadFromFile("/home/pan/ClionProjects/Flight/resources/image/background.png");
    }
private:
    sf::RenderWindow window(sf::VideoMode(480, 800), "Game");
    sf::Texture background;
    sf::Font font;
};

sf::Texture* loadTexture(string path){
    sf::Texture* t = new sf::Texture();
    if (!t->loadFromFile(path)){
        LOG(FATAL) << "The program fail to load the resources and quit now ...";
        exit(1);
    };
    return t;
}

sf::Font* loadFont(string path){
    sf::Font* t = new sf::Font();
    if(!t->loadFromFile(path)){
        LOG(FATAL) << "The program fail to load the resource and quit now ...";
        exit(1);
    }
    return t;
}

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    el::Configurations conf;
    conf.setToDefault();
    conf.set(el::Level::Global, el::ConfigurationType::Format, "%datetime %level: %msg");
    el::Loggers::reconfigureLogger("default", conf);


    sf::RenderWindow window(sf::VideoMode(480, 800), "Test");
    LOG(INFO) << "The program started";
    // show the entry windows
    LOG(DEBUG) << "Start loading the background";
    auto background = loadTexture("/home/pan/ClionProjects/Flight/resources/image/background.png");  //todo: replace the path.
    window.draw(sf::Sprite(*background));
    LOG(DEBUG) << "Start loading the Font";
    auto font = loadFont("/home/pan/ClionProjects/Flight/resources/font/STHeiti Light.ttc");
    auto title = sf::Text("Flighter", *font, 50);
    auto size = window.getSize();
    title.setPosition((size.x - title.getLocalBounds().width) / 2, 100);
    auto sub_title = sf::Text(L"载入中", *font, 20);
    sub_title.setPosition((size.x - sub_title.getLocalBounds().width) / 2, 100 + title.getLocalBounds().height + 200);
    window.draw(title);
    window.draw(sub_title);
    window.display();



    LOG(DEBUG) << "Start to loading the resource pack";
    loadResource();
    LOG(INFO) << "Finish loading the resource pack";

    // show a
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            switch (event.type){
                case sf::Event::Closed:
                    // Do Some clean stuff

                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == 57){
                        // we could start the game
                        cout << "DEBUG: Starting the game" << endl;
                        break;
                    }
            }
        }
        // go the game scene
    }
    return 0;
}