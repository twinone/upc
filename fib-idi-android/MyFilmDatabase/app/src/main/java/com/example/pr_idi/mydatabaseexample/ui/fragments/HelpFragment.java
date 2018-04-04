package com.example.pr_idi.mydatabaseexample.ui.fragments;

import android.app.DialogFragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.pr_idi.mydatabaseexample.R;

/**
 * @author Luuk W. (Twinone).
 */
public class HelpFragment extends DialogFragment {
    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View v = inflater.inflate(R.layout.fragment_text, null);
        ((TextView)v.findViewById(android.R.id.text1)).setText(R.string.dialog_help);
        getDialog().setTitle(R.string.help);
        return v;
    }
}
