# CMS_sample_simulations

##Pythia_main:  
Run with: ./Pythia_main  
Output Files: "Pythia_four_momentum.dat" and "Pythia_weight.dat"  
Program Description: This program evaluates Pythia for 13 transverse momentum intervals.  
The intervals are called bins.  
The jet's four momentum is written to -> "Pythia_four_momentum.dat"  
The bin's weight is written to -> "Pythia_weight.dat"  

##Fastjet_main:__
Run with: ./Fastjet_main ptmin zcut__
Where ptmin and zcut are command line arguments__
E.g.: ./Fastjet 150. 0.05__
Input Files: "Pythia_four_momentum.dat" and "Pythia_weight.dat"__
Output File: Zcut_int(ptmin*100).dat__
Where Zcut_int(ptmin*100) is the integer part of 100*ptmin__
E.g.: "Zcut_5.dat" for a ptmin of 0.05__
Program Description: This program reads jet's four momentum from "Pythia_four_momentum.dat"__
and bin's weight from "Pythia_weight.dat" and measures the number of jets using the anti-kt algorithm.__
The Soft Drop technique is used to groom the jets__
The jet's symmetry, transverse momentum, and its respective bin weight is written to -> "Zcut_int(ptmin*100).dat"__
