//------------------------------------------------------------------------------
// This program simulates collision events
// Prints the four-momentum of the particles in the events to "four_m.txt"
// Alexis Romero
// Date created: 06-15-2015
// Last modified: 06-24-2015 10:48am
//------------------------------------------------------------------------------

#include "Pythia8/Pythia.h"
#include <iostream>
#include <fstream>
using namespace Pythia8;
using namespace std;

int main() {

  Pythia pythia;
  pythia.readString("Beams:idA = 2212");            // Beam A -> Proton
  pythia.readString("Beams:idB = 2212");            // Beam B -> Proton
  pythia.readString("Beams:eCM = 7000.");           // CM energy
  pythia.readString("HardQCD:all = on");            // Consider hard QCD processes
  //pythia.readString("PhaseSpace:pTHatMin = 230.");   // Min transverse momentum?

    Settings& settings = pythia.settings;
  // Do not print to screen:
  pythia.readString("Next:numberShowInfo = 0");
  pythia.readString("Next:numberShowProcess = 0");
  pythia.readString("Next:numberShowEvent = 0");
    
    ofstream myfile;
    //myfile.open("pythia_bins_pt20.dat");  // Open output file for ptmin = 20
    //myfile.open("pythia_bins_pt40.dat");  // Open output file for ptmin = 40
    //myfile.open("pythia_bins_pt90.dat");  // Open output file for ptmin = 90
    myfile.open("pythia_bins_pt240.dat");  // Open output file for ptmin = 240
    
    
  //double pTlimit[9] = {20., 40., 70., 100., 150., 250., 500., 800., 0.};    // ptmin = 20
  //double pTlimit[9] = {40., 60., 90., 150., 250., 400., 600., 800., 0.};    // ptmin = 40
  //double pTlimit[9] = {90., 140., 190., 250., 350., 550., 700., 800., 0.};  // ptmin = 90
  double pTlimit[9] = {240., 300., 360., 410., 500., 600., 700., 800., 0.};   // ptmin = 240
    
    int nBin = 10.;
  // Loop over number of bins
  for (int iBin = 0; iBin < nBin; ++iBin) {
      
  // Set pT limits
  settings.parm("PhaseSpace:pTHatMin", pTlimit[iBin]);
  settings.parm("PhaseSpace:pTHatMax", pTlimit[iBin + 1]);
    
  pythia.init();
    
  int nEvent = 1000; // Number of events
    
  // Initiate event loop
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
  
    pythia.next();  // Advance next event
      
    // Initiate particle loop
    for (int i = 0; i < pythia.event.size(); ++i) if (pythia.event[i].isFinal()){
    
        cout << setw(15) << pythia.event[i].px() << setw(15) << pythia.event[i].py() << setw(15) << pythia.event[i].pz() << setw(15) << pythia.event[i].e() << setw(15) << pythia.event[i].id() << endl;
        
        // Print four-momentum to output file
        myfile << setw(15) << pythia.event[i].px() << setw(15) << pythia.event[i].py() << setw(15) << pythia.event[i].pz() << setw(15) << pythia.event[i].e() << setw(15) << pythia.event[i].id() << endl;
    
    }  //End particle loop
    
      myfile << "#EVENT" << endl;   // Indicate the end of each event
      
  }  //End event loop
    
  } // Bin loop
  return 0;
    
    myfile.close();     // Close output file
  
}   // End main program
