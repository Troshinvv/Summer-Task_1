#define SecondClass_cxx
#include "SecondClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include "GetFHCalPhi.h"
#include <math.h>
#include <TString.h>
#include <stdio.h>
#include <stdlib.h>

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

 //   FILE* fp;
 //   fp=fopen("my_file0.txt","w");
      FILE* fRes;
      fRes=fopen("ResPhin.txt","w");
      Float_t ResPhin[8]={0,0,0,0,0,0,0,0};
      Int_t ResN[8]={0,0,0,0,0,0,0,0};
    TH2F *energyxmod = new TH2F("energyxmod","ZDC_energy_mpd vs modules;number of module;Energy,GeV",90,0,100,90,0,5);
    TH1F *energy = new TH1F("energy", "energy",90,0,5);
    TH2F *energyxb = new TH2F ("energyxb", "ZDC_energy_mpd vs b;impact parameter b,fermi;energy,GeV", 90,0,18,90,0,50);
    TH1F *mod_angle =new TH1F ("mod_angle", "Distribution of module's azimuthal angle in FHCal;angle,rad;number", 90,-4,4);
    TH1F *weightangle =new TH1F("weightangle","weight_angle",90,-4,4);
    TH1F *Qxall =new TH1F ("Qxall", "Distribution of Qx and Qy in FHCal ;value of Qx,Qy,GeV;number of pulses N", 90,-3,3);
    TH1F *Qyall =new TH1F ("Qyall", "Distribution of Qy in FHCal;value of Qy,GeV;number of pulses N", 90,-3,3);
    TH1F *Qx44 =new TH1F ("Qx44","Distribution of Qx and Qy in first part of FHCal;value of Qx,Qy,Gev;number of pulses N",90,-3,3);
    TH1F *Qx90 =new TH1F ("Qx90","Distribution of Qx and Qy in second part of FHCal;value of Qx,Qy,GeV;number of pulses N",90,-3,3);
    TH1F *Qy44 =new TH1F ("Qy44","Distribution of Qy in first part of FHCal;value of Qy,Gev;number of pulses N",90,-3,3);
    TH1F *Qy90 =new TH1F ("Qy90", "Distribution of Qy in second part of FHCal;value of Qy,Gev;number of pulses N", 90,-3,3);
    TH2F *ntracksxb =new TH2F ("ntracksxb","multiplicity versus impact parameter,impact parameter b,fermi;multiplicity,number",90,0,18,90,0,500);
    TH2F *energyxntracks =new TH2F ("energyxntracks","energy versus multiplicity;multiplicity,number;energy,GeV",90,0,500,90,0,40);
    TH1F *fnall =new TH1F ("fnall","Distribution of event plane angle in FHCal;event plane angle fn,rad;number of pulses N",90,-4,4);
    TH1F *fn44 =new TH1F ("fn44","Distribution of event plane angle in first part of FHCal;event plane angle fn,rad;number of pulses N",90,-4,4);
    TH1F *fn90 =new TH1F ("fn90","Distribution of event plane angle in second part of FHCal;event plane angle fn,rad;number of pulses N",90,-4,4);
    TH1F *PhiEP =new TH1F ("PhiEP","Theoretic ditribution of reaction plane angle;angle,rad;number", 90,-4,4);


    TH1F *Qx44all[9];
    for(int j=1;j<9;j++)
    {
    Qx44all[j]=new TH1F(Form("Qx44all_%i",j),Form("Distribution of Qx in first part of FHCal with centrality %i0%;value of Qx,Gev;number of pulses N",j),90,-4,4);

    }

    TH1F *Qy44all[9];
    for(int j=1;j<9;j++)
    {

    Qy44all[j]=new TH1F(Form("Qy44all_%i",j),Form("Distribution of Qy first part of FHCal with centrality %i0%;value of Qy,Gev;number of pulses N",j),90,-4,4);
    }
    TH1F *Qx90all[9];
    for(int j=1;j<9;j++)
    {
    Qx90all[j]=new TH1F(Form("Qx90all_%i",j),Form("Distribution of Qx in second part of FHCal with centrality %i0%;value of Qx,GeV;number of pulses N",j),90,-4,4);
    }
    TH1F *Qy90all[9];
    for(int j=1;j<9;j++)
    {   
    Qy90all[j]=new TH1F(Form("Qy90all_%i",j),Form("Distribution of Qy in second part of FHCal with centrality %i0%;value of Qy,Gev;number of pulses N",j),90,-4,4);
    }



    TH1F *RecQx44all[9];
    for(int j=1;j<9;j++)
    {
    RecQx44all[j]=new TH1F(Form("RecQx44all_%i",j),Form("Distribution of Qx in first part of FHCal with centrality %i0% with recentering;value of Qx,GeV;number of pulses N",j),90,-4,4);
    }
    TH1F *RecQy44all[9];     
    for(int j=1;j<9;j++)
    {
    RecQy44all[j]=new TH1F(Form("RecQy44all_%i",j),Form("Distribution of Qy in first part of FHCal with centrality %i0% with recentering;value of Qy,Gev;number of pulses N",j),90,-4,4);
    }
    TH1F *RecQx90all[9];    
    for(int j=1;j<9;j++)
    {   
    RecQx90all[j]=new TH1F(Form("RecQx90all_%i",j),Form("Distribution of Qx in second part of FHCal with centrality %i0% with recentering;value of Qx,GeV;number of pulses N",j),90,-4,4);
    }
    TH1F *RecQy90all[9];    
    for(int j=1;j<9;j++)
    {                   
    RecQy90all[j]=new TH1F(Form("RecQy90all_%i",j),Form("Distribution of Qy in second part of FHCal with centrality %i0% with recentering;value of Qy,GeV;number of pulses N",j),90,-4,4);
    }


    TH1F *fn44all[9];
    for(int j=1;j<9;j++)
    {
    fn44all[j]=new TH1F(Form("fn44all_%i",j),Form("Distribution of event plane angle in first part of FHCal with centrality %i0%;Event plane angle fn,rad;number of pulses N",j),90,-4,4);
    }
    TH1F *fn90all[9];
    for(int j=1;j<9;j++)
    {
    fn90all[j]=new TH1F(Form("fn90all_%i",j),Form("Distribution of event plane angle in second part of FHCal with centrality %i0%;Event plane angle fn,rad;number of pulses N",j),90,-4,4);
    }









		
      
      
      
      
    TH1F *QyallB[9];
    for(int j=1;j<9;j++)
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
      float RecQx44 [9] ={0,0.01721,0.01293,0.007658,0.01912,-0.003273,0.02234,0.007018,-0.03159};
      float RecQx90 [9] ={0,0.02838,0.01913,0.02284,0.01547,-0.02274,0.01406,-0.003062,-0.03234};
      float RecQy44 [9] ={0,-0.002614,-0.01551,0.02799,-0.006327,0.005523,-0.00458,0.01763,0.01922};
      float RecQy90 [9] ={0,0.01306,-0.07839,-0.0004876,0.03239,0.01429,-0.02051,-0.006926,0.01394};
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


	
	for(int j=1;j<9;j++)
	{
	if((j-1)*10<=centrality_tpc_mpd && centrality_tpc_mpd<j*10)
	{
	QyallB[j]->Fill(Qy1);

	Qx44all[j]->Fill(Qx441);
	Qy44all[j]->Fill(Qy441);
	Qx90all[j]->Fill(Qx901);
	Qy90all[j]->Fill(Qy901);
	RecQx44all[j]->Fill(Qx441-RecQx44[j]);
	RecQy44all[j]->Fill(Qy441-RecQy44[j]);
	RecQx90all[j]->Fill(Qx901-RecQx90[j]);
	RecQy90all[j]->Fill(Qy901-RecQy90[j]);
	if(((Qx441-RecQx44[j])!=0) &&((Qy441-RecQy44[j])!=0))
	{
	fn44all[j]->Fill(atan2(Qy441-RecQy44[j],Qx441-RecQx44[j]));
	}
	if(((Qx901-RecQx90[j])!=0) &&((Qy901-RecQy90[j])!=0))
	{
	fn90all[j]->Fill(atan2(Qy901-RecQy90[j],Qx901-RecQx90[j]));
	}
	if( ((Qx901-RecQx90[j])!=0) &&((Qy901-RecQy90[j])!=0) && ((Qx441-RecQx44[j])!=0) &&((Qy441-RecQy44[j])!=0) )
	{
	ResPhin[j-1]=ResPhin[j-1]+cos(atan2(Qy901-RecQy90[j],Qx901-RecQx90[j])-atan2(Qy441-RecQy44[j],Qx441-RecQx44[j]));
	ResN[j-1]=ResN[j-1]+1;
	}
//	fprintf(fp,"%f\n",sqrt(abs(cos(atan2(Qy901-RecQy90[j],Qx901-RecQx90[j])-atan2(Qy441-RecQy44[j],Qx441-RecQx44[j])))));



	}
	}



