#include "headers.h"




platform::platform() {
    movement=STATIC;
    xPos=0;
    yPos=0;
    traveled=0;
}

float platform::getX() const {
    return xPos;
}

float platform::getY() const {
    return yPos;
}

void platform::setPos(float x, float y) {
    xPos=x;
    yPos=y;
}

void platform::setMove(platformMovement move) {
    switch(move) {
        case UP:
            movement=UP;
        break;
        case DOWN:
            movement=DOWN;
        break;
        case STATIC:
            movement=STATIC;
        break;
    }
}

int platform::getMove() {
    return movement;
}

int platform::getTraveled() {
    return traveled;
}

void platform::Travel(bool k) {
    if(k==1) {
        traveled--;
    } else {
        traveled++;
    }
}


void enemy::setPos(float x, float y) {
    xPos=x;
    yPos=y;
}

float enemy::getX() {
    return xPos;
}

float enemy::getY() {
    return yPos;
}



gameMap::gameMap() {
    capMouse=0;
}

void gameMap::newPlat(int x, int y) {
    platform newPlatform;
    newPlatform.setPos(x,y);
    platscore++;
    if(platscore%20==0) {
        newPlatform.setMove(DOWN);
    } else {
        newPlatform.setMove(STATIC);
    }
    if(platscore%15==0 && newPlatform.getMove()==STATIC) {
        enemy newEnem;
        int rngX = rngPlat(x,x+platwid-enemywid);
        newEnem.setPos(rngX,y-enemyhig);
        enemyVec.push_back(newEnem);
    }
    if(springplat==1) {
        springplat=0;
        springBoots newboots;
        int rngX = rngPlat(x,x+platwid-bootwid);
        newboots.setPos(rngX, y-boothig);
        bootVec.push_back(newboots);
    }
    platVec.push_back(newPlatform);
}

void gameMap::getMousePos(int x, int y) {
    mouseX=x;
    mouseY=y;
}

int gameMap::getmouseX() const {
    return mouseX;
}

int gameMap::getmouseY() const {
    return mouseY;
}

int gameMap::getCap() const {
    return capMouse;
}

void gameMap::toggleCap() {
    if(capMouse==1) {
        capMouse=0;
    } else {
        capMouse=1;
    }
}

int gameMap::moveCamera(long double dist, int playerHeight, int falling) {
    if(playerHeight==1 && falling==0) {
        for(int i=0;i<platVec.size();i++) {
        platVec[i].setPos(platVec[i].getX(),platVec[i].getY()-dist);
        }
        for(int i=0;i<bullVec.size();i++) {
            bullVec[i].setPos(bullVec[i].getX(),bullVec[i].getY()-dist);
        }
        for(int i=0;i<bootVec.size();i++) {
            bootVec[i].setPos(bootVec[i].getX(),bootVec[i].getY()-dist);
        }
        for(int i=0;i<enemyVec.size();i++) {
            enemyVec[i].setPos(enemyVec[i].getX(),enemyVec[i].getY()-dist);
        }
        return 1;
    } else {
        return 0;
    }
}

float gameMap::getPlatX(int i) {
    return platVec[i].getX();
}

float gameMap::getPlatY(int i) {
    return platVec[i].getY();
}

int gameMap::getPlatCount() {
    return platVec.size();
}

int gameMap::checkPlatCol(int xa, int xb, int ya, int yb, int platw, int plath) {

    for(int i=0;i<platVec.size();i++) {
        if(xa>(platVec[i].getX()+platw) || xb<platVec[i].getX()) {
        } else {
            if(yb>=(platVec[i].getY()) && yb<=(platVec[i].getY()+plath)) {
                return 1;
            }
        }
    }
    return 0;
}

int gameMap::checkSpringCol(int xa, int xb, int ya, int yb) {
    for(int i=0;i<bootVec.size();i++) {
        if(xa>(bootVec[i].getX()+bootwid) || xb<bootVec[i].getX()) {
        }else {
            if(yb<bootVec[i].getY() || ya>(bootVec[i].getY()+boothig)) {
            } else {
                return 1;
            }
        }
    }
    return 0;
}

