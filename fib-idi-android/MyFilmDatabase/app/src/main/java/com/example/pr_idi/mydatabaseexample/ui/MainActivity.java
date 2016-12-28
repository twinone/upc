package com.example.pr_idi.mydatabaseexample.ui;

import android.app.Fragment;

import android.os.Bundle;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.MenuItem;

import com.example.pr_idi.mydatabaseexample.R;
import com.example.pr_idi.mydatabaseexample.db.FilmData;
import com.example.pr_idi.mydatabaseexample.model.Film;
import com.example.pr_idi.mydatabaseexample.ui.fragments.AboutDialog;
import com.example.pr_idi.mydatabaseexample.ui.fragments.FilmListFragment;
import com.example.pr_idi.mydatabaseexample.ui.fragments.HelpFragment;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {

    /**
     * String to filter the shown elements with.
     * The filter will apply Film.toString().contains(filter) to match
     */
    private String mQuery;
    private FilmData mFilmData;
    private List<Film> mFilms;
    private List<Listener> mListeners = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.setDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);


        mFilmData = new FilmData(this);
        mFilmData.open();
        updateFilms();


        navigateToFragment(new FilmListFragment());
    }

    private void navigateToFragment(Fragment f) {
        getFragmentManager()
                .beginTransaction()
                .replace(R.id.frame_content, f, null)
                .commit();
    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }


    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        return super.onOptionsItemSelected(item);
    }

    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();

        Fragment f = null;
        switch (id) {
            case R.id.nav_film_list:
                f = new FilmListFragment();
                break;
            case R.id.nav_help:
                showHelpDialog();
                break;
            case R.id.nav_about:
                showAboutDialog();
                break;
        }

        if (f != null) {
            navigateToFragment(f);
        }
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    private void showHelpDialog() {
        new HelpFragment().show(getFragmentManager(), "");
    }

    private void showAboutDialog() {
        new AboutDialog().show(getFragmentManager(), "");
    }


    @Override
    protected void onResume() {
        mFilmData.open();
        super.onResume();
    }

    @Override
    protected void onPause() {
        mFilmData.close();
        super.onPause();
    }

    public void insertFilm(Film f) {
        mFilmData.insertFilm(f);

        updateFilms();
    }

    public void updateFilm(Film f) {
        mFilmData.updateFilm(f);

        updateFilms();
    }

    /**
     * Updates the list of films (should be called after a new insertion or deletion)
     */
    public void updateFilms() {
        mFilms = mFilmData.getAllFilms();

        // let everyone know
        for (Listener l : mListeners) {
            if (l != null) l.onFilmsChanged();
        }
    }

    /**
     * @return The list of all available films
     */
    public List<Film> getFilms() {
        return new ArrayList<>(mFilms);
    }


    public void addOnFilmsChangedListener(Listener l) {
        mListeners.add(l);
    }

    public void remove(long id) {
        mFilmData.deleteFilm(id);

        updateFilms();
    }

    public interface Listener {
        /**
         * Called when a film is inserted or deleted
         */
        void onFilmsChanged();
    }

    public String getQuery() {
        if (mQuery == null) return "";
        return mQuery;
    }


}
