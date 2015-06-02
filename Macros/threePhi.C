#include "TCanvas.h"
#include "TFile.h"

void threeAngles(){
  TFile * file0 = TFile::Open("Pyquen10000.root");
  TFile * file1 = TFile::Open("PythiaZ2Star.root");
  TFile * file2 = TFile::Open("treefile10000.root"); 

  TCanvas * c = new TCanvas("c","Phi Comparison",1);
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
  
  Tpyq ->Draw("jtphi>>hPyqP","","goff");
  Tpyt ->Draw("jtphi>>hPytP","","goff");
  Ttf ->Draw("jtphi>>hTfP","","goff");

  
  Tpyq ->Draw("jtphi>>hPyqE","","goff");
  Tpyt ->Draw("jtphi>>hPytE","","goff");
  Ttf ->Draw("jtphi>>hTfE","","goff");

  c->cd(1);
  hPyqE->Draw();

  c->cd(2);
  hPytE->Draw();

  c->cd(3);
  hTfE->Draw();

  c->cd(4);
  hPyqE->Draw();
  hPytE->Draw("SAME");
  hTfE->Draw("SAME");
  
}
