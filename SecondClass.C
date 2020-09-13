#define SecondClass_cxx
#include "SecondClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include "GetFHCalPhi.h"
#include <math.h>
#include <TString.h>

void SecondClass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L SecondClass.C
//      root> SecondClass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
     int i=0;


//  "A Part Code for Recentering"
//
//TFile* FiRec =new TFile (RecenteringFileName.Data(),"read");


    TH2F *energyxmod = new TH2F("energyxmod","ZDC_energy_mpd vs modules",90,0,100,90,0,5);
    TH1F *energy = new TH1F("energy", "energy",90,0,5);
    TH2F *energyxb = new TH2F ("energyxb", "ZDC_energy_mpd vs b", 90,0,18,90,0,50);
    TH1F *mod_angle =new TH1F ("mod_angle", "mod_angle", 90,-4,4);
    TH1F *weightangle =new TH1F("weightangle","weight_angle",90,-4,4);
    TH1F *Qxall =new TH1F ("Qxall", "Qxall", 90,-3,3);
    TH1F *Qyall =new TH1F ("Qyall", "Qyall", 90,-3,3);
    TH1F *Qx44 =new TH1F ("Qx44","Qx44",90,-3,3);
    TH1F *Qx90 =new TH1F ("Qx90","Qx90",90,-3,3);
    TH1F *Qy44 =new TH1F ("Qy44","Qy44",90,-3,3);
    TH1F *Qy90 =new TH1F ("Qy90", "Qy90", 90,-3,3);
    TH2F *ntracksxb =new TH2F ("ntracksxb","ntracksxb",90,0,18,90,0,500);
    TH2F *energyxntracks =new TH2F ("energyxntracks","energyxntracks",90,0,500,90,0,40);
    TH1F *fnall =new TH1F ("fnall","fnall",90,-4,4);
    TH1F *fn44 =new TH1F ("fn44","fn44",90,-4,4);
    TH1F *fn90 =new TH1F ("fn90","fn90",90,-4,4);
    TH1F *PhiEP =new TH1F ("PhiEP","PhiEP", 90,-4,4);
    TH1F *QyallB[8];
    for(int j=0;j<8;j++)
    {
    QyallB[j]=new TH1F(Form("QyallB_%i",j),Form("QyallB_%i",j),90,-4,4);
    }



//   " A Part Code for Recentering "
//
//    TH1F *hRecQy[8];
//    for(int j=0;j<8;j++)
//    {
//    hRecQy[j]= (TH1F*) FiRec->Get(Form("QyallB_%i",j));
//    }
//    TH1F *RecQy[8];
//    for(int j=0;j<8;j++)
//    {
//    RecQy[j]=new TH1F(Form("RecQy_%i",j),Form("RecQy_%i",j),90,-4,4);
//    }


    


   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      float Qx1 =-0.1045;
      float Qy1 =0.001949;
      float Qx441 =-0.05392;
      float Qx901 =-0.05738;
      float Qy441 =-0.008082;
      float Qy901 =0.01032;
      float en1 =0;
      for(i=0;i<90;i++)
      {
      if(i==22 || i==67)
      {
      continue;
      }
      int w_sign = (i<45) ? 1: -1;
      energyxmod->Fill(i,ZDC_energy_mpd[i]);
      energy->Fill(ZDC_energy_mpd[i]);
      en1=en1+ZDC_energy_mpd[i];
      Qx1=Qx1+ w_sign * ZDC_energy_mpd[i] * cos(GetFHCalPhi(i));
      Qy1=Qy1+ w_sign * ZDC_energy_mpd[i] * sin(GetFHCalPhi(i));
      if(i<45)
      {
      Qx441=Qx441 + w_sign * ZDC_energy_mpd[i] * cos(GetFHCalPhi(i));
      Qy441=Qy441 + w_sign * ZDC_energy_mpd[i] * sin(GetFHCalPhi(i));
      }
        else
	{
	Qx901=Qx901 + w_sign * ZDC_energy_mpd[i] * cos(GetFHCalPhi(i));
	Qy901=Qy901 + w_sign * ZDC_energy_mpd[i] * sin(GetFHCalPhi(i));
	}
	float phi=0;
	if(i==22 ||i==67)
	continue;
	else
	weightangle->Fill(GetFHCalPhi(i),ZDC_energy_mpd[i]);
	}


	
	for(int j=0;j<8;j++)
	{
	if(j*10<=centrality_tpc_mpd && centrality_tpc_mpd<(j+1)*10)
	{
	QyallB[j]->Fill(Qy1);
	}
	}



