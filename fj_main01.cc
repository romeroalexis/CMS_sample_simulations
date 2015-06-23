//------------------------------------------------------------------------------
// This program measures the number of jets produced in particle collisions??
// Reads file "four_m.txt"
// Prints the number of jets to the file "n_vs_pt.txt"
// Alexis Romero
// Date created: 06-15-2015
// Last modified: 06-23-2015 12:54am
//------------------------------------------------------------------------------

#include "fastjet/ClusterSequence.hh"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace fastjet;

int main () {
    
    //ifstream myreadfile ("single-event.dat");
    ifstream myreadfile ("four_m.dat");
    
    ofstream mywritefile("n_pt.dat");
    
    string line;
    
    vector<PseudoJet> input_particles;
    
    double px, py , pz, E;
    int nEvent = 100;
    
    for (int iEvent=0; iEvent < nEvent; iEvent++ ) {
        
        while(getline(myreadfile,line)) {
            istringstream linestream(line);
            if (line.substr(0,6) != "#EVENT"){ linestream >> px >> py >> pz >> E; input_particles.push_back(PseudoJet(px,py,pz,E));}
            if (line.substr(0,6) == "#EVENT"){ break; }
        }
        
        //cout << px << endl;
        
        double R = 0.6;
        
        JetDefinition jet_def(fastjet::antikt_algorithm, R);
        
        ClusterSequence clust_seq(input_particles, jet_def);
        
        double ptmin = 5.0;
        
        vector<PseudoJet> inclusive_jets = sorted_by_pt(clust_seq.inclusive_jets(ptmin));
        
        for (unsigned int i = 0; i < inclusive_jets.size(); i++) {
            
            printf("%5i %5u %5lu %15.8f %15.8f %15.8f\n", iEvent, i, inclusive_jets.size(), inclusive_jets[i].rap(), inclusive_jets[i].phi(), inclusive_jets[i].perp());
            
            if (i == 0) {mywritefile << inclusive_jets.size() << "  " << inclusive_jets[i].perp() << endl;}
            //if (i == 0) {mywritefile << inclusive_jets[i].perp() << endl;}
        }
        
    }   // End for (int iEvent=0; iEvent < nEvent; iEvent++ )
    
    return 0;
}   // End main()
