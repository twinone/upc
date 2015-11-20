
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
    int holding_col_margin;
    int holding_row_margin;
    int last_move_f;

    int rd;
    int last_rd;
    // s_wall_collision
    int rock_dir;
    int rock_col;

  } Details;

  vector<Details> ss_details;

  Details *details(Starship_Id sid) {
    return &ss_details[sid-begin(me())];
  }


  int mpbr, mmbr;

  void init() {
    init_common();
    dbg << "mpbr: " << mpbr << ", mmbr: " << mmbr << endl;
    analyze_map(mpbr, mmbr);
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

    }

  }
  // Run 10 times per game, including at startup
  void run_analysis() {
    int n = number_rows() / number_starships_per_player();
    int col = get_max_rival_ship_offset();
    dbg << "max rival: " << col << endl;
    col = min(number_window_columns()-3, col); // hold at most at -3
    col = max(10, col); // hold at least at col 10


    for (int i = 0; i < number_starships_per_player(); ++i) {
      Details *d = details(sid(i));
      d->holding_row = i*n + n/2;
      d->holding_col = number_window_columns() / 5 * 4;
      if (i == 0) {
        d->holding_row = get_max_money(0, number_rows()/2);
      } else {
        d->holding_row = get_max_money(number_rows()/2, number_rows());
      }
      dbg << "round="<<round() <<"ship " << sid(i) << " holding at (" << d->holding_row << "," << d->holding_col << ")" << endl;
    }
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
      // Avoids moving to any cell that's not a valid move
      if (t) { s_valid(sid);                                                          add_curr_dirmap(1 << (sw--)); t = tie(); }
      // Avoids moving to any cell at which there is a missile in the next turn
      if (t) { s_dodge_missile(sid);            dbg_pcdt("dodge_missile");            add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_imm_coll_self(sid);            dbg_pcdt("imm_coll_self");            add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_imm_collision(sid, ASTEROID);  dbg_pcdt("imm_coll_ast");            add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_imm_collision(sid, STARSHIP);  dbg_pcdt("imm_coll_sship");          add_curr_dirmap(1 << (sw--)); t = tie(); }
      // If we do thqis after imm_collision, we risk being shot at the next turn
      if (t) { s_dodge_starship_behind_me(sid); dbg_pcdt("dodge_starship_behind_me"); add_curr_dirmap(1 << (sw--)); t = tie(); }

      // If there's a rival that can collide into us and is in front of us, we break
      if (t) { s_break_behind_rivals(sid);      dbg_pcdt("break_behind_rivals");      add_curr_dirmap(1 << (sw--)); t = tie(); }
      // Don't move into positions other people can move into (people with stupid AI)
      if (t) { s_goto_same_as_rival(sid);       dbg_pcdt("goto_same_as_rival");       add_curr_dirmap(1 << (sw--)); t = tie(); }
      // Don't move into positions other people can move into (aggressively)
      if (t) { s_avoid_aggressive_rival(sid);       dbg_pcdt("aggresive");       add_curr_dirmap(1 << (sw--)); t = tie(); }
      // Don't repeat move if we're chasing
      if (t) { s_get_bonus(sid);                dbg_pcdt("get_bonus");                add_curr_dirmap(1 << (sw--)); t = tie(); }
      // Try to go around a wall of rocks, if not possible, shoot
      // with distance=2, it will move up when holding row is down and:
      // ...
      // S.X
      // X..
      // and it should go forward, and then down
      // But that avoids breaking into a wall
      if (t) { s_wall_collision(sid, 1);        dbg_pcdt("wall_collision");           add_curr_dirmap(1 << (sw--)); t = tie(); }
      // Pros: Avoid conflicting strategies (like )
      if (t) { s_repeated_move(sid);            dbg_pcdt("repeated_move");            add_curr_dirmap(1 << (sw--)); t = tie(); }
      // Avoid going right behind an obstacle
      // this breaks holding_row
      // if removed, problems are:
      // moving behind a rock with little space behind
      if (offset(s.pos) < 5)
      if (t) { s_behind_asteroid(sid);          dbg_pcdt("behind_asteroid");          add_curr_dirmap(1 << (sw--)); t = tie(); }

      //
      if (t) { s_dangerously_close_rivals(sid); dbg_pcdt("dangerously_close_rivals"); add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_kill(sid);                     dbg_pcdt("kill");                     add_curr_dirmap(1 << (sw--)); t = tie(); }
      if (t) { s_chase(sid, 1);                 dbg_pcdt("chase");                    add_curr_dirmap(1 << (sw--)); t = tie(); }

      if (t) { s_wall_collision(sid, 2);        dbg_pcdt("wall_collision");           add_curr_dirmap(1 << (sw--)); t = tie(); }

      // Move towards the holding row
      if (t) { s_holding_row(sid);              dbg_pcdt("holding row");              add_curr_dirmap(1 << (sw--)); t = tie(); }
      // Move towards the holding col
      if (t) { s_holding_col(sid);              dbg_pcdt("holding col");              add_curr_dirmap(1 << (sw--)); t = tie(); }
      // Default map
      if (t) { s_default(sid);                  dbg_pcdt("default");                  add_curr_dirmap(1 << (sw--)); t = tie(); }

      dbg << "FINAL DIRMAP" << endl; dbg_print_dirmap(); dbg << endl;
      dbg << endl << endl;


      perform_move(sid);
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
    int freq = 1;
    if (round() % freq == 0) {
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
