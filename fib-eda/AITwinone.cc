
/**
* Author: Twinone (Luuk Willemsen)
* Strategy:
*/
#include <iomanip>
#include <iostream>
#include <vector>
#include "Player.hh"


using namespace std;

#define S(x) #x
#define SX(x) S(x)

#define PLAYER_NAME Twinone
#define DEBUG true

#include <vector>

#ifdef DEBUG
#include <fstream>
#endif





struct PLAYER_NAME : public Player {
  //////////////////////////////
  ////// AI Logic //////////////
  //////////////////////////////
  /**


  - Avoid missiles
  - Avoid rocks

  - Move to bonuses
  - (Kill?)

  - Hold at horizontal position
  - Hold at vertical position


  */
  struct Details {
    int holding_row;
    int last_move;
  };

  vector<Details> ss_details;

  Details* details(Starship_Id sid) {
    return &ss_details[sid-begin(me())];
  }

  void init() {
    init_common();
    analyze_map();
    ss_details.reserve(number_starships_per_player());
    // Setup holding rows
    int n = number_rows() / number_starships_per_player();
    dbg << "rows per ship : "<<n <<endl;
    for (int i = 0; i < number_starships_per_player(); ++i) {
      details(sid(i))->last_move = I_DEFAULT;
      details(sid(i))->holding_row = i*n + n/2;
      dbg << "holding_row of " << i << " is " << ss_details[i].holding_row << endl;
    }
  }


  void cleanup() {
  }

  int ydir = 0;
  void play_round() {
    int index = 0;
    for (Starship_Id sid = begin(me()); sid != end(me()); ++sid) {
      Starship s = starship(sid);
      dbg << "######## ship=" << sid << " round=" << round() << " ";
      if (!s.alive) {
        dbg << "dead" << endl << endl;
        index++;
        continue;
      }
      dbg<<"pos=("<<first(s.pos)<<","<<second(s.pos)<<","<<offset(s.pos)<<") ########################" << endl;
      init_dirmap();
      init_curr_dirmap();

      ydir = 0;
      int cval;

      // strategies
      cval =      100;  s_kill(sid, cval);                      add_curr_dirmap(cval);
      cval =   250000;  s_get_bonus(sid, cval);                 add_curr_dirmap(cval);
      cval =   500000;  s_wall_collision(sid, cval);            add_curr_dirmap(cval);
      cval =   750000;  s_dangerously_close_rivals(sid, cval);  add_curr_dirmap(cval);
      cval =  1250000;  s_dodge_starship_behind_me(sid, cval);  add_curr_dirmap(cval);
      cval =  2500000;  s_imm_collision(sid, cval);             add_curr_dirmap(cval);
      cval =  5000000;  s_dodge_missile(sid, cval);             add_curr_dirmap(cval);
      cval = 10000000;  s_valid(sid, cval);                     add_curr_dirmap(cval);

      // Initial map
      inccd(I_SLOW_UP,   2); inccd(I_UP,      25); inccd(I_FAST_UP,   13);
      inccd(I_SLOW,      0); inccd(I_DEFAULT, 26); inccd(I_FAST,      14);
      inccd(I_SLOW_DOWN, 2); inccd(I_DOWN,    25); inccd(I_FAST_DOWN, 13);
      inccd(I_MISSILE,   1);

      // xdir
      if (offset(s.pos) < 25) { inccd(I_FAST, 15); inccd(I_FAST_UP, 15); inccd(I_FAST_DOWN, 15); }

      // yir...
      int hr = details(sid)->holding_row;
      if (first(s.pos) < hr-1) { ydir =  1; }
      if (first(s.pos) > hr+1) { ydir = -1; }

      int ydirval = 2;

      if (ydir > 0) {inccd(I_SLOW_DOWN, ydirval/2); inccd(I_DOWN, ydirval); inccd(I_FAST_DOWN, ydirval);}
      if (ydir < 0) {inccd(I_SLOW_UP,   ydirval/2); inccd(I_UP,   ydirval); inccd(I_FAST_UP,   ydirval);}


      dbg << "FINAL DIRMAP" << endl; print_dirmap(); dbg << endl;
      perform_move(sid);
      dbg << endl << endl;
      index++;
    }
  }





  //////////////////////////////
  ////// Boilerplate code //////
  //////////////////////////////
  #include "common.cc"
  static Player* factory () {
    return new PLAYER_NAME;
  }

  ofstream dbg;

  virtual void play () {
    if (round() == 0) {
      if (DEBUG) dbg.open(string(SX(PLAYER_NAME)) + ".log");
      init();
    }
    play_round();
    if (round() == number_rounds() -1) {
      cleanup();
      if (DEBUG) dbg.close();
    }
  }


  bool up(Dir d)   { return d == SLOW_UP   or d == UP   or d == FAST_UP;   }
  bool down(Dir d) { return d == SLOW_DOWN or d == DOWN or d == FAST_DOWN; }
};


/**
* Do not modify the following line.
*/
RegisterPlayer(PLAYER_NAME);
