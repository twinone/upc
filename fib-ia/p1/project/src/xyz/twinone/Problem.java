package xyz.twinone;

import IA.Red.Centro;
import IA.Red.CentrosDatos;
import IA.Red.Sensores;

import java.security.InvalidParameterException;
import java.util.Random;

public class Problem {
    private final Sensores sensores;
    private final CentrosDatos centrosDatos;

    private int mNumCentros;

    public Problem(int numSensores, int numCentrosDatos, int seed) {
        if (numSensores <= 0) throw new InvalidParameterException("numSensores should be > 0");
        if (numCentrosDatos <= 0) throw new InvalidParameterException("numCentrosDatos should be > 0");


        sensores = new Sensores(numSensores, seed);
        centrosDatos = new CentrosDatos(numCentrosDatos, seed);
    }


    public Sensores getSensores() {
        return sensores;
    }

    public CentrosDatos getCentrosDatos() {
        return centrosDatos;
    }

}
