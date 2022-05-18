#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include<bits/stdc++.h>
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
    int ques;
    Sprite in_o;
} vitris[25][15];
Texture bgmenu;
Sprite in_bgmenu;
Texture stand;
Sprite stands(stand);
Texture animation;
Sprite animated(animation);
Clock animationtimer;
IntRect curframe;
float speedtimer=0.5f;
int speed=40;
float timer=0.2f;
/// 0=up 1=down 2=right 3=left
int direction=2;
/// do vat
Sprite restart;
Texture lo;
Texture box;
Texture blank;
Texture exits;
Sprite finish;
int vitri[25][15]; /// 4 toi vinh vien ko qua duoc 5 la nen duoc hien 6 la nen bi toi
Sprite indovat[1000];
/// do lech hinh nhan vat
int deltax=30;
int deltay=46;
/// so do vat
int demdovat=7;
/// next level
int iscomplete=0;
int rickroll=10;
Texture Tdoor;
Sprite door;
Texture toi,gantoi;
Sprite dark,partdark;
Font loads;
int chayloading=0;
int isloading[10];
map<string,Sound> sounds;
map<string,SoundBuffer> soundbuffers;
Texture nut_restart;
/// map3
int delx=6;
Sprite graphic[21*14+1];
Font fonts;
/// inventory
int isHolding=0;
int Inventory=0;
int issupa1=0;
int issupa2=0;
int isDam1=0;
int isDam2=0;
int isdone1=0,isdone2=0;
Texture indung,insai;
string thats="data/music/supa.ogg";
string thats1="data/music/love_castle.ogg";
string map2_bg="data/music/map2_bg.ogg";
string sf_door_open="data/music/door_open.ogg";
string menu_bgmusic="data/music/menubg.ogg";
string sf_click="data/music/click.ogg";
unsigned long long demso=0;
char convert(int ascii) {
    return (char)ascii;
}
void sua() {
    cout<<"chay"<<demso<<endl;
    demso++;
}
void ve_3() {
    window.draw(in_bgmenu);
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++) {
//            if(vitris[i][j].check_done==1||vitris[i][j].check_done==2) {
//                vitris[i][j].in_o.setTexture(indung);
//                vitris[i][j].in_o.setPosition(40*i,40*j);
//            }
            if(vitris[i][j].check_done==0) {
                vitris[i][j].in_o.setTexture(insai);
                vitris[i][j].in_o.setPosition(40*i,40*j);
            }
            window.draw(vitris[i][j].in_o);
        }
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++)
            if(vitris[i][j].in==true)
                window.draw(vitris[i][j].chu);
    //if(isdone1==1&&isdone2==1)
    // window.draw(door);
    window.draw(animated);
    window.display();
}
void ve() {
    window.clear();
    if(rickroll==0) {
        window.draw(in_bgmenu);
        window.draw(restart);
        for(int i=0; i<=22*15; i++)
            window.draw(indovat[i]);
        if(iscomplete==1) {
            //cout<<(animated.getPosition().y+34)/40<<" "<<(animated.getPosition().x+10)/40<<endl<<"--------------"<<endl;
//            if(animated.getPosition().y+34>3*40&&animated.getPosition().x+10==18*40) {
//                window.draw(animated);
//                window.draw(door);
//            }
//            if(animated.getPosition().y+34<=3*40&&animated.getPosition().x+10==18*40) {
//                window.draw(door);
//                window.draw(animated);
//            } else {
            window.draw(restart);
            //window.draw(door);
            window.draw(animated);
            //}
        } else {
            window.draw(restart);
            window.draw(animated);
        }
//    window.draw(door);
//    window.draw(animated);
    } else {
        window.clear();
        window.draw(in_bgmenu);
        for(int i=0; i<=23*15; i++)
            window.draw(indovat[i]);
        window.draw(finish);
        window.draw(animated);
    }
    window.display();
}
void update_word_data(int xpos,int ypos,string s) {
    vitris[xpos][ypos].chu.setFont(fonts);
    vitris[xpos][ypos].chu.setCharacterSize(31);
    vitris[xpos][ypos].chu.setColor(Color::White);
    vitris[xpos][ypos].chu.setString(s);
    vitris[xpos][ypos].chu.setPosition(vitris[xpos][ypos].x,vitris[xpos][ypos].y);
}
void bg_music_map3(string paths,int playthatthing) {
    if(playthatthing==2) {
        sounds[paths].stop();
        soundbuffers[thats1].loadFromFile(thats1);
        sounds[thats1]=Sound{soundbuffers[thats1]};
        sounds[thats1].play();
        return;
    }
    if(playthatthing==1) {
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
    int cnt=0,cnt1=0;
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++) {
            if(vitris[i][j].check_done==1) {
                cnt++;
            }
            if(vitris[i][j].check_done==2)
                cnt1++;
        }
    if(cnt==9&&isdone1==0) {
        return 1;
    }
    if(cnt1==10&&isdone2==0) {
        return 2;
    }
    return 0;
}
void check_key_is_fill() {
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++) {
            if(vitris[i][j].key==vitris[i][j].ascii&&vitris[i][j].ascii!=0) {
                if(vitris[i][j].ques==1) {
                    vitris[i][j].check_done=1;
                    vitris[i][j].in_o.setTexture(indung);
                    vitris[i][j].in_o.setPosition(40*i,40*j);
                }
                if(vitris[i][j].ques==2) {
                    vitris[i][j].check_done=2;
                    vitris[i][j].in_o.setTexture(indung);
                    vitris[i][j].in_o.setPosition(40*i,40*j);
                }
                vitris[i][j].nhat=3;
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
    if (vitris[posx / 40][posy / 40].ktmove == 1) {

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
    if(isHolding==0&&vitris[posx][posy].nhat==1)
        return 1;

    if(isHolding==1&&vitris[posx][posy].nhat==0)
        return 2;
    if(isHolding==1&&vitris[posx][posy].nhat==2)
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
        vitris[posx][posy].in=false;
        Inventory=vitris[posx][posy].ascii;
        isHolding=1;
        vitris[posx][posy].ascii=0;
        vitris[posx][posy].ktmove=0;
        vitris[posx][posy].nhat=2;
    }
    if(decision==2&&vitris[posx][posy].nhat!=3) {
        vitris[posx][posy].in=true;
        vitris[posx][posy].ktmove=1;
        vitris[posx][posy].ascii=Inventory;
        vitris[posx][posy].nhat=1;
        string tmp(1,convert(vitris[posx][posy].ascii));
        //cout<<tmp<<endl;
        update_word_data(posx,posy,tmp);
        isHolding=0;
        Inventory=0;
    }
    ve_3();
}

int chay_tieng=0;
int ktketthucgame() {
    int dem=0;
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++)
            if(vitri[i][j]==3)
                dem++;
    //  cout<<demdovat<<endl;
    if(dem==demdovat&&chay_tieng==0) {
        chay_tieng=1;
        sounds[sf_door_open].play();
    }
    if(dem==demdovat)
        return 1;
    return 0;
}
int ktketthucrickroll() {
    int posx=animated.getPosition().x;
    int posy=animated.getPosition().y;
    posx+=10;
    posy+=34;
    if(posx/40==19&&posy/40==12)
        return 1;
    return 0;
    /**
       in man moi thi de o o x = 19 y=12
     *
     */

}
void chayamthanh(string paths) {

    soundbuffers[paths].loadFromFile(paths);
    sounds[paths]=Sound{soundbuffers[paths]};
    sounds[paths].play();
}
void Stops(string paths) {
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
    if(20*40==posx&&40==posy&&ktketthucgame()==1)
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
    Stops("data/music/laugh2.ogg");
    Stops("data/music/golden.ogg");
    Stops("data/music/door.ogg");
    int framecnt=4;
    float framerate=0.03;
    float chay=1;
    Music asley;
    asley.openFromFile("data/music/stage_e.ogg");
    asley.setLoop(true);
    asley.play();
    Text skips;
    skips.setFont(loads);
    skips.setString("Press Esc to Skip");
    skips.setPosition(40*17,40*1);
    skips.setCharacterSize(16);
    skips.setColor(Color::White);
    while(1) {
        window.pollEvent(e);
        if(e.type==Event::KeyPressed)
            if(e.key.code==Keyboard::Escape)
                break;
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
        window.draw(skips);
        window.display();
    }
}
void startdovat() {
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
void ketthuc() {
    Text endgame;
    endgame.setFont(loads);
    endgame.setString("THE END");
    endgame.setPosition(40*8,40*6);
    endgame.setCharacterSize(60);
    endgame.setColor(Color::White);
    Event e;
    while(1) {
        window.pollEvent(e);
        if(e.type== Event::Closed)
            window.close();
        window.clear();
        window.draw(endgame);
        window.display();
    }
}
void update_darkness(int directions) {
    int posx=animated.getPosition().x;
    int posy=animated.getPosition().y;
    posx+=10;
    posy+=34;
    if(posx==19*40&&posy==12*40) {
        ketthuc();
    }
    if(isloading[5]==0) {
        chayamthanh("data/music/bg2.ogg");
        isloading[5]=1;
    }
    cout<<posx/40<<" "<<posy/40<<endl;
    if(posx/40==4&&posy/40==4&&isloading[6]==0) {
        chayamthanh("data/music/footstep.ogg");
        isloading[6]=1;
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
        cout<<"TRIGGER"<<endl;
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
    //vitri[posx/40][posy/40]=1;
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
            // cout<<ktketthucgame()<<endl;
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

    if(iscomplete==1||ktketthucgame()==1) {
        iscomplete=1;
    }
    // cout<<"Door: "<<(door.getPosition().x)/40<<" "<<door.getPosition().y/40<<endl;

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
        direction=1;
    } else if(e.key.code==Keyboard::S) {
//        cout<<check_move_possible(1)<<endl;
        if(check_move_in_dark_possible(1)==1) {
            update_darkness(1);
            move_down(timer);
            if(animated.getPosition().y<526)
                animated.move(0,speed);
        } else
            move_down(timer);
        direction=0;
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
        direction=2;
    } else if(e.key.code==Keyboard::A) {
//        cout<<check_move_possible(3)<<endl;
        if(check_move_in_dark_possible(3)) {
            update_darkness(3);
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
    /// loading word
    sounds[map2_bg].stop();
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
    vitri[20][12]=7;
    exits.loadFromFile("data/item/1.png");
    finish.setTexture(exits);
    finish.setPosition(20*40,12*40);
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
void restart_game() {
    animated.setPosition(30,46+40*3);
    vitri[12][11]=1;
    vitri[6][5]=1;
    vitri[5][11]=1;
    vitri[8][11]=1;
    vitri[5][17]=1;
    vitri[4][4]=1;
    vitri[16][11]=1;
    vitri[15][2]=1;
    vitri[3][7]=2;
    vitri[5][9]=2;
    vitri[3][12]=2;
    vitri[5][12]=2;
    vitri[4][8]=2;
    vitri[4][19]=2;
    vitri[10][6]=2;
    iscomplete=0;
}
void preset_map2() {
    vitri[12][11]=1;
    vitri[6][5]=1;
    vitri[5][11]=1;
    vitri[8][11]=1;
    vitri[5][17]=1;
    vitri[4][4]=1;
    vitri[16][11]=1;
    vitri[15][2]=1;
    vitri[3][7]=2;
    vitri[5][9]=2;
    vitri[3][12]=2;
    vitri[5][12]=2;
    vitri[4][8]=2;
    vitri[4][19]=2;
    vitri[10][6]=2;;
    /// music
    /// background menu
    startdovat();
    animated.setPosition(30,46+40*3);
    nut_restart.loadFromFile("data/button/restart.png");
    restart.setTexture(nut_restart);
    restart.setPosition(1*40,1*40);
    restart.setScale(Vector2f(0.5,0.5));
    /// door
    door.setPosition(18*40,2*40);
    animated.setScale(Vector2f(0.7,0.7));
}
void loadings() {
    sounds[thats].stop();
    sounds[thats1].stop();
    loads.loadFromFile("data/font/PIXEL.TTF");
    Text loading;
    loading.setFont(loads);
    loading.setString("LOADING");
    loading.setPosition(40*14,40*10);
    loading.setCharacterSize(40);
    loading.setColor(Color::White);
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
    soundbuffers[map2_bg].loadFromFile(map2_bg);
    sounds[map2_bg]=Sound{soundbuffers[map2_bg]};
    sounds[map2_bg].play();
}

void open_da_gate() {
    Tdoor.loadFromFile("data/item/door.png");
    door.setTexture(Tdoor);
    door.setPosition(20*40,8*40);
    int posx=animated.getPosition().x;
    int posy=animated.getPosition().y;
    posx+=10;
    posy+=34;
    if(posx==20*40&&posy==40*1) {
        loadings();
        rickroll=0;
    }
}
int chay_tieng2=0;
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
    if(check_game_complete_map_3()==1&&issupa1==0) {
        bg_music_map3("data/music/bgmap3.ogg",1);
        issupa1=1;
        isdone1=1;
    }
    if(sounds[thats].getStatus()==Sound::Stopped&&issupa2==0&&issupa1==1&&isDam1==0) {
        bg_music_map3("data/music/bgmap3.ogg",0);
        issupa2=1;
    }
    if(check_game_complete_map_3()==2&&isDam1==0) {
        bg_music_map3("data/music/bgmap3.ogg",2);
        isDam1=1;
        isdone2=1;
    }
    if(sounds[thats1].getStatus()==Sound::Stopped&&isDam2==0&&isDam1==1&&issupa1==0) {
        bg_music_map3("data/music/bgmap3.ogg",0);
        isDam2=1;
    }
    if(chay_tieng2==0&&isdone1==1&&isdone2==1) {
        sounds[sf_door_open].play();
        chay_tieng2=1;
    }
    if(isdone1==1&&isdone2==1) {
        open_da_gate();
    }
    //cout<<isHolding<<" "<<Inventory<<endl;
    ve_3();
}
void bebug(int xpos,int ypos,string s) {
    vitris[xpos][ypos].in=true;
    vitris[xpos][ypos].nhat=true;
    vitris[xpos][ypos].chu.setFont(fonts);
    vitris[xpos][ypos].chu.setCharacterSize(31);
    vitris[xpos][ypos].chu.setColor(Color::White);
    vitris[xpos][ypos].chu.setString(s);
    vitris[xpos][ypos].ascii=(int)s[0];
    vitris[xpos][ypos].ktmove=1;
    vitris[xpos][ypos].x=40*xpos+delx;
    vitris[xpos][ypos].y=ypos*40+delx;
    vitris[xpos][ypos].chu.setPosition(vitris[xpos][ypos].x,vitris[xpos][ypos].y);
}
void set_key(int y,int x,char s,int question) {
    vitris[x][y].key=(int)s;
    vitris[x][y].check_done=0;
    vitris[x][y].ques=question;
}
void preset() {
    cout<<"chay"<<endl;
    indung.loadFromFile("data/item/keyarea/true.png");
    insai.loadFromFile("data/item/keyarea/false.png");
    fonts.loadFromFile("data/font/PIXEL.TTF");

    window.setFramerateLimit(60);
    animated.setPosition(deltax,deltay);
    animated.setScale(Vector2f(0.7,0.7));
    bg_music_map3("data/music/bgmap3.ogg",0);
    for(int i=0; i<=21; i++)
        for(int j=0; j<=14; j++) {
            vitris[i][j].in=false;
            vitris[i][j].nhat=false;
            vitris[i][j].ascii=0;
            vitris[i][j].x=40*i+delx;
            vitris[i][j].y=j*40+delx;
            vitris[i][j].check_done=3;
        }
    bebug(3,2,"S");
    bebug(5,12,"U");
    bebug(18,6,"P");
    bebug(14,5,"A");
    bebug(19,13,"I");
    bebug(9,5,"D");
    bebug(11,2,"O");
    bebug(7,4,"L");
    bebug(8,12,"Z");
    bebug(16,8,"T");
    bebug(5,11,"L");
    bebug(7,3,"Y");
    bebug(4,8,"E");
    bebug(16,7,"R");
    bebug(4,8,"O");
    bebug(7,6,"V");
    bebug(9,3,"E");
    bebug(6,2,"C");
    bebug(16,8,"A");
    bebug(6,6,"S");
    bebug(20,5,"T");
    bebug(17,8,"L");
    bebug(13,8,"E");
    bebug(3,3,"E");
    for(int i=3; i<=6; i++)
        vitris[i][2].keyarea=1;
    for(int i=8; i<=11; i++)
        vitris[i][2].keyarea=1;
    set_key(2,3,'S',1);
    set_key(2,4,'U',1);
    set_key(2,5,'P',1);
    set_key(2,6,'E',1);
    set_key(2,7,'R',1);
    set_key(2,9,'I',1);
    set_key(2,10,'D',1);
    set_key(2,11,'O',1);
    set_key(2,12,'L',1);
    set_key(8,3,'L',2);
    set_key(8,4,'O',2);
    set_key(8,5,'V',2);
    set_key(8,6,'E',2);
    set_key(8,8,'C',2);
    set_key(8,9,'A',2);
    set_key(8,10,'S',2);
    set_key(8,11,'T',2);
    set_key(8,12,'L',2);
    set_key(8,13,'E',2);
}
int is_complete_set_map_2=0;
int is_complete_set_map_3=0;
void start() {
    lo.loadFromFile("data/item/hole.png");
    blank.loadFromFile("data/item/blank.png");
    box.loadFromFile("data/item/box.png");
    bgmenu.loadFromFile("data/bg/menu/bg.png");
    soundbuffers[sf_door_open].loadFromFile(sf_door_open);
    sounds[sf_door_open]=Sound{soundbuffers[sf_door_open]};
    Texture T_buttonplay,T_buttonexit,T_menu;
    T_buttonplay.loadFromFile("data/button/button_play.png");
    T_buttonexit.loadFromFile("data/button/button_exit.png");
    T_menu.loadFromFile("data/bg/menu.png");
    soundbuffers[menu_bgmusic].loadFromFile(menu_bgmusic);
    sounds[menu_bgmusic]=Sound{soundbuffers[menu_bgmusic]};
    sounds[menu_bgmusic].play();
    soundbuffers[sf_click].loadFromFile(sf_click);
    sounds[sf_click]=Sound{soundbuffers[sf_click]};
    Sprite menubg(T_menu);
    Sprite button_play(T_buttonplay);
    Sprite button_exit(T_buttonexit);
    button_play.setPosition(40*9+20,40*7);
    button_exit.setPosition(40*9+20,40*9);
    in_bgmenu.setTexture(bgmenu);
    window.setFramerateLimit(60);
    Text names;
    loads.loadFromFile("data/font/PIXEL.TTF");
    names.setFont(loads);
    names.setString("DARK ROOM");
    names.setPosition(40*5,40*2);
    names.setCharacterSize(60);
    names.setColor(Color::Red);
    while (window.isOpen()) {
        Event event,e;
        int isMoving=0;
        Vector2i pos=Mouse::getPosition(window);
        while(window.pollEvent(e)) {
            if(e.type== Event::Closed)
                window.close();
            ///nhan nut
            if(rickroll==2&&is_complete_set_map_3==0) {
                is_complete_set_map_3=1;
                preset();
            }
            if(rickroll==0&&is_complete_set_map_2==0) {
                preset_map2();
                is_complete_set_map_2=1;
            }
            //cout<<"check"<<rickroll<<endl;
            if(e.type==Event::KeyPressed) {
                if(rickroll==2)
                    control_map3(e);
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
                if(rickroll==0) {
                    controls(e);
                }

            }
            if(rickroll==0) {
                if(e.type==Event::MouseButtonPressed)
                    if(e.key.code==Mouse::Left)
                        if(restart.getGlobalBounds().contains(pos.x,pos.y)) {
                            restart_game();
                        }
            }
            if(rickroll==10) {
                if(e.type==Event::MouseButtonPressed)
                    if(e.key.code==Mouse::Left)
                        if(button_play.getGlobalBounds().contains(pos.x,pos.y)) {
                            sounds[sf_click].play();
                            Text loading;
                            loading.setFont(loads);
                            loading.setString("LOADING");
                            loading.setPosition(40*14,40*10);
                            loading.setCharacterSize(40);
                            loading.setColor(Color::White);
                            Texture loading_run;
                            Sprite aniloading(loading_run);
                            aniloading.setPosition(630,470);
                            loading_run.loadFromFile("data/ani/run_left.png");
                            rickroll=2;
                            sounds[menu_bgmusic].stop();
                            float frame=0;
                            float anispeed=0.08;
                            int framecnt=4;
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
                if(e.key.code==Mouse::Left)
                    if(button_exit.getGlobalBounds().contains(pos.x,pos.y)) {
                        sounds[sf_click].play();
                        window.close();
                    }
            }
            if(isMoving==0)
                update_idle(direction);
        }
        if(rickroll==2)
            ve_3();
        if(rickroll!=2&&rickroll!=10) {
            ve();
        }
        if(rickroll==10) {
            window.clear();
            window.draw(menubg);
            window.draw(button_play);
            window.draw(button_exit);
            window.draw(names);
            window.display();
        }
    }
}
int main() {
    start();
    return 0;
}