int gameMap::checkEnemyCol(int xa, int xb, int ya, int yb, int enemyW, int enemyH) {
    for(int i=0;i<enemyVec.size();i++) {
        if(xa>(enemyVec[i].getX()+enemyW) || xb<enemyVec[i].getX()) {
        }else {
            if(yb<enemyVec[i].getY() || ya>(enemyVec[i].getY()+enemyH)) {
            } else {
                return 1;
            }
        }
    }
    return 0;
}

int gameMap::checkEnemyKill(int xa, int xb, int ya, int yb, int enemyW, int enemyH) {
    for(int i=0;i<enemyVec.size();i++) {
        if(xa>(enemyVec[i].getX()+enemyW) || xb<enemyVec[i].getX()) {
        } else {
            if(yb>=(enemyVec[i].getY()) && yb<=(enemyVec[i].getY()+enemyH)) {
                return 1;
            }
        }
    }
    return 0;
}







void gameMap::newBullet(int playerX, int playerY, int mouseXPos, int mouseYPos) {
    bullet newBull;
    float vectorX = mouseXPos-playerX;
    float vectorY = mouseYPos-playerY;
    newBull.setPos(playerX, playerY);
    if(abs(vectorX)>abs(vectorY)) {
        newBull.setVec(2*vectorX/abs(vectorX), 2*vectorY/abs(vectorX));
    } else {
        newBull.setVec(2*vectorX/abs(vectorY), 2*vectorY/abs(vectorY));
    }
    bullVec.push_back(newBull);
}

int gameMap::getBullCount() {
    return bullVec.size();
}

int gameMap::getBullX(int i) {
    return bullVec[i].getX();
}

int gameMap::getBullY(int i) {
    return bullVec[i].getY();
}

void gameMap::updateBullet(int w, int h, int bgw, int bgh) {
    for(int i=0;i<bullVec.size();i++) {
        bullVec[i].setPos(bullVec[i].getX()+bullVec[i].getvecX(), bullVec[i].getY()+bullVec[i].getvecY());
        if(bullVec[i].getY()<h/2-bgh/2 || bullVec[i].getY()>h/2+bgh/2) {
            bullVec.erase(bullVec.begin()+i);
        }
        if(bullVec[i].getX()>(w/2+bgw/2)) {
            bullVec[i].setPos(w/2-bgw/2, bullVec[i].getY());
        }
        if(bullVec[i].getX()<(w/2-bgw/2)) {
            bullVec[i].setPos(w/2+bgw/2, bullVec[i].getY());
        }
    }
}

int gameMap::rngPlat(int a, int b) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist(a,b);
    int rng = dist(mt);
    return rng;
}

void gameMap::popFrontPlat() {
   platVec.erase(platVec.begin());
}

void gameMap::setBullPos(int x, int y, int i) {
    bullVec[i].setPos(x, y);
}


int gameMap::getPlatScore() {
    return platscore;
}

int gameMap::getPlatMove(int i) {
    return platVec[i].getMove();
}

void gameMap::setPlatPos(float x, float y, int i) {
    platVec[i].setPos(x, y);
}

int gameMap::getTraveled(int i) {
    return platVec[i].getTraveled();
}

void gameMap::Travel(int k, int i) {
    platVec[i].Travel(k);
}

void gameMap::setPlatMove(int i, platformMovement move) {
    platVec[i].setMove(move);
}

void gameMap::newBoots(float x, float y) {
    springBoots boots;
    boots.setPos(x,y);
    bootVec.push_back(boots);
}

int gameMap::getBootCount() {
    return bootVec.size();
}

float gameMap::getBootX(int i) {
    return bootVec[i].getX();
}

float gameMap::getBootY(int i) {
    return bootVec[i].getY();
}

int gameMap::getEnemyCount() {
    return enemyVec.size();
}

float gameMap::getEnemyX(int i) {
    return enemyVec[i].getX();
}

float gameMap::getEnemyY(int i) {
    return enemyVec[i].getY();
} 

void gameMap::updateEnemy(int h, int bgh, int enemyH, int enemyW, int bulletDim) {
    for(int i=0;i<enemyVec.size();i++) {
        if(enemyVec[i].getY()>h/2+bgh/2) {
            popEnemy();
        }
        for(int j=0;j<bullVec.size();j++) {
            if(bullVec[j].getX()+bulletDim<enemyVec[i].getX() || bullVec[j].getX()>enemyVec[i].getX()+enemyW) {
            } else {
                if(bullVec[j].getY()>enemyVec[i].getY()+enemyH || bullVec[j].getY()+bulletDim<enemyVec[i].getY()) {
                } else {
                    popEnemy();
                }
            }
        }
    }
}

