
const Dir NODIR = {-1, -1};
// Indexes for the vector
static const int I_SLOW_UP   = 0;
static const int I_UP        = 1;
static const int I_FAST_UP   = 2;
static const int I_SLOW      = 3;
static const int I_DEFAULT   = 4;
static const int I_FAST      = 5;
static const int I_SLOW_DOWN = 6;
static const int I_DOWN      = 7;
static const int I_FAST_DOWN = 8;
static const int I_MISSILE   = 9;

static const int F_SLOW_UP   = 1 << 0;
static const int F_UP        = 1 << 1;
static const int F_FAST_UP   = 1 << 2;
static const int F_SLOW      = 1 << 3;
static const int F_DEFAULT   = 1 << 4;
static const int F_FAST      = 1 << 5;
static const int F_SLOW_DOWN = 1 << 6;
static const int F_DOWN      = 1 << 7;
static const int F_FAST_DOWN = 1 << 8;
static const int F_MISSILE   = 1 << 9;

static const int F_MASK_V = F_UP | F_DEFAULT | F_DOWN;
static const int F_MASK_H = F_SLOW | F_DEFAULT | F_FAST;
static const int F_MASK_DOWN = F_SLOW_DOWN | F_DOWN | F_FAST_DOWN;
static const int F_MASK_UP   = F_SLOW_UP   | F_UP   | F_FAST_UP;
static const int F_MASK_SLOW = F_SLOW_UP   | F_SLOW | F_SLOW_DOWN;
static const int F_MASK_FAST = F_FAST_UP   | F_FAST | F_FAST_DOWN;


vector<int> dirmap;
vector<double> curr_dirmap;
vector<Dir> dirs = { SLOW_UP, UP, FAST_UP, SLOW, DEFAULT, FAST, SLOW_DOWN, DOWN, FAST_DOWN, NODIR };

void init_common() {
  dirmap.reserve(10);
  curr_dirmap.reserve(10);
}
Starship_Id sid(int idx) {
  return idx + begin(me());
}


bool tie() {
  bool t = false;
  int max;
  for (int i = 0; i < 10; ++i) {
    if (dirmap[i] > max) {
      max = dirmap[i];
      t = false;
    }
    else if (dirmap[i] == max) t = true;
  }
  if (!t) {
    dbg << "############" << endl;
    dbg << "#  NO TIE! #" << endl;
    dbg << "############" << endl;
  }
  return t;
}

void add_curr_dirmap(int val) {
  for (int i = 0; i < 10; ++i) {
    if (curr_dirmap[i] < -1.0) curr_dirmap[i] = -1.0;
    if (curr_dirmap[i] > 1.0) curr_dirmap[i] = 1.0;
    double m = 0;
    if (curr_dirmap[i] < 0) m = -0.55 + curr_dirmap[i] / 2;
    if (curr_dirmap[i] > 0) m =  0.55 + curr_dirmap[i] / 2;

    dirmap[i] += m * val;
  }

  init_curr_dirmap();
}
void init_dirmap() {
  for (int i = 0; i < 10; ++i) dirmap[i] = 0;
}

void init_curr_dirmap() {
  for (int i = 0; i < 10; ++i) curr_dirmap[i] = 0;
}
// Returns the highest rated rival
Player_Id highest_rated_rival() {
  int max = -1;
  Player_Id pid = 0;
  for (int i = 0; i < number_players(); i++) {
    if (i == me()) continue;
    int s = score(i);
    if (s > max) { pid = i; max = s; }
  }
  return pid;
}
int num_alive_starships() {
  int c;
  for (int i = 0; i < number_starships(); ++i) if (starship(i).alive) c++;
  return c;
}

// Returns the offset of the aircraft from the beginning of the window
int offset(const Pos &p) {
  int n = number_universe_columns();
  int s = second(p) % n;
  int w = round() % n;
  if (w > s) s += n;
  return s - w;
}

string dirToString(Dir d) {
  if (d == UP) return "UP";
  if (d == DOWN) return "DOWN";
  if (d == DEFAULT) return "DEFAULT";
  if (d == FAST_UP) return "FAST_UP";
  if (d == FAST_DOWN) return "FAST_DOWN";
  if (d == FAST) return "FAST";
  if (d == SLOW) return "SLOW";
  if (d == SLOW_UP) return "SLOW_UP";
  if (d == SLOW_DOWN) return "SLOW_DOWN";
  return "NONE";
}

// Increase a cell's value by i
void inccd(int what, double i) {
  dirmap[what] += i;
}

// Increase a cell's value by i
void deccd(int what, double i) {
  inccd(what, -i);
}

bool issetc(int what) {
  return curr_dirmap[what] != 0;
}

// Decrease these cells by i
void deccf(int what, double i) {
  inccf(what, -i);
}

