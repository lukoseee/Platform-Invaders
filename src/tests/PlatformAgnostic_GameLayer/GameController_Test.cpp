#include "../test.hpp"
#include "../../main/PlatformAgnostic_GameLayer/Player.hpp"
#include "../../main/PlatformAgnostic_GameLayer/GameController.hpp"

// Mocking the HardwareInterface for testing
class MockHardwareInterface : public HardwareInterface {
public:

    queue<string> mockInputBuffer;
    
    string getNextInput() override {
        if (mockInputBuffer.empty()) {
            return "UNDEFINED"; // Simulate empty behavior
        }
        string input = mockInputBuffer.front();
        mockInputBuffer.pop(); // Simulate consuming the input
        return input;
    }

    bool isEmpty() override {
        return mockInputBuffer.empty();
    }

};


// Global variables
GameController* controller;
MockHardwareInterface* mockHardware;    
Player*  player;

// Set up the test environment
void setUp() {
    printf("Setting up...\n");
    controller = new GameController(); 
    printf("GameController created\n");

    mockHardware = new MockHardwareInterface(); 
    printf("MockHardwareInterface created\n");

    controller->hardwareInterface = mockHardware;
    printf("Hardware interface injected\n");

    player = new Player();
    printf("Player created: %p\n", player);

    controller->entities->push_back(player);
    printf("Player added to entities: %p\n", controller->entities);
}

void testPollInputBuffer_ValidInput() {
    // Simulate adding input to the buffer
    mockHardware->mockInputBuffer.push("a");

    // Poll the input buffer
    string input = controller->pollInputBuffer();

    // Check if the input is correct
    check(input == "a");
}

void testPollInputBuffer_EmptyInput() {
    string input = controller->pollInputBuffer();
    check(input == "UNDEFINED");
}


void testProcessInput_MoveLeft() {
    // Simulate input "a" for moving left
    controller->processInput("a");

    // Check if the player's position updated correctly
    position pos = player->getPosition();
    printf("Position after moveLeft: x = %d, y = %d\n", pos.x, pos.y); // Debug print

    check(pos.x == -1);
}

void testProcessInput_MoveRight() {
    // Simulate input "d" for moving right
    controller->processInput("d");

    // Check if the player's position updated correctly
    position pos = player->getPosition();
    printf("Position after moveLeft: x = %d, y = %d\n", pos.x, pos.y); // Debug print

    check(pos.x == 1);
}

void testStartGame() {
    // Start the game
    controller->startGame();

    // Check if the game state is RUNNING
    check(controller->state == RUNNING);

    // Check if a player was added to the entities list
    printf("Number of entities: %zu\n", controller->entities->size());
    check(controller->entities->size() == 2);

    // Verify player's initial position
    Player* player = dynamic_cast<Player*>(controller->entities->front());
    check(player != nullptr); // Ensure the entity is a Player
    if (player) {
        position pos = player->getPosition();
        check(pos.x == 0);
        check(pos.y == 0);
    }
}

void testGameLoop() {
    // Start the game
    controller->startGame();

    // Simulate input to move the player left
    mockHardware->mockInputBuffer.push("a");

    // Run the game loop
    controller->gameLoop();

    // Verify that the player's position was updated
    Player* player = dynamic_cast<Player*>(controller->entities->front());
    check(player != nullptr);
    if (player) {
        position pos = player->getPosition();
        check(pos.x == -1); // Assuming "a" moves left
        check(pos.y == 0);
    }

    // Verify that the game state is GAMEOVER after the loop ends
    check(controller->state == GAMEOVER);
}

// Test for running the game loop once
void testRunOnce() {
    controller->startGame();

    // Simulate input to move right
    mockHardware->mockInputBuffer.push("d");

    // Run the game loop
    controller->gameLoop();

    // Verify that the player's position is updated
    Player* player = dynamic_cast<Player*>(controller->entities->front());
    check(player != nullptr);
    if (player) {
        position pos = player->getPosition();
        printf("Position after running game loop: x = %d, y = %d\n", pos.x, pos.y);
        check(pos.x == 1); // Assuming "d" moves right
        check(pos.y == 0);
    }
}




int main() {
    // Set up the test environment
    setBeforeEach(setUp);

    // Add test cases
    addTest(testPollInputBuffer_ValidInput);
    addTest(testPollInputBuffer_EmptyInput);
    addTest(testProcessInput_MoveLeft);
    addTest(testProcessInput_MoveRight);
    addTest(testStartGame);
    addTest(testGameLoop);
    addTest(testRunOnce);


    // Run the tests
    runTests();

    // Clean up
    cleanTests();
    return 0;
}
