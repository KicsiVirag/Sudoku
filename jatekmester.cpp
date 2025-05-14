#include "jatekmester.hpp"

using namespace genv;
using namespace std;

JatekMester::JatekMester(int w, int h): width(w), height(h), running(true) {
    gout.open(width, height);
}

void JatekMester::run(){
    enum State {MENU, GAME, WIN};
    State state = MENU;
    event ev;

    gout.loaded_font("Liberation Sans Bold", 24, true);

    while(running && gin >> ev){
        switch(state){
        case MENU:
            gout << mevo_to(0, 0) << color(240, 240, 245) << box(width, height);

            string title = "SUDOKU";
            int title_width = gout.twidth(title);
            gout << font("Liberation Sans Bold", 48)
                 << move_to(width/2 - title_width/2, height/3);
                 << color(50, 50, 150) << text(title);

            string instruction = "Nyomj meg egy billentyût a kezdéshez";
            string exit_info= "ESC a kilépéshez";
            int instr_width = gout.twidth(instruction);

            gout << font("Liberation Sans Bold", 20)
                 << move_to(width/2-instr_width/2, height/2)
                 << color(80, 80, 80) << text(instruction);

            gout << move_to(width/2 - gout.twidth(exit_info)/2, height/2 +30)
                 << color(150, 50, 50) << text(exit_info);

            gout << refresh;

            if(ev.keycode == key_escape){
                running = false;
            }
            if(ev.keycode != 0 ){
                state = GAME;
            }
            break;

        }
    }
}