void gameMap::popEnemy() {
    enemyVec.erase(enemyVec.begin());
}

void gameMap::gameInit(int enemywidth, int enemyheight, int bootwidth, int bootheight, int platwidth, int platheight) {
    enemywid=enemywidth;
    enemyhig=enemyheight;
    bootwid=bootwidth;
    boothig=bootheight;
    platwid=platwidth;
    plathig=platheight;
    platscore=0;
    springplat=0;
}

void gameMap::setSpringPlat(int i) {
    springplat=i;
}

void gameMap::popBoot() {
    bootVec.pop_back();
}








void springBoots::setPos(float x, float y) {
    xPos=x;
    yPos=y;
}

float springBoots::getX() {
    return xPos;
}

float springBoots::getY() {
    return yPos;
}


void bullet::setPos(float x, float y) {
    xPos=x;
    yPos=y;
}

float bullet::getX() {
    return xPos;
}

float bullet::getY() {
    return yPos;
}

void bullet::setVec(float x, float y) {
    vecX=x;
    vecY=y;
}

float bullet::getvecX() {
    return vecX;
}

float bullet::getvecY() {
    return vecY;
}





doodle::doodle() {
    xPos=0;
    yPos=0;
    dir=RIGHT;
    mL=0;
    mR=0;
    time=getTickCount();
    falling=1;
    jumpSpeed=0.017;
    basejump=jumpSpeed;
    gap=1;
}

void doodle::initDoodle(float x, long double gconst, int halfH) {
    xstep=x;
    g=gconst;
    h=halfH;
    yPos=h;
    isDead=0;
}

void doodle::toggleSpring() {
    if(basejump==jumpSpeed) {
        jumpSpeed*=sqrt(2);
    } else {
        jumpSpeed=basejump;
    }
}

long double doodle::getbase() {
    return basejump;
}

long double doodle::getjump() {
    return jumpSpeed;
}

void doodle::updatePlayer(int limit) {
    if(mR==1) {
        changeDir(RIGHT);
        xPos+=xstep;
    } else if(mL==1) {
        changeDir(LEFT);
        xPos-=xstep;
    }
    if(time==0) {
        time+=getTickCount();
    }
    deltaT=time-getTickCount();
    if(falling==1) {
        
        speed=g*deltaT;
        dist=speed*deltaT;
        yPos+=dist;
    } else {
        speed=jumpSpeed+g*deltaT;
        if(speed<=0) {
            falling=1;
            time=getTickCount();
        }
    }
    dist=speed*deltaT;
    if(yPos<=limit) {
        yPos=limit-1;
    } else {
        yPos+=dist;
    }
}


void doodle::platJump() {
    falling=0;
    speed=jumpSpeed;
}

void doodle::changeDir(playerDir direction) {
    dir=direction;
}


void doodle::toggleMove(FRKey k) {
    switch(k) {
        case FRKey::RIGHT:
            if(mR==0) {
                mR=1;
            } else {
                mR=0;
            }
        break;
        case FRKey::LEFT:
            if(mL==0) {
                mL=1;
            } else {
                mL=0;
            }
    }
}


int doodle::getPlayerX() {
    return xPos;
}

int doodle::getPlayerY() {
    return yPos;
}

int doodle::getDir() {
    return dir;
}

void doodle::setPlayerPos(int x, int y) {
    xPos=x;
    yPos=y;
}

int doodle::getFalling() {
    return falling;
}

long double doodle::getDist() {
    return dist;
}

int doodle::getDeath() {
    return isDead;
}

void doodle::toggleDeath() {
    if(isDead==1) {
        isDead=0;
    } else {
        isDead=1;
    }
}

void doodle::addGap() {
    gap-=dist/5;
}


int doodle::getGap() {
    return gap;
}




display::display() {
    txtVec.resize(20);
}

