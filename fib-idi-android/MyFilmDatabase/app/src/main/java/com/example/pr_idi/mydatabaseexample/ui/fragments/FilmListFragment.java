package com.example.pr_idi.mydatabaseexample.ui.fragments;

import android.app.Fragment;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.support.annotation.Nullable;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.helper.ItemTouchHelper;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.Button;
import android.widget.RatingBar;
import android.widget.TextView;

import com.example.pr_idi.mydatabaseexample.model.Film;
import com.example.pr_idi.mydatabaseexample.R;
import com.example.pr_idi.mydatabaseexample.ui.MainActivity;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.List;
import java.util.Set;


/**
 * @author Luuk W. (Twinone).
 * @author David W. (Hoturan).
 */
public class FilmListFragment extends Fragment implements View.OnClickListener, MainActivity.Listener {

    /**
     * Time to undo a removal
     */
    private static final int REMOVAL_TIMEOUT = 10000;
    private RecyclerView mRecycler;
    private MyAdapter mAdapter;
    private FloatingActionButton mAdd;
    private long mRemovalId = -1;

    private Handler mHandler = new Handler();
    private Runnable mRemovalRunnable = new Runnable() {
        @Override
        public void run() {
            flushRemoval();
        }
    };

    private List<Film> mFilteredFilms;
    private Snackbar mSnackBar;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        getActivity().setTitle(R.string.app_name);

        View root = inflater.inflate(R.layout.fragment_film_list, null);

        insertDummyData();
        mRecycler = (RecyclerView) root.findViewById(R.id.recycler);

        LinearLayoutManager llm = new LinearLayoutManager(getActivity());
        llm.setOrientation(LinearLayoutManager.VERTICAL);
        mRecycler.setLayoutManager(llm);

