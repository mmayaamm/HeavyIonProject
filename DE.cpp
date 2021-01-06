#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void DataDump(const char *inputFile){
  gSystem->Load("libDelphes");
  ofstream File;
  File.open("EventData3.txt");
  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);
//  Jet *jet;
  GenParticle *GenPart;
  GenParticle *daughter1;
  GenParticle *daughter2;
  GenParticle *mot1;
  GenParticle *mot2;
  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  TClonesArray *branchTrack = treeReader->UseBranch("Track");
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchPhoton   = treeReader->UseBranch("Photon");
//  TClonesArray *branchGenParticle      = treeReader->UseBranch("GenParticle");
   // Load selected branches with data from specified event
   treeReader->ReadEntry(1);
   int i = 0;
   while(branchParticle->At(i)){
       GenPart = (GenParticle*) branchParticle->At(i);
     File<<"*********************************************"<<endl;
    File << "PDG ID: " << GenPart->PID <<endl;
    File<< "Status: " << GenPart->Status <<endl;
    File<< "Mass: " << GenPart->Mass <<endl;
    File<<"Pt: " << GenPart->PT <<endl;
    if(GenPart->M1 >= 0){
      mot1 = (GenParticle*) branchParticle->At(GenPart->M1);

   File << "Mothers: " << mot1->PID << ",";
  }
    if(GenPart->M2 >= 0){
      mot2 = (GenParticle*) branchParticle->At(GenPart->M2);

     File<< mot2->PID<< endl;
   }
   else{
     File<<endl;
   }
   if(GenPart->D1 >= 0 ){
     daughter1 = (GenParticle*) branchParticle->At(GenPart->D1);
   File << "Daughters: " << daughter1->PID << ",";
 }
   if(GenPart->D2 >= 0){
     daughter2 = (GenParticle*) branchParticle->At(GenPart->D2);

    File<<daughter2->PID<< endl;
  }
  else{
    File<<endl;
  }
    //File<< "Daughter1,Daughter2: "<< daughter1 << "," << daughter2<<endl;
  i++;
}
    File.close();
  }

void An(const char *inputFile)
{
  gSystem->Load("libDelphes");
  /*ofstream File;
  File.open("EventData.txt");*/
  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);
//  Jet *jet;
  GenParticle *GenPart;
  GenParticle *daughter1;
  GenParticle *daughter2;
  GenParticle *mot1;
  GenParticle *mot2;
  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchParticle = treeReader->UseBranch("Particle");
  TClonesArray *branchTrack = treeReader->UseBranch("Track");
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchPhoton   = treeReader->UseBranch("Photon");
  //TClonesArray *branchGenParticle      = treeReader->UseBranch("GenParticle");
  TH1 *histMassC = new TH1F("Chargino Mass", "Chargino Mass; Mass(GeV);" ,100, 100, 250);
  TH1 *histPhiC = new TH1F("Chargino Phi", "Chargino Phi; Phi(radians);" ,100, -4, 4);
  TH1 *histPIDC =  new TH1F("Chargino PDGID", "Chargino PDGID; PDGID;", 100, 0, 1300000);
  TH1 *histPTC = new TH1F("Chargino", "Chargino P_{T}; P_{T}(Gev);" ,100, 0, 600);
  TH1 *histEtaC = new TH1F("Chargino", "Chargino Eta; Eta;" ,100, -10, 10);

  TH1 *histMassN = new TH1F("Neutralino Mass", "Neutralino Mass; Mass(GeV);" ,100, 0,300);
  TH1 *histPhiN = new TH1F("Neutralino Phi", "Neutralino Phi; Phi(radians);" ,100, -4, 4);
  TH1 *histPIDN =  new TH1F("Neutralino PDGID", "Neutralino PDGID; PDGID;", 100, 0, 1300000);
  TH1 *histPTN = new TH1F("Neutralino", "Neutralino P_{T}; P_{T}(Gev);" ,100, 0, 600);
  TH1 *histEtaN = new TH1F("Neutralino", "Neutralino Eta; Eta;" ,100, -10, 10);

  TH1 *histMass = new TH1F("Chargino daughter Mass", "Chargino daughter Mass; Mass(GeV);" ,100, 50, 250);
  TH1 *histPhi = new TH1F("Chargino daughter Phi", "Chargino daughter Phi; Phi(radians);" ,100, -4, 4);
  TH1 *histPID =  new TH1F("Chargino daughter PDGID", "Chargino daughter PDGID; PDGID;", 100, 1000024, 1000030);
  TH1 *histPIDL =  new TH1F("Chargino daughter PDGID", "Chargino daughter PDGID; PDGID;", 100, 0, 100);
  TH1 *histPT = new TH1F("Chargino daughter", "Chargino daughter P_{T}; P_{T}(GeV);" ,100, 0, 600);
  TH1 *histEta = new TH1F("Chargino daughter", "Chargino daughter Eta; Eta;" ,100, -10, 10);
  // Book histograms
  TH1 *histMassE = new TH1F("electron kinematics", "electron; Mass(GeV); ", 100, 25, 100);
  TH1 *histPhiE = new TH1F("electron kinematics", "W; Phi(radians);" ,100, -4, 4);
  TH1 *histPIDE =  new TH1F("W kinematics", "W PDGID; PDGID;", 40, -20, 20);
  TH1 *histPTE = new TH1F("Electron kinematics", "electron; P_{T}(GeV)" ,100, 0, 600);
  TH1 *histEtaE = new TH1F("Electron kinematics", "electron ; Eta;" ,100, -10, 10);

  TH1 *histMassP = new TH1F("pion", "pion Mass; Mass(GeV); ", 100, 0, 300);
  TH1 *histPhiP = new TH1F("Pion", "pion Phi; Phi(radians);" ,100, -4, 4);
  TH1 *histPIDP =  new TH1F("Pion", "pion PDGID; PDGID;", 100, 0, 1300000);
  TH1 *histPTP = new TH1F("Pion", "pion; P_{T}(GeV);" ,100, 0, 600);
  TH1 *histEtaP = new TH1F(" Pion ", "pion; Eta;" ,100, -10, 10);

  TH1 *histMassWL = new TH1F("Lepton from W decay", "Lepton Mass; Mass(GeV); ", 100, 0, 300);
  TH1 *histPhiWL = new TH1F("Lepton from W decay", "Lepton Phi; Phi(radians);" ,100, -4, 4);
  TH1 *histPIDWL =  new TH1F("Lepton from W decay", "Lepton PDGID; PDGID;", 100, 0, 1300000);
  TH1 *histPTWL = new TH1F("Lepton from W decay", "Lepton; P_{T}(Gev);" ,100, 0, 600);
  TH1 *histEtaWL = new TH1F(" Lepton from W decay", "Lepton; Eta;" ,100, -10, 10);
  //TH1 *hist       = new TH1F("MET", "MET", 100, 0.0, 300.0);*/

