#include "Pythia8/Pythia.h"
#include <iostream>
#include <fstream>

using namespace Pythia8;
using namespace std;

int main() {
    
    ofstream myfile_4m;
    myfile_4m.open("pythia_four_momentum.dat");     // Outputs particles' four momentum
    ofstream myfile_weights;
    myfile_weights.open("pythia_weight.dat");      // Outputs bins' weight
    
    vector<Pythia*> pythias;                        // Create a vector of class Pythia
    
    int nBin = 13;
    for (int iBin = 0; iBin < nBin; iBin++) {
        
        Pythia* pythia_pointer = new Pythia();
        
        Pythia& pythia = *pythia_pointer;
        
        Settings& settings = pythia.settings;
        
        pythia.readString("Beams:idA = 2212");      // Proton-Proton collision
        pythia.readString("Beams:idB = 2212");
        pythia.readString("Beams:eCM = 7000.");     // Default beam energy at the LHC
        pythia.readString("HardQCD:all = on");
        
        // Reduce output to screen
        pythia.readString("Init:showProcesses = off");
        pythia.readString("Init:showMultipartonInteractions = off");
        pythia.readString("Init:showChangedSettings = off");
        pythia.readString("Init:showChangedParticleData = off");
        pythia.readString("Next:numberCount = 1000000000");
        pythia.readString("Next:numberShowInfo = 0");
        pythia.readString("Next:numberShowProcess = 0");
        pythia.readString("Next:numberShowEvent = 0");
        
        // Set up bin limits - last bin open-ended
        double pTlimit[14] = {40., 60., 80.,120., 160., 240., 320., 480., 640., 960., 1280., 1920., 2560., 0.};
        
        settings.parm("PhaseSpace:pTHatMin", pTlimit[iBin]);
        settings.parm("PhaseSpace:pTHatMax", pTlimit[iBin + 1]);
        
        // Initiate pythia
        pythia.init();
        
        pythias.push_back(pythia_pointer);
        
    }
    
    // Four-momentum file header
    myfile_4m << "# ========================================================================================" << endl;
    myfile_4m << "#" << setw(14) << "Bin no." << setw(15) << "Event no." << setw(15) << "Px" << setw(15)
    << "Py" << setw(15) << "Pz" << setw(15) << "E" << endl;
    myfile_4m << "# ========================================================================================" << endl;
    
    // Weight file header
    //myfile_weights << "# ==============================" << endl;
    //myfile_weights << "#" << " Cross section for " << nBin << " bins" << endl;
    //myfile_weights << "# ==============================" << endl;
    
    int nEvent= 100000;
    for (int iEvent = 0; iEvent < nEvent; iEvent++) {
        
        for (unsigned iBin = 0; iBin < pythias.size(); iBin++) {
            
            // Generate next event
            pythias.at(iBin)->next();
            
            for (int i = 0; i < pythias.at(iBin)->event.size(); i++) if (pythias.at(iBin)->event[i].isFinal()) {
                
                // Output bin no. and four-momentum
                myfile_4m << setw(15) << iBin << setw(15) << pythias.at(iBin) -> event[i].px()
                << setw(15) << pythias.at(iBin) -> event[i].py() << setw(15) << pythias.at(iBin) -> event[i].pz()
                << setw(15) << pythias.at(iBin) -> event[i].e() << endl;
            }
            
            // Indicate end of each event
            myfile_4m << "#END Event " << endl;
        }
    }
    
    for (unsigned iBin = 0; iBin < pythias.size(); iBin++) {
        
        // Define weight as the bin's estimated cross section divided by the accumulated weight
        double weight = 1e9 * pythias.at(iBin)->info.sigmaGen() / pythias.at(iBin)->info.weightSum();
        
        myfile_weights << weight << endl;
        //cout << weight << endl;
        
        delete pythias.at(iBin);
    }
}