void display::checkBounds() {
    if(getPlayerX()<(width/2)-(bgwidth/2)-(playerW*2)/3) {
        setPlayerPos((width/2)+(bgwidth/2)-playerW/2, getPlayerY());
    }
    if(getPlayerX()>(width/2)+(bgwidth/2)-(playerW/3)) {
        setPlayerPos((width/2)-(bgwidth/2)-playerW/2, getPlayerY());
    }
    if(getFalling()==1) {
        if(checkPlatCol(getPlayerX()+(playerW/3), getPlayerX()+(playerW*2/3), getPlayerY(), getPlayerY()+playerH, platW, platH*0.5)==1) {
            platJump();
        }
        if(checkEnemyKill(getPlayerX()+(playerW/3), getPlayerX()+(playerW/3), getPlayerY(), getPlayerY()+playerH, enemyW, enemyH*0.3)) {
            popEnemy();
        }
    }
    if(getPlayerY()>height/2+bgheight/2) {
        toggleDeath();
    }
    if(checkEnemyCol(getPlayerX(), getPlayerX()+playerW, getPlayerY(), getPlayerY()+playerH, enemyW, enemyH)==1) {
        toggleDeath();
    }
    if(checkSpringCol(getPlayerX(), getPlayerX()+playerW, getPlayerY(), getPlayerY()+playerH)==1 && getbase()==getjump()) {
        popBoot();
        springtime=getTickCount();
        toggleSpring();
    }
}

void display::read(int argc, char *argv[]) {
    if(argc>1) {
        if(argv[1][0]=='-' && argv[1][1]=='w') {
            if(argc==4 && (atoi(argv[2])>=200 && atoi(argv[3])>=200)) {
                width = atoi(argv[2]);
                height = atoi(argv[3]);
            } else {
                height=800;
                width=600;
            }
        } else {
            std::cout<<"Invalid Window Size"<<std::endl;
            exit(0);
        }
    } else {
        height=800;
        width=600;
    }
}

void display::initDisplay() {
    springdelta=1000;
    gapClone=0;
    getSpriteSize(txtVec[1], platW, platH);
    getSpriteSize(txtVec[2], playerW, playerH);
    platScale = float(bgwidth)/(5*platW);
    platW=platW*platScale;
    platH=platH*platScale;
    setSpriteSize(txtVec[1], platW, platH);
    for(int i=0;i<5;i++) {
        newPlat((width/2)-(bgwidth/2)+i*platW,height-platH);
    }
    playerW=platW;
    playerH=platW;
    setSpriteSize(txtVec[2], platW, platW);
    setSpriteSize(txtVec[3], platW, platW);
    bgx=(width-bgwidth)/2;
    bgy=(height-bgheight)/2;
    setSpriteSize(txtVec[4], platW/5, platW/5);
    platlevel=height/2+bgheight/2-platH;
}

int display::getWinHeight() {
    return height;
}

int display::getWinWidth() {
    return width;
}

void display::loadTxt() {
    txtVec[0] = createSprite("../Project/data/bck@2x.png");
    if(height>width) {
        bgwidth=width;
        bgheight=width*4/3;
    } else {
        bgwidth=height*3/4;
        bgheight=height;
    }
    setSpriteSize(txtVec[0],bgwidth,bgheight);
    txtVec[1] = createSprite("../Project/data/platform.png");
    txtVec[2] = createSprite("../Project/data/underwater-right@2x.png");
    txtVec[3] = createSprite("../Project/data/underwater-left@2x.png");
    txtVec[4] = createSprite("../Project/data/bullet.png");
    txtVec[5] = createSprite("../Project/data/0.png");
    txtVec[6] = createSprite("../Project/data/1.png");
    txtVec[7] = createSprite("../Project/data/2.png");
    txtVec[8] = createSprite("../Project/data/3.png");
    txtVec[9] = createSprite("../Project/data/4.png");
    txtVec[10] = createSprite("../Project/data/5.png");
    txtVec[11] = createSprite("../Project/data/6.png");
    txtVec[12] = createSprite("../Project/data/7.png");
    txtVec[13] = createSprite("../Project/data/8.png");
    txtVec[14] = createSprite("../Project/data/9.png");
    txtVec[15] = createSprite("../Project/data/boot.png");
    txtVec[16] = createSprite("../Project/data/ooga-pada@2x.png");
    setSpriteSize(txtVec[5],bgwidth/20, bgheight/20);
    setSpriteSize(txtVec[6],bgwidth/20, bgheight/20);
    setSpriteSize(txtVec[7],bgwidth/20, bgheight/20);
    setSpriteSize(txtVec[8],bgwidth/20, bgheight/20);
    setSpriteSize(txtVec[9],bgwidth/20, bgheight/20);
    setSpriteSize(txtVec[10],bgwidth/20, bgheight/20);
    setSpriteSize(txtVec[11],bgwidth/20, bgheight/20);
    setSpriteSize(txtVec[12],bgwidth/20, bgheight/20);
    setSpriteSize(txtVec[13],bgwidth/20, bgheight/20);
    setSpriteSize(txtVec[14],bgwidth/20, bgheight/20);
    setSpriteSize(txtVec[15],bgwidth/20, bgwidth/20);
    getSpriteSize(txtVec[15], bootW, bootH);
    setSpriteSize(txtVec[16],bgwidth/10, bgheight/10);
    getSpriteSize(txtVec[16], enemyW, enemyH);
}

