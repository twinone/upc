
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

static const int F_SLOW_UP   = 1 << 1;
static const int F_UP        = 1 << 2;
static const int F_FAST_UP   = 1 << 3;
static const int F_SLOW      = 1 << 4;
static const int F_DEFAULT   = 1 << 5;
static const int F_FAST      = 1 << 6;
static const int F_SLOW_DOWN = 1 << 7;
static const int F_DOWN      = 1 << 8;
static const int F_FAST_DOWN = 1 << 9;
static const int F_MISSILE   = 1 << 10;

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
  for (int i = 1; i <= 10; i++) {
    if (what & (1<<i)) {
      setc(i-1, val);
    }
  }
}
int flag(int index) {
  assert(index >= 0 && index <= 10);
  return 1 << (index-1);
}
void setc(int what, double val) {
  assert(abs(val) <= 1);
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


void  analyze_map() {
  dbg << "---------------------" << endl;
  dbg << "--  MAP ANALYSIS  ---" << endl;
  dbg << "---------------------" << endl << endl;

  dbg << "Bonus density" << endl;
  dbg << "=============" << endl;
  dbg << "  row    pb    mb rocks score" << endl;
  // analyze bonus density
  int mpb = 0; int mpbr = 0;
  int mmb = 0; int mmbr = 0;
  int mr = 0; int mrr = 0;
  for (int i = 0; i < number_rows(); ++i) {
    int cpb = 0; int cmb = 0; int cr = 0;
    for (int j = 0; j < number_universe_columns(); ++j) {
      Cell c = cell({i,j});
      if (c.type == POINT_BONUS) ++cpb;
      if (c.type == MISSILE_BONUS) ++cmb;
      if (c.type == ASTEROID) ++cr;
    }
    dbg << right << setw(5) << i << " "
        << right << setw(5) << cpb << " "
        << right << setw(5) << cmb << " "
        << right << setw(5) << cr << " "
        << right << setw(5) << int(2*cpb+5*cmb-cr) << " "
        << endl;
    if (cpb > mpb) { mpb = cpb; mpbr = i; }
    if (cmb > mmb) { mmb = cmb; mmbr = i; }
    if (cr  > mr)  { mr  = cr;  mrr  = i; }
  }


  dbg << "---------------------" << endl;
  dbg << "most point   bonuses at row " << mpbr << endl;
  dbg << "most missile bonuses at row " << mmbr << endl;
  dbg << "most rocks at row           " << mrr << endl;
  dbg << "---------------------" << endl << endl;


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

bool collision(const Pos& pos) {
  return within_universe(pos) && (cell(pos).type == ASTEROID || cell(pos).type == STARSHIP);
}

void s_default(Starship_Id sid) {
  // Initial map
/*
  deccf(F_SLOW_UP,   1-0.2); deccf(F_UP,      1-0.6); deccf(F_FAST_UP,   1-0.3);
  deccf(F_SLOW,      1-0.1); deccf(F_DEFAULT, 1-0.7); deccf(F_FAST,      1-0.4);
  deccf(F_SLOW_DOWN, 1-0.2); deccf(F_DOWN,    1-0.6); deccf(F_FAST_DOWN, 1-0.3);
  deccf(F_MISSILE,   1-0.05);
*/
  inccf(F_SLOW_UP,   0.2); inccf(F_UP,      0.6); inccf(F_FAST_UP,   0.3);
  inccf(F_SLOW,      0.1); inccf(F_DEFAULT, 0.7); inccf(F_FAST,      0.4);
  inccf(F_SLOW_DOWN, 0.2); inccf(F_DOWN,    0.6); inccf(F_FAST_DOWN, 0.3);
  inccf(F_MISSILE,   0.05);
}
// Decreases the value of a cell where there's an asteriod
// By val
void s_imm_collision(Starship_Id sid) {
  Starship s = starship(sid);
  bool ast_su = collision(s.pos+SLOW_UP);
  bool ast_u  = collision(s.pos+UP);
  bool ast_fu = collision(s.pos+FAST_UP);
  bool ast_df = collision(s.pos+DEFAULT);
  bool ast_f  = collision(s.pos+FAST);
  bool ast_sd = collision(s.pos+SLOW_DOWN);
  bool ast_d  = collision(s.pos+DOWN);
  bool ast_fd = collision(s.pos+FAST_DOWN);

  if (ast_su) deccf(F_MASK_UP, 1.0);
  else if (ast_u) { deccf(F_SLOW_UP, 0.9); deccf(F_UP|F_FAST_UP, 1.0); }
  else if (ast_fu) { deccf(F_SLOW_UP, 0.8); deccf(F_UP, 0.9); deccf(F_FAST_UP, 1.0); }

  if (ast_sd) deccf(F_MASK_DOWN, 1.0);
  else if (ast_d) { deccf(F_SLOW_DOWN, 0.9); deccf(F_DOWN|F_FAST_DOWN, 1.0); }
  else if (ast_fd) { deccf(F_SLOW_DOWN, 0.8); deccf(F_DOWN, 0.9); deccf(F_FAST_DOWN, 1.0); }

  if (ast_df) { deccf(F_SLOW, 0.9); deccf(F_MASK_V|F_MASK_FAST, 1.0); }
  if (ast_f) { deccf(F_SLOW, 0.8); deccf(F_DEFAULT, 0.9); deccf(F_MASK_FAST, 1.0); }
/*
  if (ast_su) deccf(F_SLOW_UP, 1.0);
  if (ast_su || ast_u || ast_df) deccf(F_UP, 1.0);
  if (ast_su || ast_u || ast_df || ast_f || ast_fu) deccf(F_FAST_UP, 1.0);

  if (ast_df)  deccf(F_DEFAULT, 1.0);
  if (ast_df || ast_f)  deccf(F_FAST, 1.0);

  if (ast_sd) deccf(F_SLOW_DOWN, 1.0);
  if (ast_sd || ast_d || ast_df) deccf(F_DOWN, 1.0);
  if (ast_sd || ast_d || ast_df || ast_f || ast_fd) deccf(F_FAST_DOWN, 1.0);
  */
  //
}

void s_kill(Starship_Id sid) {
  int min_missiles_to_kill = 2;
  Starship s = starship(sid);
  int d;
  Cell c = in_front(s.pos, d);
  if (d < 6 && c.type == STARSHIP && player_of(c.sid) != me()) {
    if (cell(s.pos+DEFAULT).type != MISSILE && cell(s.pos+FAST).type != MISSILE) {
      if (s.nb_miss >= min_missiles_to_kill) {
        inccf(F_MISSILE, 1.0);
      } else {
        dbg << "not enough missiles to kill, want "<< min_missiles_to_kill << ", have " << s.nb_miss << endl;
      }
    } else {
      dbg << "missile already in front of me!" << endl;
    }
  }

}

bool type_in_area(const Pos& tl, const Pos& br, CType t) {
  assert(first(tl) <= first(br));
  assert(second(tl) <= second(br));
  for (int i = first(tl); i <= first(br); ++i) {
    for (int j = second(tl); j <= second(br); ++j) {
      if (cell(Dir{i, j}).type == t) return true;
    }
  }
  return false;
}
bool is_rival(const Pos& pos) {
  if (!within_universe(pos)) return false;
  Cell c = cell(pos);
  return c.type == STARSHIP && player_of(c.sid) != me();
}

bool rival_in_area(const Pos& tl, const Pos& br) {
  assert(first(tl) <= first(br));
  assert(second(tl) <= second(br));
  for (int i = first(tl); i <= first(br); ++i) {
    for (int j = second(tl); j <= second(br); ++j) {
      if (is_rival(Dir{i, j})) return true;
    }
  }
  return false;
}

void s_dangerously_close_rivals(Starship_Id sid) {
  Starship s = starship(sid);

  if (is_rival(s.pos+DEFAULT)) deccf(F_MASK_FAST|F_MASK_V, 1.0);
  if (is_rival(s.pos+UP)); // TODO
}

void s_get_behind_rival(Starship_Id sid) {

}

void s_dodge_starship_behind_me(Starship_Id sid) {
  Starship s = starship(sid);
  int dst;
  Cell c = behind(s.pos, dst);
  if (c.type == STARSHIP && player_of(c.sid) != me()) {
    if (dst <= 4) { deccf(F_SLOW, 1.0); dbg << "dodging starship!" << endl; }
    // TODO also deccf missile?
    if (dst <= 3) { deccf(F_DEFAULT|F_FAST, 1.0); }
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
}
void s_wall_collision(Starship_Id sid) {
  Starship s = starship(sid);
  int rd = details(sid)->rd;

  if (rd > 0 && rd < 2) {
    int lim = max(first(s.pos)+1, number_rows() - first(s.pos));
    bool cangoup = true;
    bool cangodown = true;
    bool foundup = false;
    bool founddown = false;
    for (int i = 1; i <= lim; ++i) {
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
      if (rdup ==   -1 || rdup > rd) { foundup = true; }
      if (rddown == -1 || rddown > rd) { founddown = true; }
      dbg << "i="<<i << ", rdup="<<rdup<<", rddown="<<rddown<<", rd="<<rd
      <<"found="<<foundup << "," << founddown << ", cango=" <<cangoup<<","<<cangodown<<endl;

      if (foundup || founddown) { break; }
      if (!cangoup && !cangodown) { break; }
    }
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
        // TODO avoid up/down
        if (foundup) { inccf(F_MASK_UP, 1.0); dbg << "found up!" << endl;}
        else if (founddown) { inccf(F_MASK_DOWN, 1.0); dbg << "found down!" << endl; }
      }
    } else {
      dbg << "cannot go up nor down";
      inccf(F_MISSILE, 1.0);
    }

  }
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
  else if (b_fu) { inccf(F_DEFAULT, 0.9); inccf(F_SLOW_UP, 0.8); inccf(F_UP, 0.9); inccf(F_FAST_UP, 0.9); }

  if (b_sd)      { inccf(F_SLOW_DOWN, 1.0); inccf(F_DOWN, 0.9); inccf(F_FAST_DOWN, 0.8); }
  else if (b_d)  { inccf(F_DEFAULT, 0.9); inccf(F_SLOW_DOWN, 0.9); inccf(F_DOWN, 0.95); inccf(F_FAST_DOWN, 0.9); }
  else if (b_fd) { inccf(F_DEFAULT, 0.9); inccf(F_SLOW_DOWN, 0.8); inccf(F_DOWN, 0.9); inccf(F_FAST_DOWN, 0.9); }

  if (b_df)      { inccf(F_DEFAULT, 0.8); inccf(F_FAST, 0.7); }
  else if (b_f)  { inccf(F_DEFAULT, 0.7); inccf(F_FAST, 0.8); }


}
void s_repeated_move(Starship_Id sid) {
    if (round() == 0) return;
    int lm = details(sid)->last_move_f;
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
