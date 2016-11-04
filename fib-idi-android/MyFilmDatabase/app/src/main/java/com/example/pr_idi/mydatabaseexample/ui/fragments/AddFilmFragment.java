package com.example.pr_idi.mydatabaseexample.ui.fragments;

import android.app.Dialog;
import android.app.DialogFragment;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AlertDialog;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import com.example.pr_idi.mydatabaseexample.model.Film;
import com.example.pr_idi.mydatabaseexample.R;
import com.example.pr_idi.mydatabaseexample.ui.MainActivity;

/**
 * @author Luuk W. (Twinone).
 */
public class AddFilmFragment extends DialogFragment {

    private EditText title;
    private EditText director;
    private EditText country;
    private EditText year;
    private EditText protagonist;
    private EditText critics_rate;

    private MainActivity getMainActivity() {
        return (MainActivity) getActivity();
    }


    @Nullable
    public View onCreateDialogView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View v = inflater.inflate(R.layout.film_list_item, null);

        title = (EditText) v.findViewById(R.id.et_title);
        director = (EditText) v.findViewById(R.id.et_director);
        country = (EditText) v.findViewById(R.id.et_country);
        year = (EditText) v.findViewById(R.id.et_year);
        protagonist = (EditText) v.findViewById(R.id.et_protagonist);
        critics_rate = (EditText) v.findViewById(R.id.et_critics_rate);

        return v;
    }

    private void save() {
        Film f = new Film();
        f.setTitle(title.getText().toString());
        f.setDirector(director.getText().toString());
        f.setCountry(country.getText().toString());
        if (!year.getText().toString().isEmpty())
            f.setYear(Integer.parseInt(year.getText().toString()));
        f.setProtagonist(protagonist.getText().toString());
        if (!critics_rate.getText().toString().isEmpty())
            f.setCritics_rate(Integer.parseInt(critics_rate.getText().toString()));

        getMainActivity().get
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder ab = new AlertDialog.Builder(getActivity());
        ab.setTitle(R.string.new_film_tit);
        ab.setPositiveButton(android.R.string.ok,
                new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {
                        save();
                    }
                }
        );
        ab.setNegativeButton(android.R.string.cancel,
                new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {
                        dialog.dismiss();
                    }
                }
        );
        ab.create();
        View view = onCreateDialogView(getActivity().getLayoutInflater(), null, null);
        onViewCreated(view, null);
        ab.setView(view);
        return ab.create();
    }
}
