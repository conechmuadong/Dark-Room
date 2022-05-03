#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include<bits/stdc++.h>
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(900, 600), "Re_Schola");

Sprite in_bgmenu;
Texture stand;
Sprite stands(stand);
Texture animation;
Sprite animated(animation);
Clock animationtimer;
IntRect curframe;
float speedtimer=0.5f;
int speed=40;
/// 0=up 1=down 2=right 3=left
int direction=2;
/// do vat
Texture lo;
Texture box;
Texture blank;
int vitri[21][14];
Sprite indovat[1000];
/// do lech hinh nhan vat
int deltax=30;
int deltay=46;
/// so do vat
int demdovat=4;
void ve() {
    window.clear();
    window.draw(in_bgmenu);
    for(int i=0; i<21*14; i++)
        window.draw(indovat[i]);
    window.draw(animated);
    window.display();
}
int check_move_possible(int directions) {
    int posx=animated.getPosition().x;
    int posy=animated.getPosition().y;
    posx+=40-deltax;
    posy+=34;
    int debug=1;
    switch (directions) {
    case 1: {
        posy+=40*debug;
        break;
    }
    case 0: {
        posy-=40*debug;
        break;
    }
    case 2: {
        posx+=40*debug;
        break;
    }
    case 3: {
        posx-=40*debug;
        break;
    }
    }
    cout<<"1, "<<posx/40<<" "<<posy/40<<" "<<vitri[posx/40][posy/40]<<endl<<"-----------------"<<endl;
    if(vitri[posx/40][posy/40]==1||vitri[posx/40][posy/40]==3) {
        switch (directions) {
        case 1: {
            posy+=40;
            break;
        }
        case 0: {
            posy-=40;
            break;
        }
        case 2: {
            posx+=40;
            break;
        }
        case 3: {
            posx-=40;
            break;
        }
        }
        cout<<"2, "<<posx/40<<" "<<posy/40<<endl;
        if(vitri[posx/40][posy/40]==1||vitri[posx/40][posy/40]==3)
            return 0;
        if(posx/40-1<0||posx/40+1>21||posy/40-1<0||posy/40+1>14)
            return 0;
    }

    //cout<<posx<<" "<<posy<<endl;
//    if(posx<0||posx/40>21||posy<0||posy/40>14||vitri[posx][posy]==1)
//        return 0;
    return 1;
}
int ktketthucgame() {
    int dem=0;
    for(int i=0; i<21; i++)
        for(int j=0; j<14; j++)
            if(vitri[i][j]==3)
                dem++;
                cout<<demdovat<<endl;
    if(dem==demdovat)
        return 1;
    return 0;
}
void startdovat() {
    lo.loadFromFile("data/item/hole.png");
    blank.loadFromFile("data/item/blank.png");
    box.loadFromFile("data/item/box.png");
    int chay=0;
    for(int i=0; i<21; i++)
        for(int j=0; j<14; j++) {
            if(vitri[i][j]==1 || vitri[i][j]==3) {
                //cout<<i<<" "<<j<<endl;
                indovat[14*(i-0)+j].setTexture(box);
                indovat[14*(i-0)+j].setPosition(40*i,40*j);
                chay++;
            }
            if(vitri[i][j]==0) {
                indovat[14*(i-0)+j].setTexture(blank);
                indovat[14*(i-0)+j].setPosition(40*i,40*j);
                chay++;
            }
            if(vitri[i][j]==2) {
                indovat[14*(i-0)+j].setTexture(lo);
                indovat[14*(i-0)+j].setPosition(40*i,40*j);
                chay++;
            }
        }
}
void resetbang() {
    for(int i=0; i<21; i++)
        for(int j=0; j<14; j++) {
            if(vitri[i][j]==1||vitri[i][j]==3) {
                indovat[14*(i-0)+j].setTexture(box);
                indovat[14*(i-0)+j].setPosition(40*i,40*j);
            }
            if(vitri[i][j]==0) {
                indovat[14*(i-0)+j].setTexture(blank);
                indovat[14*(i-0)+j].setPosition(40*i,40*j);
            }
            if(vitri[i][j]==2) {
                indovat[14*(i-0)+j].setTexture(lo);
                indovat[14*(i-0)+j].setPosition(40*i,40*j);
            }
        }
}
void update_dovat(int directions) {
    int posx=animated.getPosition().x;
    int posy=animated.getPosition().y;
    posx+=10;
    posy+=34;
    switch (directions) {
    case 1: {
        posy+=40;

        break;
    }
    case 0: {
        posy-=40;
        break;
    }
    case 2: {
        posx+=40;
        break;
    }
    case 3: {
        posx-=40;
        break;
    }
    }

    if(vitri[posx/40][posy/40]==1||vitri[posx/40][posy/40]==3) {
        if(vitri[posx/40][posy/40]==3)
            vitri[posx/40][posy/40]=2;
        else
            vitri[posx/40][posy/40]=0;
        switch (directions) {
        case 1: {
            posy+=40;
            break;
        }
        case 0: {
            posy-=40;
            break;
        }
        case 2: {
            posx+=40;
            break;
        }
        case 3: {
            posx-=40;
            break;
        }
        }
        //cout<<posx/40<<" "<<posy/40<<endl;
        if(vitri[posx/40][posy/40]==2) {
            vitri[posx/40][posy/40]=3;
            cout<<ktketthucgame()<<endl;
        } else
            vitri[posx/40][posy/40]=1;
    }
    //vitri[posx/40][posy/40]=1;
    resetbang();
}
void update_idle(int dir) {
    stand.loadFromFile("data/ani/stand.png");
    animated.setTexture(stand);
    animated.setTextureRect(IntRect(dir*100,0,110,100));
    animationtimer.restart();
}
void move_up(float timer) {
    animation.loadFromFile("data/ani/run_up.png");
    animated.setTexture(animation);
//    curframe.height=110;
//    curframe.top=0;
//    curframe.left=0;
//    curframe.width=100;
    if(animationtimer.getElapsedTime().asSeconds()>=speedtimer) {
        curframe.left+=100;
        if(curframe.left>=300)
            curframe.left=0;
        animationtimer.restart();
        animated.setTextureRect(curframe);
    }
}
void move_down(float timer) {
    animation.loadFromFile("data/ani/run_down.png");
    animated.setTexture(animation);
//    curframe.height=110;
//    curframe.top=0;
//    curframe.left=0;
//    curframe.width=100;
    if(animationtimer.getElapsedTime().asSeconds()>=speedtimer) {
        curframe.left+=100;
        if(curframe.left>=300)
            curframe.left=0;
        animationtimer.restart().asSeconds();
        animated.setTextureRect(curframe);
    }
}
void move_right(float timer) {
    animation.loadFromFile("data/ani/run_right.png");
    animated.setTexture(animation);
//    curframe.height=110;
//    curframe.top=0;
//    curframe.left=0;
//    curframe.width=100;
    if(animationtimer.getElapsedTime().asSeconds()>=speedtimer) {
        curframe.left+=100;
        if(curframe.left>=300)
            curframe.left=0;
        animationtimer.restart().asSeconds();
        animated.setTextureRect(curframe);
    }
}
void move_left(float timer) {
    animation.loadFromFile("data/ani/run_left.png");
    animated.setTexture(animation);
//    curframe.height=110;
//    curframe.top=0;
//    curframe.left=0;
//    curframe.width=100;
    if(animationtimer.getElapsedTime().asSeconds()>=speedtimer) {
        curframe.left+=100;
        if(curframe.left>=300)
            curframe.left=0;
        animationtimer.restart();
        animated.setTextureRect(curframe);
    }
}
void controls(Event e) {

    curframe.height=110;
    curframe.top=0;
    curframe.left=0;
    curframe.width=100;
    float timer=0.2f;
    animationtimer.restart();
    if(e.key.code==Keyboard::W) {
//            cout<<check_move_possible(0)<<endl;
        if(check_move_possible(0)==1) {
            update_dovat(0);
            move_up(timer);
            if(animated.getPosition().y>6)
                animated.move(0,-speed);
        } else
            move_up(timer);
        direction=1;
    } else if(e.key.code==Keyboard::S) {
//        cout<<check_move_possible(1)<<endl;
        if(check_move_possible(1)==1) {
            update_dovat(1);
            move_down(timer);
            if(animated.getPosition().y<526)
                animated.move(0,speed);
        } else
            move_down(timer);
        direction=0;
    }
    if(e.key.code==Keyboard::D) {
//        cout<<check_move_possible(2)<<endl;
        if(check_move_possible(2)) {
            update_dovat(2);
            move_right(timer);
            if(animated.getPosition().x<830)
                animated.move(speed,0);
        } else
            move_right(timer);
        direction=2;
    } else if(e.key.code==Keyboard::A) {
//        cout<<check_move_possible(3)<<endl;
        if(check_move_possible(3)) {
            update_dovat(3);
            move_left(timer);
            if(animated.getPosition().x>-10)
                animated.move(-speed,0);
        } else
            move_left(timer);
        direction=3;
    }
    ve();
}
void loading_sceen() {
    float frame=0;
    float anispeed=0.003;
    int framecnt=4;
    Texture loading_run;
    Sprite aniloading(loading_run);
    aniloading.setPosition(630,470);
    loading_run.loadFromFile("data/ani/run_left.png");
    int repeate=4;
    do {
        if((int)(frame+anispeed)>=framecnt) {
            frame=0;
            repeate--;
            continue;
        }
        frame+=anispeed;
        aniloading.setTextureRect(IntRect(int(frame)*100,0,100,110));
        window.clear();
        window.draw(aniloading);
        window.display();

    } while(repeate>0);
}
void start() {
    vitri[12][11]=1;
    vitri[13][11]=1;
    vitri[14][11]=1;
    vitri[15][11]=1;
    vitri[12][12]=2;
    vitri[13][12]=2;
    vitri[14][12]=2;
    vitri[15][12]=2;
    /// music
    Music menu_bgm,click;
    menu_bgm.openFromFile("data/music/menu.ogg");
    click.openFromFile("data/music/click.ogg");
    menu_bgm.setVolume(50);
    click.setVolume(50);
    menu_bgm.setLoop(true);
    // menu_bgm.play();
    /// background menu
    Texture bgmenu;
    bgmenu.loadFromFile("data/bg/menu/bg.png");
    in_bgmenu.setTexture(bgmenu);
    /// button
    Texture btPlay,btCredit;
    btPlay.loadFromFile("data/button/button02.png");
    btCredit.loadFromFile("data/button/button01.png");
    Sprite bt_play(btPlay),bt_credit(btCredit);
    bt_play.setPosition(310,320);
    bt_credit.setPosition(310,408);
    int play=0,credit=0;
    Texture loading_run;
    Sprite aniloading(loading_run);
    aniloading.setPosition(630,470);
    loading_run.loadFromFile("data/ani/run_left.png");
    float frame=0;
    float anispeed=0.004;
    int framecnt=4;
    window.setFramerateLimit(60);
    startdovat();
    animated.setPosition(30,46);
    while (window.isOpen()) {
        Event event,e;
        int isMoving=0;
        Vector2i pos= Mouse::getPosition(window);
        while(window.pollEvent(e)) {
            if(e.type== Event::Closed)
                window.close();
//            if(e.type== Event::MouseButtonPressed) {
//                if(e.key.code == Mouse::Left) {
//                    if(bt_play.getGlobalBounds().contains(pos.x,pos.y)) {
//                        click.play();
//                        play=1;
//                    }
//                }
//            }
//            if(e.type== Event::MouseButtonPressed) {
//                if(e.key.code == Mouse::Left) {
//                    if(bt_credit.getGlobalBounds().contains(pos.x,pos.y)) {
//                        click.play();
//                        credit=1;
//                    }
//                }
//            }
            ///nhan nut
            if(animated.getLocalBounds().contains(animated.getPosition().x,animated.getPosition().y))
                frame=0;
            if(e.type==Event::KeyPressed) {
                controls(e);
            }
            if(isMoving==0)
                update_idle(direction);
        }
        animated.setScale(Vector2f(0.7,0.7));
        //cout<<animated.getPosition().x<<" "<<animated.getPosition().y<<endl;
        ve();
    }
}
int main() {
    start();
    return 0;
}