// " A  Part Code for  Recentering "
//
//     for(int j=1;j<9;j++)
//      {
//      if((j-1)*10<=centrality_tpc_mpd && centrality_tpc_mpd<j*10)
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
       TLegend* leg1 = new TLegend(0.8,0.5,1,0.7);
       leg1->AddEntry(Qxall,"Qx","l");
       leg1->AddEntry(Qyall,"Qy","l");
       leg1->Draw();

       c5->Print("QxQyall.pdf");
       TCanvas* c6 =new TCanvas("c6","histo5");
       Qx44->Draw();
       Qx44->SetLineColor(kBlue);
       Qy44->Draw("same");
       Qy44->SetLineColor(kRed);
       TLegend* leg2 = new TLegend(0.8,0.5,1,0.7);
       leg2->AddEntry(Qx44,"Qx","l");
       leg2->AddEntry(Qy44,"Qy","l");
       leg2->Draw();
       c6->Print("QxQy0_44.pdf");
       TCanvas* c7 =new TCanvas("c7","histo6");
       Qx90->Draw();
       Qx90->SetLineColor(kBlue);
       Qy90->Draw("same");
       Qy90->SetLineColor(kRed);
       TLegend* leg3 = new TLegend(0.8,0.5,1,0.7);
       leg3->AddEntry(Qx90,"Qx","l");
       leg3->AddEntry(Qy90,"Qy","l");
       leg3->Draw();
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
      TCanvas* c13[9];
      for(int j=1;j<9;j++)
      {
      c13[j] =new TCanvas(Form("c13_%i",j),Form("c13_%i",j));
      QyallB[j]->Draw();
      c13[j]->Print(Form("QyallB_%i.pdf",j));
      }



      TCanvas* x44[9];
      TLegend* leg4[9];
      for(int j=1;j<9;j++)
      {
      x44[j]=new TCanvas(Form("x44_%i",j),Form("x44_%i",j));
      Qx44all[j]->Draw();
      Qx44all[j]->SetLineColor(kBlue);
      RecQx44all[j]->Draw("same");
      RecQx44all[j]->SetLineColor(kRed);
      leg4[j]=new TLegend(0.8,0.5,1,0.7);
      leg4[j]->AddEntry(Qx44all[j],"Qx","l");
      leg4[j]->AddEntry(RecQx44all[j],"Qx recentering","l");
      leg4[j]->Draw();
      x44[j]->Print(Form("Qx44all_%i.pdf",j));
      }
      TCanvas* y44[9];
      TLegend* leg5[9];
      for(int j=1;j<9;j++)
      {
      y44[j]=new TCanvas(Form("y44_%i",j),Form("y44_%i",j));
      Qy44all[j]->Draw();
      Qy44all[j]->SetLineColor(kBlue);
      RecQy44all[j]->Draw("same");
      RecQy44all[j]->SetLineColor(kRed);
      leg5[j]= new TLegend(0.8,0.5,1,0.7);
      leg5[j]->AddEntry(Qy44all[j],"Qy","l");
      leg5[j]->AddEntry(RecQy44all[j],"Recentering Qy","l");
      leg5[j]->Draw();
      y44[j]->Print(Form("Qy44all_%i.pdf",j));
      }
      TCanvas* x90[9];
      TLegend* leg6[9];
      for(int j=1;j<9;j++)
      {
      x90[j]=new TCanvas(Form("x90_%i",j),Form("x90_%i",j));
      Qx90all[j]->Draw();
      Qx90all[j]->SetLineColor(kBlue);
      RecQx90all[j]->Draw("same");
      RecQx90all[j]->SetLineColor(kRed);
      leg6[j]=new TLegend(0.8,0.5,1,0.7);
      leg6[j]->AddEntry(Qx90all[j],"Qx","l");
      leg6[j]->AddEntry(RecQx90all[j],"Recentering Qx","l");
      leg6[j]->Draw();
      x90[j]->Print(Form("Qx90all_%i.pdf",j));
      }
      TCanvas* y90[9];
      TLegend* leg7[9];
      for(int j=1;j<9;j++)
      {
      y90[j]=new TCanvas(Form("y90_%i",j),Form("y90_%i",j));
      Qy90all[j]->Draw();
      Qy90all[j]->SetLineColor(kBlue);
      RecQy90all[j]->Draw("same");
      RecQy90all[j]->SetLineColor(kRed);
      leg7[j]=new TLegend(0.8,0.5,1,0.7);
      leg7[j]->AddEntry(Qy90all[j],"Qy","l");
      leg7[j]->AddEntry(RecQy90all[j],"Recentering Qy","l");
      leg7[j]->Draw();
      y90[j]->Print(Form("Qy90all_%i.pdf",j));
      }
      TCanvas* f44[9];
      for(int j=1;j<9;j++)
      {
      f44[j]= new TCanvas(Form("f44_%i",j),Form("f44_%i",j));
      fn44all[j]->Draw();
      f44[j]->Print(Form("fn44all_%i.pdf",j));
      }
      TCanvas* f90[9];
      for(int j=1;j<9;j++)
      {
      f90[j]= new TCanvas(Form("f90_%i",j),Form("f90_%i",j));
      fn90all[j]->Draw();
      f90[j]->Print(Form("fn90all_%i.pdf",j));
      }


					  
					  
      


//   "A Part Code for Recentering"
//
//      TCanvas* c14[9];
//      for(int j=1;j<9;j++)
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

      for(int j=0;j<9;j++)
      {
      fprintf(fRes,"%f\n",sqrt(ResPhin[j]/ResN[j]));
      }
      fclose(fRes);

      // if (Cut(ientry) < 0) continue;
//      fclose(fp);
   }