// Increase these cells by i
void inccf(int what, double val) {
  assert(abs(val) <= 1);
  for (int i = 0; i < 10; i++) {
    if (what & (1<<i)) {
      setc(i, val);
    }
  }
}
int flag(int index) {
  assert(index >= 0 && index < 10);
  return 1 << index;
}
void setc(int what, double val) {
  assert(abs(val) <= 1);
  // By default, we only allow to decrease if <0
  // and only allow to increase if >0
  if ((val < 0 && val < curr_dirmap[what]) || (val > 0 && val > curr_dirmap[what]))
    curr_dirmap[what] = val;
}

void dbg_print_dirmap() {
  for (int i = 0; i < 10; i++) {
    if (i%3 == 0 && i != 0) dbg <<endl;
    dbg << right << setw(10) <<  dirmap[i] << "\t";
  }
  dbg<<endl;
}
bool dbg_print_curr_dirmap() {
  bool a = false;
  for (int i = 0; i < 10; i++) if (curr_dirmap[i] != 0) a = true;
  if (!a) return false;
  for (int i = 0; i < 10; i++) {
    if (i%3 == 0 && i != 0) dbg <<endl;
    dbg << right << setw(10) <<  curr_dirmap[i] << "\t";
  }
  dbg<<endl;
  return true;
}

void perform_move(Starship_Id sid) {
  int max = dirmap[0];
  int maxi = 0;
  for (int i = 0; i < 10; ++i) {
    if (dirmap[i] > max) {
      max = dirmap[i];
      maxi = i;
    }
  }
  Dir d = dirs[maxi];
  if (d != NODIR) {
    dbg << "move: " << dirToString(d) << endl;
    move(sid, d);
  }
  else {
    dbg << "move: MISSILE" << endl;
    shoot(sid);
  }
  dbg << "setting last move flag: " << flag(maxi) << endl;
  details(sid)->last_move_f = flag(maxi);
}


// returns behind but not AT pos
Cell behind(const Pos& pos, int &dst) {
  Cell c = cell(pos-DEFAULT);
  for (dst = 1; dst < number_universe_columns()/2; dst++) {
    c = cell(pos-dst*DEFAULT);
    if (c.type == MISSILE || c.type == STARSHIP) {
      return c;
    }
  }
  return c;
}

// Returns the distance to the first object in front of you that's not a missile
Cell in_front(const Pos& pos, int &dst) {
  Cell c = cell(pos+DEFAULT);
  for (dst = 1; dst < number_universe_columns()/2; dst++) {
    c = cell(pos+dst*DEFAULT);
    if (c.type != MISSILE && c.type != EMPTY) {
      return c;
    }
  }
  return c;
}


bool can_self_reach(const Pos& pos, int n) {
  return self_in_area(pos+Dir{-n, -2*n}, pos+Dir{n, 0});
}
// Returns whether a rival can move into this cell in n turns
bool can_rival_reach(const Pos& pos, int n) {
  return rival_in_area(pos+Dir{-n, -2*n}, pos+Dir{n, 0});
}



bool can_rival_reach_now_wo_coll(const Pos& pos) {
  // FIXME
  // ..M
  // X.R
  // Rival cannot reach M because there's an asteroid at X
  bool r = within_universe(pos) &&
       (rival_in_area(pos+Dir{-1, -2}, pos+Dir{0, 0})
    && !type_in_area(pos+Dir{-1, -2}, pos+Dir{0, 0}, ASTEROID))

    || (rival_in_area(pos+Dir{0, -2}, pos+Dir{1, 0})
    && !type_in_area(pos+Dir{0, -2}, pos+Dir{1, 0}, ASTEROID))

    || (rival_in_area(pos+Dir{0, -2}, pos+Dir{0, 0})
    && !type_in_area(pos+Dir{0, -2}, pos+Dir{0, 0}, ASTEROID));
    dbg << "checkinf pos: " << pos << ": " << r << endl;
    return r;
}

bool can_rival_reach_area(const Pos& p1, const Pos& p2, int n) {
  return rival_in_area(p1+Dir{-n, -2*n}, p2+Dir{n, 0});
}


// minrow inclusive, maxrow exclusive
int get_max_money(int minrow, int maxrow) {
  int mpb = 0; mpbr = 0;
  for (int i = minrow; i < maxrow; ++i) {
    int cpb = 0;
    for (int j = 0; j < number_universe_columns(); ++j) {
      Cell c = cell({i,j});
      if (c.type == POINT_BONUS) ++cpb;
    }
    if (cpb > mpb) { mpb = cpb; mpbr = i; }
  }
  return mpbr;
}

