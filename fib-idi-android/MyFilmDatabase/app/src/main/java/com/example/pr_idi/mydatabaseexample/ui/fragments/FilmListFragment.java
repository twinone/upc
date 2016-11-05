package com.example.pr_idi.mydatabaseexample.ui.fragments;

import android.app.Fragment;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.content.ContextCompat;
import android.support.v7.widget.DefaultItemAnimator;
import android.support.v7.widget.DividerItemDecoration;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.transition.TransitionManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

import com.example.pr_idi.mydatabaseexample.model.Film;
import com.example.pr_idi.mydatabaseexample.R;
import com.example.pr_idi.mydatabaseexample.ui.MainActivity;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * @author Luuk W. (Twinone).
 */
public class FilmListFragment extends Fragment implements View.OnClickListener, MainActivity.Listener {

    private RecyclerView mRecycler;
    private MyAdapter mAdapter;
    private FloatingActionButton mAdd;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_film_list, null);

        mRecycler = (RecyclerView) root.findViewById(R.id.recycler);

        LinearLayoutManager llm = new LinearLayoutManager(getActivity());
        llm.setOrientation(LinearLayoutManager.VERTICAL);

        mRecycler.setLayoutManager(llm);


        mAdapter = new MyAdapter();
        mRecycler.setAdapter(mAdapter);

        mAdd = (FloatingActionButton) root.findViewById(R.id.fab_add);
        mAdd.setOnClickListener(this);


        // Get events for film insertion / deletion
        getMainActivity().addOnFilmsChangedListener(this);
        return root;
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

    private List<Film> getFilms() {
        return getMainActivity().getFilms();
    }


    private class MyAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {
        private Set<Integer> mExpandedFilmIds = new HashSet<>();

        @Override
        public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            View v = LayoutInflater.from(getActivity()).inflate(R.layout.film_list_item, null);
            return new MyViewHolder(v);
        }

        @Override
        public void onBindViewHolder(final RecyclerView.ViewHolder holder, int position) {
            final MyViewHolder h = (MyViewHolder) holder;
            final Film f = getFilms().get(position);
            final boolean isExpanded = mExpandedFilmIds.contains((int)f.getId());

            View v = h.getView();
            v.setActivated(isExpanded);
            v.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    if (isExpanded) mExpandedFilmIds.remove((int) f.getId());
                    else mExpandedFilmIds.add((int) f.getId());

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
            return getFilms().size();
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
        mAdapter.notifyDataSetChanged();
    }

}
