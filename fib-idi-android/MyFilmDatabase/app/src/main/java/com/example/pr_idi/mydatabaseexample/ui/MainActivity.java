package com.example.pr_idi.mydatabaseexample.ui;


import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import com.example.pr_idi.mydatabaseexample.model.Film;
import com.example.pr_idi.mydatabaseexample.db.FilmData;
import com.example.pr_idi.mydatabaseexample.ui.fragments.FilmListFragment;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    /**
     * String to filter the shown elements with.
     * The filter will apply Film.toString().contains(filter) to match
     */
    private String mQuery;
    private FilmData mFilmData;
    private List<Film> mFilms;
    private List<Listener> mListeners = new ArrayList<>();

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


        mFilmData = new FilmData(this);
        mFilmData.open();
        updateFilms();

        getFragmentManager()
                .beginTransaction()
                .replace(android.R.id.content, new FilmListFragment(), null)
                .commit();
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