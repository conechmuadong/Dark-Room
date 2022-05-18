
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include<bits/stdc++.h>
#include "mainmenu.h"
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(880, 600), "Project X: The Game but Incompleted");
Menu menu;
Sprite in_bgmenu;
Texture bgmenu;
Texture stand;
Sprite stands(stand);
Texture animation;
Sprite animated(animation);
Clock animationtimer;
IntRect curframe;
float speedtimer=0.5f;
int speed=40;
float timer=0.2f;
int delx=6;
/// 0=up 1=down 2=right 3=left
enum Direction{
    UP = 0,
    DOWN = 1,
    RIGHT = 2,
    LEFT = 3,
};
int direction = RIGHT;
/// do vat
Texture lo;
Texture box;
Texture blank;
int vitri[25][15];
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
} vitri1[25][15]; /// 4 toi vinh vien ko qua duoc 5 la nen duoc hien 6 la nen bi toi
Sprite graphic[21*14+1];
Font fonts;
Sprite indovat[1000];
/// do lech hinh nhan vat
int deltax=30;
int deltay=46;
/// so do vat
int demdovat=4;
/// next level
int iscomplete=0;
int rickroll=0;
int isHolding=0;
int Inventory=0;
int issupa=0;
Texture indung,insai;
Texture Tdoor;
Sprite door;
Texture toi,gantoi;
Sprite dark,partdark;
int chayloading=0;
map<string,Sound> sounds;
map<string,SoundBuffer> soundbuffers;
int isloading[10];
char convert(int ascii) {
    return (char)ascii;
}
void ve_3() {
    window.draw(in_bgmenu);
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++) {
            if(vitri1[i][j].check_done==1) {
                vitri1[i][j].in_o.setTexture(indung);
                vitri1[i][j].in_o.setPosition(40*i,40*j);
                window.draw(vitri1[i][j].in_o);
            }
            if(vitri1[i][j].check_done==0) {
                vitri1[i][j].in_o.setTexture(insai);
                vitri1[i][j].in_o.setPosition(40*i,40*j);
                window.draw(vitri1[i][j].in_o);
            }
        }
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++)
            if(vitri1[i][j].in==true)
                window.draw(vitri1[i][j].chu);
    window.draw(animated);
    window.display();
}
void update_word_data(int xpos,int ypos,string s) {
    vitri1[xpos][ypos].chu.setFont(fonts);
    vitri1[xpos][ypos].chu.setCharacterSize(31);
    vitri1[xpos][ypos].chu.setColor(Color::White);
    vitri1[xpos][ypos].chu.setString(s);
    vitri1[xpos][ypos].chu.setPosition(vitri1[xpos][ypos].x,vitri1[xpos][ypos].y);
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
            if(vitri1[i][j].check_done==1)
                cnt++;
    if(cnt==8)
        return 1;
    return 0;
}
void check_key_is_fill() {
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++) {
            if(vitri1[i][j].key==vitri1[i][j].ascii&&vitri1[i][j].ascii!=0) {
                vitri1[i][j].check_done=true;
//                vitri[i][j].ktmove=1;
                vitri1[i][j].nhat=0;

            }
        }
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
    if(isHolding==0&&vitri1[posx][posy].nhat==1)
        return 1;

    if(isHolding==1&&vitri1[posx][posy].nhat==0)
        return 2;
    if(isHolding==1&&vitri1[posx][posy].nhat==2)
        return 2;
    else
        return 0;
//    cout<<vitri[posx][posy].nhat<<endl;
//    if(vitri[posx][posy].nhat==1) {
//        cout<<"2"<<endl;
//        if(isHolding==0) {

//        }1
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
        vitri1[posx][posy].in=false;
        Inventory=vitri1[posx][posy].ascii;
        isHolding=1;
        vitri1[posx][posy].ascii=0;
        vitri1[posx][posy].ktmove=0;
        vitri1[posx][posy].nhat=2;
    }
    if(decision==2) {
        vitri1[posx][posy].in=true;
        vitri1[posx][posy].ktmove=1;
        vitri1[posx][posy].ascii=Inventory;
        vitri1[posx][posy].nhat=1;
        string tmp(1,convert(vitri1[posx][posy].ascii));
        //cout<<tmp<<endl;
        update_word_data(posx,posy,tmp);
        isHolding=0;
        Inventory=0;
    }
    ve_3();
}