        mRecycler.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent e) {
                if (e.getAction() == MotionEvent.ACTION_DOWN) {
                    flushRemoval();
                }
                return false;
            }
        });

        mAdapter = new MyAdapter();
        mRecycler.setAdapter(mAdapter);

        ItemTouchHelper.SimpleCallback cb = new ItemTouchHelper.SimpleCallback(0, ItemTouchHelper.LEFT | ItemTouchHelper.RIGHT) {
            @Override
            public boolean onMove(RecyclerView recyclerView, RecyclerView.ViewHolder holder, RecyclerView.ViewHolder target) {
                return false;
            }

            @Override
            public void onSwiped(RecyclerView.ViewHolder holder, int swipeDir) {
                //Remove swiped item from list and notify the RecyclerView
                int pos = holder.getAdapterPosition();
                queueRemoval(mFilteredFilms.get(pos));
            }
        };
        new ItemTouchHelper(cb).attachToRecyclerView(mRecycler);


        mAdd = (FloatingActionButton) root.findViewById(R.id.fab_add);
        mAdd.setOnClickListener(this);


        // Get events for film insertion / deletion
        getMainActivity().addOnFilmsChangedListener(this);
        return root;
    }

    /**
     * Adds a film pending for removal
     */
    private void queueRemoval(Film f) {


        long id = f.getId();
        flushRemoval();
        mRemovalId = id;
        mSnackBar = Snackbar.make(
                getView(),
                getString(R.string.deleted, f.getTitle()),
                Snackbar.LENGTH_INDEFINITE);


        mSnackBar.setAction(R.string.undo, new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                cancelRemoval();
                onFilmsChanged();
            }
        });
        mSnackBar.show();

        mHandler.postDelayed(mRemovalRunnable, REMOVAL_TIMEOUT);
        onFilmsChanged();
    }

    private void cancelRemoval() {
        mRemovalId = -1;
        mHandler.removeCallbacks(mRemovalRunnable);
    }

    private void flushRemoval() {
        if (mRemovalId != -1) getMainActivity().remove(mRemovalId);
        cancelRemoval();
        if (mSnackBar != null) {
            mSnackBar.dismiss();
            mSnackBar = null;
        }
    }

    @Override
    public void onPause() {
        super.onPause();

        // Make sure we actually remove removed films
        flushRemoval();
    }

    @Override
    public void onResume() {
        super.onResume();

        onFilmsChanged();
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.fab_add:
                new AddFilmFragment().show(getActivity().getFragmentManager(), null);
                break;
        }

    }


    private MainActivity getMainActivity() {
        return (MainActivity) getActivity();
    }


    private class MyAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {
        private Set<Long> mExpandedFilmIds = new HashSet<>();


        @Override
        public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            View v = LayoutInflater.from(getActivity()).inflate(R.layout.film_list_item, null);
            return new MyViewHolder(v);
        }

        @Override
        public void onBindViewHolder(final RecyclerView.ViewHolder holder, int position) {
            final MyViewHolder h = (MyViewHolder) holder;
            Film f = mFilteredFilms.get(position);


            Log.d("List", "positon:" + position + ", size=" + mFilteredFilms.size() + ", film=" + f.toString());

            View v = h.getView();


            TextView title = (TextView) v.findViewById(R.id.tv_title);
            TextView director = (TextView) v.findViewById(R.id.tv_director);
            TextView country = (TextView) v.findViewById(R.id.tv_country);
            TextView year = (TextView) v.findViewById(R.id.tv_year);
            TextView protagonist = (TextView) v.findViewById(R.id.tv_protagonist);
            RatingBar critics_rate = (RatingBar) v.findViewById(R.id.ratingBar);

            critics_rate.setOnRatingBarChangeListener(new RatingBar.OnRatingBarChangeListener() {
                @Override
                public void onRatingChanged(RatingBar ratingBar, float rating, boolean fromUser) {
                    // Don't trigger the listener when setting the value programmatically
                    if (!fromUser) return;

                    Film f = mFilteredFilms.get(holder.getAdapterPosition());
                    float r = rating * 2;
                    f.setCritics_rate((int) r);
                    getMainActivity().updateFilm(f);
                }
            });

            title.setText(f.getTitle());
            director.setVisibility(f.getDirector().isEmpty() ? View.GONE : View.VISIBLE);
            director.setText(f.getDirector());
            country.setVisibility(f.getCountry().isEmpty() ? View.GONE : View.VISIBLE);
            country.setText(f.getCountry());
            year.setVisibility(f.getYear() == 0 ? View.GONE : View.VISIBLE);
            year.setText(String.valueOf(f.getYear()));
            protagonist.setVisibility(f.getProtagonist().isEmpty() ? View.GONE : View.VISIBLE);
            protagonist.setText(f.getProtagonist());

            critics_rate.setRating((float) f.getCritics_rate() / 2);
        }

        @Override
        public int getItemCount() {
            return mFilteredFilms.size();
        }

    }

    private static class MyViewHolder extends RecyclerView.ViewHolder {
        private final View mView;

        public MyViewHolder(View itemView) {
            super(itemView);
            mView = itemView;
        }

        public View getView() {
            return mView;
        }
    }

    @Override
    public void onFilmsChanged() {
        mFilteredFilms = new ArrayList<>();
        if (!isAdded()) return;
        for (Film f : getMainActivity().getFilms()) {
            if (mRemovalId != -1 && f.getId() == mRemovalId) continue;
            if (!f.toString().toLowerCase().contains(getMainActivity().getQuery().toLowerCase()))
                continue;
            mFilteredFilms.add(f);
        }

        Collections.sort(mFilteredFilms, new Comparator<Film>() {
            @Override
            public int compare(Film a, Film b) {
                if (getMainActivity().getSortByTitle())
                    return (int) (a.getTitle().compareToIgnoreCase(b.getTitle()));
                else
                    return (int) (b.getYear() - a.getYear());
            }
        });

        mAdapter.notifyDataSetChanged();
    }

    private void insertDummyData() {
        SharedPreferences sp = getActivity().getSharedPreferences("init", Context.MODE_PRIVATE);
        boolean init = sp.getBoolean("init", false);

        if (init) return;
        // To debug:
        // if (getMainActivity().getFilms().size() > 0) return;

        sp.edit().putBoolean("init", true).apply();
        // Insert the 4 initial films asked for by the teachers
        insertFilm("Captain America", "Joe Russo", "USA", 2011, "Chris Evans", 0);
        insertFilm("Finding Dory", "Andrew Stanton", "USA", 2016, "Ellen DeGeneres", 0);
        insertFilm("Doctor Strange", "Scott Derrickson", "USA", 2010, "Benedict Cumberbatch", 0);
        insertFilm("Suicide Squad", "David Ayer", "USA", 2016, "Will Smith", 0);
        //insertFilm("Star Trek Beyond", "Justin Lin", "USA", 2016, "", 0);
    }

    private void insertFilm(
            String title,
            String director,
            String country,
            int year,
            String protagonist,
            int critics_rate) {
        Film f = new Film();
        f.setTitle(title);
        f.setDirector(director);
        f.setCountry(country);
        f.setYear(year);
        f.setProtagonist(protagonist);
        f.setCritics_rate(critics_rate);
        getMainActivity().insertFilm(f);
    }


}