void display::draw() {
    drawSprite(txtVec[0], bgx, bgy);
    for(int i=0;i<getPlatCount();i++) {
        drawSprite(txtVec[1], getPlatX(i), getPlatY(i));
    }
    for(int i=0;i<getBullCount();i++) {
        drawSprite(txtVec[4], getBullX(i), getBullY(i));
    }
    if(getDir()==RIGHT) {
        drawSprite(txtVec[2],getPlayerX(), getPlayerY());
    } else {
        drawSprite(txtVec[3],getPlayerX(), getPlayerY());
    }
    for(int i=0;i<getBootCount();i++) {
        drawSprite(txtVec[15], getBootX(i), getBootY(i));
    }
    for(int i=0;i<getEnemyCount();i++) {
        drawSprite(txtVec[16], getEnemyX(i), getEnemyY(i));
    }
    for(int i=0;i<scoreArr.size();i++) {
        switch(scoreArr[i]) {
            case 0:
                drawSprite(txtVec[5], (width/2-bgwidth/2)+(i*bgwidth/20), height/2-bgheight/2);
            break;
            case 1:
                drawSprite(txtVec[6], (width/2-bgwidth/2)+(i*bgwidth/20), height/2-bgheight/2);
            break;
            case 2:
                drawSprite(txtVec[7], (width/2-bgwidth/2)+(i*bgwidth/20), height/2-bgheight/2);
            break;
            case 3:
                drawSprite(txtVec[8], (width/2-bgwidth/2)+(i*bgwidth/20), height/2-bgheight/2);
            break;
            case 4:
                drawSprite(txtVec[9], (width/2-bgwidth/2)+(i*bgwidth/20), height/2-bgheight/2);
            break;
            case 5:
                drawSprite(txtVec[10], (width/2-bgwidth/2)+(i*bgwidth/20), height/2-bgheight/2);
            break;
            case 6:
                drawSprite(txtVec[11], (width/2-bgwidth/2)+(i*bgwidth/20), height/2-bgheight/2);
            break;
            case 7:
                drawSprite(txtVec[12], (width/2-bgwidth/2)+(i*bgwidth/20), height/2-bgheight/2);
            break;
            case 8:
                drawSprite(txtVec[13], (width/2-bgwidth/2)+(i*bgwidth/20), height/2-bgheight/2);
            break;
            case 9:
                drawSprite(txtVec[14], (width/2-bgwidth/2)+(i*bgwidth/20), height/2-bgheight/2);
            break;
        }
    }
    for(int i=0;i<platArr.size();i++) {
        switch(platArr[i]) {
            case 0:
                drawSprite(txtVec[5], (width/2-bgwidth/2)+(i*bgwidth/20), (height/2-bgheight/2)+(bgheight/20));
            break;
            case 1:
                drawSprite(txtVec[6], (width/2-bgwidth/2)+(i*bgwidth/20), (height/2-bgheight/2)+(bgheight/20));
            break;
            case 2:
                drawSprite(txtVec[7], (width/2-bgwidth/2)+(i*bgwidth/20), (height/2-bgheight/2)+(bgheight/20));
            break;
            case 3:
                drawSprite(txtVec[8], (width/2-bgwidth/2)+(i*bgwidth/20), (height/2-bgheight/2)+(bgheight/20));
            break;
            case 4:
                drawSprite(txtVec[9], (width/2-bgwidth/2)+(i*bgwidth/20), (height/2-bgheight/2)+(bgheight/20));
            break;
            case 5:
                drawSprite(txtVec[10], (width/2-bgwidth/2)+(i*bgwidth/20), (height/2-bgheight/2)+(bgheight/20));
            break;
            case 6:
                drawSprite(txtVec[11], (width/2-bgwidth/2)+(i*bgwidth/20),(height/2-bgheight/2)+(bgheight/20));
            break;
            case 7:
                drawSprite(txtVec[12], (width/2-bgwidth/2)+(i*bgwidth/20), (height/2-bgheight/2)+(bgheight/20));
            break;
            case 8:
                drawSprite(txtVec[13], (width/2-bgwidth/2)+(i*bgwidth/20), (height/2-bgheight/2)+(bgheight/20));
            break;
            case 9:
                drawSprite(txtVec[14], (width/2-bgwidth/2)+(i*bgwidth/20), (height/2-bgheight/2)+(bgheight/20));
            break;
        }
    }
}