void bebug(int xpos,int ypos,string s) {
    vitri1[xpos][ypos].in=true;
    vitri1[xpos][ypos].nhat=true;
    vitri1[xpos][ypos].chu.setFont(fonts);
    vitri1[xpos][ypos].chu.setCharacterSize(31);
    vitri1[xpos][ypos].chu.setColor(Color::White);
    vitri1[xpos][ypos].chu.setString(s);
    vitri1[xpos][ypos].ascii=(int)s[0];
    vitri1[xpos][ypos].ktmove=1;
    vitri1[xpos][ypos].x=40*xpos+delx;
    vitri1[xpos][ypos].y=ypos*40+delx;
    vitri1[xpos][ypos].chu.setPosition(vitri1[xpos][ypos].x,vitri1[xpos][ypos].y);
}
void set_key(int y,int x,char s) {
    vitri1[x][y].key=(int)s;
    vitri1[x][y].check_done=0;
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
            vitri1[i][j].in=false;
            vitri1[i][j].nhat=false;
            vitri1[i][j].ascii=0;
            vitri1[i][j].x=40*i+delx;
            vitri1[i][j].y=j*40+delx;
            vitri1[i][j].check_done=2;
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
        vitri1[i][2].keyarea=1;
    for(int i=8; i<=11; i++)
        vitri1[i][2].keyarea=1;
    set_key(2,3,'S');
    set_key(2,4,'U');
    set_key(2,5,'P');
    set_key(2,6,'A');
    set_key(2,8,'I');
    set_key(2,9,'D');
    set_key(2,10,'O');
    set_key(2,11,'L');
}
void ve() {
    window.clear();
    if(rickroll==0) {
        window.draw(in_bgmenu);
        for(int i=0; i<=22*15; i++)
            window.draw(indovat[i]);
        if(iscomplete==1) {
            //cout<<(animated.getPosition().y+34)/40<<" "<<(animated.getPosition().x+10)/40<<endl<<"--------------"<<endl;
            if(animated.getPosition().y+34>3*40&&animated.getPosition().x+10==18*40) {
                window.draw(animated);
                //window.draw(door);
            }
            if(animated.getPosition().y+34<=3*40&&animated.getPosition().x+10==18*40) {
                //window.draw(door);
                window.draw(animated);
            } else {
                //window.draw(door);
                window.draw(animated);
            }
        } else {
            window.draw(animated);
        }
//    window.draw(door);
//    window.draw(animated);
    } else {
        window.clear();
        window.draw(in_bgmenu);
        for(int i=0; i<=23*15; i++)
            window.draw(indovat[i]);
        window.draw(animated);
    }
    window.display();
}
int ktketthucgame() {
    int dem=0;
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++)
            if(vitri[i][j]==3)
                dem++;
    cout<<demdovat<<endl;
    if(dem==demdovat)
        return 1;
    return 0;
}
void chayamthanh(string paths) {

    soundbuffers[paths].loadFromFile(paths);
    sounds[paths]=Sound{soundbuffers[paths]};
    sounds[paths].play();
}
void Stops(string paths){
sounds[paths].stop();
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
    if(door.getPosition().x==posx&&door.getPosition().y+40*2==posy&&ktketthucgame()==1)
        rickroll=1;
    //cout<<"1, "<<posx/40<<" "<<posy/40<<" "<<vitri[posx/40][posy/40]<<endl<<"-----------------"<<endl;
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
        //cout<<"2, "<<posx/40<<" "<<posy/40<<endl;
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
int check_move_in_dark_possible(int directions) {
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
    //cout<<"1, "<<posx/40<<" "<<posy/40<<" "<<vitri[posx/40][posy/40]<<endl<<"-----------------"<<endl;
    if(vitri[posx/40][posy/40]==4) {
//        switch (directions) {
//        case 1: {
//            posy+=40;
//            break;
//        }
//        case 0: {
//            posy-=40;
//            break;
//        }
//        case 2: {
//            posx+=40;
//            break;
//        }
//        case 3: {
//            posx-=40;
//            break;
//        }
//        }
//        //cout<<"2, "<<posx/40<<" "<<posy/40<<endl;
//        if(vitri[posx/40][posy/40]==1||vitri[posx/40][posy/40]==3)
//            return 0;
//        if(posx/40-1<0||posx/40+1>21||posy/40-1<0||posy/40+1>14)
        return 0;
    }

    //cout<<posx<<" "<<posy<<endl;
//    if(posx<0||posx/40>21||posy<0||posy/40>14||vitri[posx][posy]==1)
//        return 0;
    return 1;
}
void rickrolltime() {
    Event e;
    Texture hay;
    Stops("data/music/bg2.ogg");
    Stops("data/music/footstep.ogg");
    Stops("data/music/laugh1.ogg");
    int framecnt=4;
    float framerate=0.05;
    float chay=1;
    Music asley;
    asley.openFromFile("data/music/stage_e.ogg");
    asley.setLoop(true);
    asley.play();
    while(1) {
        /*Texture endgameText;
        Sprite endgame;
        endgameText.loadFromFile("data/bg/endgame.png");
        endgame.setTexture(endgameText);*/
        window.pollEvent(e);
        if(e.type==Event::KeyPressed)
            if(e.key.code==Keyboard::Escape)
            {
                window.close();
                break;
            }
        if((int)(chay+framerate)>framecnt) {
            chay=1;
        }
        string locations="data/ani/debug/secret/rick";
        stringstream tmp;
        chay+=framerate;
        int dem=(int)chay;
        tmp<<dem;
        string so=tmp.str();
        locations=locations+so+".png";
        hay.loadFromFile(locations);
        Sprite rick(hay);
        window.clear();
        window.draw(rick);
        window.display();
    }
}
void startdovat() {
    lo.loadFromFile("data/item/hole.png");
    blank.loadFromFile("data/item/blank.png");
    box.loadFromFile("data/item/box.png");
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++) {
            if(vitri[i][j]==1 || vitri[i][j]==3) {
                //cout<<i<<" "<<j<<endl;
                indovat[15*(i-0)+j].setTexture(box);
                indovat[15*(i-0)+j].setPosition(40*i,40*j);
            }
            if(vitri[i][j]==0) {
                indovat[15*(i)+j].setTexture(blank);
                indovat[15*(i)+j].setPosition(40*i,40*j);
            }
            if(vitri[i][j]==2) {
                indovat[15*(i-0)+j].setTexture(lo);
                indovat[15*(i-0)+j].setPosition(40*i,40*j);
            }
        }
}
void resetbang() {
    if(rickroll==0)
        for(int i=0; i<=21; i++)
            for(int j=0; j<=14; j++) {
                if(vitri[i][j]==1||vitri[i][j]==3) {
                    indovat[15*(i-0)+j].setTexture(box);
                    indovat[15*(i-0)+j].setPosition(40*i,40*j);
                }
                if(vitri[i][j]==0) {
                    indovat[15*(i-0)+j].setTexture(blank);
                    indovat[15*(i-0)+j].setPosition(40*i,40*j);
                }
                if(vitri[i][j]==2) {
                    indovat[15*(i-0)+j].setTexture(lo);
                    indovat[15*(i-0)+j].setPosition(40*i,40*j);
                }
            } else
        for(int i=0; i<=21; i++)
            for(int j=0; j<=14; j++) {
                if(vitri[i][j]==4||vitri[i][j]==6) {
                    indovat[15*(i-0)+j].setTexture(toi);
                    indovat[15*(i-0)+j].setPosition(40*i,40*j);
                }
                if(vitri[i][j]==5) {
                    indovat[15*(i-0)+j].setTexture(gantoi);
                    indovat[15*(i-0)+j].setPosition(40*i,40*j);
                }
            }
}
void update_darkness(int directions) {
    int posx=animated.getPosition().x;
    int posy=animated.getPosition().y;
    posx+=10;
    posy+=34;
    Music tmp;
    SoundBuffer backsground;

    if(isloading[5]==0){
    chayamthanh("data/music/bg2.ogg");
    isloading[5]=1;
    }
    Sound bg;
    bg.setBuffer(backsground);
    bg.play();
    cout<<posx/40<<" "<<posy/40<<endl;
    if(posx/40==4&&posy/40==4) {
        chayamthanh("data/music/footstep.ogg");
        isloading[0]=1;
    }
    if(posx/40==4&&posy/40==7&&isloading[0]==0) {

        chayamthanh("data/music/laugh1.ogg");
        isloading[0]=1;
    }
    if(posx/40==12&&posy/40==5&&isloading[1]==0) {

        chayamthanh("data/music/laugh2.ogg");
        isloading[1]=1;
    }
    if(posx/40==19&&posy/40==6&&isloading[2]==0) {

        chayamthanh("data/music/door.ogg");
        isloading[2]=1;
    }
    if(posx/40==5&&posy/40==11&&isloading[3]==0) {
        chayamthanh("data/music/golden.ogg");
        isloading[3]=1;
    }
    if(posx/40==17&&posy/40==12&&isloading[4]==0) {
        //cout<<"TRIGGER"<<endl;
        rickrolltime();
        isloading[4]=1;
    }
    int xdau=posx;
    int ydau=posy;
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

    vitri[xdau/40][ydau/40]=6;
    if(vitri[posx/40][posy/40]==6) {
        xdau=posx;
        ydau=posy;
        if(vitri[posx/40][posy/40]==6)
            vitri[posx/40][posy/40]=5;
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
        if(vitri[posx/40][posy/40]==6) {
            vitri[posx/40][posy/40]=5;
        }
    }
    resetbang();
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
    if (vitri1[posx / 40][posy / 40].ktmove == 1) {

        return 0;
    }
    return 1;
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
void controls(Event e) {

    if(iscomplete==1||ktketthucgame()==1) {
        iscomplete=1;
    }
    cout<<"Door: "<<(door.getPosition().x)/40<<" "<<door.getPosition().y/40<<endl;

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
        direction=DOWN;
    } else if(e.key.code==Keyboard::S) {
//        cout<<check_move_possible(1)<<endl;
        if(check_move_possible(1)==1) {
            update_dovat(1);
            move_down(timer);
            if(animated.getPosition().y<526)
                animated.move(0,speed);
        } else
            move_down(timer);
        direction=UP;
    }
    if(e.key.code==Keyboard::D) {
        if(check_move_possible(2)) {
            update_dovat(2);
            move_right(timer);
            if(animated.getPosition().x<830)
                animated.move(speed,0);
        } else
            move_right(timer);
        direction=RIGHT;
    } else if(e.key.code==Keyboard::A) {
//        cout<<check_move_possible(3)<<endl;
        if(check_move_possible(3)) {
            update_dovat(3);
            move_left(timer);
            if(animated.getPosition().x>-10)
                animated.move(-speed,0);
        } else
            move_left(timer);
        direction=LEFT;
    }
    ve();
}
void control_map2(Event e) {
    if(e.key.code==Keyboard::W) {
//            cout<<check_move_possible(0)<<endl;
        if(check_move_in_dark_possible(0)==1) {
            update_darkness(0);
            move_up(timer);
            if(animated.getPosition().y>6)
                animated.move(0,-speed);
        } else
            move_up(timer);
        direction=DOWN;
    } else if(e.key.code==Keyboard::S) {
//        cout<<check_move_possible(1)<<endl;
        if(check_move_in_dark_possible(1)==1) {
            update_darkness(1);
            move_down(timer);
            if(animated.getPosition().y<526)
                animated.move(0,speed);
        } else
            move_down(timer);
        direction=UP;
    }
    if(e.key.code==Keyboard::D) {
//        cout<<check_move_possible(2)<<endl;
        if(check_move_in_dark_possible(2)) {
            update_darkness(2);
            move_right(timer);
            if(animated.getPosition().x<830)
                animated.move(speed,0);
        } else
            move_right(timer);
        direction=RIGHT;
    } else if(e.key.code==Keyboard::A) {
//        cout<<check_move_possible(3)<<endl;
        if(check_move_in_dark_possible(3)) {
            update_darkness(3);
            move_left(timer);
            if(animated.getPosition().x>-10)
                animated.move(-speed,0);
        } else
            move_left(timer);
        direction=LEFT;
    }
    ve();
}
void loading_sceen() {
    /// loading word
    Font loads;
    loads.loadFromFile("data/font/PIXEL.TTF");
    Text loading;
    loading.setFont(loads);
    loading.setString("LOADING");
    loading.setPosition(40*14,40*10);
    loading.setCharacterSize(40);
    loading.setColor(Color::White);
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++)
            vitri[i][j]=4;
    vitri[2][5]=6;
    vitri[2][4]=6;
    vitri[2][3]=6;
    vitri[3][3]=6;
    vitri[4][3]=6;
    for(int i=4; i<=8; i++)
        vitri[4][i]=6;
    for(int i=5; i<=12; i++)
        vitri[i][8]=6;
    for(int i=8; i>=3; i--)
        vitri[12][i]=6;
    for(int i=12; i<=19; i++)
        vitri[i][3]=6;
    for(int i=4; i<=10; i++)
        vitri[19][i]=6;
    for(int i=18; i>=5; i--)
        vitri[i][10]=6;
    for(int i=10; i<=12; i++)
        vitri[5][i]=6;
    for(int i=6; i<=20; i++)
        vitri[i][12]=6;
    resetbang();
    direction=2;
    float frame=0;
    float anispeed=0.08;
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
        window.draw(loading);
        window.display();

    } while(repeate>0);
}

