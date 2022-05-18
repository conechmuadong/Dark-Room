#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(880, 600), "Re_Schola");
struct data {
    Text chu;
    int ascii;
    int x;
    int y;
    bool in;
    int nhat;
    int ktmove;
    int key;
    int keyarea;
    int check_done;
    Sprite in_o;
} vitri[25][15];
Texture bgmenu;
Sprite in_bgmenu;
Texture stand;
Sprite stands(stand);
Texture animation;
Sprite animated(animation);
Clock animationtimer;
IntRect curframe;
float speedtimer = 0.5f;
int speed = 40;
float timer = 0.2f;
/// 0=up 1=down 2=right 3=left
int direction = 2; /// 4 toi vinh vien ko qua duoc 5 la nen duoc hien 6 la nen bi toi
Sprite indovat[1000];
/// do lech hinh nhan vat
int deltax = 30;
int deltay = 46;
int delx=6;
Sprite graphic[21*14+1];
Font fonts;
/// inventory
int isHolding=0;
int Inventory=0;
int issupa=0;
Texture indung,insai;
map<string,Sound> sounds;
map<string,SoundBuffer> soundbuffers;
char convert(int ascii) {
    return (char)ascii;
}
void ve_3() {
    window.draw(in_bgmenu);
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++) {
            if(vitri[i][j].check_done==1) {
                vitri[i][j].in_o.setTexture(indung);
                vitri[i][j].in_o.setPosition(40*i,40*j);
                window.draw(vitri[i][j].in_o);
            }
            if(vitri[i][j].check_done==0) {
                vitri[i][j].in_o.setTexture(insai);
                vitri[i][j].in_o.setPosition(40*i,40*j);
                window.draw(vitri[i][j].in_o);
            }
        }
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++)
            if(vitri[i][j].in==true)
                window.draw(vitri[i][j].chu);
    window.draw(animated);
    window.display();
}
void update_word_data(int xpos,int ypos,string s) {
    vitri[xpos][ypos].chu.setFont(fonts);
    vitri[xpos][ypos].chu.setCharacterSize(31);
    vitri[xpos][ypos].chu.setColor(Color::White);
    vitri[xpos][ypos].chu.setString(s);
    vitri[xpos][ypos].chu.setPosition(vitri[xpos][ypos].x,vitri[xpos][ypos].y);
}
void bg_music_map3(string paths,int playthatthing) {
    if(playthatthing==1) {
        string thats="data/music/supa.ogg";
        sounds[paths].stop();
        soundbuffers[thats].loadFromFile(thats);
        sounds[thats]=Sound{soundbuffers[thats]};
        sounds[thats].play();
        return;
    } else {
        soundbuffers[paths].loadFromFile(paths);
        sounds[paths]=Sound{soundbuffers[paths]};
        sounds[paths].setLoop(true);
        sounds[paths].play();
    }
}
int check_game_complete_map_3() {
    int cnt=0;
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++)
            if(vitri[i][j].check_done==1)
                cnt++;
    if(cnt==8)
        return 1;
    return 0;
}
void check_key_is_fill() {
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++) {
            if(vitri[i][j].key==vitri[i][j].ascii&&vitri[i][j].ascii!=0) {
                vitri[i][j].check_done=true;
//                vitri[i][j].ktmove=1;
                vitri[i][j].nhat=0;

            }
        }
}
int check_move(int directions) {
    int posx = animated.getPosition().x;
    int posy = animated.getPosition().y;
    posx += 40 - deltax;
    posy += 34;
    int debug = 1;
    switch (directions) {
    case 1: {
        posy += 40 * debug;
        break;
    }
    case 0: {
        posy -= 40 * debug;
        break;
    }
    case 2: {
        posx += 40 * debug;
        break;
    }
    case 3: {
        posx -= 40 * debug;
        break;
    }
    }
    if (vitri[posx / 40][posy / 40].ktmove == 1) {

        return 0;
    }
    return 1;
}
int check_word(int directions) {
    Event e;
    int posx = animated.getPosition().x;
    int posy = animated.getPosition().y;
    posx += 40 - deltax;
    posy += 34;
    int debug = 1;
    switch (directions) {
    case 0: {
        posy += 40 * debug;
        break;
    }
    case 1: {
        posy -= 40 * debug;
        break;
    }
    case 2: {
        posx += 40 * debug;
        break;
    }
    case 3: {
        posx -= 40 * debug;
        break;
    }
    }
    posx=posx/40;
    posy=posy/40;
    //cout<<vitri[posx][posy].nhat<<endl;
    if(isHolding==0&&vitri[posx][posy].nhat==1)
        return 1;

    if(isHolding==1&&vitri[posx][posy].nhat==0)
        return 2;
    if(isHolding==1&&vitri[posx][posy].nhat==2)
        return 2;
    else
        return 0;
//    cout<<vitri[posx][posy].nhat<<endl;
//    if(vitri[posx][posy].nhat==1) {
//        cout<<"2"<<endl;
//        if(isHolding==0) {

//        }
//    } else {
//        if(isHolding==1) {

//        }
//    }
//    ve_3();
}
void update_word(int directions,int decision) {
    Event e;
    int posx = animated.getPosition().x;
    int posy = animated.getPosition().y;
    posx += 40 - deltax;
    posy += 34;
    int debug = 1;
    switch (directions) {
    case 0: {
        posy += 40 * debug;
        break;
    }
    case 1: {
        posy -= 40 * debug;
        break;
    }
    case 2: {
        posx += 40 * debug;
        break;
    }
    case 3: {
        posx -= 40 * debug;
        break;
    }
    }
    posx=posx/40;
    posy=posy/40;
    if(decision==1) {
        vitri[posx][posy].in=false;
        Inventory=vitri[posx][posy].ascii;
        isHolding=1;
        vitri[posx][posy].ascii=0;
        vitri[posx][posy].ktmove=0;
        vitri[posx][posy].nhat=2;
    }
    if(decision==2) {
        vitri[posx][posy].in=true;
        vitri[posx][posy].ktmove=1;
        vitri[posx][posy].ascii=Inventory;
        vitri[posx][posy].nhat=1;
        string tmp(1,convert(vitri[posx][posy].ascii));
        //cout<<tmp<<endl;
        update_word_data(posx,posy,tmp);
        isHolding=0;
        Inventory=0;
    }
    ve_3();
}
void update_idle(int dir) {
    stand.loadFromFile("data/ani/stand.png");
    animated.setTexture(stand);
    animated.setTextureRect(IntRect(dir * 100, 0, 110, 100));
    animationtimer.restart();
}
void move_up(float timer) {
    animation.loadFromFile("data/ani/run_up.png");
    animated.setTexture(animation);

    if (animationtimer.getElapsedTime().asSeconds() >= speedtimer) {
        curframe.left += 100;
        if (curframe.left >= 300)
            curframe.left = 0;
        animationtimer.restart();
        animated.setTextureRect(curframe);
    }
}
void move_down(float timer) {
    animation.loadFromFile("data/ani/run_down.png");
    animated.setTexture(animation);

    if (animationtimer.getElapsedTime().asSeconds() >= speedtimer) {
        curframe.left += 100;
        if (curframe.left >= 300)
            curframe.left = 0;
        animationtimer.restart().asSeconds();
        animated.setTextureRect(curframe);
    }
}
void move_right(float timer) {
    animation.loadFromFile("data/ani/run_right.png");
    animated.setTexture(animation);

    if (animationtimer.getElapsedTime().asSeconds() >= speedtimer) {
        curframe.left += 100;
        if (curframe.left >= 300)
            curframe.left = 0;
        animationtimer.restart().asSeconds();
        animated.setTextureRect(curframe);
    }
}
void move_left(float timer) {
    animation.loadFromFile("data/ani/run_left.png");
    animated.setTexture(animation);
    if (animationtimer.getElapsedTime().asSeconds() >= speedtimer) {
        curframe.left += 100;
        if (curframe.left >= 300)
            curframe.left = 0;
        animationtimer.restart();
        animated.setTextureRect(curframe);
    }
}
void control_map3(Event e) {
    if (e.key.code == Keyboard::W) {
        if (check_move(0) == 1) {
            move_up(timer);
            if (animated.getPosition().y > 6)
                animated.move(0, -speed);
        } else {
            move_up(timer);
        }
        direction = 1;
    } else if (e.key.code == Keyboard::S) {
        if (check_move(1) == 1) {

            move_down(timer);
            if (animated.getPosition().y < 526)
                animated.move(0, speed);
        } else {

            move_down(timer);
        }
        direction = 0;
    }
    if (e.key.code == Keyboard::D) {

        if (check_move(2)) {
//        if(true){

            move_right(timer);
            if (animated.getPosition().x < 830)
                animated.move(speed, 0);
        } else {

            move_right(timer);
        }
        direction = 2;
    } else if (e.key.code == Keyboard::A) {
        if (check_move(3)) {

            move_left(timer);
            if (animated.getPosition().x > -10)
                animated.move(-speed, 0);
        } else {

            move_left(timer);
        }
        direction = 3;
    }
    //cout<<check_word(direction)<<endl;
    if(check_word(direction)==1) {
        if(e.key.code==Keyboard::E)
            update_word(direction,check_word(direction));
        return;
    }
    if(check_word(direction)==2) {
        if(e.key.code==Keyboard::E)
            update_word(direction,check_word(direction));
    }
    check_key_is_fill();
    cout<<check_game_complete_map_3()<<endl;
    if(check_game_complete_map_3()&&issupa==0) {
        bg_music_map3("data/music/bgmap3.ogg",1);
        issupa=1;
    }
    //cout<<isHolding<<" "<<Inventory<<endl;
    ve_3();
}
void bebug(int xpos,int ypos,string s) {
    vitri[xpos][ypos].in=true;
    vitri[xpos][ypos].nhat=true;
    vitri[xpos][ypos].chu.setFont(fonts);
    vitri[xpos][ypos].chu.setCharacterSize(31);
    vitri[xpos][ypos].chu.setColor(Color::White);
    vitri[xpos][ypos].chu.setString(s);
    vitri[xpos][ypos].ascii=(int)s[0];
    vitri[xpos][ypos].ktmove=1;
    vitri[xpos][ypos].x=40*xpos+delx;
    vitri[xpos][ypos].y=ypos*40+delx;
    vitri[xpos][ypos].chu.setPosition(vitri[xpos][ypos].x,vitri[xpos][ypos].y);
}
void set_key(int y,int x,char s) {
    vitri[x][y].key=(int)s;
    vitri[x][y].check_done=0;
}
void preset() {
    indung.loadFromFile("data/item/keyarea/true.png");
    insai.loadFromFile("data/item/keyarea/false.png");
    fonts.loadFromFile("data/font/PIXEL.TTF");
    bgmenu.loadFromFile("data/bg/menu/bg.png");
    in_bgmenu.setTexture(bgmenu);
    window.setFramerateLimit(60);
    animated.setPosition(deltax,deltay);
    animated.setScale(Vector2f(0.7,0.7));
    bg_music_map3("data/music/bgmap3.ogg",0);
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++) {
            vitri[i][j].in=false;
            vitri[i][j].nhat=false;
            vitri[i][j].ascii=0;
            vitri[i][j].x=40*i+delx;
            vitri[i][j].y=j*40+delx;
            vitri[i][j].check_done=2;
        }
    bebug(3,2,"S");
    bebug(5,12,"U");
    bebug(18,6,"P");
    bebug(14,5,"A");
    bebug(19,13,"I");
    bebug(9,5,"D");
    bebug(10,2,"O");
    bebug(7,4,"L");
    bebug(8,12,"Z");
    bebug(16,8,"T");
    bebug(5,11,"L");
    bebug(7,3,"Y");
    for(int i=3; i<=6; i++)
        vitri[i][2].keyarea=1;
    for(int i=8; i<=11; i++)
        vitri[i][2].keyarea=1;
    set_key(2,3,'S');
    set_key(2,4,'U');
    set_key(2,5,'P');
    set_key(2,6,'A');
    set_key(2,8,'I');
    set_key(2,9,'D');
    set_key(2,10,'O');
    set_key(2,11,'L');
}
void start() {

    preset();
    while (window.isOpen()) {
        Event e;
        int isMoving = 0;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
            if (e.type == Event::KeyPressed) {
                control_map3(e);
            }
            if (isMoving == 0)
                update_idle(direction);

        }
        ve_3();
    }
}
int main() {
    start();
    return 0;

}
