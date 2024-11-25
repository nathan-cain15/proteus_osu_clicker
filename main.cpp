#include <FEHImages.h>
#include <windows.h>
#include <string.h>
#include <time.h>

// functions
void drawMenu();
void drawHowToPlay();
void drawCredits();
void drawBackButton();
void drawGrassBackground();
void drawTrees();

// structs
struct Coords {
    int x;
    int y;
};
struct Button {
    Coords upperLeft;
    Coords bottomRight;
};

struct Stats {
    int money;
    int playTime;
    int moneyPerSecond;
};

class GameController {
    private:
        
        float xTouched, yTouched;
        char gameState;
        Stats stats;
    
    public:
        bool touched;
        GameController();
        bool isButtonTouched(Button button);
        float* getxRef();
        float* getyRef();
        
        char getGameState();
        void setGameState(char);

        void drawStats();

};



 
int main(void)
{
    // create gamecontroller
    GameController gameController = GameController();

    // touching variables
    float x_position, y_position, x_trash, y_trash;


    // create menu buttons
    struct Button playGameButton, statsButton, howToPlayButton, creditsButton, backButton;
    
    playGameButton.upperLeft.x = 105;
    playGameButton.upperLeft.y = 82;
    playGameButton.bottomRight.x = 214;
    playGameButton.bottomRight.y = 115;

    statsButton.upperLeft.x = 105;
    statsButton.upperLeft.y = 120;
    statsButton.bottomRight.x = 214;
    statsButton.bottomRight.y = 153;

    howToPlayButton.upperLeft.x = 105;
    howToPlayButton.upperLeft.y = 160;
    howToPlayButton.bottomRight.x = 214;
    howToPlayButton.bottomRight.y = 193;

    creditsButton.upperLeft.x = 105;
    creditsButton.upperLeft.y = 198;
    creditsButton.bottomRight.x = 214;
    creditsButton.bottomRight.y = 234;

    backButton.upperLeft.x = 284;
    backButton.upperLeft.y = 5;
    backButton.bottomRight.x = 310;
    backButton.bottomRight.y = 29;



    
    while(1) {
        gameController.touched = false;
        LCD.SetFontColor(BLACK);

        if (LCD.Touch(gameController.getxRef(), gameController.getyRef())){
            gameController.touched = true;

            // use when needing to look at coordinates
            // LCD.WriteLine("The screen is under pressure");
            // LCD.Write("At x coordinate: ");
            // LCD.WriteLine(*gameController.getxRef());
            // LCD.Write("At y coordinate: ");
            // LCD.WriteLine(*gameController.getyRef());

            /* Wait until the user touches the screen */
            while(!LCD.Touch(gameController.getxRef(), gameController.getyRef())) {};
            /* Wait until the touch releases */
            while(LCD.Touch(&x_trash,&y_trash)) {};

        }
        
        

         if (gameController.getGameState() == 'm'){
            drawMenu();

            // check if any buttons are being touched
            if (gameController.touched){
                
                if (gameController.isButtonTouched(playGameButton)){
                    gameController.setGameState('g');
                } else if (gameController.isButtonTouched(statsButton)){
                    gameController.setGameState('s');
                } else if (gameController.isButtonTouched(howToPlayButton)){
                    gameController.setGameState('h');
                } else if (gameController.isButtonTouched(creditsButton)){
                    gameController.setGameState('c');
                }
            }
         } else if (gameController.getGameState() == 'g'){
            LCD.Clear();
            drawGrassBackground();
            drawTrees();
            drawBackButton();

            if (gameController.touched && gameController.isButtonTouched(backButton)){
                gameController.setGameState('m');
            }

         } else if (gameController.getGameState() == 's'){
            gameController.drawStats();

            if (gameController.touched && gameController.isButtonTouched(backButton)){
                gameController.setGameState('m');
            }

         } else if (gameController.getGameState() == 'h'){
            drawHowToPlay();

            if (gameController.touched && gameController.isButtonTouched(backButton)){
                gameController.setGameState('m');
            }
         } else if (gameController.getGameState() == 'c'){
            drawCredits();

            if (gameController.touched && gameController.isButtonTouched(backButton)){
                gameController.setGameState('m');
            }
         }
        

        LCD.Update(); //Never quit     
    }

    return 0;
}

void drawMenu(){

    // draw title px 320, 240

    LCD.SetBackgroundColor(GRAY);
    LCD.Clear();

    FEHImage menuState;
    menuState.Open("images/menu_text6.png");
    menuState.Draw(0, 0);
    menuState.Close();
}

