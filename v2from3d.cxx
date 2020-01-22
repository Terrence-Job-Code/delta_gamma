#include "rootheader.h"


void v2from3d()
{
    // char dataFile[256] = "Data/Results/Run11_200GeV/testing/Run11_200GeV_MoreMods02.root";
    char dataFile[256] = "Data/Results/Run11_200GeV/testing/Run11_200GeV_MoreMods03.root";
    
    TFile *file = new TFile(dataFile);

    // x = <cos>
    // y = Ach
    // z = eta

    // Centralities
    // C1 : 70 - 80%
    // C2 : 60 - 70%
    // C3 : 50 - 60%
    // C4 : 40 - 50%
    // C5 : 30 - 40%
    // C6 : 20 - 30%
    // C7 : 10 - 20%
    // C8 : 5 - 10%
    // C9 : 0 - 5%

    const static int numCentralities = 9;

    char centrality[numCentralities][256]={
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
 
    TH2D *hsin2PetaP[numCentralities];
    TH2D *hcos2PetaP[numCentralities];
    TH2D *hsin2MetaP[numCentralities];
    TH2D *hcos2MetaP[numCentralities];

    TH2D *hsin2PetaM[numCentralities];
    TH2D *hcos2PetaM[numCentralities];
    TH2D *hsin2MetaM[numCentralities];
    TH2D *hcos2MetaM[numCentralities];

    TProfile *hsin2PetaPpfy[numCentralities];
    TProfile *hcos2PetaPpfy[numCentralities];
    TProfile *hsin2MetaPpfy[numCentralities];
    TProfile *hcos2MetaPpfy[numCentralities];

    TProfile *hsin2PetaMpfy[numCentralities];
    TProfile *hcos2PetaMpfy[numCentralities];
    TProfile *hsin2MetaMpfy[numCentralities];
    TProfile *hcos2MetaMpfy[numCentralities];


    char getName[256];

    for(int i = 0; i < numCentralities; i++)
    {
        sprintf(getName,"h2dcosP2etaPC%i",i+1);
        hcos2PetaP[i] = (TH2D*) file->Get(getName);

        sprintf(getName,"h2dcosP2etaMC%i",i+1);
        hcos2PetaM[i] = (TH2D*) file->Get(getName);

        sprintf(getName,"h2dcosM2etaPC%i",i+1);
        hcos2MetaP[i] = (TH2D*) file->Get(getName);

        sprintf(getName,"h2dcosM2etaMC%i",i+1);
        hcos2MetaM[i] = (TH2D*) file->Get(getName);

        sprintf(getName,"h2dsinP2etaPC%i",i+1);
        hsin2PetaP[i] = (TH2D*) file->Get(getName);

        sprintf(getName,"h2dsinP2etaMC%i",i+1);
        hsin2PetaM[i] = (TH2D*) file->Get(getName);

        sprintf(getName,"h2dsinM2etaPC%i",i+1);
        hsin2MetaP[i] = (TH2D*) file->Get(getName);

        sprintf(getName,"h2dsinM2etaMC%i",i+1);
        hsin2MetaM[i] = (TH2D*) file->Get(getName);

        hcos2PetaPpfy[i] = hcos2PetaP[i]->ProfileY();
        hcos2PetaMpfy[i] = hcos2PetaM[i]->ProfileY();
        hcos2MetaPpfy[i] = hcos2MetaP[i]->ProfileY();
        hcos2MetaMpfy[i] = hcos2MetaM[i]->ProfileY();

        hsin2PetaPpfy[i] = hsin2PetaP[i]->ProfileY();
        hsin2PetaMpfy[i] = hsin2PetaM[i]->ProfileY();
        hsin2MetaPpfy[i] = hsin2MetaP[i]->ProfileY();
        hsin2MetaMpfy[i] = hsin2MetaM[i]->ProfileY();

        // rebinning
      
        if(hcos2PetaPpfy[i]->GetNbinsX()==100)
        { 
            hcos2PetaPpfy[i] -> Rebin(2);
            hcos2PetaMpfy[i] -> Rebin(2);
            hcos2MetaPpfy[i] -> Rebin(2);
            hcos2MetaMpfy[i] -> Rebin(2);
            
            hsin2PetaPpfy[i] -> Rebin(2);
            hsin2PetaMpfy[i] -> Rebin(2);
            hsin2MetaPpfy[i] -> Rebin(2);
            hsin2MetaMpfy[i] -> Rebin(2);
        }

    }

    // calculating v22
    
    int AchBins = hsin2PetaPpfy[0]->GetNbinsX();
   
    // p/m refer to sign of charge and eta, respectively
    double cos2pp = 0;
    double cos2pm = 0;
    double cos2mp = 0;
    double cos2mm = 0;

    double sin2pp = 0;
    double sin2pm = 0;
    double sin2mp = 0;
    double sin2mm = 0;

    double cos2ppyErr = 0;
    double cos2pmyErr = 0;
    double cos2mpyErr = 0;
    double cos2mmyErr = 0;

    double sin2ppyErr = 0;
    double sin2pmyErr = 0;
    double sin2mpyErr = 0;
    double sin2mmyErr = 0;

    // some extra plotting variables
    double cos2ppArr[numCentralities][AchBins];
    double cos2pmArr[numCentralities][AchBins];
    double cos2mpArr[numCentralities][AchBins];
    double cos2mmArr[numCentralities][AchBins];

    double cos2ppArrErr[numCentralities][AchBins];
    double cos2pmArrErr[numCentralities][AchBins];
    double cos2mpArrErr[numCentralities][AchBins];
    double cos2mmArrErr[numCentralities][AchBins];

    double sin2ppArr[numCentralities][AchBins];
    double sin2pmArr[numCentralities][AchBins];
    double sin2mpArr[numCentralities][AchBins];
    double sin2mmArr[numCentralities][AchBins];

    double sin2ppArrErr[numCentralities][AchBins];
    double sin2pmArrErr[numCentralities][AchBins];
    double sin2mpArrErr[numCentralities][AchBins];
    double sin2mmArrErr[numCentralities][AchBins];




    // double cos2pxErr = 0;
    // double cos2mxErr = 0;
    // double sin2pxErr = 0;
    // double sin2mxErr = 0;

    // p/m refers to sign of charge for v22
    double v22p[numCentralities][AchBins];
    double v22m[numCentralities][AchBins];

    double v22pErr[numCentralities][AchBins];
    double v22mErr[numCentralities][AchBins];

    double Achp[numCentralities][AchBins];
    double Achm[numCentralities][AchBins];

    double AchpErr[numCentralities][AchBins];
    double AchmErr[numCentralities][AchBins];

    // need to produce data that has Ach binned half as much, maybe reduce more later

    double v2p[numCentralities][AchBins];
    double v2m[numCentralities][AchBins];

    double v2pErr[numCentralities][AchBins];
    double v2mErr[numCentralities][AchBins];

    // sub stands for subtraction
    double v2sub[numCentralities][AchBins];
    double v2subErr[numCentralities][AchBins];

    
    // calculating v2 values
    for(int i = 0; i < numCentralities; i++)
    {
        for(int j = 0; j < AchBins; j++)
        {
            cos2pp = hcos2PetaPpfy[i]->GetBinContent(j);       
            cos2pm = hcos2PetaMpfy[i]->GetBinContent(j);       
            cos2mp = hcos2MetaPpfy[i]->GetBinContent(j);  
            cos2mm = hcos2MetaMpfy[i]->GetBinContent(j);  
            
            cos2ppyErr = hcos2PetaPpfy[i]->GetBinError(j); 
            cos2pmyErr = hcos2PetaMpfy[i]->GetBinError(j); 
            cos2mpyErr = hcos2MetaPpfy[i]->GetBinError(j);     
            cos2mmyErr = hcos2MetaMpfy[i]->GetBinError(j);     

            sin2pp = hsin2PetaPpfy[i]->GetBinContent(j);       
            sin2pm = hsin2PetaMpfy[i]->GetBinContent(j);  
            sin2mp = hsin2MetaPpfy[i]->GetBinContent(j);  
            sin2mm = hsin2MetaMpfy[i]->GetBinContent(j);  
            
            sin2ppyErr = hsin2PetaPpfy[i]->GetBinError(j); 
            sin2pmyErr = hsin2PetaMpfy[i]->GetBinError(j); 
            sin2mpyErr = hsin2MetaPpfy[i]->GetBinError(j);     
            sin2mmyErr = hsin2MetaMpfy[i]->GetBinError(j);     

            v22p[i][j] = cos2pp*cos2pm + sin2pp*sin2pm;
            v22m[i][j] = cos2mp*cos2mm + sin2mp*sin2mm;

            v22pErr[i][j] = fabs(v22p[i][j])*( TMath::Sqrt( TMath::Power(cos2ppyErr/cos2pp,2) + TMath::Power(cos2pmyErr/cos2pm,2) ) 
                    + TMath::Sqrt(TMath::Power(sin2ppyErr/sin2pp,2) + TMath::Power(sin2pmyErr/sin2pm,2) ) ); 

            v22mErr[i][j] = fabs(v22m[i][j])*( TMath::Sqrt( TMath::Power(cos2mpyErr/cos2mp,2) + TMath::Power(cos2mmyErr/cos2mm,2) )
                    + TMath::Sqrt( TMath::Power(sin2mpyErr/sin2mp,2) + TMath::Power(sin2mmyErr/sin2mm,2) ) ); 

            cos2ppArr[i][j] = cos2pp;
            cos2pmArr[i][j] = cos2pm;
            cos2mpArr[i][j] = cos2mp;
            cos2mmArr[i][j] = cos2mm;

            sin2ppArr[i][j] = sin2pp;
            sin2pmArr[i][j] = sin2pm;
            sin2mpArr[i][j] = sin2mp;
            sin2mmArr[i][j] = sin2mm;

            cos2ppArrErr[i][j] = cos2ppyErr;
            cos2pmArrErr[i][j] = cos2pmyErr;
            cos2mpArrErr[i][j] = cos2mpyErr;
            cos2mmArrErr[i][j] = cos2mmyErr;

            sin2ppArrErr[i][j] = sin2ppyErr;
            sin2pmArrErr[i][j] = sin2pmyErr;
            sin2mpArrErr[i][j] = sin2mpyErr;
            sin2mmArrErr[i][j] = sin2mmyErr;

            if(isnan(v22p[i][j])) v22p[i][j] = 0;
            if(isnan(v22m[i][j])) v22m[i][j] = 0;

            if(isnan(v22pErr[i][j]) || isinf(v22pErr[i][j]))
            {
                v22pErr[i][j] = 0;
            }

            if(isnan(v22mErr[i][j]))
            {
                v22mErr[i][j] = 0;
            }

            Achp[i][j] = hcos2PetaPpfy[i]->GetBinCenter(j);
            Achm[i][j] = Achp[i][j]; 

            AchpErr[i][j] = hcos2PetaPpfy[i]->GetBinWidth(j)/2;
            AchmErr[i][j] = AchpErr[i][j];

            if(v22p[i][j]>=0)
            {
                v2p[i][j] = TMath::Sqrt(v22p[i][j]);
            }
            if(v22p[i][j]<0)
            {
                v2p[i][j] = 0;
            }

            if(v22m[i][j]>=0)
            {
                v2m[i][j] = TMath::Sqrt(v22m[i][j]);
            }
            if(v22m[i][j]<0)
            {
                v2m[i][j] = 0;
            }

            v2pErr[i][j] = 0.5*fabs(v2p[i][j])*TMath::Sqrt(v22pErr[i][j]/v22p[i][j]); 
            v2mErr[i][j] = 0.5*fabs(v2m[i][j])*TMath::Sqrt(v22mErr[i][j]/v22m[i][j]);

            // unsure if the isnan is necessary, but it's a nice precaution
            if( isnan(v2pErr[i][j]) )
            {
                v2pErr[i][j] = 0;
            } 

            if( isnan(v2mErr[i][j]) )
            {
                v2mErr[i][j] = 0;
            } 

            // calculation to prepare for fitting
            if(v2p[i][j]!=0 && v2m[i][j]!=0)
            {
                v2sub[i][j] = v2m[i][j] - v2p[i][j];
                v2subErr[i][j] = TMath::Sqrt( TMath::Power(v2mErr[i][j],2) + TMath::Power(v2pErr[i][j],2) );
            }
            else
            {
                v2sub[i][j] = 0;
                v2subErr[i][j] = 0;
            }

        }
    }

    // some extra graphs

    TGraphErrors *gcos2pp[numCentralities];
    TGraphErrors *gcos2pm[numCentralities];
    TGraphErrors *gcos2mp[numCentralities];
    TGraphErrors *gcos2mm[numCentralities];

    TGraphErrors *gsin2pp[numCentralities];
    TGraphErrors *gsin2pm[numCentralities];
    TGraphErrors *gsin2mp[numCentralities];
    TGraphErrors *gsin2mm[numCentralities];

    // end of extra graphs

    // plotting

    TGraphErrors *gv22p[numCentralities];
    TGraphErrors *gv22m[numCentralities];
     
    TGraphErrors *gv2p[numCentralities];
    TGraphErrors *gv2m[numCentralities];

    TGraphErrors *gv2sub[numCentralities];

    TCanvas *cv22p[numCentralities];
    TCanvas *cv22m[numCentralities];

    TCanvas *cv2p[numCentralities];
    TCanvas *cv2m[numCentralities];

    TCanvas *cv2sub[numCentralities];

    TLine *AchLine = new TLine(-0.5,0,0.5,0);
    TLine *centLine = new TLine(0,0,100,0);
    AchLine->SetLineColor(3);
    centLine->SetLineColor(2);

    char canName[256];
    char graName[256];
    char graTitle[256];
    char fitName[256];

    double rFitVal[numCentralities];
    double rFitValErr[numCentralities];
    double centVals[numCentralities] = {75,65,55,45,35,25,15,7.5,2.5};
    double centValsErr[numCentralities] = {0,0,0,0,0,0,0,0,0};

    TF1 *rFits[numCentralities];
  
    TCanvas *cv2subMult = new TCanvas("cv2subMult");
    cv2subMult->Divide(3,3);

    for(int i = 0; i < numCentralities; i++)
    {
        gv22p[i] = new TGraphErrors(AchBins,Achp[i],v22p[i],AchpErr[i],v22pErr[i]);
        gv22m[i] = new TGraphErrors(AchBins,Achm[i],v22m[i],AchmErr[i],v22mErr[i]);

        gv2p[i] = new TGraphErrors(AchBins,Achp[i],v2p[i],AchpErr[i],v2pErr[i]);
        gv2m[i] = new TGraphErrors(AchBins,Achm[i],v2m[i],AchmErr[i],v2mErr[i]);

        gv2sub[i] = new TGraphErrors(AchBins,Achp[i],v2sub[i],AchpErr[i],v2subErr[i]);

        //sprintf(canName,"cv22p%i",i);
        //cv22p[i] = new TCanvas(canName);
        //gv22p[i]->GetXaxis()->SetRangeUser(-0.6,0.6);
        //gv22p[i]->Draw("apz");

        //
        //sprintf(canName,"cv22m%i",i);
        //cv22m[i] = new TCanvas(canName);
        //gv22m[i]->GetXaxis()->SetRangeUser(-0.6,0.6);
        //gv22m[i]->Draw("apz");

        //sprintf(canName,"cv2p%i",i);
        //cv2p[i] = new TCanvas(canName);
        //sprintf(graTitle,"v2p C%i",i+1);
        //gv2p[i]->SetTitle(graTitle);
        //gv2p[i]->GetXaxis()->SetRangeUser(-0.6,0.6);
        //gv2p[i]->Draw("apz"); 
        
        //sprintf(canName,"cv2m%i",i);
        //cv2m[i] = new TCanvas(canName);
        //sprintf(graTitle,"v2m C%i",i+1);
        //gv2m[i]->SetTitle(graTitle);
        //gv2m[i]->GetXaxis()->SetRangeUser(-0.6,0.6);
        //gv2m[i]->Draw("apz");

        // subtraction and fitting graph
        sprintf(canName,"cv2sub%i",i);
        sprintf(fitName,"fits%i",i);
        rFits[i] = new TF1(fitName,"[0] + [1]*x",-0.1,0.1);
        
        // cv2sub[i] = new TCanvas(canName);
        cv2subMult->cd(i+1);

        sprintf(graTitle,"v2{#pi_{-}} - v2{#pi_{+}} Centrality = %s",centrality[i]);
        gv2sub[i]->SetTitle(graTitle);
        gv2sub[i]->SetMarkerStyle(4);

        if(i==0) gv2sub[i]->GetXaxis()->SetRangeUser(-0.20,0.20);
        if(i==1) gv2sub[i]->GetXaxis()->SetRangeUser(-0.15,0.15);
        if(i==2) gv2sub[i]->GetXaxis()->SetRangeUser(-0.15,0.15);
        if(i==3) gv2sub[i]->GetXaxis()->SetRangeUser(-0.15,0.15);
        if(i==4) gv2sub[i]->GetXaxis()->SetRangeUser(-0.12,0.12);
        if(i==5) gv2sub[i]->GetXaxis()->SetRangeUser(-0.12,0.12);
        if(i==6) gv2sub[i]->GetXaxis()->SetRangeUser(-0.15,0.11);
        if(i==7) gv2sub[i]->GetXaxis()->SetRangeUser(-0.11,0.18);
        if(i==8) gv2sub[i]->GetXaxis()->SetRangeUser(-0.13,0.13);

        if(i==0) gv2sub[i]->GetYaxis()->SetRangeUser(-0.015,0.015);
        if(i==1) gv2sub[i]->GetYaxis()->SetRangeUser(-0.008,0.010);
        if(i==2) gv2sub[i]->GetYaxis()->SetRangeUser(-0.008,0.010);
        if(i==3) gv2sub[i]->GetYaxis()->SetRangeUser(-0.012,0.013);
        if(i==4) gv2sub[i]->GetYaxis()->SetRangeUser(-0.008,0.013);
        if(i==5) gv2sub[i]->GetYaxis()->SetRangeUser(-0.015,0.020);
        if(i==6) gv2sub[i]->GetYaxis()->SetRangeUser(-0.022,0.022);
        if(i==7) gv2sub[i]->GetYaxis()->SetRangeUser(-0.023,0.018);
        if(i==8) gv2sub[i]->GetYaxis()->SetRangeUser(-0.025,0.017);

        gv2sub[i]->Draw("apz");
        gv2sub[i]->GetXaxis()->SetTitle("A_{ch}");
        gv2sub[i]->GetYaxis()->SetTitle("v2{-}-v2{+}");
        AchLine->Draw("same");

        gv2sub[i]->Fit(rFits[i],"R");
        rFitVal[i] = rFits[i]->GetParameter(1);
        rFitValErr[i] = rFits[i]->GetParError(1);

    }

    cv2subMult->SaveAs("Plots/200GeV_Run11plots/v2subMult.pdf");
    
    TCanvas *crValvsCen = new TCanvas("crFitVals");
    TGraphErrors *grFits = new TGraphErrors(numCentralities,centVals,rFitVal,centValsErr,rFitValErr);
    grFits->SetTitle("slope vs centrality");
    grFits->GetXaxis()->SetTitle("centrality");
    grFits->GetYaxis()->SetTitle("r (slope)");
    grFits->SetMarkerStyle(4);
    grFits->Draw("apz");
    centLine->Draw("same");
    grFits->GetYaxis()->SetRangeUser(-0.04,0.04);
    crValvsCen->SaveAs("Plots/200GeV_Run11plots/rslope.pdf");

    // drawing 
    char mgName[256];
    char mgTitle[256];

    //TCanvas *ccos2pmMult = new TCanvas("ccos2pmMult");
    //TMultiGraph *mgcos2pm[numCentralities];
    //ccos2pmMult->Divide(3,3);

    //TCanvas *csin2pmMult = new TCanvas("csin2pmMult");
    //TLegend *tlsin2pm[numCentralities];
    //TMultiGraph *mgsin2pm[numCentralities];
    //csin2pmMult->Divide(3,3);

    //for(int i = 0; i < numCentralities; i++)
    //{
    //    sprintf(mgName,"mgsin2pm%i",i);
    //    sprintf(mgTitle,"<sin2#phi> centrality = %s",centrality[i]);
    //    mgsin2pm[i] = new TMultiGraph(mgName,mgTitle);

    //    gv22p[i]->SetMarkerColor(2);
    //    gv22p[i]->SetMarkerStyle(4);
    //    gv22m[i]->SetMarkerColor(4);
    //    gv22m[i]->SetMarkerStyle(8);

    //    mgv22pm[i]->Add(gv22p[i]);
    //    mgv22pm[i]->Add(gv22m[i]);

    //    cv22pmMult->cd(i+1);
    //    mgv22pm[i]->Draw("apz");
    //    AchLine->Draw("same");

    //    //mgv22pm[i]->GetYaxis()->SetRangeUser(-0.001,0.0015);

    //    mgv22pm[i]->GetXaxis()->SetTitle("A_{ch}");
    //    mgv22pm[i]->GetYaxis()->SetTitle("<sin2#phi>");

    //    tlsin2pm[i] = new TLegend(0.7,0.65,1.0,0.8);
    //    tlsin2pm[i]->AddEntry(gv22p[i],"v^{2}{2} #pi_{+}");
    //    tlsin2pm[i]->AddEntry(gv22m[i],"v^{2}{2} #pi_{-}");
    //    tlsin2pm[i]->Draw();
    //}


    TCanvas *cv22pmMult = new TCanvas("cv22pmMult");
    TLegend *tlv22pm[numCentralities];
    TMultiGraph *mgv22pm[numCentralities];
    cv22pmMult->Divide(3,3);

    for(int i = 0; i < numCentralities; i++)
    {
        sprintf(mgName,"mgv22%i",i);
        sprintf(mgTitle,"v^{2}{2} centrality = %s",centrality[i]);
        mgv22pm[i] = new TMultiGraph(mgName,mgTitle);

        gv22p[i]->SetMarkerColor(2);
        gv22p[i]->SetMarkerStyle(4);
        gv22m[i]->SetMarkerColor(4);
        gv22m[i]->SetMarkerStyle(8);

        mgv22pm[i]->Add(gv22p[i]);
        mgv22pm[i]->Add(gv22m[i]);

        cv22pmMult->cd(i+1);
        mgv22pm[i]->Draw("apz");
        AchLine->Draw("same");

        mgv22pm[i]->GetYaxis()->SetRangeUser(-0.001,0.0015);

        mgv22pm[i]->GetXaxis()->SetTitle("A_{ch}");
        mgv22pm[i]->GetYaxis()->SetTitle("v^{2}{2}");

        tlv22pm[i] = new TLegend(0.7,0.65,1.0,0.8);
        tlv22pm[i]->AddEntry(gv22p[i],"v^{2}{2} #pi_{+}");
        tlv22pm[i]->AddEntry(gv22m[i],"v^{2}{2} #pi_{-}");
        tlv22pm[i]->Draw();
    }

    cv22pmMult->SaveAs("Plots/200GeV_Run11plots/v22multi.pdf");

    TCanvas *cv2pmMult = new TCanvas("cv2pmMult");
    TLegend *tlv2pm[numCentralities];
    TMultiGraph *mgv2pm[numCentralities];
    cv2pmMult->Divide(3,3);
    for(int i = 0; i < numCentralities; i++)
    {
        sprintf(mgName,"mgv2%i",i);
        sprintf(mgTitle,"v{2} centrality = %s",centrality[i]);
        mgv2pm[i] = new TMultiGraph(mgName,mgTitle);

        gv2p[i]->SetMarkerColor(2);
        gv2p[i]->SetMarkerStyle(4);
        gv2m[i]->SetMarkerColor(4);
        gv2m[i]->SetMarkerStyle(8);

        mgv2pm[i]->Add(gv2p[i]);
        mgv2pm[i]->Add(gv2m[i]);

        cv2pmMult->cd(i+1);
        mgv2pm[i]->Draw("apz");
        AchLine->Draw("same");

        if(i==0) mgv2pm[i]->GetYaxis()->SetRangeUser(-0.005,0.035);
        if(i==1) mgv2pm[i]->GetYaxis()->SetRangeUser(-0.005,0.040);
        if(i==2) mgv2pm[i]->GetYaxis()->SetRangeUser(-0.010,0.040);
        if(i==3) mgv2pm[i]->GetYaxis()->SetRangeUser(-0.010,0.040);
        if(i==4) mgv2pm[i]->GetYaxis()->SetRangeUser(-0.010,0.040);
        if(i==5) mgv2pm[i]->GetYaxis()->SetRangeUser(-0.005,0.040);
        if(i==6) mgv2pm[i]->GetYaxis()->SetRangeUser(-0.005,0.035);
        if(i==7) mgv2pm[i]->GetYaxis()->SetRangeUser(-0.005,0.040);
        if(i==8) mgv2pm[i]->GetYaxis()->SetRangeUser(-0.005,0.042);

        mgv2pm[i]->GetXaxis()->SetTitle("A_{ch}");
        mgv2pm[i]->GetYaxis()->SetTitle("v{2}");


        tlv2pm[i] = new TLegend(0.7,0.65,1.0,0.8);
        tlv2pm[i]->AddEntry(gv22p[i],"v{2} #pi_{+}");
        tlv2pm[i]->AddEntry(gv22m[i],"v{2} #pi_{-}");
        tlv2pm[i]->Draw();
    }

    cv2pmMult->SaveAs("Plots/200GeV_Run11plots/v2multi.pdf");


    // some debug

    cout << AchBins << endl;

    //for(int i = 0; i < numCentralities; i++)
    //{
    //    printf("\n v22p[%i]=\n",i);

    //    for(int j = 0; j < AchBins; j++)
    //    {
    //        printf("%.3f\t",v22p[i][j]);
    //    }

    //    printf("\n v22m[%i]=\n",i);

    //    for(int j = 0; j < AchBins; j++)
    //    {
    //        printf("%.3f\t",v22m[i][j]);
    //    }

    //    printf("\n v2p[%i]=\n",i);

    //    for(int j = 0; j < AchBins; j++)
    //    {
    //        printf("%.3f\t",v2p[i][j]);
    //    }

    //    printf("\n v2m[%i]=\n",i);

    //    for(int j = 0; j < AchBins; j++)
    //    {
    //        printf("%.3f\t",v2m[i][j]);
    //    }

    //}


    return;
}