void  analyze_map(int &mpbr, int &mmbr) {
  /*
  dbg << "---------------------" << endl;
  dbg << "--  MAP ANALYSIS  ---" << endl;
  dbg << "---------------------" << endl << endl;

  dbg << "Bonus density" << endl;
  dbg << "=============" << endl;
  dbg << "  row    pb    mb rocks score" << endl;
  */

  // analyze bonus density
  int mpb = 0; mpbr = 0;
  int mmb = 0; mmbr = 0;
  int mr = 0; int mrr = 0;
  for (int i = 0; i < number_rows(); ++i) {
    int cpb = 0; int cmb = 0; int cr = 0;
    for (int j = 0; j < number_universe_columns(); ++j) {
      Cell c = cell({i,j});
      if (c.type == POINT_BONUS) ++cpb;
      if (c.type == MISSILE_BONUS) ++cmb;
      if (c.type == ASTEROID) ++cr;
    }

    /*
    dbg << right << setw(5) << i << " "
        << right << setw(5) << cpb << " "
        << right << setw(5) << cmb << " "
        << right << setw(5) << cr << " "
        << right << setw(5) << int(2*cpb+5*cmb-cr) << " "
        << endl;
    */
    if (cpb > mpb) { mpb = cpb; mpbr = i; }
    if (cmb > mmb) { mmb = cmb; mmbr = i; }
    if (cr  > mr)  { mr  = cr;  mrr  = i; }
  }

/**
  dbg << "---------------------" << endl;
  dbg << "most point   bonuses at row " << mpbr << endl;
  dbg << "most missile bonuses at row " << mmbr << endl;
  dbg << "most rocks at row           " << mrr << endl;
  dbg << "---------------------" << endl << endl;

*/
}


////////////////////////////////////////////////////////////////////////////////
////// s_valid
////////////////////////////////////////////////////////////////////////////////
/*
This strategy decreases cells you cannot go to by val
*/
void s_valid(Starship_Id sid) {
  Starship s = starship(sid);
  int up = first(s.pos) != 0;
  int down = first(s.pos) != number_rows() -1;
  int slow = ww(s.pos+SLOW);
  int fast = ww(s.pos+FAST);

  if (!slow || !up)   deccf(F_SLOW_UP, 1.0);
  if (!up)            deccf(F_UP, 1.0);
  if (!fast || !up)   deccf(F_FAST_UP, 1.0);
  if (!slow)          deccf(F_SLOW, 1.0);
  if (!fast)          deccf(F_FAST, 1.0);
  if (!slow || !down) deccf(F_SLOW_DOWN, 1.0);
  if (!down)          deccf(F_DOWN, 1.0);
  if (!fast || !down) deccf(F_FAST_DOWN, 1.0);
  if (s.nb_miss == 0) deccf(F_MISSILE, 1.0);
}



// shortcut for within_window(pos, round()+1);
bool ww(const Pos& pos) {
  return within_window(pos, round()+1);
}


void s_default(Starship_Id sid) {
  // Initial map
/*
  deccf(F_SLOW_UP,   1-0.2); deccf(F_UP,      1-0.6); deccf(F_FAST_UP,   1-0.3);
  deccf(F_SLOW,      1-0.1); deccf(F_DEFAULT, 1-0.7); deccf(F_FAST,      1-0.4);
  deccf(F_SLOW_DOWN, 1-0.2); deccf(F_DOWN,    1-0.6); deccf(F_FAST_DOWN, 1-0.3);
  deccf(F_MISSILE,   1-0.05);
*/

  // We prefer to break because:
  //   it looks good
  //   it doesn't make us go away from our holding row
  //   it doesn't create ties

  // We prefer going slow up/down because:
  inccf(F_SLOW_UP,   0.1); inccf(F_UP,      0.6); inccf(F_FAST_UP,   0.3);
  inccf(F_SLOW,      0.2); inccf(F_DEFAULT, 0.7); inccf(F_FAST,      0.4);
  inccf(F_SLOW_DOWN, 0.1); inccf(F_DOWN,    0.6); inccf(F_FAST_DOWN, 0.3);
  inccf(F_MISSILE,   0.05);
}

CType typeof(const Pos& pos) {
  if (!within_universe(pos)) return EMPTY;
  return cell(pos).type;
}
void s_imm_coll_self(Starship_Id sid) {
  Starship s = starship(sid);
  // Ship that's behind gives way
  // If they're at the same col, only avoid crashing into eachother by maintaining row or moving apart
  if (self_in_area(s.pos+Dir{-2, 0}, s.pos+Dir{-1, 0})) { deccf(F_MASK_UP|F_MISSILE, 1.0); dbg << "found self slow_up" << endl; }
  if (self_in_area(s.pos+Dir{1, 0}, s.pos+Dir{2, 0})) { deccf(F_MASK_DOWN|F_MISSILE, 1.0); dbg << "found self slow_down" << endl; }

  if (self_in_area(s.pos+Dir{-2, 1}, s.pos+Dir{2, 1})) { deccf(F_MASK_V|F_MASK_FAST|F_MISSILE, 1.0); }
  else if (self_in_area(s.pos+Dir{-2, 2}, s.pos+Dir{2, 2})) { deccf(F_MASK_FAST|F_MISSILE, 1.0); }

/*
  if (is_self(s.pos+UP)) { deccf(F_UP|F_FAST_UP, 1.0); deccf(F_DEFAULT|F_FAST, 0.9); dbg << "found self up" << endl; }
  if (is_self(s.pos+DOWN)) { deccf(F_DOWN|F_FAST_DOWN, 1.0); deccf(F_DEFAULT|F_FAST, 0.9); dbg << "found self down" << endl; }

  if (is_self(s.pos+FAST_UP)) { deccf(F_FAST_UP, 1.0); deccf(F_FAST, 0.9); dbg << "found self fast up" << endl; }
  if (is_self(s.pos+FAST_DOWN)) { deccf(F_FAST_DOWN, 1.0); deccf(F_FAST, 0.9); dbg << "found self fast down" << endl; }

  if (is_self(s.pos+DEFAULT)) { deccf(F_DEFAULT|F_FAST, 1.0); dbg << "found self default" << endl; }
  if (is_self(s.pos+FAST)) { deccf(F_FAST, 1.0); dbg << "found self F_FAST_DOWN" << endl; }
  */
}