// " A  Part Code for  Recentering "
//
//     for(int j=0;j<8;j++)
//      {
//      if(j*10<=centrality_tpc_mpd && centrality_tpc_mpd<(j+1)*10)
//      {
//      float QyRec= Qy1-hRecQy[j]->GetMean();
//      RecQy[j]->Fill(QyRec);
//      }
//      }





      energyxb->Fill(b_mc,en1);
      Qxall->Fill(Qx1);
      Qyall->Fill(Qy1);
      Qx44->Fill(Qx441);
      Qx90->Fill(Qx901);
      Qy44->Fill(Qy441);
      Qy90->Fill(Qy901);
      int tracks1=0;
      if(Qx1!=0 && Qy1!=0)
      {
      fnall->Fill(atan2(Qy1,Qx1));
      }
      if(Qx441!=0 && Qy441!=0)
      {
      fn44->Fill(atan2(Qy441,Qx441));
      }
      if(Qx901!=0 && Qy901!=0)
      {
      fn90->Fill(atan2(Qy901,Qx901));
      }
      for(int k=0;k < n_tracks_mpd;k++)
      {
      if(abs(eta_mpd[k])<0.5)
      {
      tracks1=tracks1+1;
      }
      }
      ntracksxb->Fill(b_mc,tracks1);
      energyxntracks->Fill(tracks1,en1);
      PhiEP->Fill(phiEP_mc-3.1415926535);
      }
      for(int j=0;j<90;j++)
      {
       if(j==22 || j==67)
       continue;
       float angle = GetFHCalPhi(j);
       mod_angle->Fill(angle);
       }
       TCanvas* c1 =new TCanvas("c1","histo");
       energyxmod->Draw("colz");
       energyxmod->SetLineColor(kBlue);
       c1->Print("Energy_in_modules.pdf");
       TCanvas* c2 =new TCanvas("c2","histo1");
       energy->Draw();
       energy->SetLineColor(kRed);
       c2->Print("Energy.pdf");
       TCanvas* c3 =new TCanvas("c3","histo2");
       energyxb->Draw("colz");
       c3->Print("energy_vs_b.pdf");
       TCanvas* c4 = new TCanvas("c4","histo3");
       mod_angle->Draw();
       c4->Print("mod_angle.pdf");
       TCanvas* c5=new TCanvas("c5","histo4");
       Qxall->Draw();
       Qxall->SetLineColor(kBlue);
       Qyall->Draw("same");
       Qyall->SetLineColor(kRed);
       c5->Print("QxQyall.pdf");
       TCanvas* c6 =new TCanvas("c6","histo5");
       Qx44->Draw();
       Qx44->SetLineColor(kBlue);
       Qy44->Draw("same");
       Qy44->SetLineColor(kRed);
       c6->Print("QxQy0_44.pdf");
       TCanvas* c7 =new TCanvas("c7","histo6");
       Qx90->Draw();
       Qx90->SetLineColor(kBlue);
       Qy90->Draw("same");
       Qy90->SetLineColor(kRed);
       c7->Print("QxQy45_89.pdf");
       TCanvas* c8 =new TCanvas("c8","histo7");
       ntracksxb->Draw("colz");
       c8->Print("ntracksxb.pdf");
       TCanvas* c9 =new TCanvas("c9","histo8");
       energyxntracks->Draw("colz");
       c9->Print("energyxntracks.pdf");
       TCanvas* c10 =new TCanvas("c10","histo9");
       fnall->Draw();
       c10->Print("fnall.pdf");
       TCanvas* c11 =new TCanvas("c11","histo10");
       fn44->Draw();
       c11->Print("fn44.pdf");
       TCanvas* c12 =new TCanvas("c12","histo11");
       fn90->Draw();
       c12->Print("fn90.pdf");
      TCanvas* c13[8];
      for(int j=0;j<8;j++)
      {
      c13[j] =new TCanvas(Form("c13_%i",j),Form("c13_%i",j));
      QyallB[j]->Draw();
      c13[j]->Print(Form("QyallB_%i.pdf",j));
      }
      


//   "A Part Code for Recentering"
//
//      TCanvas* c14[8];
//      for(int j=0;j<8;j++)
//      {
//      c14[j] =new TCanvas(Form("c14_%i",j),Form("c14_%i",j));
//     RecQy[j]->Draw();
//      c14[j]->Print(Form("RecQy_%i.pdf",j));
//      }



      TCanvas* c15 =new TCanvas("c15","histo15");
      weightangle->Draw();
      c15->Print("weight_angle.pdf");
      TCanvas* c16 =new TCanvas("c16","histo16");
      PhiEP->Draw();
      c16->Print("PhiEP_mc.pdf");

      // if (Cut(ientry) < 0) continue;
   }