/*  Double_t weight = 0.0004 * 300 * 1E3 / numberOfEntries;
  Double_t yield = 0;
  Double_t y2 = 0;*/

  // Loop over all events
   for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
    //std::cout<<branchTrack->At(0);
        // If event contains at  1 jet

      // Take first jet
    int  i = 0;
    while(branchParticle->At(i)){
      GenPart = (GenParticle*) branchParticle->At(i);
      if(abs(GenPart->PID) == 11){
            histMassE->Fill(GenPart->Mass);
            histPhiE->Fill(GenPart->Phi);
            histPTE->Fill(GenPart->PT);
            histEtaE->Fill(GenPart->Eta);
            //histPIDW->Fill(GenPart->PID);
            //std::cout<<"1"<<endl;
        /*    daughter1 = (GenParticle*) branchParticle->At(GenPart->D1);
            if(GenPart->D1 > 0){
              histPIDW->Fill(daughter1->PID);
            //  daughter1 = (GenParticle*) branchParticle->At(GenPart->D1);
            if(abs(daughter1->PID) >= 1 && abs(daughter1->PID) <= 8){
            //std::cout<<"2"<<endl;
              //daughter1 = (GenParticle*) branchParticle->At(GenPart->D1);
              histMassWM->Fill(daughter1->Mass);
              histPhiWM->Fill(daughter1->Phi);
              histPTWM->Fill(daughter1->PT);
              histEtaWM->Fill(daughter1->Eta);
              //histPIDW->Fill(daughter1->PID);
            }
            else if(abs(daughter1->PID) >= 11 && abs(daughter1->PID) <= 18){
            //std::cout<<"2"<<endl;
              //daughter1 = (GenParticle*) branchParticle->At(GenPart->D1);
              histMassWL->Fill(daughter1->Mass);
              histPhiWL->Fill(daughter1->Phi);
              histPTWL->Fill(daughter1->PT);
              histEtaWL->Fill(daughter1->Eta);
            //  histPIDWL->Fill(daughter1->PID);
            }
          }
          daughter2 = (GenParticle*) branchParticle->At(GenPart->D2);
          if(GenPart->D2 > 0){
            histPIDW->Fill(daughter2->PID);
              //daughter2 = (GenParticle*) branchParticle->At(GenPart->D1);
              if(abs(daughter2->PID) >= 1 && abs(daughter2->PID) <= 8  ){
              histPhiWM->Fill(daughter2->Phi);
            ///histPIDWM->Fill(daughter2->PID);
              histMassWM->Fill(daughter2->Mass);
              histPTWM->Fill(daughter2->PT);
              histEtaWM->Fill(daughter2->Eta);
            }
            else if(abs(daughter2->PID) >= 11 && abs(daughter2->PID) <= 18){
              //daughter2 = (GenParticle*) branchParticle->At(GenPart->D2);
              histMassWL->Fill(daughter2->Mass);
              histPhiWL->Fill(daughter2->Phi);
              histPIDWL->Fill(daughter2->PID);
              histPTWL->Fill(daughter2->PT);
              histEtaWL->Fill(daughter2->Eta);
            }*/
          }
          if(abs(GenPart->PID) == 211){
                histMassP->Fill(GenPart->Mass);
                histPhiP->Fill(GenPart->Phi);
                histPTP->Fill(GenPart->PT);
                histEtaP->Fill(GenPart->Eta);
              }
          if(abs(GenPart->PID) == 1000022 && GenPart->Status == 1 ){
          histMassN->Fill(GenPart->Mass);
          histPhiN->Fill(GenPart->Phi);
          histPTN->Fill(GenPart->PT);
          histEtaN->Fill(GenPart->Eta);
          histPIDN->Fill(GenPart->PID);
        }
        if(abs(GenPart->PID) == 1000024 && GenPart->Status == 62){
        histMassC->Fill(GenPart->Mass);
        histPhiC->Fill(GenPart->Phi);
        histPTC->Fill(GenPart->PT);
        histEtaC->Fill(GenPart->Eta);
        histPIDC->Fill(GenPart->PID);
      //std::cout<<"1"<<endl;
        if(GenPart->D1 >= 0 ){
        //std::cout<<"2"<<endl;
          daughter1 = (GenParticle*) branchParticle->At(GenPart->D1);
          histMass->Fill(daughter1->Mass);
          histPhi->Fill(daughter1->Phi);
          histPT->Fill(daughter1->PT);
          histEta->Fill(daughter1->Eta);
          if(abs(daughter1->PID) >= 100000){
            histPID->Fill(abs(daughter1->PID));
          }
          else{
            histPIDL->Fill(abs(daughter1->PID));
          }
        }
        if(GenPart->D2 >= 0 ){
          daughter2 = (GenParticle*) branchParticle->At(GenPart->D2);
          histMass->Fill(daughter2->Mass);
          histPhi->Fill(daughter2->Phi);
          histPT->Fill(daughter2->PT);
          histEta->Fill(daughter2->Eta);
          if(abs(daughter2->PID) >= 100000){
            histPID->Fill(abs(daughter2->PID));
          }
          else{
            histPIDL->Fill(abs(daughter2->PID));
          }

        }
      }

      i++;
    }
    /*  File<<"*********************************************"<<endl;
      File << "PDG ID: " << GenPart->PID <<endl;
      if(GenPart->M1 >= 0){*/
      //  mot1 = (GenParticle*) branchParticle->At(GenPart->M1);

    /*  File << "Mothers: " << mot1->PID << ",";
    }
      if(GenPart->M2 >= 0){
        mot2 = (GenParticle*) branchParticle->At(GenPart->M2);

       File<< mot2->PID<< endl;
     }
     else{
       File<<endl;
     }
     if(GenPart->D1 >= 0 ){
       daughter1 = (GenParticle*) branchParticle->At(GenPart->D1);
     File << "Daughters: " << daughter1->PID << ",";
   }
     if(GenPart->D2 >= 0){
       daughter2 = (GenParticle*) branchParticle->At(GenPart->D2);

      File<<daughter2->PID<< endl;
    }
    else{
      File<<endl;
    }
      //File<< "Daughter1,Daughter2: "<< daughter1 << "," << daughter2<<endl;      File<< "Status: " << GenPart->Status <<endl;
      File<< "Mass: " << GenPart->Mass <<endl;
      File<<"Pt: " << GenPart->PT <<endl;*/

    }