// Decreases the value of a cell where there's an asteriod
// By val
void s_imm_collision(Starship_Id sid, CType type) {
  Starship s = starship(sid);
  bool ast_su = typeof(s.pos+SLOW_UP) == type;
  bool ast_u  = typeof(s.pos+UP) == type;
  bool ast_fu = typeof(s.pos+FAST_UP) == type;
  bool ast_df = typeof(s.pos+DEFAULT) == type;
  bool ast_f  = typeof(s.pos+FAST) == type;
  bool ast_sd = typeof(s.pos+SLOW_DOWN) == type;
  bool ast_d  = typeof(s.pos+DOWN) == type;
  bool ast_fd = typeof(s.pos+FAST_DOWN) == type;

  if (ast_su) deccf(F_MASK_UP, 1.0);
  else if (ast_u) { deccf(F_UP|F_FAST_UP, 1.0); }
  else if (ast_fu) { deccf(F_FAST_UP, 1.0); }

  if (ast_sd) deccf(F_MASK_DOWN, 1.0);
  else if (ast_d) { deccf(F_DOWN|F_FAST_DOWN, 1.0); }
  else if (ast_fd) { deccf(F_FAST_DOWN, 1.0); }

  if (ast_f) { deccf(F_MASK_FAST, 1.0); }
  if (ast_df) { deccf(F_MASK_V|F_MASK_FAST, 1.0); }
}

void s_kill(Starship_Id sid) {
  int min_missiles_to_kill = 2;
  Starship s = starship(sid);
  int d;
  Cell c = in_front(s.pos, d);
  if (c.type == STARSHIP && player_of(c.sid) != me()) {
    dbg << "rival in front!" << endl;
    dbg << "I have " << s.nb_miss << " missiles and he's at distance " << d << endl;
    if (cell(s.pos+DEFAULT).type != MISSILE && cell(s.pos+FAST).type != MISSILE) {
      if (s.nb_miss - d > min_missiles_to_kill) {
        inccf(F_MISSILE, 1.0);
      }
    } else {
      dbg << "missile already in front of me!" << endl;
    }
  }
}

int score_of_pos(const Pos& pos) {
  if (!within_universe(pos)) return -1;
  Cell c = cell(pos);
  if (c.type != STARSHIP || player_of(c.sid) == me()) return -1;
  return score(player_of(c.sid));
}

void s_goto_same_as_rival(Starship_Id sid) {
  Starship s = starship(sid);
  if (can_rival_reach_now_wo_coll(s.pos+SLOW_DOWN)) { deccf(F_SLOW_DOWN, 1.0); dbg << "avoid rival (can reach down)" << endl; }
  if (can_rival_reach_now_wo_coll(s.pos+DOWN     )) { deccf(F_DOWN, 1.0); dbg << "avoid rival (can reach down)" << endl; }
  if (can_rival_reach_now_wo_coll(s.pos+FAST_DOWN)) { deccf(F_FAST_DOWN, 1.0); dbg << "avoid rival (can reach down)" << endl; }

  if (can_rival_reach_now_wo_coll(s.pos+SLOW_UP)) { deccf(F_SLOW_UP, 1.0); dbg << "avoid rival (can reach up)" << endl; }
  if (can_rival_reach_now_wo_coll(s.pos+UP     )) { deccf(F_UP, 1.0); dbg << "avoid rival (can reach up)" << endl; }
  if (can_rival_reach_now_wo_coll(s.pos+FAST_UP)) { deccf(F_FAST_UP, 1.0); dbg << "avoid rival (can reach up)" << endl; }

  /*
  if (can_rival_reach_area(s.pos+SLOW_DOWN, s.pos+FAST_DOWN, 1)) { deccf(F_MASK_DOWN, 1.0); dbg << "avoid rival (can reach down)" << endl; }
  if (can_rival_reach_area(s.pos+SLOW_UP,   s.pos+FAST_UP,   1)) { deccf(F_MASK_UP, 1.0);   dbg << "avoid rival (can reach up)"   << endl; }
  */
}

void s_avoid_aggressive_rival(Starship_Id sid) {
  Starship s = starship(sid);
  if (can_rival_reach_now_wo_coll(s.pos))         { deccf(F_SLOW,    1.0); dbg << "aggressive rival can reach SLOW" << endl; }
  if (can_rival_reach_now_wo_coll(s.pos+DEFAULT)) { deccf(F_DEFAULT, 1.0); dbg << "aggressive rival can reach DEFAULT" << endl; }
  if (can_rival_reach_now_wo_coll(s.pos+FAST))    { deccf(F_FAST,    1.0); dbg << "aggressive rival can reach FAST" << endl; }
}

