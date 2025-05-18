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

    gout.load_font("Liberation Sans Bold", 24, true);

    while(running && gin >> ev){
        switch(state){
            case MENU: {

                gout << move_to(0, 0) << color(240, 240, 245) << box(width, height);

                string title = "SUDOKU";
                int title_width = gout.twidth(title);
                gout << font("Liberation Sans Bold", 48)
                     << move_to(width/2 - title_width/2, height/3)
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


            case WIN:{
                gout << move_to(0, 0) << color(220, 255, 220) << box(width,height);

                string win_msg = "Gratulálok! Kész a SUDOKU!";
                int msg_width = gout.twidth(win_msg);

                gout << font("Liberation Sans Bold", 32)
                     << move_to(width/2 -msg_width/2, height/3)
                     << color(0, 100, 0) << text(win_msg);

                string new_game = "Nyomj bármilyen billentyû egy új játékhoz";
                string exit_game = "ESC a kilépéshez";

                gout << font("Liberation Sans Bold", 20)
                     << move_to(width/2 - gout.twidth(new_game)/2, height/2)
                     << color(80, 80, 80) << text(new_game);

                gout << move_to(width/2 - gout.twidth(exit_game)/2, height/2 + 30)
                     << color(150, 50, 50) << text(exit_game);

                gout << refresh;

                if (!(gin >> ev)) {
                    running = false;
                    break;
                }

                if (ev.type == ev_key) {
                    if (ev.keycode == key_escape) {
                        running = false;
                    } else {
                        board = SudokuBoard();
                        state = GAME;
                    }
                }
                break;
            }

            case GAME: {
                if(ev.keycode == key_escape){
                    running = false;
                    break;
                }
                board.handle(ev);
                board.check_conflicts();
                gout << move_to(0, 0) << color(240,240,240) << box(width, height);
                board.draw();
                if(board.check_win()){
                    state = WIN;
                    continue;
                }
                gout << refresh;
                break;
            }
        }
    }
}
