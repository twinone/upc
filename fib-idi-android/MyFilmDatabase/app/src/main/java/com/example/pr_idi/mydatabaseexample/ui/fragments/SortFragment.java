package com.example.pr_idi.mydatabaseexample.ui.fragments;

import android.app.DialogFragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

import com.example.pr_idi.mydatabaseexample.R;
import com.example.pr_idi.mydatabaseexample.ui.MainActivity;

/**
 * @author Luuk W. (Twinone).
 */
public class SortFragment extends DialogFragment {

    public MainActivity getMainActivity() {
        return ((MainActivity) getActivity());
    }
    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        getDialog().setTitle(R.string.action_sort);
        View v = inflater.inflate(R.layout.fragment_sort, null);
        RadioGroup rg = ((RadioGroup)v.findViewById(R.id.rg));
        rg.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                getMainActivity().setSortByTitle(checkedId == R.id.sort_title);
                getDialog().dismiss();
            }
        });
        if (!getMainActivity().getSortByTitle()) {
            ((RadioButton)rg.findViewById(R.id.sort_year)).setChecked(true);
        }
        return v;
    }
}