void s_break_behind_rivals(Starship_Id sid) {
  Starship s = starship(sid);
  // If they're already only one position before us, break, and go behind them
  if (rival_in_area(s.pos+Dir{-1,0}, s.pos+Dir{1,1})) {
    inccf(F_MASK_SLOW, 1.0);
  }
/*else if (rival_in_area(s.pos+Dir{-1,2}, s.pos+Dir{1,3})) {
    inccf(F_MASK_SLOW, 0.9); inccf(F_MASK_V|F_MISSILE, 1.0);
  } else if (rival_in_area(s.pos+Dir{-1,3}, s.pos+Dir{1,4})) {
    inccf(F_MASK_SLOW, 0.8); inccf(F_MASK_V, 0.9); inccf(F_MASK_FAST, 1.0);
  }*/
}
void s_chase(Starship_Id sid, int dst) {
  Starship s = starship(sid);
  // If they're already only one position before us, break, and go behind them
  if (rival_in_area(s.pos+UP, s.pos+DOWN)) {
    int up   = score_of_pos(s.pos+UP);
    int def  = score_of_pos(s.pos+DEFAULT);
    int down = score_of_pos(s.pos+DOWN);
    if (def >= 0 && def >= up && def >= down) {
      inccf(F_SLOW, 1.0); dbg << "chasing the guy before me!" << endl;
    } else {
      if (up >= 0 && up >= down) {
        dbg << "chasing the guy above me!" << endl;
        inccf(F_SLOW_UP, 1.0);
      }
      if (down >= 0 && down >= up) {
        dbg << "chasing the guy below me!" << endl;
        inccf(F_SLOW_DOWN, 1.0);
      }
    }
  } else if (rival_in_area(s.pos+Dir{-1,3}, s.pos+Dir{1,3})) {
      int up   = score_of_pos(s.pos+UP);
      int def  = score_of_pos(s.pos+DEFAULT);
      int down = score_of_pos(s.pos+DOWN);
      if (def >= 0 && def >= up && def >= down) {
        inccf(F_SLOW, 1.0); dbg << "chasing the guy fast before me!" << endl;
      } else {
        if (up >= 0 && up >= down) {
          dbg << "chasing the guy fast above me!" << endl;
          inccf(F_SLOW_UP, 0.9); inccf(F_UP, 1.0);
        }
        if (down >= 0 && down >= up) {
          dbg << "chasing the guy fast below me!" << endl;
          inccf(F_SLOW_DOWN, 0.9); inccf(F_DOWN, 1.0);
        }
      }
    }

}

int count_in_area(const Pos& tl, const Pos& br, CType t) {
  int c = 0;
  assert(first(tl) <= first(br) && second(tl) <= second(br));
  for (int i = first(tl); i <= first(br); ++i) {
    for (int j = second(tl); j <= second(br); ++j) {
      if (cell(Dir{i, j}).type == t) c++;
    }
  }
  return c;
}

// Stops if one found
bool type_in_area(const Pos& tl, const Pos& br, CType t) {
  assert(first(tl) <= first(br) && second(tl) <= second(br));
  for (int i = first(tl); i <= first(br); ++i) {
    for (int j = second(tl); j <= second(br); ++j) {
      if (typeof(Pos{i, j}) == t) return true;
    }
  }
  return false;
}
bool is_rival(const Pos& pos) {
  if (!within_universe(pos)) return false;
  Cell c = cell(pos);
  return c.type == STARSHIP && player_of(c.sid) != me();
}

bool is_self(const Pos& pos) {
  if (!within_universe(pos)) return false;
  Cell c = cell(pos);
  return c.type == STARSHIP && player_of(c.sid) == me();
}

bool self_in_area(const Pos& tl, const Pos& br) {
  assert(first(tl) <= first(br) && second(tl) <= second(br));
  for (int i = first(tl); i <= first(br); ++i) {
    for (int j = second(tl); j <= second(br); ++j) {
      if (is_self(Pos{i, j})) return true;
    }
  }
  return false;
}
bool rival_in_area(const Pos& tl, const Pos& br) {
  assert(first(tl) <= first(br) && second(tl) <= second(br));
  for (int i = first(tl); i <= first(br); ++i) {
    for (int j = second(tl); j <= second(br); ++j) {
      if (is_rival(Pos{i, j})) return true;
    }
  }
  return false;
}

void s_dangerously_close_rivals(Starship_Id sid) {
  Starship s = starship(sid);

  if (is_rival(s.pos+DEFAULT)) deccf(F_MASK_FAST|F_MASK_V, 1.0);
  if (is_rival(s.pos+UP)); // TODO
}

