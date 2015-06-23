//------------------------------------------------------------------------------
// This program reads input file "four_m.dat" and measures the number of
// resulting jets.
// Prints transverse momentum of each event to "pt.dat"
// Alexis Romero
// Date created: 06-15-2015
// Last modified: 06-23-2015 3:07pm
//------------------------------------------------------------------------------


#include "fastjet/ClusterSequence.hh"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace fastjet;

int main () {
    
    ifstream myreadfile ("four_m.dat");  // Input file
    
    ofstream mywritefile("pt.dat");  // Output file
    
    string line;
    
    double px, py , pz, E;  // Declare four-momentum variables
    
    int nEvent = 300;  // Enter number of events
    
    // Begin iEvent-loop
    for (int iEvent=0; iEvent < nEvent; iEvent++ ) {
        
            vector<PseudoJet> input_particles;  // Define PseudoJet vector
        
        while(getline(myreadfile,line)) {
            
            istringstream linestream(line);
            // If line is NOT #Event -> input four-momentum to PseudoJet
            if (line.substr(0,6) != "#EVENT"){ linestream >> px >> py >> pz >> E; input_particles.push_back(PseudoJet(px,py,pz,E));}
            // If line is #Event -> Break, reset PseudoJet
            if (line.substr(0,6) == "#EVENT"){ break; }
            
        }
        
        double R = 0.6;  // Enter jet radius
        
        // Define Jet:
        // Indicate algotithm and radius
        JetDefinition jet_def(fastjet::antikt_algorithm, R);
        
        // Cluster jets by transverse momentum
        ClusterSequence clust_seq(input_particles, jet_def);
        
        double ptmin = 5.0;  // Enter minimum transverse momentum
        
        // Define inclusive jets
        vector<PseudoJet> inclusive_jets = sorted_by_pt(clust_seq.inclusive_jets(ptmin));
        
        // Begin i-particle loop
        for (unsigned int i = 0; i < inclusive_jets.size(); i++) {
            
            printf("%5i %5u %5lu %15.8f %15.8f %15.8f\n", iEvent, i, inclusive_jets.size(), inclusive_jets[i].rap(), inclusive_jets[i].phi(), inclusive_jets[i].perp());
            
            // Print jet with max transverse momentum to output file
            if (i == 0) {mywritefile << inclusive_jets[i].perp() << endl;}
            
        }  // End i-particle loop -> for (unsigned int i = 0; i < inclusive_jets.size(); i++)
        
    }   // End iEvent-loop -> for (int iEvent=0; iEvent < nEvent; iEvent++ )
    
    return 0;
}   // End main()