void start(Event e,int isMoving) {
    float frame=0;
    float anispeed=0.004;
    int framecnt=4;
    if(animated.getLocalBounds().contains(animated.getPosition().x,animated.getPosition().y))
        frame=0;
    if(e.type==Event::KeyPressed) {
        if(rickroll==1) {
            if(chayloading==0) {
                loading_sceen();
                animated.setPosition(40*2-10,40*5+6);
                chayloading=1;
                toi.loadFromFile("data/item/dark.png");
                gantoi.loadFromFile("data/item/partdark.png");
            }
            control_map2(e);
        }
        else if (check_game_complete_map_3())
        {
            controls(e);
        }
        else
        {
            control_map3(e);
        }
        cout<<"Rickroll="<<rickroll<<endl;
    }

    if(isMoving==0)
        update_idle(direction);
    animated.setScale(Vector2f(0.7,0.7));
    if(check_game_complete_map_3())
        ve();
    else
    {
        ve_3();
    }
}
int main() {
    bool firstTime = true;
    int gameStatus=0;
    vitri[12][11]=1;
    vitri[13][11]=1;
    vitri[14][11]=1;
    vitri[15][11]=1;
    vitri[12][12]=2;
    vitri[13][12]=2;
    vitri[14][12]=2;
    vitri[15][12]=2;
    Texture bgmenu;
    bgmenu.loadFromFile("data/bg/menu/bg.png");
    in_bgmenu.setTexture(bgmenu);
    window.setFramerateLimit(60);
    startdovat();
    animated.setPosition(30,46);

    /// door
    Tdoor.loadFromFile("data/item/door.png");
    door.setTexture(Tdoor);
    door.setPosition(20*40,0*40);
    int isMoving=0;
    while (window.isOpen()) {
        Event event,e;
        while(window.pollEvent(e)) {
            if(e.type== Event::Closed)
                window.close();
            switch(gameStatus)
            {
            case 1:
                if (firstTime)
                {
                    firstTime = false;
                    loading_sceen();
                    vitri[12][11]=1;
                    vitri[13][11]=1;
                    vitri[14][11]=1;
                    vitri[15][11]=1;
                    vitri[12][12]=2;
                    vitri[13][12]=2;
                    vitri[14][12]=2;
                    vitri[15][12]=2;
                }
                preset();
                start(e,isMoving);
                break;
            case -1:
                window.close();
                break;
            default:
                    window.clear();
                    menu.render(&window);
                    window.display();
                    gameStatus=menu.getEvent(&window);//,e);
                break;
            }
        }
    }
    return 0;
}