float display::calcMove() {
    return float(bgwidth)/float(200);
}

long double display::calcFall() {
    return 2*pow(10,-5);
}

int display::getInitPlayerY() {
    return (height/2);
}

void display::placeDoodle() {
    setPlayerPos((width/2)-(playerW/2), getInitPlayerY());
}

int display::getPlayerMiddleX() {
    return getPlayerX()+playerW/2;
}

int display::getPlayerMiddleY() {
    return getPlayerY()+playerH/2;
}

int display::getBulletSize() {
    int a;
    getSpriteSize(txtVec[4], a, a);
    return a;
}

void display::updatePlatform() {
    for(int i=0;i<getPlatCount();i++) {
        if(getPlatMove(i)==DOWN) {
            setPlatPos(getPlatX(i), getPlatY(i)+1, i);
            Travel(1, i);
        }
        if(getPlatMove(i)==UP) {
            setPlatPos(getPlatX(i), getPlatY(i)-1, i);
            Travel(0, i);
        }
        if(abs(getTraveled(i))>bgwidth/3) {
            if(getPlatMove(i)==UP) {
                setPlatMove(i, DOWN);
            } else {
                setPlatMove(i, UP);
            }
        }
        if(getPlatY(i)>(height/2+bgheight*2/3)) {
            popFrontPlat();
        }
    }
    if(platlevel>height/2-bgheight/2) {
        while(getPlatY(getPlatCount()-1)>height/2-bgheight/2) {
            int x =rngPlat(getbgheight()/12, getbgheight()/6);
            platlevel-=x;
            newPlat(rngPlat((getWinWidth()/2-getbgwidth()/2)+platW, (getWinWidth()/2+getbgwidth()/2))-platW,platlevel);
        }
    }
    while(getPlatY(getPlatCount()-1)>height/2-bgheight/2) {
        int y =rngPlat(getbgheight()/12, getbgheight()/6);
        int x = rngPlat((getWinWidth()/2-getbgwidth()/2)+platW, (getWinWidth()/2+getbgwidth()/2))-platW;
        newPlat(x ,height/2-bgheight/2-y);
        if(gapClone>=1000) {
            gapClone=0;
            setSpringPlat(1);
        }
    }
    scoreArr.clear();
    unsigned int n = getGap();
    while (n!=0) {
        scoreArr.insert(scoreArr.begin(), n%10);
        n/=10;
    }
    platArr.clear();
    n = getPlatScore();
    while(n!=0) {
        platArr.insert(platArr.begin(), n%10);
        n/=10;
    }
}

int display::getbgheight() {
    return bgheight;
}

int display::getbgwidth() {
    return bgwidth;
}

int display::checkHeight() {
    if(getPlayerY()<height/3) {
        return 1;
    } else {
        return 0;
    }
}

int display::getEnemyW() {
    return enemyW;
}

int display::getEnemyH() {
    return enemyH;
}

int display::getplatHeight() {
    return platH;
}

int display::getplatWidth() {
    return platW;
}

void display::addCloneGap() {
    gapClone-=getDist()/5;
}

int display::getBootW() {
    return bootW;
}

int display::getBootH() {
    return bootH;
}

void display::checkSpringTime() {
    if(getTickCount()>springtime+springdelta && getbase()!=getjump()) {
        toggleSpring();
    }
}