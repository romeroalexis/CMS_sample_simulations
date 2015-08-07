#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace fastjet;
using namespace std;

int main() {
    
    ifstream myreadfile_4m("pythia_four_momentum.dat");     // Read particles' four-momenta from file
    ifstream myreadfile_weight("pythia_weight.dat");       // Read bins' weights from file
    
    string line;
    
    int iBin = 0;
    string weight[13];
    while (getline (myreadfile_weight,line)) {
        
        istringstream linestream(line);
        linestream >> weight[iBin];         // store weights in string
        iBin++;
    }
    
    int iEvent = 0;
    while (iEvent < 1300000) {
        
        vector<PseudoJet> input_particles;
        
        int Bin, Event;
        double Px, Py, Pz, E;
        
        while (getline (myreadfile_4m,line)) {
            
            istringstream linestream(line);
            if (line.substr(0,4) == "#END") {
                iEvent++;
                break;
            }
            
            if (line.substr(0,4) != "#END")
                linestream >> Bin >> Px >> Py >> Pz >> E;
            input_particles.push_back(PseudoJet(Px, Py, Pz, E));
        }
        
        double R = 0.5;         // Jet radius
        double ptmin = 150.0;   // Define min transverse momentum
        double z_cut = 0.05;    // Define symmetry cut
        double beta = 0.0;
        
        contrib:: SoftDrop sd(beta,z_cut);
        
        JetDefinition jet_def(fastjet::antikt_algorithm, R);
        ClusterSequence clust_seq(input_particles, jet_def);
        vector<PseudoJet> inclusive_jets = sorted_by_pt(clust_seq.inclusive_jets(ptmin));
        
        for (unsigned int i = 0; i < inclusive_jets.size(); i++) {
            
            PseudoJet sd_jet = sd(inclusive_jets[i]);
            
            if (i == 0) {
                
                // Write symmetry (zg), pT, and weight to file
                mywritefile << setw(15) << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << setw(15) << inclusive_jets[i].perp() << setw(15) << weight[Bin] << endl;
                //cout << Bin << "   Symmetry= " << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << "   pT=" << inclusive_jets[i].perp() << "   weight=  " << weight[Bin] << endl;
            }
        }
    }
}
