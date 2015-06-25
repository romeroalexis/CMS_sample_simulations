//------------------------------------------------------------------------------
// This program reads input file "four_m.dat" and measures the number of
// resulting jets.
// Prints transverse momentum of each event to "pt.dat"
// Alexis Romero
// Date created: 06-15-2015
// Last modified: 06-24-2015 10:49pm
//------------------------------------------------------------------------------

#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace fastjet;

int main () {
    
  //ofstream mywritefile1("A1_pythia20.dat");  // Output file //C1
  //ofstream mywritefile1("A1_pythia40.dat");  // Output file //C1
  //ofstream mywritefile1("A1_pythia90.dat");  // Output file //C1
  ofstream mywritefile1("A1_pythia240.dat");  // Output file //C1
    
    
  string line;
    
  int nEvent = 10000;  // Enter number of events
    
  for (int iEvent=0; iEvent < nEvent; iEvent++ ) {  // Begin iEvent-loop
        
    vector<PseudoJet> input_particles;  // Define PseudoJet vector
    
    while(getline(cin,line)) {
        
      istringstream linestream(line);
        
      double px, py , pz, E;  // Declare four-momentum variables
  
      // If line is NOT #Event -> input four-momentum to PseudoJet
      if (line.substr(0,6) != "#EVENT"){ linestream >> px >> py >> pz >> E; input_particles.push_back(PseudoJet(px,py,pz,E));}
        
      // If line is #Event -> Break, reset PseudoJet
        else {break;}
    }
        
    double R = 0.6;  // Enter jet radius
    //double ptmin = 25.0;  // C4
    //double ptmin = 50.0;  // C4
    //double ptmin = 100.0;  // C4
    double ptmin = 50.0;  // C4
  
    // Define Jet:
    // Indicate algotithm and radius
    JetDefinition jet_def(fastjet::antikt_algorithm, R);
        
    // Cluster jets by transverse momentum
    ClusterSequence clust_seq(input_particles, jet_def);
      
    // Define inclusive jets
    vector<PseudoJet> inclusive_jets = sorted_by_pt(clust_seq.inclusive_jets(ptmin));
      
      double z_cut = 0.05;  //C2
      double beta = 0.0;
      contrib:: SoftDrop sd(beta,z_cut);
      //cout << "SoftDrop groomer is: " << sd.description() << endl;
      
    // Begin i-particle loop
    for (unsigned int i = 0; i < inclusive_jets.size(); i++) {
        
        PseudoJet sd_jet = sd(inclusive_jets[i]);
        cout << endl;
        
        cout << "Original jet:     " << iEvent << "  " << i << "  " << inclusive_jets.size() << " pt =  " << inclusive_jets[i].perp() << " y   " << inclusive_jets[i].rap() << " phi =  " << inclusive_jets[i].phi() << endl;
        cout << "SoftDropped jet:  " << iEvent << "  " << i << "  " << inclusive_jets.size() << " pt =  " << sd_jet.perp() << " y   " << sd_jet.rap() << " phi =  " << sd_jet.phi() << endl;
        cout << " Delta_R between subjets:  " << sd_jet.structure_of<contrib::SoftDrop>().delta_R() << endl;
        cout << " Symmetry measure (z):     " << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << endl;
        cout << " Mass drop(mu):            " << sd_jet.structure_of<contrib::SoftDrop>().mu() << endl;
        
      // Print jet with max transverse momentum to output file
  
      //if ((i == 0) && (sd_jet.perp()>50.)) {mywritefile1 << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << endl;}
      //if ((i == 0) && (sd_jet.perp()>100.)) {mywritefile1 << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << endl;}
      //if ((i == 0) && (sd_jet.perp()>200.)) {mywritefile1 << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << endl;}
      if ((i == 0) && (sd_jet.perp()>100.)) {mywritefile1 << sd_jet.structure_of<contrib::SoftDrop>().symmetry() << endl;}
  
        
    }  // End i-particle loop -> for (unsigned int i = 0; i < inclusive_jets.size(); i++)
        
  }   // End iEvent-loop -> for (int iEvent=0; iEvent < nEvent; iEvent++ )

    
  return 0;
}   // End main()
