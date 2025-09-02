#include "leaderboardManager.hpp"

#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm> 

LeaderboardManager::LeaderboardManager(PlatformInterface* p, Renderer* renderer) {
    this->renderer = renderer;

    visualRenderer = p->getVisualRenderer();
    resourceMan = p->getResourceManager();
    clockMan = p->getClockManager();
    audioRenderer = p->getAudioRenderer();
    userInputMan = p->getUserInputManager();
}

LeaderboardManager::~LeaderboardManager() {
    cleanUp();
}

void LeaderboardManager::cleanUp() {
    for (ImageInfo* img : imgBuff) {
        renderer->remove(img);
        delete img;
    }
    imgBuff.clear();

    nameImages.clear();
    scoreImages.clear();

    renderer->remove(leaderboardScreen);
    delete leaderboardScreen;
    leaderboardScreen = nullptr;
}

void LeaderboardManager::initalise() {
    leaderboardScreen = resourceMan->makeImage(LBOARD_SCREEN_PATH, WINDOW_WIDTH, WINDOW_HEIGHT, true);
    renderer->render(leaderboardScreen, { 0, 0 });
}

GUIState LeaderboardManager::loop() {
    // read the scores the data
    std::string data = resourceMan->readFile(SCORES_TXT);

    std::vector<std::pair<std::string, std::string>> nameScores;
    std::stringstream ss(data);
    std::string line;

    // ignore 1st line
    std::getline(ss, line);

    // insert score data vector of pairs of {name, score}
    while (std::getline(ss, line)) {
        std::stringstream line_stream(line);
        std::string name, score;

        std::getline(line_stream, name, ',');
        std::getline(line_stream, score);

        nameScores.push_back({ name, score });
    }

    // sort pairs by score int value
    std::sort(nameScores.begin(), nameScores.end(),
        // lambda to compare the int value of two scores in nameScores
        [](std::pair<std::string, std::string>& a, std::pair<std::string, std::string>& b) {
            return std::stoi(a.second) > std::stoi(b.second);
        });

    for (int i = 0; i < NUM_HIGH_SCORES && i < nameScores.size(); i++) {
        std::pair<std::string, std::string> pair = nameScores[i];
        int j;

        // render name
        nameImages = constructName(pair.first);
        j = 0;
        for (ImageInfo* img : nameImages) {
            renderer->render(img, { LBOARD_NAME_OFFSET.x + j, LBOARD_NAME_OFFSET.y - (i * LBOARD_ENTRIES_GAP) });
            imgBuff.push_back(img);
            j++;
        }

        // render score
        scoreImages = constructScore(pair.second);
        j = 0;
        for (ImageInfo* img : scoreImages) {
            renderer->render(img, { LBOARD_SCORE_OFFSET.x + j, LBOARD_SCORE_OFFSET.y - (i * LBOARD_ENTRIES_GAP) });
            imgBuff.push_back(img);
            j++;
        }
    }

    // loop
    while (true) {
        // the sole purpose of the leaderboard loop is to wait for the user to
        // press 'ENTER', at which point we break from the loop an return
        // to the main manu.

        bool enterFlag = false;
        while (!userInputMan->isEmpty()) {
            UserInput input = userInputMan->getNextInput();
            if (input == RETURN_DOWN)
                enterFlag = true;
        }

        if (enterFlag) {
            cleanUp();
            return MAIN_MENU;
        }

        visualRenderer->updateDisplay();
        clockMan->synchronizeFrame();
    }
}

std::list<ImageInfo*> LeaderboardManager::constructName(std::string str) {
    std::list<ImageInfo*> name;

    // for each char in the string, associate it to the image path for that char
    for (char c : str) {
        std::string path;
        switch (c) {
        case 'A': path = A_PATH; break;
        case 'B': path = B_PATH; break;
        case 'C': path = C_PATH; break;
        case 'D': path = D_PATH; break;
        case 'E': path = E_PATH; break;
        case 'F': path = F_PATH; break;
        case 'G': path = G_PATH; break;
        case 'H': path = H_PATH; break;
        case 'I': path = I_PATH; break;
        case 'J': path = J_PATH; break;
        case 'K': path = K_PATH; break;
        case 'L': path = L_PATH; break;
        case 'M': path = M_PATH; break;
        case 'N': path = N_PATH; break;
        case 'O': path = O_PATH; break;
        case 'P': path = P_PATH; break;
        case 'Q': path = Q_PATH; break;
        case 'R': path = R_PATH; break;
        case 'S': path = S_PATH; break;
        case 'T': path = T_PATH; break;
        case 'U': path = U_PATH; break;
        case 'V': path = V_PATH; break;
        case 'W': path = W_PATH; break;
        case 'X': path = X_PATH; break;
        case 'Y': path = Y_PATH; break;
        case 'Z': path = Z_PATH; break;
        }
        name.push_back(resourceMan->makeImage(path, CELL_SIZE, CELL_SIZE, true));
    }
    return name;
}

std::list<ImageInfo*> LeaderboardManager::constructScore(std::string str) {
    std::list<ImageInfo*> score;

    // for each char in the string, associate it to the image path for that char
    for (char c : str) {
        std::string path;
        switch (c) {
        case '0': path = ZERO_PATH; break;
        case '1': path = ONE_PATH; break;
        case '2': path = TWO_PATH; break;
        case '3': path = THREE_PATH; break;
        case '4': path = FOUR_PATH; break;
        case '5': path = FIVE_PATH; break;
        case '6': path = SIX_PATH; break;
        case '7': path = SEVEN_PATH; break;
        case '8': path = EIGHT_PATH; break;
        case '9': path = NINE_PATH; break;
        }
        score.push_back(resourceMan->makeImage(path, CELL_SIZE, CELL_SIZE, true));
    }
    return score;
}