//    File.close();
    //  jet = (Jet*) branchJet->At(0);
//std::cout<<"happened"<<endl;
      // Plot jet transverse momentum
      //histJetPT->Fill(jet->PT);

      // Print jet transverse momentum
    //  cout << "Jet pt: "<<jet->PT << endl;

  //}

  /*  Electron *elec1, *elec2;

    // If event contains at least 2 electrons
    if(branchElectron->GetEntries() > 1)
    {
      // Take first two electrons
      elec1 = (Electron *) branchElectron->At(0);
      elec2 = (Electron *) branchElectron->At(1);

      // Plot their invariant mass
      histMass->Fill(((elec1->P4()) + (elec2->P4())).M());
    }

    if(branchMET->GetEntries() > 0)
    {
      float Met = (MissingET *) branchMET->At(0);
      histMET->Fill(Met->MET(), weight);
    }
    if(branchPhoton->GetEntries() > 1)
    {
      phot1 = (Photon *) branchPhoton->At(0);
      phot2 = (Photon *) branchPhoton->At(1);
      if(phot1->PT() < 20 | phot2->PT() < 20 | abs(phot1->Eta()) > 2.5 | abs(phot2->Eta()) > 2.5) continue;
      histDiPhotMass->Fill(((phot1->P4()) + (phot2->P4())).M(), weight);
    }

    yield += weight;
    y2 += weight*weight;

  }

  cout << "Event yield:   " << yield << " +/- " << sqrt(y2) << endl;
  cout << "Selection Eff: " << yield / (weight*numberOfEntries) << endl;

  // Show resulting histograms
  //histJetPT->Draw();
  //histMass->Draw();
  TCanvas * canvas1 = new TCanvas("canvas1");
    TCanvas * canvas2 = new TCanvas("canvas2");
    canvas1->cd();
    histJetPT->Draw();
    canvas2->cd();
    histMass->Draw();
TFile *file1 = new TFile("histos.root", "UPDATE");
  histJetPT->Write();
  histMass->Write();
  histMET->Write();
  histDiPhotMass->Write();
  file1->Close(); */
  TCanvas *MassP= new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histMassP->Draw();
  MassP->SaveAs("histMassP2.png");
  TCanvas *PTP= new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPTP->Draw();
  PTP->SaveAs("histPTP2.png");
  TCanvas *EtaP = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histEtaP->Draw();
  EtaP->SaveAs("histEtaP2.png");
  TCanvas *PIDP = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPIDP->Draw();
  PIDP->SaveAs("histPDGIDP2.png");
  TCanvas *PhiP = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPhiP->Draw();
  PhiP->SaveAs("histPhiP2.png");

  TCanvas *MassE = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histMassE->Draw();
  MassE->SaveAs("histMassE2.png");
  TCanvas *PTE= new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPTE->Draw();
  PTE->SaveAs("histPTE2.png");
  TCanvas *EtaE = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histEtaE->Draw();
  EtaE->SaveAs("histEtaE2.png");
  TCanvas *PIDE = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPIDE->Draw();
  PIDE->SaveAs("histPIDE2.png");
  TCanvas *PhiE = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPhiE->Draw();
  PhiE->SaveAs("histPhiE2.png");




  TCanvas *Mass= new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histMass->Draw();
  Mass->SaveAs("histMass2.png");
  TCanvas *PT= new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPT->Draw();
  PT->SaveAs("histPT2.png");
  TCanvas *Eta = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histEta->Draw();
  Eta->SaveAs("histEta2.png");
  TCanvas *PID = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPID->Draw();
  PID->SaveAs("histPDGID2.png");
  TCanvas *PIDL = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPIDL->Draw();
  PIDL->SaveAs("histPDGIDL2.png");
  TCanvas *Phi = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPhi->Draw();
  Phi->SaveAs("histPhi2.png");

  TCanvas *MassC = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histMassC->Draw();
  MassC->SaveAs("histMassC2.png");
  TCanvas *PTC= new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPTC->Draw();
  PTC->SaveAs("histPTC2.png");
  TCanvas *EtaC = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histEtaC->Draw();
  EtaC->SaveAs("histEtaC2.png");
  TCanvas *PIDC = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPIDC->Draw();
  PIDC->SaveAs("histPDGIDC2.png");
  TCanvas *PhiC = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
  histPhiC->Draw();
  PhiC->SaveAs("histPhiC2.png");


    TCanvas *MassN = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
    histMassN->Draw();
    MassN->SaveAs("histMassN2.png");
    TCanvas *PTN = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
    histPTN->Draw();
    PTN->SaveAs("histPTN2.png");
    TCanvas *EtaN = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
    histEtaN->Draw();
    EtaN->SaveAs("histEtaN2.png");
    TCanvas *PIDN = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
    histPIDN->Draw();
    PIDN->SaveAs("histPDGIDN2.png");
    TCanvas *PhiN = new TCanvas("my_canvas","Plotting Canvas",150,10,990,660);
    histPhiN->Draw();
    PhiN->SaveAs("histPhiN2.png");
}
