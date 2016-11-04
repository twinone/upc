package com.example.pr_idi.mydatabaseexample.db;

/**
 * FilmData
 * Created by pr_idi on 10/11/16.
 */

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;

import com.example.pr_idi.mydatabaseexample.model.Film;

import java.util.ArrayList;
import java.util.List;

public class FilmData {

    // Database fields
    private SQLiteDatabase db;
    private MySQLiteHelper helper;

    private static final String[] ALL_COLS = {
            MySQLiteHelper.COLUMN_ID,
            MySQLiteHelper.COLUMN_TITLE,
            MySQLiteHelper.COLUMN_DIRECTOR,
            MySQLiteHelper.COLUMN_COUNTRY,
            MySQLiteHelper.COLUMN_YEAR_RELEASE,
            MySQLiteHelper.COLUMN_PROTAGONIST,
            MySQLiteHelper.COLUMN_CRITICS_RATE,
    };

    public FilmData(Context context) {
        helper = new MySQLiteHelper(context);
    }

    public void open() throws SQLException {
        db = helper.getWritableDatabase();
    }

    public void close() {
        helper.close();
    }

    public void insertFilm(Film f) {
        ContentValues values = new ContentValues();

        values.put(MySQLiteHelper.COLUMN_TITLE, f.getTitle());
        values.put(MySQLiteHelper.COLUMN_DIRECTOR, f.getDirector());
        values.put(MySQLiteHelper.COLUMN_COUNTRY, f.getCountry());
        values.put(MySQLiteHelper.COLUMN_YEAR_RELEASE, f.getYear());
        values.put(MySQLiteHelper.COLUMN_PROTAGONIST, f.getProtagonist());
        values.put(MySQLiteHelper.COLUMN_CRITICS_RATE, f.getCritics_rate());

        db.insert(MySQLiteHelper.TABLE_FILMS, null,
                values);
    }

    public void deleteFilm(Film film) {
        long id = film.getId();
        db.delete(MySQLiteHelper.TABLE_FILMS, MySQLiteHelper.COLUMN_ID
                + " = " + id, null);
    }

    public List<Film> getAllFilms() {
        List<Film> comments = new ArrayList<>();

        Cursor cursor = db.query(MySQLiteHelper.TABLE_FILMS,
                ALL_COLS, null, null, null, null, null);

        cursor.moveToFirst();
        while (!cursor.isAfterLast()) {
            Film comment = cursorToFilm(cursor);
            comments.add(comment);
            cursor.moveToNext();
        }

        // make sure to close the cursor
        cursor.close();
        return comments;
    }

    private Film cursorToFilm(Cursor cursor) {
        Film film = new Film();
        film.setId(cursor.getLong(0));
        film.setTitle(cursor.getString(1));
        film.setDirector(cursor.getString(2));
        film.setCountry(cursor.getString(3));
        film.setYear(cursor.getInt(4));
        film.setProtagonist(cursor.getString(5));
        film.setCritics_rate(cursor.getInt(6));
        return film;
    }
}