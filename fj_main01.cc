//------------------------------------------------------------------------------
// This program measures the number of jets produced in particle collisions??
// Reads file "four_m.txt"
// Prints the number of jets to the file "n_vs_pt.txt"
// Alexis Romero
// Date created: 06-15-2015
// Last modified: 06-19-2015 9:34am
//------------------------------------------------------------------------------


#include "fastjet/ClusterSequence.hh"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    
    // Open input file
    //ofstream myfile;
    //myfile.open("n_vs_pt.txt");
    double px, py, pz, E;
    int iEvent = 0;
    
    ifstream myreadfile ("four_m.dat");
    
    string line;
    
    while (getline(myreadfile,line)){
        
        istringstream linestream(line);
        
        if (line.substr(0,4) == "#END") {break;}
        
        if (line.substr(0,6) == "#EVENT") { iEvent +=1;}
        
        linestream >> px >> py >> pz >> E;
        
        // Create pseudojet
        vector<fastjet::PseudoJet> input_particles;
        
        input_particles.push_back(fastjet::PseudoJet(px,py,pz,E));
        
        // Jet radius
        double R = 0.9;
        
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
        
        for (unsigned int i = 0; i < inclusive_jets.size(); i++){
            
            //cout << i << "  " << inclusive_jets.size() << endl;
            
            // Print to screen description of each jet
            printf("%5i %5u %15.8f %15.8f %15.8f\n", iEvent, i, inclusive_jets[i].rap(), inclusive_jets[i].phi(), inclusive_jets[i].perp());}
    }
    
    return 0;
    
}// End main()
