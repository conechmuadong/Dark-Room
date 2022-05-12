#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.h"
#include<bits/stdc++.h>
using namespace std;
using namespace sf;

RenderWindow window(VideoMode(880, 600), "Re_Schola");

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
Texture lo;
Texture box;
Texture blank;
int vitri[25][15]; /// 4 toi vinh vien ko qua duoc 5 la nen duoc hien 6 la nen bi toi
Sprite indovat[1000];
/// do lech hinh nhan vat
int deltax=30;
int deltay=46;
/// so do vat
int demdovat=4;
/// next level
int iscomplete=0;
int rickroll=0;
Texture Tdoor;
Sprite door;
Texture toi,gantoi;
Sprite dark,partdark;
int chayloading=0;
map<string,Sound> sounds;
map<string,SoundBuffer> soundbuffers;
int isloading[10];
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
                window.draw(door);
            }
            if(animated.getPosition().y+34<=3*40&&animated.getPosition().x+10==18*40) {
                window.draw(door);
                window.draw(animated);
            } else {
                window.draw(door);
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

    /// door
    Tdoor.loadFromFile("data/item/door.png");
    door.setTexture(Tdoor);
    door.setPosition(18*40,2*40);

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
                if(rickroll==1) {
                    if(chayloading==0) {
                        loading_sceen();
                        animated.setPosition(40*2-10,40*5+6);
                        chayloading=1;
                        toi.loadFromFile("data/item/dark.png");
                        gantoi.loadFromFile("data/item/partdark.png");
                    }
                    control_map2(e);
                } else
                    controls(e);
                cout<<"Rickroll="<<rickroll<<endl;
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
