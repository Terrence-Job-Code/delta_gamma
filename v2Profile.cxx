#include "rootheader.h"

void  v2Profile()
{
    //TFile *file = new TFile("output.root");
    // TFile *file = new TFile("v2profs.root");
    // TFile *file = new TFile("Run11_200GeVfemto.root");
    // TFile *file = new TFile("Data/Results/Run11_200GeV/Run11_200GeVfemto_attempt3.root");
    TFile *file = new TFile("Data/Results/Run11_200GeV/NoGap/Run11_200GeVfemto_noGap.root");

    const static int numCentBins = 9;

    // may want to change these names as some point
    //v2_2Plus = (TProfile*) file->Get("hist7_pfx");
    //v2_2Minus = (TProfile*) file->Get("hist8_pfx"); 

    // Centrality numbers
    // 1 : 70 - 80% // most peripheral
    // 2 : 60 - 70%
    // 3 : 50 - 60% 
    // 4 : 40 - 50%
    // 5 : 30 - 40%
    // 6 : 20 - 30%
    // 7 : 10 - 20%
    // 8 : 5  -10%
    // 9 : 0 - 5%

    // will work these into sprintf calls
    double energy = 200;
    double run = 11;

    TProfile *v2_2Plus[numCentBins];
    TProfile *v2_2Minus[numCentBins];

    TLine *tline = new TLine(-0.5,0,0.5,0);
    tline->SetLineColor(6);

    char pName[256];
    char mName[256];

    // this initial code will have some flip flopping right now until I optimize the code a bit more 
    // TH2D *hv22EPplu[numCentBins];
    // TH2D *hv22EPmin[numCentBins];

    for(int i = 0; i < numCentBins; i++)
    {
        sprintf(pName,"v22PvsAchC%i_pfx",i+1);
        sprintf(mName,"v22MvsAchC%i_pfx",i+1);

        v2_2Plus[i] = (TProfile*) file->Get(pName);
        v2_2Minus[i] = (TProfile*) file->Get(mName);
        
        //sprintf(pName,"v22EPplu%i",i);
        //sprintf(mName,"v22EPmin%i",i);

        //hv22EPplu[i] = (TH2D*) file->Get(pName);
        //hv22EPmin[i] = (TH2D*) file->Get(mName);

        //v2_2Plus[i] = hv22EPplu[i]->ProfileX();
        //v2_2Minus[i] = hv22EPmin[i]->ProfileX();
    }

    //cout << v2_2Plus->GetBinContent(7) << endl;

    double prev = 0;
    double next = 0;
    // double theXcut = 0.1;

    // will use this instead of determining other length values
    int numBins = 50; // will need to put this in ahead of time based on my other code

    double v2AchxP[numCentBins][numBins];
    double v2AchxPErr[numCentBins][numBins];
    double v2AchyP[numCentBins][numBins];
    double v2AchyPErr[numCentBins][numBins];

    double v2AchxM[numCentBins][numBins];
    double v2AchxMErr[numCentBins][numBins];
    double v2AchyM[numCentBins][numBins];
    double v2AchyMErr[numCentBins][numBins];

    for(int i = 0; i < numCentBins; i++)
    {
        for(int j = 1; j < v2_2Plus[i]->GetNbinsX(); j++)
        {
            prev = v2_2Plus[i]->GetBinContent(j);
            if(prev>=0)
            {
                next = TMath::Sqrt(prev);
                v2AchxP[i][j-1] = v2_2Plus[i]->GetBinCenter(j);
                
                // while this isn't desireable for the error, this is what root does by default for the projection
                v2AchxPErr[i][j-1] = v2_2Plus[i]->GetBinWidth(j);  
                v2AchyP[i][j-1] = next;
                v2AchyPErr[i][j-1] = next*(0.5)*(v2_2Plus[i]->GetBinError(j))/(v2_2Plus[i]->GetBinContent(j));
            }
            else
            {
                v2AchxP[i][j-1] = -1;
                v2AchxPErr[i][j-1] = 0;
                v2AchyP[i][j-1] = 0;
                v2AchyPErr[i][j-1] = 0;
            }
            // printf("%.2f \t %i \t %i \n",v2AchyP[i][j-1],i,j);
        }
    }

    TGraphErrors *v2_plus[numCentBins];


    for(int i = 0; i < numCentBins; i++)
    {
        v2_plus[i] = new TGraphErrors(numBins,v2AchxP[i],v2AchyP[i],v2AchxPErr[i],v2AchyPErr[i]);
    }

    cout << "v2 plus graph" << endl;
    TCanvas *cv2P[numCentBins];
    char centPluStr[256];
    char centrality[numCentBins][256]={
        {" 70 - 80%"},
        {" 60 - 70%"},
        {" 50 - 60%"},
        {" 40 - 50%"},
        {" 30 - 40%"},
        {" 20 - 30%"},
        {" 10 - 20%"},
        {" 5 - 10%"},
        {" 0 - 5%"}
        };
    char canName[256];
    char savPlu[256];

    for(int i = 0; i < numCentBins; i++)
    {
        sprintf(canName,"cP%i",i);
        sprintf(centPluStr,"v2_{+}{2} vs A_{ch} Centrality%s",centrality[i]);
        sprintf(savPlu,"Plots/testPlots/v2pluC%i.pdf",i+1);
        cv2P[i] = new TCanvas(canName);
        v2_plus[i]->SetTitle(centPluStr);
        v2_plus[i]->GetXaxis()->SetTitle("A_{ch}");
        v2_plus[i]->GetYaxis()->SetTitle("v2_{+}");
        v2_plus[i]->SetMarkerColor(3);
        v2_plus[i]->SetLineColor(3);
        // v2_2Plus->Draw("hist");
        v2_plus[i]->Draw("apz");
        // c1->SaveAs("Plots/testPlots/v2+graph.pdf");
        cv2P[i]->SaveAs(savPlu);
        cv2P[i]->Close();
    }

    for(int i = 0; i < numCentBins; i++)
    {
        for(int j = 1; j < v2_2Minus[i]->GetNbinsX(); j++)
        {
            prev = v2_2Minus[i]->GetBinContent(j);
            if(prev>=0)
            {
                next = TMath::Sqrt(prev);
                v2AchxM[i][j-1] = v2_2Minus[i]->GetBinCenter(j);
                
                // while this isn't desireable for the error, this is what root does by default for the projection
                v2AchxMErr[i][j-1] = v2_2Minus[i]->GetBinWidth(j);
                v2AchyM[i][j-1] = next;
                v2AchyMErr[i][j-1] = next*(0.5)*(v2_2Minus[i]->GetBinError(j))/(v2_2Minus[i]->GetBinContent(j));
            }
            else
            {
                v2AchxM[i][j-1] = -1;
                v2AchxMErr[i][j-1] = 0;
                v2AchyM[i][j-1] = 0;
                v2AchyMErr[i][j-1] = 0;
            }
        }
    }

    TGraphErrors *v2_minus[numCentBins];

    for(int i = 0; i < numCentBins; i++)
    {
        v2_minus[i] = new TGraphErrors(numBins,v2AchxM[i],v2AchyM[i],v2AchxMErr[i],v2AchyMErr[i]);
    }

    TCanvas *cv2M[numCentBins];
    char centMinStr[256];
    char savMin[256];

    for(int i = 0; i < numCentBins; i++)
    {
        sprintf(canName,"cM%i",i);
        sprintf(centMinStr,"v2_{-}{2} vs A_{ch} Centrality%s",centrality[i]);
        sprintf(savMin,"Plots/testPlots/v2minC%i.pdf",i+1);
        cv2M[i] = new TCanvas(canName);
        v2_minus[i]->SetTitle(centMinStr);
        v2_minus[i]->GetXaxis()->SetTitle("A_{ch}");
        v2_minus[i]->GetYaxis()->SetTitle("v2_{-}");
        v2_minus[i]->SetLineColor(6);
        v2_minus[i]->SetMarkerColor(6);
        // v2_2Plus->Draw("hist");
        v2_minus[i]->Draw("apz");
        // cv2M[i]->SaveAs("Plots/testPlots/v2+graph.pdf");
        cv2M[i]->SaveAs(savMin);
        cv2M[i]->Close();
    }

    // cout << "before m - p" << endl;
        
    TCanvas *cv2PM[numCentBins];
    TGraphErrors *grv2pm_plu[numCentBins];
    TGraphErrors *grv2pm_min[numCentBins];
    TMultiGraph *mgv2pm[numCentBins];

    for(int i = 0; i < numCentBins; i++)
    {
        grv2pm_plu[i] = new TGraphErrors(numBins,v2AchxP[i],v2AchyP[i],v2AchxPErr[i],v2AchyPErr[i]);
        grv2pm_min[i] = new TGraphErrors(numBins,v2AchxM[i],v2AchyM[i],v2AchxMErr[i],v2AchyMErr[i]);
    }

    char centMPstr[256];
    char savName[256];

    TLegend *legV2pm[numCentBins];

    for(int i = 0; i < numCentBins; i++)
    {
        sprintf(canName,"cMP%i",i);
        sprintf(centMPstr,"v2_{-}{2} and v2_{+}{2} vs A_{ch} Centrality%s",centrality[i]);
        sprintf(savName,"Plots/200GeV_Run11plots/v2pm%i.pdf",i);
        mgv2pm[i] = new TMultiGraph(canName,centMPstr);
        cv2PM[i] = new TCanvas(canName);

        grv2pm_plu[i]->SetTitle(centMPstr);
        grv2pm_min[i]->SetTitle(centMPstr);

        // v2_plus[i]->SetMarkerStyle(3);
        grv2pm_plu[i]->SetMarkerColor(3);
        grv2pm_plu[i]->SetLineColor(3);
        // grv2pm_plu[i]->Draw("apz");
        // v2_minus[i]->SetMarkerStyle(6);
        grv2pm_min[i]->SetMarkerColor(6);
        grv2pm_min[i]->SetLineColor(6);

        grv2pm_plu[i]->SetMarkerStyle(3);
        grv2pm_min[i]->SetMarkerStyle(1);

        grv2pm_plu[i]->GetXaxis()->SetRangeUser(-0.2,0.2);
        grv2pm_min[i]->GetXaxis()->SetRangeUser(-0.2,0.2);
        mgv2pm[i]->Add(grv2pm_plu[i]);
        mgv2pm[i]->Add(grv2pm_min[i]);
        mgv2pm[i]->Draw("apz");
        tline->Draw("same");
        mgv2pm[i]->GetXaxis()->SetTitle("A_{ch}");
        mgv2pm[i]->GetYaxis()->SetTitle("v2");

        mgv2pm[i]->GetXaxis()->SetRangeUser(-0.15,0.15);
        if(i!=0) mgv2pm[i]->GetYaxis()->SetRangeUser(0.03,0.06);
        if(i==0) mgv2pm[i]->GetYaxis()->SetRangeUser(0.02,0.08);

        legV2pm[i] = new TLegend(0.7,0.65,1.0,0.85);
        legV2pm[i]->AddEntry(grv2pm_min[i],"run11 #pi^{-}");
        legV2pm[i]->AddEntry(grv2pm_plu[i],"run11 #pi^{+}");
        legV2pm[i]->Draw();

        // grv2pm_min[i]->Draw("same apz");
        cv2PM[i]->SaveAs(savName);
    }


    // creating the slope value for the chiral magnetic wave paper
    double v2mMinv2p[numCentBins][numBins];
    double v2mMinv2pErr[numCentBins][numBins];
    double v2pmx[numCentBins][numBins];
    double v2pmxErr[numCentBins][numBins];


    for(int i = 0; i < numCentBins; i++)
    {

        for(int j = 0; j < numBins; j++)
        {
            if(v2AchxM[i][j]!=-1 && v2AchxP[i][j]!=-1)
            {
                v2mMinv2p[i][j] = v2AchyM[i][j] - v2AchyP[i][j];
                v2mMinv2pErr[i][j] = TMath::Sqrt(TMath::Power(v2AchyMErr[i][j],2) + TMath::Power(v2AchyPErr[i][j],2));
                v2pmx[i][j] = v2AchxM[i][j];
                v2pmxErr[i][j] = v2AchxMErr[i][j];
            }
            else
            {
                v2mMinv2p[i][j] = 0;
                v2mMinv2pErr[i][j] = 0;
                v2pmx[i][j] = -1;
                v2pmxErr[i][j] = 0;
            }
        }
    }

    for(int i = 0; i < numCentBins; i++)
    {
        for(int j = 0; j < numBins; j++)
        {
            //if(v2pmx[i][j] == 0) printf("x = 0 at %i and %i \n",i,j);
            if(i == 2) // specific bug check and fix 
            {
                printf("v2pmx[%i][%i] = %f \t v2mMinv2p[%i][%i] = %f \n",i,j, v2pmx[i][j],i,j,v2mMinv2p[i][j]);
            } 
            if(i == 6) // specific bug check and fix 
            {
                printf("v2pmx[%i][%i] = %f \t v2mMinv2p[%i][%i] = %f \n",i,j, v2pmx[i][j],i,j,v2mMinv2p[i][j]);
                
                if(v2pmx[i][j] == 0.)
                {
                    if( abs( v2mMinv2p[i][j] ) > 1) v2mMinv2p[i][j] = 0; // this is a temporary bug fix
                    v2pmx[i][j] = -1;   
                }
            }

            if(abs(v2pmx[i][j]) < 0.001 )
            {
                v2pmx[i][j] = -1;
                v2mMinv2p[i][j] = 0;
                v2mMinv2pErr[i][j] = 0;
            }
        }
    }

    cout << "plotted values in TGraph" << endl;

    for(int i = 0; i < numCentBins; i++)
    {
        for(int j = 0; j < numBins; j++)
        {
            printf("v2pmx[%i][%i] = %f \t v2mMinv2p[%i][%i] = %f \n",i,j, v2pmx[i][j],i,j,v2mMinv2p[i][j]);
        }
        cout << "\n" << endl;
    }


    TGraphErrors *tgShrunkV2mp[numCentBins];
    TF1 *fits[numCentBins];

    double rFitVals[numCentBins];
    double rFitValErrs[numCentBins];

    char fitName[256];
    char graphName[256];

    // TCanvas *cmFit = new TCanvas(); // will be a multiplot
    TCanvas *cmFit[numCentBins]; // will be a multiplot

    for(int i = 0; i < numCentBins; i++)
    {
        // cmFit->Divide(3,3);
        // cmFit->cd(i+1);

        sprintf(canName,"cSub%i",i);

        cmFit[i] = new TCanvas(canName);

        tgShrunkV2mp[i] = new TGraphErrors(numBins,v2pmx[i],v2mMinv2p[i],v2pmxErr[i],v2mMinv2pErr[i]);

        sprintf(fitName,"fits%i",i+1);
        sprintf(graphName,"v2_{-}{2} - v2_{+}{2} vs A_{ch} Centrality%s",centrality[i]);
        sprintf(savName,"Plots/200GeV_Run11plots/v2pminv2m%i.pdf",i);


        tgShrunkV2mp[i]->SetTitle(graphName);
        tgShrunkV2mp[i]->GetXaxis()->SetTitle("A_{ch}");
        tgShrunkV2mp[i]->GetYaxis()->SetTitle("v2_{-} - v2_{+}");
        tgShrunkV2mp[i]->GetXaxis()->SetRangeUser(-0.15,0.15);
        tgShrunkV2mp[i]->GetYaxis()->SetRangeUser(-0.04,0.04);
        // if(i>=3)tgShrunkV2mp[i]->GetYaxis()->SetRangeUser(-0.004,0.01);
        // if(i<3)tgShrunkV2mp[i]->GetYaxis()->SetRangeUser(-0.015,0.015);
        tgShrunkV2mp[i]->SetMarkerStyle(3);
        tgShrunkV2mp[i]->SetLineColor(4);
        tgShrunkV2mp[i]->SetMarkerColor(4);
        tgShrunkV2mp[i]->Draw("apz");

        // Ach is a function of centrality, so these shouldn't all be the same

        fits[i] = new TF1(fitName,"[0] + [1]*x",-0.1,0.1);
        if(i==7) fits[i] = new TF1(fitName,"[0] + [1]*x",-0.05,0.05);
        if(i==8) fits[i] = new TF1(fitName,"[0] + [1]*x",-0.07,0.07);

        tgShrunkV2mp[i]->Fit(fits[i],"R");
        tline->Draw("same");
        // cout << fits[i]->GetParameter(1) << endl;
        // cout << fits[i]->GetParError(1) << endl;
        rFitVals[i] = fits[i]->GetParameter(1);
        rFitValErrs[i] = fits[i]->GetParError(1);
        // fits[i]->Draw("same");
        cmFit[i]->SaveAs(savName);
    }

    double centralityMidVals[numCentBins] = {75,65,55,45,35,25,15,7.5,2.5};
    double centralityErrors[numCentBins] = {0,0,0,0,0,0,0,0,0};

    TLine *tline2 = new TLine(-0.5,0,100,0);
    tline2->SetLineColor(6);
    TGraphErrors *tgRvals = new TGraphErrors(numCentBins,centralityMidVals,rFitVals,centralityErrors,rFitValErrs);

    sprintf(savName,"Plots/200GeV_Run11plots/rslope.pdf");

    TCanvas *cRfits = new TCanvas();
    tgRvals->SetTitle("r slope value vs centrality");
    tgRvals->GetXaxis()->SetTitle("Centrality (%)");
    tgRvals->GetYaxis()->SetTitle("slope r value");
    tgRvals->SetMarkerStyle(4);
    tgRvals->Draw("apz");
    tline2->Draw("same");

    cRfits->SaveAs(savName);    

    return;
}


