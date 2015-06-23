//------------------------------------------------------------------------------
// This program simulates collision events
// Prints the four-momentum of the particles in the events to "four_m.txt"
// Alexis Romero
// Date created: 06-15-2015
// Last modified: 06-23-2015 3:03am
//------------------------------------------------------------------------------

#include "Pythia8/Pythia.h"
#include <iostream>
#include <fstream>
using namespace Pythia8;
using namespace std;

int main() {

  Pythia pythia;
  pythia.readString("Beams:eCM = 800.");            // CM energy
  pythia.readString("HardQCD:all = on");            // Consider hard QCD processes
  pythia.readString("PhaseSpace:pTHatMin = 20.");   // Min transverse momentum?
    
  
  // Do not print to screen:
  pythia.readString("Next:numberShowInfo = 0");
  pythia.readString("Next:numberShowProcess = 0");
  pythia.readString("Next:numberShowEvent = 0");
    
  pythia.init();
    
  int nEvent = 300; // Number of events
    
    ofstream myfile;
    
    myfile.open("four_m.dat");  // Open output file
    
  // Initiate event loop
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
  
    pythia.next();  // Advance next event
      
    // Initiate particle loop
    for (int i = 0; i < pythia.event.size(); ++i) if (pythia.event[i].isFinal()){
    
        // Print four-momentum to output file
        myfile << setw(15) << pythia.event[i].px() << setw(15) << pythia.event[i].py() << setw(15) << pythia.event[i].pz() << setw(15) << pythia.event[i].e() << endl;
    
    }  //End particle loop
    
      myfile << "#EVENT" << endl;   // Indicate the end of each event
      
  }  //End event loop
    
  return 0;
    
    myfile.close();     // Close output file
  
}   // End main program
