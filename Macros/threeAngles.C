#include "TCanvas.h"
#include "TFile.h"
#include "THStack.h"
#include "iostream.h"

void threeAngles(){

  THStack *hsP = new THStack("hsP","Stacked #phi");
  THStack *hsE = new THStack("hsE","Stacked #eta");

  TFile * file0 = TFile::Open("Pyquen10000.root");
  TFile * file1 = TFile::Open("PythiaZ2Star.root");
  TFile * file2 = TFile::Open("treefile10000.root"); 

  TCanvas * c = new TCanvas("c","Eta Comparison",1);
  c -> Divide(2,2);
  
  
  TTree *Tpyq = (TTree*)file0 -> Get("dijet/t");
  TTree *Tpyt = (TTree*)file1 -> Get("dijet/t");
  TTree *Ttf = (TTree*)file2 -> Get("dijet/t");  
  
  Tpyq ->Print();
  Tpyt ->Print();
  Ttf -> Print();
  // Tpyq ->Draw("jtphi");
  
  TH1F * hPyqP = new TH1F ("hPyqP","PYQUEN Jet #phi (rad)",60,-3.14,3.14);  
  TH1F * hPytP = new TH1F ("hPytP","PYTHIA Z2 Jet #phi (rad)",60,-3.14,3.14);  
  TH1F * hTfP = new TH1F ("hTfP","Tree File Jet #phi (rad)",60,-3.14,3.14);
  TH1F * hPyqE = new TH1F("hPyqE","PYQUEN Jet #eta (rad)",60,-2,2);
  TH1F * hPytE = new TH1F("hPytE","PYTHIA Z2 Jet #eta (rad)",60,-2,2);
  TH1F * hTfE = new TH1F("hTfE","Tree File Jet #eta (rad)",60,-2,2);

  Int_t Npyq = Tpyq->GetEntries();
  Int_t Npyt = Tpyt->GetEntries();
  Int_t Ntf = Ttf->GetEntries();

  cout << Npyq <<"\n";
  cout << Npyt<<"\n";
  cout << Ntf<<"\n";

  Tpyq ->Draw("jtphi>>hPyqP","","goff");
  Tpyt ->Draw("jtphi>>hPytP","","goff");
  Ttf ->Draw("jtphi>>hTfP","","goff");

  hPyqP ->Scale(1./Npyq);
  hPytP ->Scale(1./Npyt);
  hTfP ->Scale(1./Ntf);
  
  Tpyq ->Draw("jteta>>hPyqE","","goff");
  Tpyt ->Draw("jteta>>hPytE","","goff");
  Ttf ->Draw("jteta>>hTfE","","goff");

  hPyqE ->Scale(1./Npyq);
  hPytE ->Scale(1./Npyt);
  hTfE ->Scale(1./Ntf);

  c->cd(1);
  hPyqE->Draw();

  c->cd(2);
  hPytE->Draw();

  c->cd(3);
  hTfE->Draw();

  c->cd(4);
  hsE->Add(hPyqE);
  hsE->Add(hPytE);
  hsE->Add(hTfE);
  hsE->Draw();
  c->SaveAs("threeEta.pdf","RECREATE");

  TCanvas * c2 = new TCanvas("c2","Phi Comparison",1);
  c2 -> Divide(2,2);

  c2->cd();
  c2->cd(1);
  hPyqP->Draw();

  c2->cd(2);
  hPytP->Draw();

  c2->cd(3);
  hTfP->Draw();

  c2->cd(4);
  hsP->Add(hPyqP);
  hsP->Add(hPytP);
  hsP->Add(hTfP);
  hsP->Draw();  
  c2->SaveAs("threePhi.pdf","RECREATE");
}
