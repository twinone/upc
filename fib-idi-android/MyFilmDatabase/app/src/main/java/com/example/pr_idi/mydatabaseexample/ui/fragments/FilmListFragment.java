package com.example.pr_idi.mydatabaseexample.ui.fragments;

import android.app.Fragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.pr_idi.mydatabaseexample.model.Film;
import com.example.pr_idi.mydatabaseexample.R;
import com.example.pr_idi.mydatabaseexample.ui.MainActivity;

import java.util.List;

/**
 * @author Luuk W. (Twinone).
 */
public class FilmListFragment extends Fragment implements View.OnClickListener {

    private RecyclerView mRecycler;
    private FloatingActionButton mAdd;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.fragment_film_list, null);

        mRecycler = (RecyclerView) root.findViewById(R.id.recycler);
        mRecycler.setAdapter(new MyAdapter());
        mAdd = (FloatingActionButton) root.findViewById(R.id.fab_add);
        mAdd.setOnClickListener(this);


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

        @Override
        public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            View v = LayoutInflater.from(getActivity()).inflate(R.layout.film_list_item, null);
            return new MyViewHolder(v);
        }

        @Override
        public void onBindViewHolder(RecyclerView.ViewHolder holder, int position) {
            View v = ((MyViewHolder) holder).getView();
            TextView tv = (TextView) v.findViewById(R.id.text);
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
}
