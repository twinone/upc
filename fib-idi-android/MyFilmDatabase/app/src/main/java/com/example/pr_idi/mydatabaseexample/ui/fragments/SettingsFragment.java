package com.example.pr_idi.mydatabaseexample.ui.fragments;

import android.app.Fragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.example.pr_idi.mydatabaseexample.R;

/**
 * @author Luuk W. (Twinone).
 */
public class SettingsFragment extends Fragment {

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        getActivity().setTitle(R.string.action_settings);
        return super.onCreateView(inflater, container, savedInstanceState);
    }
}