void s_dodge_starship_behind_me(Starship_Id sid) {
  Starship s = starship(sid);
  int dst;
  Cell c = behind(s.pos, dst);
  if (c.type == STARSHIP && player_of(c.sid) != me()) {
    if (dst <= 4) { deccf(F_SLOW, 1.0); dbg << "dodging starship!" << endl; }
    if (dst <= 3) { deccf(F_DEFAULT|F_MISSILE, 0.9); deccf(F_FAST, 0.8); }
    // if (dst <= 2) then_im_dead();
  }
  Pos sup = s.pos+SLOW_UP;
  if (ww(sup)) {
    // We can GO TOWARDS a distance of at most 4
    if      (rival_in_area(sup-DEFAULT*2, sup)) { deccf(F_MASK_UP, 1.0); dbg << "dodge enemy above a" << endl; }
    else if (rival_in_area(sup-DEFAULT*3, sup)) { deccf(F_SLOW_UP|F_UP, 1.0); dbg << "dodge enemy above b" << endl; }
    else if (rival_in_area(sup-DEFAULT*4, sup)) { deccf(F_SLOW_UP, 1.0); dbg << "dodge enemy above c" << endl; }
    else dbg << "no rival up" << endl;

  }
  Pos sdown = s.pos+SLOW_DOWN;
  if (ww(sdown)) {
    if      (rival_in_area(sdown-DEFAULT*2, sdown)) { deccf(F_MASK_DOWN, 1.0); dbg << "dodge enemy below a" << endl; }
    else if (rival_in_area(sdown-DEFAULT*3, sdown)) { deccf(F_SLOW_DOWN|F_DOWN, 1.0); dbg << "dodge enemy below b" << endl; }
    else if (rival_in_area(sdown-DEFAULT*4, sdown)) { deccf(F_SLOW_DOWN, 1.0); dbg << "dodge enemy below c" << endl; }
    else dbg << "no rival down" << endl;
  }
}

// returns whether there's any missile from pos (including) to pos-n(including)
bool missile_behind(const Pos& pos, int n) {
  return type_in_area(pos-DEFAULT*n, pos, MISSILE);
  //for (int i = 0; i <= n; ++i) if (cell(pos-DEFAULT*i).type == MISSILE) return true;
  //return false;
}

// Dodges missiles on it's way to kill me
// AND avoids moving into one
void s_dodge_missile(Starship_Id sid) {
  Starship s = starship(sid);
  int dst;
  Cell c = behind(s.pos, dst);
  if (c.type == MISSILE) {
    if (dst <= 4) { deccf(F_SLOW, 1.0); dbg << "dodging missile!" << endl; }
    // throwing a missile will make us go at default speed
    // which will get us killed by the missile, so we don't want to do that
    if (dst == 3) { deccf(F_DEFAULT|F_MISSILE, 1.0); }
    // if (dst <= 2) then_im_dead();
  }
  if (ww(s.pos+SLOW_UP)) {
    if (missile_behind(s.pos+SLOW_UP-DEFAULT*2, 2)) deccf(F_SLOW_UP, 1.0);
    if (missile_behind(s.pos+UP-DEFAULT*2, 2)) deccf(F_UP, 1.0);
    if (missile_behind(s.pos+FAST_UP-DEFAULT*2, 2)) deccf(F_FAST_UP, 1.0);
  }
  if (ww(s.pos+SLOW_DOWN)) {
    if (missile_behind(s.pos+SLOW_DOWN-DEFAULT*2, 2)) deccf(F_SLOW_DOWN, 1.0);
    if (missile_behind(s.pos+DOWN-DEFAULT*2, 2)) deccf(F_DOWN, 1.0);
    if (missile_behind(s.pos+FAST_DOWN-DEFAULT*2, 2)) deccf(F_FAST_DOWN, 1.0);
  }
}
// Returns -1 if no rock found
// Returns 0 if pos is a rock
// Returns the distance to the rock
int rock_distance(const Pos &pos) {
  assert(within_universe(pos));
  for (int i = 0; i < number_universe_columns(); ++i) {
    if (cell(pos+DEFAULT*i).type == ASTEROID) return i;
  }
  return -1;
}

void s_far_wall(Starship_Id sid) {
  Starship s = starship(sid);
  int rd = details(sid)->rd;
  if (rd > 0 && rd < 4) deccf(F_FAST, 1.0);
  if (rd > 0 && rd < 3) deccf(F_DEFAULT, 1.0);
  /*
  if (within_universe(s.pos+SLOW_UP)) {
    rd = rock_distance(s.pos+SLOW_UP);
    if (rd > 0 && rd < 4) deccf(F_FAST_UP, 1.0);
    if (rd > 0 && rd < 3) deccf(F_UP, 1.0);
    if (rd > 0 && rd < 2) deccf(F_SLOW_UP, 1.0);
  }
  if (within_universe(s.pos+SLOW_DOWN)) {
    rd = rock_distance(s.pos+SLOW_DOWN);
    if (rd > 0 && rd < 4) deccf(F_FAST_DOWN, 1.0);
    if (rd > 0 && rd < 3) deccf(F_DOWN, 1.0);
    if (rd > 0 && rd < 2) deccf(F_SLOW_DOWN, 1.0);
  }
  */
}

