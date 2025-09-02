#pragma once

#include "../../../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "../GameManagerInterface.hpp"
#include <list>
#include <vector>

/*
 Manager class to handle the maintaining and rendering of the player's score
 */
class ScoreManager : public GameManagerInterface{
public:
    ScoreManager(VisualRendererInterface*, ResourceManagerInterface*);
    ~ScoreManager();

    void updateAndRender() override;
    
    void initialise();
    void addScore(int value);
    void resetScore();
    int getScore() const;

private:
    ImageInfo* convertDigit(int digit);
    
    
    int score;
    int lastRenderedScore;

    // The scoreboard background (e.g. "score.png")
    ImageInfo* headerImage;
    
    std::list<ImageInfo*> digits;

    // Screen position of the scoreboard background
    const int backgroundX = 100;
    const int backgroundY = 20;

    // Track which digit images we rendered in the last frame,
    // so we can remove them before rendering new ones.
    std::vector<ImageInfo*> previouslyRenderedDigits;
};