void GameController::drawStats(){
    LCD.Clear();
    LCD.SetFontColor(WHITE);

    // make money string to display
    char moneyStr1[30] = "Money: ";
    char moneyStr2[30];
    
    sprintf(moneyStr2, "%d", stats.money);
    strcat(moneyStr1, moneyStr2);

    // make money per second string to display
    char mpsStr1[50] = "Money per Second: ";
    char mpsStr2[50];

    sprintf(mpsStr2, "%d", stats.moneyPerSecond);
    strcat(mpsStr1, mpsStr2);

    // make play time string to display
    char playTimeStr1[30] = "Play Time: ";
    char playTimeStr2[30];

    sprintf(playTimeStr2, "%d", stats.playTime);
    strcat(playTimeStr1, playTimeStr2);

    LCD.Clear();
    LCD.WriteAt(moneyStr1, 50, 50);
    LCD.WriteAt(mpsStr1, 50, 80);
    LCD.WriteAt(playTimeStr1, 50, 110);

    drawBackButton();
}

void drawHowToPlay(){
    LCD.Clear();
    drawBackButton();
    LCD.SetFontColor(WHITE);
    
    LCD.WriteAt("Click the buckeye to ", 20, 50);
    LCD.WriteAt("aquire money which can", 20, 70);
    LCD.WriteAt("be used to buy upgrades", 20, 90);
    LCD.WriteAt("and buildings, as you ", 20, 110);
    LCD.WriteAt("travel through time ", 20, 130);
    LCD.WriteAt("building Ohio State", 20, 150);
    LCD.WriteAt("yourself", 20, 170);
    

}

void drawCredits(){
    LCD.Clear();
    drawBackButton();
    LCD.SetFontColor(WHITE);

    LCD.WriteAt("This game was created", 20, 50);
    LCD.WriteAt("by Nathan Cain and", 20, 70);
    LCD.WriteAt("Spencer Minnery, and", 20, 90);
    LCD.WriteAt("was inspired by cookie", 20, 110);
    LCD.WriteAt("clicker.", 20, 130);
}

void drawBackButton(){
    FEHImage backButton;
    backButton.Open("images/backbutton2.png");
    backButton.Draw(0,0);
    backButton.Close();
}

void drawGrassBackground(){
    FEHImage grassBackground;
    grassBackground.Open("images/grassBackground.png");
    grassBackground.Draw(0,0);
    grassBackground.Close();
}

void drawTrees(){
    //initialize values
    /* Note that the tree image is drawn in the center of a
    320x240 image, so for the tree to appear in the top left
    of the screen, the tree must be drawn at negative coordinates.
    subtract about 140 from x and 80 from y for where you want to
    place the trees*/
    const int treePosArrLength = 4; //how many trees to draw -- need to update number of coordinates
    int xPositionsForTrees[treePosArrLength] = {-140,-140,100,100};
    int yPositionsForTrees[treePosArrLength] = {-80,100,90,-80};
    FEHImage trees[treePosArrLength];
    

    //create a new tree FEHImage object for each item in the trees array
    for (int i = 0; i < treePosArrLength;i++) {
        FEHImage tree;
        trees[i] = tree;

        //determine whether to display tree1 or tree2
        int currentTime = time(NULL);
        if (currentTime%2==0) {
            tree.Open("images/tree1.png");
        }
        else {
            tree.Open("images/tree2.png");
        }

        //draw tree at coordinates
        int x = xPositionsForTrees[i];
        int y = yPositionsForTrees[i];
        tree.Draw(x,y);
        tree.Close();
        
    }
}

GameController::GameController(){
    gameState = 'm';
    stats.money = 0;
    stats.moneyPerSecond = 0;
    stats.playTime = 0;
}

float* GameController::getxRef(){
    return &xTouched;
}

float* GameController::getyRef(){
    return &yTouched;
}

// returns true if the input x and y values are within the boundaries of the button
bool GameController::isButtonTouched(struct Button button){
    bool isClicked = false;
    if (button.upperLeft.x <= xTouched && xTouched <= button.bottomRight.x && button.upperLeft.y <= yTouched && yTouched <= button.bottomRight.y ){
        isClicked = true;
    }
    return isClicked;
}

char GameController::getGameState(){
    return gameState;
}

void GameController::setGameState(char newGameState){
    gameState = newGameState;
}






