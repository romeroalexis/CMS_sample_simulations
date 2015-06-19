//------------------------------------------------------------------------------
// This program simulates collision events
// Prints the four-momentum of the particles in the events to "four_m.txt"
// Alexis Romero
// Date created: 06-15-2015
// Last modified: 06-19-2015 9:34am
//------------------------------------------------------------------------------

#include "Pythia8/Pythia.h"
#include <iostream>
#include <fstream>      // Output to file
using namespace Pythia8;
using namespace std;

int main() {

  Pythia pythia;
  pythia.readString("Beams:eCM = 800.");            // CM energy?
  pythia.readString("HardQCD:all = on");            // Consider hard QCD processes
  pythia.readString("PhaseSpace:pTHatMin = 20.");   // Min transverse momentum?
    
  pythia.readString("Next:numberShowInfo = 0");
  pythia.readString("Next:numberShowProcess = 0");
  pythia.readString("Next:numberShowEvent = 0");
    
  pythia.init();
    
  int nEvent = 5;
    
    ofstream myfile;
    myfile.open("four_m.txt");
    
  // Initiate event loop
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
  
    pythia.next();      // Advance next event

    cout << "Event no:" << iEvent << endl;
      
    // Initiate particle loop
    for (int i = 0; i < pythia.event.size(); ++i) if (pythia.event[i].isFinal()){
    
        // Print to screen
        cout << "i = " << i << pythia.event[i].p() << endl;
        
        // Print to "four_m.txt" file
        myfile << setw(15) << pythia.event[i].px() << setw(15) << pythia.event[i].py() << setw(15) << pythia.event[i].pz() << setw(15) << pythia.event[i].e() << endl;
    
    }  //End particle loop
    
      // Indicates the end of each event
      myfile << "END EVENT" << endl;
      
      
  }  //End event loop
  
  return 0;
    
    myfile.close();     // Close output file
  
}
