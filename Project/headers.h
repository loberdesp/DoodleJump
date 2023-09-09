#include "../Framework/inc/Framework.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <random>


enum platformMovement {STATIC, UP, DOWN};

class platform {
	float xPos, yPos;
    platformMovement movement;
	int traveled;
    
    public:
        platform();
		float getX() const;
		float getY() const;
		void setPos(float x, float y);
		void setMove(platformMovement move);
		int getMove();
		int getTraveled();
		void Travel(bool k);
};



class bullet {
	float xPos, yPos;
	float vecX, vecY;

	public:
	void setPos(float x, float y);
	float getX();
	float getY();
	float getvecX();
	float getvecY();
	void setVec(float x, float y);
};

class springBoots {
	float xPos, yPos;
	
	public:
		void setPos(float x, float y);
		float getX();
		float getY();
};

class enemy {
	float xPos, yPos;
	float xSize, ySize;

	public:
		void setPos(float x, float y);
		float getX();
		float getY();
};

class gameMap {
	std::vector<platform> platVec;
	std::vector<bullet> bullVec;
	std::vector<springBoots> bootVec;
	std::vector<enemy> enemyVec;
	int mouseX, mouseY;
	bool capMouse;
	float score;
	int platscore;
	int enemywid, enemyhig, bootwid, boothig, platwid, plathig;
	int springplat;


    public:
		gameMap();
		void gameInit(int enemywidth, int enemyheight, int bootwidth, int bootheight, int platwidth, int platheight);
		void newPlat(int x, int y);
		void popFrontPlat();
		void getMousePos(int x, int y);
		int getmouseX() const;
		int getmouseY() const;
		int getCap() const;
		void toggleCap();
		int moveCamera(long double dist, int playerHeight, int falling);
		float getPlatX(int i);
		float getPlatY(int i);
		int getPlatCount();
		int checkPlatCol(int xa, int xb, int ya, int yb, int platw, int plath);
		void newBullet(int playerX, int playerY, int mouseXPos, int mouseYPos);
		int getBullCount();
		int getBullX(int i);
		int getBullY(int i);
		void updateBullet(int w, int h, int bgw, int bgh);
		int rngPlat(int a, int b);
		void setBullPos(int x, int y, int i); 
		int getPlatScore();
		int getPlatMove(int i);
		void setPlatMove(int i, platformMovement move);
		void setPlatPos(float x, float y, int i);
		int getTraveled(int i);
		void Travel(int k, int i);
		void newBoots(float x, float y);
		int getBootCount();
		float getBootX(int i);
		float getBootY(int i);
		int getEnemyCount();
		float getEnemyX(int i);
		float getEnemyY(int i);
		int checkEnemyCol(int xa, int xb, int ya, int yb, int enemyw, int enemyh);
		void updateEnemy(int h, int bgh, int enemyH, int enemyW, int bulletDim);
		int checkEnemyKill(int xa, int xb, int ya, int yb, int enemyw, int enemyh);
		void popEnemy();
		void setSpringPlat(int i);
		int checkSpringCol(int xa, int xb, int ya, int yb);
		void popBoot();
};



enum playerDir {LEFT, RIGHT};



class doodle : public bullet {
	float xPos,yPos;
	float xstep;
	playerDir dir;
	long double g, speed, dist, jumpSpeed, basejump;
	bool mL, mR;
	int time, deltaT;
	bool falling;
	int h;
	bool isDead;
	long double gap;
	bool springed;

	public:
		doodle();
		void initDoodle(float pos, long double g, int halfH);
		void updatePlayer(int limit);
		void toggleMove(FRKey k);
		int getPlayerX();
		int getPlayerY();
		int getDir();
		void changeDir(playerDir direction);
		void setPlayerPos(int x, int y);
		int getFalling();
		void platJump();
		long double getDist();
		void toggleDeath();
		int getDeath();
		void addGap();
		int getGap();
		void toggleSpring();
		long double getjump();
		long double getbase();
};


class display : public gameMap, public doodle {
	int width, height;
	int bgwidth, bgheight;
	std::vector<Sprite*> txtVec;
	float platScale;
	int playerW, playerH;
	int platW, platH;
	int bootW, bootH;
	int bgx, bgy;
	int enemyW, enemyH;
	long double platlevel;
	std::vector<int> scoreArr;
	std::vector<int> platArr;
	long double gapClone;
	int springtime, springdelta;

	public:
		display();
		void initDisplay();
		void loadTxt();
		void read(int argc, char *argv[]);
		int getWinWidth();
		int getWinHeight();
		void draw();
		void checkBounds();
		float calcMove();
		long double calcFall();
		int getInitPlayerY();
		void placeDoodle();
		int getPlayerMiddleX();
		int getPlayerMiddleY();
		int getBulletSize();
		void updatePlatform();
		int getbgwidth();
		int getbgheight();
		int checkHeight();
		int getEnemyW();
		int getEnemyH();
		int getplatHeight();
		int getplatWidth();
		void addCloneGap();
		int getBootW();
		int getBootH();
		void checkSpringTime();
};




class MyFramework : public Framework {

gameMap map;
doodle player;
display disp;

public:

    MyFramework(int argc, char *argv[]) {
        disp.read(argc, argv);
    }

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = disp.getWinWidth();
		height = disp.getWinHeight();
		fullscreen = false;
	}

	virtual bool Init() {
		disp.loadTxt();
		disp.initDisplay();
		disp.initDoodle(disp.calcMove(), disp.calcFall(), disp.getInitPlayerY());
		disp.placeDoodle();
		disp.gameInit(disp.getEnemyW(), disp.getEnemyH(), disp.getBootW(), disp.getBootH(), disp.getplatWidth(), disp.getplatHeight());
		return true;
	}

	virtual void Close() {
		
	}

	virtual bool Tick() {
		disp.updatePlatform();
		disp.checkSpringTime();
		disp.updatePlayer(disp.getWinHeight()/3);
		disp.checkBounds();
		disp.updateBullet(disp.getWinWidth(), disp.getWinHeight(), disp.getbgwidth(), disp.getbgheight());
		disp.updateEnemy(disp.getWinHeight(), disp.getbgheight(), disp.getEnemyH(), disp.getEnemyW(), disp.getBulletSize());
		if(disp.moveCamera(disp.getDist(), disp.checkHeight(), disp.getFalling())==1) {
			disp.addGap();
			disp.addCloneGap();
		}
		disp.draw();
		return disp.getDeath();
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
			map.getMousePos(x,y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if(button==FRMouseButton::LEFT && isReleased==1) {
			disp.newBullet(disp.getPlayerMiddleX(), disp.getPlayerMiddleY(), map.getmouseX()-(disp.getBulletSize()/2), map.getmouseY()-(disp.getBulletSize()/2));
		}
		if(button==FRMouseButton::RIGHT && isReleased==1) {
		}
	}

	virtual void onKeyPressed(FRKey k) {
		if(k==FRKey::RIGHT) {
			disp.toggleMove(FRKey::RIGHT);
		}
		if(k==FRKey::LEFT) {
			disp.toggleMove(FRKey::LEFT);
		}
	}

	virtual void onKeyReleased(FRKey k) {
		if(k==FRKey::RIGHT) {
			disp.changeDir(RIGHT);
			disp.toggleMove(FRKey::RIGHT);
		}
		if(k==FRKey::LEFT) {
			disp.toggleMove(FRKey::LEFT);
		}
		if(k==FRKey::UP) {
			disp.toggleSpring();
		}
	}
	
	virtual const char* GetTitle() override
	{
		return "Doodle Jump";
	}
};