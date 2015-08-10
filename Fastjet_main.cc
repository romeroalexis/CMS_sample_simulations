#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace fastjet;
using namespace std;

int main(int argc, char* argv[]) {
    
    //This program reads command line arguments:
    //Argv[0]: filename, Argv[1]: pTmin, Argv[2]: Zcut
    //End program if the no. of arguments provided is not 3
    if (argc != 3) {
        cout << "Run with: ./fastjet ptmin z_cut" << endl;
        cout << "    e.g.: ./fastjet 150. 0.05" << endl;
        return 0;
    }
    
    ofstream mywritefile;
    
    ifstream myreadfile_4m("pythia_four_momentum.dat");     //Read four-momentum from file
    ifstream myreadfile_weight("pythia_weights.dat");       //Read bin weight from file
    
    string line;
    
    int iBin = 0;
    string weight[13];
    while (getline (myreadfile_weight,line)) {
        
        istringstream linestream(line);
        linestream >> weight[iBin];                         //Store weights in a string
        iBin++;                                             //Advance bin no.
    }
    
    double ptmin = atof(argv[1]);                           //Read pTmin from command line argument
    double z_cut = atof(argv[2]);                           //Read Zcut from command line argument
    int Z_cut_file = (int) (z_cut*100);                     //Integer part of (Zcut*100)
    
    //Output file is named after the Zcut.
    //E.g.: "Zcut_5.dat" for a Zcut or 0.05
    mywritefile.open("Zcut_" + to_string(Z_cut_file) + ".dat");
    
    // mywritefile header
    //mywritefile << "---------------------------------------------------------------------------" << endl;
    //mywritefile << "                 Symmetry" << "      Transverse Momentum" << "                   Weight" << endl;
    //mywritefile << "                     (Zg)" << "                     (pT)" << endl;
    //mywritefile << "---------------------------------------------------------------------------" << endl;
    
    // Do while iEvent < bins*100000
    int iEvent = 0;
    while (iEvent < 1300000) {
        
        vector<PseudoJet> input_particles;
        
        int Bin, Event;                                     //Bin and Event
        double Px, Py, Pz, E;                               //Four-momentum components
        
        while (getline (myreadfile_4m,line)) {
            
            istringstream linestream(line);
            if (line.substr(0,4) == "#END") {
                iEvent++;
                break;
            }
            
            if (line.substr(0,4) != "#END")
                linestream >> Bin >> Event >> Px >> Py >> Pz >> E;
            input_particles.push_back(PseudoJet(Px, Py, Pz, E));
        }
        
        double R = 0.5;                                     //Jet radius
        double beta = 0.0;                                  //Soft Drop parameter
        
        contrib:: SoftDrop sd(beta,z_cut);
        
        //Jet algorithm use: antikt
        JetDefinition jet_def(fastjet::antikt_algorithm, R);
        ClusterSequence clust_seq(input_particles, jet_def);
        vector<PseudoJet> inclusive_jets = sorted_by_pt(clust_seq.inclusive_jets(ptmin));
        
        for (unsigned int i = 0; i < inclusive_jets.size(); i++) {
            
            PseudoJet sd_jet = sd(inclusive_jets[i]);
            
            if (i == 0) {
                //Output the hardest jet to file
                mywritefile << setw(25) << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << setw(25) << inclusive_jets[i].perp() << setw(25) << weight[Bin] << endl;
                cout << "bin=  " << Bin << "   Event = " << iEvent << endl;
            }
        }
    }
    mywritefile.close();
    return 0;
}
