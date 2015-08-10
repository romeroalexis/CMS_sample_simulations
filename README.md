# CMS_sample_simulations

Pythia_main:
Run with: ./Pythia_main
Output Files: "Pythia_four_momentum.dat" and "Pythia_weight.dat"
Program Description: This program evaluates Pythia for 13 transverse momentum intervals.
The intervals are called bins.
The jet's four momentum is written to -> "Pythia_four_momentum.dat"
The bin's weight is written to -> "Pythia_weight.dat"

Fastjet_main:
Run with: ./Fastjet_main ptmin zcut
Where ptmin and zcut are command line arguments
E.g.: ./Fastjet 150. 0.05
Input Files: "Pythia_four_momentum.dat" and "Pythia_weight.dat"
Output File: Zcut_int(ptmin*100).dat
Where Zcut_int(ptmin*100) is the integer part of 100*ptmin
E.g.: "Zcut_5.dat" for a ptmin of 0.05
Program Description: This program reads jet's four momentum from "Pythia_four_momentum.dat"
and bin's weight from "Pythia_weight.dat" and measures the number of jets using the anti-kt algorithm.
The Soft Drop technique is used to groom the jets
The jet's symmetry, transverse momentum, and its respective bin weight is written to -> "Zcut_int(ptmin*100).dat"