// BFS for a rival
Pos get_closest_rival(Starship_Id sid, int d) {
  Pos p = starship(sid).pos;
  bool fdef = false;
  bool fdown = false;
  bool fup = false;
  for (int i = 1; i < d; ++i) {
    dbg << "checking " << Dir{0, i} << endl;
    if (is_rival(p+Dir{0, i})) return p+Dir{0, i};
    for (int j = 0; j < i; ++j) {
      dbg << "up " << Dir{-i, j} << endl;
      dbg << "down " << Dir{+i, j} << endl;
      if (is_rival(p+Dir{-i,j}) || is_rival(p+Dir{-i,-i+j})) return p+Dir{-i,j};
      if (is_rival(p+Dir{+i,j}) || is_rival(p+Dir{+i,+i-j})) return p+Dir{-+i,j};
    }
  }
  return p;
}

// Returns the column of the ship that's the farthest
int get_max_rival_ship_offset() {
  int max = 0;
  for (int i = 0; i < number_starships(); ++i) {
    Starship s = starship(i);
    dbg << "starship at " << s.pos << " is from player " <<player_of(i) << endl;
    if (player_of(i) != me() && s.alive) {
      int o = offset(s.pos);
      if (o > max) max = o;
    }
  }
  return max;
}

// Parameters
// distance: Distance to the wall to detect
void s_wall_collision(Starship_Id sid, int distance) {
  Starship s = starship(sid);
  Details *d = details(sid);
  int rd = d->rd;
  if (rd > 0 && rd < distance+1) {
    int lim = max(first(s.pos)+1, number_rows() - first(s.pos));
    bool cangoup = true;
    bool cangodown = true;
    bool foundup = false;
    bool founddown = false;
    // found row
    int fupd = 0;
    int fdownd = 0;
    for (int i = 1; i <= lim; ++i) {

      int dir = get_wd(sid);
      if (dir == I_UP || dir == I_DOWN) {
        dbg << "[ KEEPING DIRECTION ]" << endl;
        founddown = cangodown = dir == I_DOWN;
        foundup = cangoup = dir == I_UP;
        break;
      }


      Pos pup = s.pos+SLOW_UP*i;
      Pos pdown = s.pos+SLOW_DOWN*i;
      int rdup = rd;
      int rddown = rd;

      if (cangoup && within_universe(pup)) {
        rdup = rock_distance(pup);
      } else rdup--;
      if (cangodown && within_universe(pdown)) {
        rddown = rock_distance(pdown);
      } else rddown--;
      if (rdup   >= 0 && rdup   < rd) { cangoup = false; }
      if (rddown >= 0 && rddown < rd) { cangodown = false; }
      if (rdup ==   -1 || rdup > rd) { foundup = true; fupd = i; }
      if (rddown == -1 || rddown > rd) { founddown = true; fdownd = i; }
      dbg << "i="<<i << ", rdup="<<rdup<<", rddown="<<rddown<<", rd="<<rd
      <<", found="<<foundup << "," << founddown << ", cango=" <<cangoup<<","<<cangodown<<endl;

      if (foundup || founddown) { break; }
      if (!cangoup && !cangodown) { break; }
    }
    dbg << "end loop " << "found="<<foundup << "," << founddown << ", cango=" <<cangoup<<","<<cangodown<<endl;
    if (!cangoup) {
      deccf(F_MASK_UP, 1.0);
      dbg << "cannot go up!" << endl;
    }
    if (!cangodown) {
      deccf(F_MASK_DOWN, 1.0);
      dbg << "cannot go down!" << endl;
    }
    if (cangodown || cangoup) {
      if (!foundup || !founddown) {
        // MASK_H to avoid getting stuck behind a rock
        if (foundup) { set_wd(sid, I_UP); inccf(F_MASK_UP, 1.0); deccf(F_MASK_H, 1.0); dbg << "found up!" << endl;}
        else if (founddown) { set_wd(sid, I_DOWN); inccf(F_MASK_DOWN, 1.0); deccf(F_MASK_H, 1.0); dbg << "found down!" << endl; }
      }
    } else {
      dbg << "cannot go up nor down";
      inccf(F_MISSILE, 1.0);
    }
    deccf(F_SLOW, 1.0);
  }
}

int get_wd(Starship_Id sid) {
  Starship s = starship(sid);
  Details *d = details(sid);
  if (d->rock_dir != I_DEFAULT && d->rock_col > second(s.pos)) {
    // Didn't dodge the wall yet
    return d->rock_dir;
  }
  return I_DEFAULT; // No direction
}
void set_wd(Starship_Id sid, int dir) {
  dbg << "Setting direction" << endl;
  Starship s = starship(sid);
  Details *d = details(sid);
  d->rock_dir = dir;
  d->rock_col = first(s.pos) + d->rd;
}
void clear_wd(Starship_Id sid) {
  details(sid)->rock_dir = I_DEFAULT;
}





bool bonus(const Pos& pos) {
  if (!within_universe(pos)) return false;
  if (cell(pos).type == POINT_BONUS) return true;
  if (cell(pos).type == MISSILE_BONUS) return true;
  return false;
}

