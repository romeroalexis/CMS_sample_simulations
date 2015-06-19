
#include "fastjet/ClusterSequence.hh"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

int main(){
    
    // Open input file
    ofstream myfile;
    myfile.open("bb.txt");
    
    string line;
    
    ifstream myreadfile ("four_m.txt");
    
    if (myreadfile.is_open()) {         //myreadfile bracket 1
    
        getline(myreadfile,line);
        
    int nEvent = 5;
        
        for (int iEvent = 0; iEvent < nEvent; ++iEvent){    // iEvent loop 2
            
            if (line != "END EVENT") {    // If line != Eveng statement 3
            
    // Create pseudojet
    vector<fastjet::PseudoJet> input_particles;
    
    // Four-momentum components
    double px, py, pz, E;
    
    // Read four-momentum components from input file
    while (myreadfile >> px >> py >> pz >> E) {
        input_particles.push_back(fastjet::PseudoJet(px,py,pz,E));}
    
    // Jet radius
    double R = 0.7;
    
    // Define jet
    // Algorith used: antikt_algorithm
    // Other possible algorithms: {kt_algorithm, cambridge_algorithm, ..}
    fastjet::JetDefinition jet_def(fastjet::antikt_algorithm, R);
    
    // Jet cluster sequence
    fastjet::ClusterSequence clust_seq(input_particles, jet_def);
    
    // Minimum transverse momentum
    double ptmin = 5.0;
    
    // Sort jets by transverse momentum
    vector<fastjet::PseudoJet> inclusive_jets = sorted_by_pt(clust_seq.inclusive_jets(ptmin));
    
    // Print jet description to screen: {index, rap, phi, pt}
    cout << "Ran " << jet_def.description() << endl;
    
    //Label columns
    printf("%5s %15s %15s %15s\n","jet #", "rapidity", "phi", "pt");
    
    // Jet loop
    for (unsigned int i = 0; i < inclusive_jets.size(); i++){   // Begin jet loop
        
        // Print to screen description of each jet
        printf("%5u %15.8f %15.8f %15.8f\n", i, inclusive_jets[i].rap(), inclusive_jets[i].phi(), inclusive_jets[i].perp());
        
        // Print to "n_vs_pt.txt"
        myfile << iEvent << "   " << inclusive_jets[i].perp() << endl;
    }   // End jet loop
                
            } //if line != Event statement -3
            
            else {
                break;
            }
            
            
            } // iEvent loop -2
                
        myreadfile.close();
        
    } // If myreadfile open -1
    
    return 0;
    
    myfile.close();
    
}
