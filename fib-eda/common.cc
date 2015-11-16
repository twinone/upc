
const Dir NODIR = {-1, -1};
// Indexes for the vector
int I_SLOW_UP = 0;
int I_UP = 1;
int I_FAST_UP = 2;
int I_SLOW = 3;
int I_DEFAULT = 4;
int I_FAST = 5;
int I_SLOW_DOWN = 6;
int I_DOWN = 7;
int I_FAST_DOWN = 8;
int I_MISSILE = 9;

vector<int> dirmap;
vector<int> curr_dirmap;
vector<Dir> dirs = { SLOW_UP, UP, FAST_UP, SLOW, DEFAULT, FAST, SLOW_DOWN, DOWN, FAST_DOWN, NODIR };

void init_common() {
  dirmap.reserve(10);
  curr_dirmap.reserve(10);
}
Starship_Id sid(int idx) {
  return idx + begin(me());
}
void add_curr_dirmap(int absval) {
  for (int i = 0; i < 10; ++i) {
    if (curr_dirmap[i] < -absval) curr_dirmap[i] = -absval;
    else if (curr_dirmap[i] > absval) curr_dirmap[i] = absval;
    dirmap[i] += curr_dirmap[i];
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
void inccd(int what, int i) {
  dirmap[what] += i;
}

// Increase a cell's value by i
void deccd(int what, int i) {
  inccd(what, -i);
}

bool issetc(int what) {
  return curr_dirmap[what] != 0;
}
void setc(int what, int i) {
  curr_dirmap[what] = i;
}
// Increase a cell's value by i
void incc(int what, int i) {
  curr_dirmap[what] += i;
}

// Increase a cell's value by i
void decc(int what, int i) {
  incc(what, -i);
}

void print_dirmap() {
  for (int i = 0; i < 10; i++) {
    if (i%3 == 0 && i != 0) dbg <<endl;
    dbg << right << setw(10) <<  dirmap[i] << "\t";
  }
  dbg<<endl;
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
    dbg << "move: SHOOT" << endl;
    shoot(sid);
  }
  dbg << "setting last move to " << dirToString(dirs[maxi]) << endl;
  details(sid)->last_move = maxi;
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
  dbg << "---------------------" << endl;


}


////////////////////////////////////////////////////////////////////////////////
////// s_valid
////////////////////////////////////////////////////////////////////////////////
/*
This strategy decreases cells you cannot go to by val
*/
void s_valid(Starship_Id sid, int v) {
  Starship s = starship(sid);
  int up = first(s.pos) != 0;
  int down = first(s.pos) != number_rows() -1;
  int slow = ww(s.pos+SLOW);
  int fast = ww(s.pos+FAST);

  if (!slow || !up)   decc(I_SLOW_UP, v);
  if (!up)            decc(I_UP, v);
  if (!fast || !up)   decc(I_FAST_UP, v);
  if (!slow)          decc(I_SLOW, v);
  if (!fast)          decc(I_FAST, v);
  if (!slow || !down) decc(I_SLOW_DOWN, v);
  if (!down)          decc(I_DOWN, v);
  if (!fast || !down) decc(I_FAST_DOWN, v);
  if (s.nb_miss == 0) decc(I_MISSILE, v);
}



// shortcut for within_window(pos, round()+1);
bool ww(const Pos& pos) {
  return within_window(pos, round()+1);
}

////////////////////////////////////////////////////////////////////////////////
////// s_imm_asteriods
////////////////////////////////////////////////////////////////////////////////

bool collision(const Pos& pos) {
  return within_universe(pos) && (cell(pos).type == ASTEROID || cell(pos).type == STARSHIP);
}
// Decreases the value of a cell where there's an asteriod
// By val
void s_imm_collision(Starship_Id sid, int v) {
  Starship s = starship(sid);
  bool ast_su = collision(s.pos+SLOW_UP);
  bool ast_u  = collision(s.pos+UP);
  bool ast_fu = collision(s.pos+FAST_UP);
  bool ast_df = collision(s.pos+DEFAULT);
  bool ast_f  = collision(s.pos+FAST);
  bool ast_sd = collision(s.pos+SLOW_DOWN);
  bool ast_d  = collision(s.pos+DOWN);
  bool ast_fd = collision(s.pos+FAST_DOWN);

  if (ast_su) decc(I_SLOW_UP, v);
  if (ast_su || ast_u || ast_df) decc(I_UP, v);
  if (ast_su || ast_u || ast_df || ast_f || ast_fu) decc(I_FAST_UP, v);

  if (ast_df)  decc(I_DEFAULT, v);
  if (ast_df || ast_f)  decc(I_FAST, v);

  if (ast_sd) decc(I_SLOW_DOWN, v);
  if (ast_sd || ast_d || ast_df) decc(I_DOWN, v);
  if (ast_sd || ast_d || ast_df || ast_f || ast_fd) decc(I_FAST_DOWN, v);
  //
}

void s_kill(Starship_Id sid, int v) {
  int min_missiles_to_kill = 3;
  Starship s = starship(sid);
  int d;
  Cell c = in_front(s.pos, d);
  if (d < 6 && c.type == STARSHIP && player_of(c.sid) != me()) {
    if (cell(s.pos+DEFAULT).type != MISSILE && cell(s.pos+FAST).type != MISSILE) {
      if (s.nb_miss >= min_missiles_to_kill) {
        inccd(I_MISSILE, v);
      } else {
        dbg << "not enough missiles to kill, want "<< min_missiles_to_kill << ", have " << s.nb_miss << endl;
      }
    } else {
      dbg << "missile already in front of me!" << endl;
    }
  }

}

bool is_rival(const Pos& pos) {
  if (!within_universe(pos)) return false;
  Cell c = cell(pos);
  return c.type == STARSHIP && c.sid != me();
}

void s_dangerously_close_rivals(Starship_Id sid, int v) {
  Starship s = starship(sid);
  if (is_rival(s.pos+SLOW_UP)) { decc(I_SLOW_UP, v); decc(I_UP, v); decc(I_FAST_UP, v); decc(I_SLOW, v); decc(I_DEFAULT, v); decc(I_FAST, v); }
  else if (is_rival(s.pos+UP)) { decc(I_UP, v); decc(I_FAST_UP, v); decc(I_DEFAULT, v); decc(I_FAST, v); }

  if (is_rival(s.pos+SLOW_DOWN)) { decc(I_SLOW_DOWN, v); decc(I_DOWN, v); decc(I_FAST_DOWN, v); decc(I_SLOW, v); decc(I_DEFAULT, v); decc(I_FAST, v); }
  else if (is_rival(s.pos+DOWN)) { decc(I_DOWN, v); decc(I_FAST_DOWN, v); decc(I_DEFAULT, v); decc(I_FAST, v); }

}

void s_dodge_starship_behind_me(Starship_Id sid, int v) {
  Starship s = starship(sid);
  int dst;
  Cell c = behind(s.pos, dst);
  if (c.type == STARSHIP && player_of(c.sid) != me()) {
    if (dst <= 4) { decc(I_SLOW, v); dbg << "dodging starship!" << endl; }
    if (dst <= 3) { decc(I_DEFAULT, v); }
    // if (dst <= 2) then_im_dead();
  }
  if (ww(s.pos+UP)) {
    c = behind(s.pos+UP, dst);
    if (c.type == STARSHIP && player_of(c.sid) != me()) {
      if      (dst == 0) { decc(I_FAST_UP, v); }
      else if (dst == 1) { decc(I_FAST_UP, v); decc(I_UP, v); }
      else if (dst <  6) { decc(I_FAST_UP, v); decc(I_UP, v); decc(I_SLOW_UP, v); }
      if (dst < 6) dbg << "starship above me at distance"<<dst<<"!" << endl;
    }
  }
  if (ww(s.pos+DOWN)) {
    c = behind(s.pos+DOWN, dst);
    if (c.type == STARSHIP && player_of(c.sid) != me()) {
      if      (dst == 0) { decc(I_FAST_DOWN, v); }
      else if (dst == 1) { decc(I_FAST_DOWN, v); decc(I_DOWN, v); }
      else if (dst <  6) { decc(I_FAST_DOWN, v); decc(I_DOWN, v); decc(I_SLOW_DOWN, v); }
      if (dst < 6) dbg << "starship beneath me at distance"<<dst<<"!" << endl;
    }
  }
}

// returns whether there's any missile from pos (including) to pos-n(including)
bool contains_missile(const Pos& pos, int n) {
  for (int i = 0; i <= n; ++i) if (cell(pos-DEFAULT*i).type == MISSILE) return true;
  return false;
}
// Dodges missiles on it's way to kill me
// AND avoids moving into one
void s_dodge_missile(Starship_Id sid, int v) {
  Starship s = starship(sid);
  int dst;
  Cell c = behind(s.pos, dst);
  if (c.type == MISSILE) {
    if (dst <= 4) { decc(I_SLOW, v); dbg << "dodging missile!" << endl; }
    if (dst == 3) { decc(I_DEFAULT, v); }
    // if (dst <= 2) then_im_dead();
  }
  if (ww(s.pos+UP)) {
    if (contains_missile(s.pos+SLOW_UP-DEFAULT*2, 2)) decc(I_SLOW_UP, v);
    if (contains_missile(s.pos+UP-DEFAULT*2, 2)) decc(I_UP, v);
    if (contains_missile(s.pos+FAST_UP-DEFAULT*2, 2)) decc(I_FAST_UP, v);
    /*
    c = behind(s.pos+SLOW_UP, dst);
    if (c.type == MISSILE) {
      if      (dst == 0) { decc(I_FAST_UP, v); }
      else if (dst == 1) { decc(I_FAST_UP, v); decc(I_UP, v); }
      else if (dst <  6) { decc(I_FAST_UP, v); decc(I_UP, v); decc(I_SLOW_UP, v); }
      if (dst < 6) dbg << "missile above me at distance"<<dst<<"!" << endl;
    }
    */
  }
  if (ww(s.pos+DOWN)) {
    c = behind(s.pos+DOWN, dst);
    if (c.type == MISSILE) {
      if      (dst == 0) { decc(I_FAST_DOWN, v); }
      else if (dst == 1) { decc(I_FAST_DOWN, v); decc(I_DOWN, v); }
      else if (dst <  6) { decc(I_FAST_DOWN, v); decc(I_DOWN, v); decc(I_SLOW_DOWN, v); }
      if (dst < 6) dbg << "missile beneath me at distance"<<dst<<"!" << endl;
    }
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

int rock_wall_direction = 0;
void s_wall_collision(Starship_Id sid, int v) {
  Starship s = starship(sid);
  int rd = rock_distance(s.pos);
  if (rd > 0 && rd < 3) {
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
      decc(I_SLOW_UP, v); decc(I_UP, v); decc(I_FAST_UP, v);
      dbg << "cannot go up!" << endl;
    }
    if (!cangodown) {
      decc(I_SLOW_DOWN, v); decc(I_DOWN, v); decc(I_FAST_DOWN, v);
      dbg << "cannot go down!" << endl;
    }
    if (cangodown || cangoup) {
      if (!foundup || !founddown) {
        // TODO avoid up/down
        if (foundup) { incc(I_SLOW_UP, v); incc(I_UP, v); incc(I_FAST_UP, v); dbg << "found up!" << endl;}
        else if (founddown) { incc(I_SLOW_DOWN, v); incc(I_DOWN, v); incc(I_FAST_DOWN, v); dbg << "found down!" << endl; }
      }
    }

  }
}





bool bonus(const Pos& pos) {
  if (!within_universe(pos)) return false;
  if (cell(pos).type == POINT_BONUS) return true;
  if (cell(pos).type == MISSILE_BONUS) return true;
  return false;
}

void s_get_bonus(Starship_Id sid, int v) {
  Starship s = starship(sid);
  int b_su = bonus(s.pos+SLOW_UP);
  int b_u  = bonus(s.pos+UP);
  int b_fu = bonus(s.pos+FAST_UP);
  int b_df = bonus(s.pos+DEFAULT);
  int b_f  = bonus(s.pos+FAST);
  int b_sd = bonus(s.pos+SLOW_DOWN);
  int b_d  = bonus(s.pos+DOWN);
  int b_fd = bonus(s.pos+FAST_DOWN);


  if (b_su)      { incc(I_SLOW_UP, int(v*1.0)); incc(I_UP, int(v*1.0)); incc(I_FAST_UP, int(v*1.0)); }
  else if (b_u)  { setc(I_DEFAULT, int(v*0.9));  incc(I_SLOW_UP, int(v*0.9)); incc(I_UP, int(v*1.0)); incc(I_FAST_UP, int(v*0.9)); }
  else if (b_fu) { setc(I_DEFAULT, int(v*0.9));  incc(I_SLOW_UP, int(v*0.8)); incc(I_UP, int(v*0.9)); incc(I_FAST_UP, int(v*0.9)); }

  if (b_sd)      { incc(I_SLOW_DOWN, int(v*1.0)); incc(I_DOWN, int(v*1.0)); incc(I_FAST_DOWN, int(v*1.0)); }
  else if (b_d)  { setc(I_DEFAULT, int(v*0.9));  incc(I_SLOW_DOWN, int(v*0.9)); incc(I_DOWN, int(v*1.0)); incc(I_FAST_DOWN, int(v*0.9)); }
  else if (b_fd) { setc(I_DEFAULT, int(v*0.9));  incc(I_SLOW_DOWN, int(v*0.8)); incc(I_DOWN, int(v*0.9)); incc(I_FAST_DOWN, int(v*0.9)); }

  if (b_df)      { incc(I_DEFAULT, int(v*0.8)); incc(I_FAST, int(v*0.7)); }
  else if (b_f)  { incc(I_DEFAULT, int(v*0.7)); incc(I_FAST, int(v*0.8)); }


}
