
/**
* Author: Twinone (Luuk Willemsen)
* Strategy:
*/
#include <iomanip>
#include <iostream>
#include <vector>
#include <sstream>
#include "Player.hh"



using namespace std;

#define S(x) #x
#define SX(x) S(x)

#define PLAYER_NAME Twinone
#define DEBUG true

#include <vector>

#include <fstream>


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

  typedef struct Details {
    int holding_row;
    int holding_col;
    int holding_col_margin = 3;
    int holding_row_margin = 2;
    int last_move_f = F_DEFAULT;
    int rd = -1;
    int last_rd = -1;
    int rock_dir = I_DEFAULT;
    int rock_col = 0;
  } Details;
  vector<Details> ss_details;

  Details* details(Starship_Id sid) {
    return &ss_details[sid-begin(me())];
  }



  void init() {
    init_common();
    ss_details.reserve(number_starships_per_player());

    int n = number_rows() / number_starships_per_player();
    dbg << "rows per ship : " << n << endl;
    int base_hc = number_window_columns() / 3 * 2;
    for (int i = 0; i < number_starships_per_player(); ++i) {
      Details *d = details(sid(i));
      d->holding_col_margin = 3;
      d->holding_row_margin = 1;
      d->last_move_f        = F_DEFAULT;
      d->rd                 = -1;
      d->last_rd            = -1;
      d->rock_dir           = I_DEFAULT;
      d->rock_col           = 0;

      d->holding_row = i*n + n/2;
      d->holding_col = base_hc - number_starships_per_player() + 2*i;
      dbg << "ship " << sid(i) << " holding at (" << d->holding_row << "," << d->holding_col << ")" << endl;
    }
  }
  // Run 10 times per game, including at startup
  void run_analysis() {
    // tell spacecrafts where to hold so they can get more bonuses

    // Higher level functions
  }



  void cleanup() {
  }

  void dbg_pcdt(string s) {
    dbg << s << endl;
    dbg_print_curr_dirmap();
    dbg << "------" << endl;
  }

  void play_round() {
    dbg << "___BEGIN_ROUND_" << round() << endl;
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

      details(sid)->rd = rock_distance(s.pos);

      // strategies
      int sw = 25; // strategy weight
      bool t = true; // tie found
      if (t) { s_valid(sid);                                                          add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_dodge_missile(sid);            dbg_pcdt("dodge_missile");            add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_imm_collision(sid);            dbg_pcdt("imm_collision");            add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_dodge_starship_behind_me(sid); dbg_pcdt("dodge_starship_behind_me"); add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_repeated_move(sid);            dbg_pcdt("repeated_move");            add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_wall_collision(sid);           dbg_pcdt("wall_collision");           add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_dangerously_close_rivals(sid); dbg_pcdt("dangerously_close_rivals"); add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_get_bonus(sid);                dbg_pcdt("get_bonus");                add_curr_dirmap(1 << (sw--)); t = tie(); }
      //if (t) { s_far_wall(sid);                 dbg_pcdt("far_wall");                 add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_kill(sid);                     dbg_pcdt("kill");                     add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_holding_row(sid);              dbg_pcdt("holding row");              add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_holding_col(sid);              dbg_pcdt("holding col");              add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_default(sid);                  dbg_pcdt("default");                  add_curr_dirmap(1 << (sw--)); t = tie(); }


      dbg << "FINAL DIRMAP" << endl; dbg_print_dirmap(); dbg << endl;
      perform_move(sid);
      dbg << endl << endl;


      details(sid)->last_rd = details(sid)->rd;

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
      stringstream ss;
      ss << string(SX(PLAYER_NAME)) << me() << ".log";
      string s;
      ss >> s;
      dbg.open(s);
      init();
    }
    if ((round() % (number_rounds() / 10)) == 0) {
      run_analysis();
    }
    play_round();
    if (round() == number_rounds() -1) {
      cleanup();
      dbg.close();
    }
  }


  bool up(Dir d)   { return d == SLOW_UP   or d == UP   or d == FAST_UP;   }
  bool down(Dir d) { return d == SLOW_DOWN or d == DOWN or d == FAST_DOWN; }
};


/**
* Do not modify the following line.
*/
RegisterPlayer(PLAYER_NAME);
