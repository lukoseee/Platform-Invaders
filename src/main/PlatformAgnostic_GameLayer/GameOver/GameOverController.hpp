#pragma once

#include "../GUIInterface.hpp"
#include <vector>

class GameOverController : public GUIInterface{
public:
    GameOverController(PlatformInterface*);
    ~GameOverController();
    
    void initalise() override;
    GUIState loop() override;
    void cleanUp() override;
    void setScore(int score);
    
private:
    ImageInfo* background;
    int finalScore;
    std::string nameBuilder;
    std::vector<ImageInfo*> chars;
    ImageInfo* scoreDisplay;
    std::vector<ImageInfo*> scoreDigits;  // Store rendered digit images
    void renderScoreDigits();         // New method to display score
    void addCharacter(const char* path, char c);
};
