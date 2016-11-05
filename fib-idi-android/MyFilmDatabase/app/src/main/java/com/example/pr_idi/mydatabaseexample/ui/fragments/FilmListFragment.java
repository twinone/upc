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
import android.widget.TextView;

import com.example.pr_idi.mydatabaseexample.model.Film;
import com.example.pr_idi.mydatabaseexample.R;
import com.example.pr_idi.mydatabaseexample.ui.MainActivity;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * @author Luuk W. (Twinone).
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
                showAddDialog();
                break;
        }

    }


    private void showAddDialog() {
        AddFilmFragment aff = new AddFilmFragment();
        aff.show(getActivity().getFragmentManager(), null);
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
            final Film f = mFilteredFilms.get(position);
            final boolean isExpanded = mExpandedFilmIds.contains(f.getId());

            View v = h.getView();
            v.setActivated(isExpanded);
            v.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    if (isExpanded) mExpandedFilmIds.remove(f.getId());
                    else mExpandedFilmIds.add(f.getId());

                    notifyDataSetChanged();
                }
            });
            v.findViewById(R.id.rl_detail).setVisibility(isExpanded ? View.VISIBLE : View.GONE);

            TextView title = (TextView) v.findViewById(R.id.tv_title);
            TextView director = (TextView) v.findViewById(R.id.tv_director);
            TextView country = (TextView) v.findViewById(R.id.tv_country);
            TextView year = (TextView) v.findViewById(R.id.tv_year);
            TextView protagonist = (TextView) v.findViewById(R.id.tv_protagonist);
            TextView critics_rate = (TextView) v.findViewById(R.id.tv_critics_rate);

            title.setText(f.getTitle());
            if (f.getDirector().isEmpty()) director.setVisibility(View.GONE);
            director.setText(f.getDirector());
            if (f.getCountry().isEmpty()) country.setVisibility(View.GONE);
            country.setText(f.getCountry());
            if (f.getYear() == 0) year.setVisibility(View.GONE);
            year.setText(String.valueOf(f.getYear()));
            if (f.getProtagonist().isEmpty()) protagonist.setVisibility(View.GONE);
            protagonist.setText(f.getProtagonist());
            if (f.getCritics_rate() == 0) critics_rate.setVisibility(View.GONE);
            critics_rate.setText(String.valueOf(f.getCritics_rate()));
        }

        @Override
        public int getItemCount() {
            Log.d("Main", "getCount()" + mFilteredFilms.size());
            return mFilteredFilms.size();
        }

    }

    private static class MyViewHolder extends RecyclerView.ViewHolder {
        private View mView;

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
        for (Film f : getMainActivity().getFilms()) {
            if (mRemovalId != -1 && f.getId() == mRemovalId) continue;
            if (!f.toString().contains(getMainActivity().getQuery())) continue;
            mFilteredFilms.add(f);
        }

        mAdapter.notifyDataSetChanged();
    }

    private void insertDummyData() {
        SharedPreferences sp = getActivity().getSharedPreferences("init", Context.MODE_PRIVATE);
        boolean init = sp.getBoolean("init", false);

        // TODO
        //if (init) return;
        if (getMainActivity().getFilms().size() >= 10) return;

        sp.edit().putBoolean("init", true).apply();
        insertFilm("Captain America", "Joe Russo", "USA", 2016, "", 0);
        insertFilm("Finding Dory", "Andrew Stanton", "USA", 2016, "", 0);
        insertFilm("Doctor Strange", "Scott Derrickson", "USA", 2016, "", 0);
        insertFilm("Suicide Squad", "David Ayer", "USA", 2016, "", 0);
        insertFilm("Star Trek Beyond", "Justin Lin", "USA", 2016, "", 0);
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