void s_get_bonus(Starship_Id sid) {
  Starship s = starship(sid);
  int b_su = bonus(s.pos+SLOW_UP);
  int b_u  = bonus(s.pos+UP);
  int b_fu = bonus(s.pos+FAST_UP);
  int b_df = bonus(s.pos+DEFAULT);
  int b_f  = bonus(s.pos+FAST);
  int b_sd = bonus(s.pos+SLOW_DOWN);
  int b_d  = bonus(s.pos+DOWN);
  int b_fd = bonus(s.pos+FAST_DOWN);


  if (b_su)      { inccf(F_SLOW_UP, 1.0); inccf(F_UP, 0.9); inccf(F_FAST_UP, 0.8); }
  else if (b_u)  { inccf(F_DEFAULT, 0.9); inccf(F_SLOW_UP, 0.9); inccf(F_UP, 0.95); inccf(F_FAST_UP, 0.8); }
  else if (b_fu) { inccf(F_DEFAULT, 0.9); inccf(F_SLOW_UP, 0.8); inccf(F_UP, 0.9); inccf(F_FAST_UP, 1.0); }

  if (b_sd)      { inccf(F_SLOW_DOWN, 1.0); inccf(F_DOWN, 0.9); inccf(F_FAST_DOWN, 0.8); }
  else if (b_d)  { inccf(F_DEFAULT, 0.9); inccf(F_SLOW_DOWN, 0.9); inccf(F_DOWN, 0.95); inccf(F_FAST_DOWN, 0.9); }
  else if (b_fd) { inccf(F_DEFAULT, 0.9); inccf(F_SLOW_DOWN, 0.8); inccf(F_DOWN, 0.9); inccf(F_FAST_DOWN, 1.0); }

  if (b_df)      { inccf(F_DEFAULT, 0.8); inccf(F_FAST, 0.7); }
  else if (b_f)  { inccf(F_DEFAULT, 0.7); inccf(F_FAST, 0.8); }


}
void s_dont_break(Starship_Id sid) {
  deccf(F_SLOW, 1.0);
}
void s_repeated_move(Starship_Id sid) {
    if (round() == 0) return;
    int lm = details(sid)->last_move_f;
    dbg << "last move: " << lm << endl;
    if (lm == F_SLOW) deccf(F_SLOW, 1.0);
    if (lm == F_SLOW_UP) deccf(F_SLOW_DOWN, 1.0);
    if (lm == F_SLOW_DOWN) deccf(F_SLOW_UP, 1.0);
}


void s_holding_row(Starship_Id sid) {
  Starship s = starship(sid);

  // Y
  int hr = details(sid)->holding_row;
  int hm = details(sid)->holding_row_margin;

  int ydir = 0;
  if (first(s.pos) < hr-hm) { ydir =  1; }
  if (first(s.pos) > hr+hm) { ydir = -1; }

//  if (ydir > 0) { inccf(F_SLOW_DOWN, 0.5); inccf(F_DOWN | F_FAST_DOWN, 1.0); }
//  if (ydir < 0) { inccf(F_SLOW_UP,   0.5); inccf(F_UP   | F_FAST_UP,   1.0); }
  if (ydir > 0) { inccf(F_MASK_DOWN, 1.0); }
  if (ydir < 0) { inccf(F_MASK_UP,   1.0); }
}


void s_holding_col(Starship_Id sid) {
  Starship s = starship(sid);
  // X
  int hc = details(sid)->holding_col;
  int hm = details(sid)->holding_col_margin;
  dbg << "holding col: " << hc << " margin: " << hm << endl;
  if (offset(s.pos) < (hc - hm)) { inccf(F_MASK_FAST, 1.0); dbg << "fast!" << endl; }
  if (offset(s.pos) > (hc + hm)) { inccf(F_MASK_SLOW, 1.0); dbg << "slow!" << endl; }
}

// Avoids moving behind a rock at distance positions
void s_behind_asteroid(Starship_Id sid) {
  Starship s = starship(sid);
  Details *d = details(sid);

  if (ASTEROID == typeof(s.pos+Dir{-1, 3})) deccf(F_FAST_UP,   1.0);
  if (ASTEROID == typeof(s.pos+Dir{-1, 2})) deccf(F_UP,        1.0);
  if (ASTEROID == typeof(s.pos+Dir{-1, 1})) deccf(F_SLOW_UP,   1.0);

  if (ASTEROID == typeof(s.pos+Dir{ 1, 3})) deccf(F_FAST_DOWN, 1.0);
  if (ASTEROID == typeof(s.pos+Dir{ 1, 2})) deccf(F_DOWN,      1.0);
  if (ASTEROID == typeof(s.pos+Dir{ 1, 1})) deccf(F_SLOW_DOWN, 1.0);

  if (ASTEROID == typeof(s.pos+Dir{ 0, 3})) { deccf(F_FAST,    1.0); }
  if (ASTEROID == typeof(s.pos+Dir{ 0, 2})) { deccf(F_DEFAULT, 1.0); }
}
