#include "rootheader.h"

double errorProp(double val1, double val1err, double val2, double val2err);

void delGam()
{
    char fileName[512];
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_Mar29_2019/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_April01_2019/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_April03_2019/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_April15_2019/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_April17_2019/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_April27_2019/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_April29_2019/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_May5_2019/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_May8_2019/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_May12_2019/femtoDstHist200_Run16.root");
    // the June trees and onward have a correction factor added into the formula, which caused some extra splitting in the results
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_June10_2019/femtoDstHist200_16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_June12_2019/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_June12_2019_02/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_June25_2019/femtoDstHist200_Run16.root");
    sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_June26_2019/femtoDstHist200_Run16.root");

    TFile *file = new TFile(fileName);
   
    TH2D *hdgULvsCent;
    TH2D *hdgLSvsCent;
    TProfile *profdgULvsCent;
    TProfile *profdgLSvsCent;
    
    TProfile *profv22RefvsCent;
   
    hdgULvsCent = (TH2D*) file->Get("hdgULvsCent");
    hdgLSvsCent = (TH2D*) file->Get("hdgLSvsCent");
    // profdgULvsCent = hdgULvsCent->ProfileX();
    // profdgLSvsCent = hdgLSvsCent->ProfileX();

    // profdgULvsCent = (TProfile*) file->Get("profdgULvsCentAll"); 
    // profdgLSvsCent = (TProfile*) file->Get("profdgLSvsCentAll");

    profdgULvsCent = (TProfile*) file->Get("profULnoLR"); 
    profdgLSvsCent = (TProfile*) file->Get("profLSnoLR");



    profv22RefvsCent = (TProfile*) file->Get("profcRefv22vsCent");

    TLine *centLine = new TLine(0,0,100,0);
    TLine *AchLine = new TLine(-0.5,0,0.5,0);

    // profdgULvsCent->Draw();  

    const int red = 2;
    const int neonGreen = 3;
    const int blue = 4;
    const int neonYellow = 5; // don't ever use
    const int magenta = 6;
    const int turquoise = 7;
    const int green = 8;
    const int purple = 9;
    const int white = 10;
    const int grey = 11;
    const int darkGrey = 12; 

    const int dot = 1;
    const int cross = 2;
    const int star = 3;
    const int openCircle = 4;
    const int xcross = 5;
    const int circleDot = 6;
    const int solidSquare = 7;
    const int solidCircle = 8;

    const int numCentralities = 9;

    const bool rebin=true;
    const int rebinAmount = 8;

    centLine->SetLineColor(red);
    AchLine->SetLineColor(red);
    
    const double centralityVals[numCentralities] = {2.5,7.5,15,25,35,45,55,65,75};
    const double centralityValsErrs[numCentralities] = {0,0,0,0,0,0,0,0,0};

    // data published in PRL C88, 064911 2013 (Fluctuations of charge separation)

    const double gammaOSPapVal[numCentralities] = {-1.10869e-5,-7.15236e-6,-9.5635e-6,-1.02598e-5,-8.69571e-7,4.12098e-6,7.52751e-5,2.73956e-4,7.09372e-4};
    const double gammaOSPapErr[numCentralities] = {3.51296e-7,3.82974e-7,3.36705e-7,5.00471e-7,8.72383e-7,1.80796e-6,4.33676e-6,1.09898e-5,2.59136e-5};
    
    const double gammaSSPapVal[numCentralities] = {-2.52632e-5,-4.5792e-5,-8.39357e-5,-1.52627e-4,-2.225659e-4,-3.35177e-4,-4.38005e-4,-5.72402e-4,-5.45818e-4};
    const double gammaSSPapErr[numCentralities] = {3.51389e-7,3.83108e-7,3.36874e-7,5.00875e-7,8.7351e-7,1.81174e-6,4.35229e-6,1.1061e-5,2.62257e-5};
    

    char centralities[numCentralities][64] = {
        {"70-80 %"},
        {"60-70 %"},
        {"50-60 %"},
        {"40-50 %"},
        {"30-40 %"},
        {"20-30 %"},
        {"10-20 %"},
        {"5-10 %"},
        {"0-5%"}
    };

    double ULvsCentVals[numCentralities];
    double ULvsCentValsErr[numCentralities];
    
    double LSvsCentVals[numCentralities]; 
    double LSvsCentValsErr[numCentralities]; 

    double v22vsCentVals[numCentralities];
    double v22vsCentValsErr[numCentralities];

    double v2vsCentVals[numCentralities];
    double v2vsCentValsErr[numCentralities];

    int nbins = profdgULvsCent->GetNbinsX();

    int kounter = 0;

    for(int i = 0; i < nbins; i++)
    {
        if( fabs( profdgULvsCent->GetBinContent(i) ) > 0.00 )
        {
            ULvsCentVals[kounter] = profdgULvsCent->GetBinContent(i);
            ULvsCentValsErr[kounter] = profdgULvsCent->GetBinError(i);
            LSvsCentVals[kounter] = profdgLSvsCent->GetBinContent(i);
            LSvsCentValsErr[kounter] = profdgLSvsCent->GetBinError(i);

            v22vsCentVals[kounter] = profv22RefvsCent->GetBinContent(i);
            v22vsCentValsErr[kounter] = profv22RefvsCent->GetBinError(i);

            // cout << kounter << endl;

            kounter++;
        }
    } 

    double ULv22vsCentVals[numCentralities];
    double ULv22vsCentValsErr[numCentralities];

    double LSv22vsCentVals[numCentralities];
    double LSv22vsCentValsErr[numCentralities];

    double ULv2vsCentVals[numCentralities];
    double ULv2vsCentValsErr[numCentralities];

    double LSv2vsCentVals[numCentralities];
    double LSv2vsCentValsErr[numCentralities];

    for(int i = 0; i < numCentralities; i++)
    {
        ULv22vsCentVals[i] = ULvsCentVals[i]/v22vsCentVals[i];
        LSv22vsCentVals[i] = LSvsCentVals[i]/v22vsCentVals[i];

        ULv22vsCentValsErr[i] = fabs(ULv22vsCentVals[i])*errorProp(ULvsCentVals[i],
                ULvsCentValsErr[i],v22vsCentVals[i],v22vsCentValsErr[i]);

        LSv22vsCentValsErr[i] = fabs(LSv22vsCentVals[i])*errorProp(LSvsCentVals[i],
                LSvsCentValsErr[i],v22vsCentVals[i],v22vsCentValsErr[i]);

        v2vsCentVals[i] = TMath::Sqrt(v22vsCentVals[i]);
        v2vsCentValsErr[i] = 0.5*v2vsCentVals[i]*v22vsCentValsErr[i]/v22vsCentVals[i];

        // cout << v2vsCentVals[i] << endl;

        ULv2vsCentVals[i] = ULvsCentVals[i]/v2vsCentVals[i];
        LSv2vsCentVals[i] = LSvsCentVals[i]/v2vsCentVals[i];

        ULv2vsCentValsErr[i] = fabs(ULv2vsCentVals[i])*errorProp(ULvsCentVals[i],
                ULvsCentValsErr[i],v2vsCentVals[i],v2vsCentValsErr[i]);

        LSv2vsCentValsErr[i] = fabs(LSv2vsCentVals[i])*errorProp(LSvsCentVals[i],
                LSvsCentValsErr[i],v2vsCentVals[i],v2vsCentValsErr[i]);
    }

    TCanvas *cdg = new TCanvas("cdg");
    profdgULvsCent->SetMarkerColor(blue);
    profdgULvsCent->SetLineColor(blue);
    profdgULvsCent->SetMarkerStyle(openCircle);

    profdgLSvsCent->SetMarkerColor(red);
    profdgLSvsCent->SetLineColor(red);
    profdgLSvsCent->SetMarkerStyle(openCircle);
        
    profdgULvsCent->Draw();
    profdgLSvsCent->Draw("same");


    TGraphErrors *tgeULv22vsCent = new TGraphErrors(numCentralities,centralityVals,ULv22vsCentVals,centralityValsErrs,ULv22vsCentValsErr);
    TGraphErrors *tgeLSv22vsCent = new TGraphErrors(numCentralities,centralityVals,LSv22vsCentVals,centralityValsErrs,LSv22vsCentValsErr);

    TGraphErrors *tgeULv2vsCent = new TGraphErrors(numCentralities,centralityVals,ULv2vsCentVals,centralityValsErrs,ULv2vsCentValsErr);
    TGraphErrors *tgeLSv2vsCent = new TGraphErrors(numCentralities,centralityVals,LSv2vsCentVals,centralityValsErrs,LSv2vsCentValsErr);

    // official star data
    TGraphErrors *tgeStarDatGammaOS = new TGraphErrors(numCentralities,centralityVals,gammaOSPapVal,centralityValsErrs,gammaOSPapErr);
    TGraphErrors *tgeStarDatGammaSS = new TGraphErrors(numCentralities,centralityVals,gammaSSPapVal,centralityValsErrs,gammaSSPapErr);
    /////////////////////
    //
    // EDIT: the official star data here currently is for a slightly different observable

    TMultiGraph *tmgv22 = new TMultiGraph("tmgv22","<cos(#phi_{#alpha} + #phi_{#beta} - 2#phi_{c})>/v_{2}{2} vs Centrality");
    TMultiGraph *tmgv2 = new TMultiGraph("tmgv2","<cos(#phi_{#alpha} + #phi_{#beta} - 2#phi_{c})>/v_{2} vs Centrality");

    TLegend *ldgv22 = new TLegend(0.7,0.65,1.0,0.8);
    TLegend *ldgv2 = new TLegend(0.7,0.65,1.0,0.8);

    tgeULv22vsCent->SetMarkerStyle(openCircle);
    tgeULv22vsCent->SetMarkerColor(blue);
    tgeULv22vsCent->SetLineColor(blue);

    tgeLSv22vsCent->SetMarkerStyle(openCircle);
    tgeLSv22vsCent->SetMarkerColor(red);
    tgeLSv22vsCent->SetLineColor(red);

    tgeULv2vsCent->SetMarkerStyle(openCircle);
    tgeULv2vsCent->SetMarkerColor(blue);
    tgeULv2vsCent->SetLineColor(blue);

    tgeLSv2vsCent->SetMarkerStyle(openCircle);
    tgeLSv2vsCent->SetMarkerColor(red);
    tgeLSv2vsCent->SetLineColor(red);

    // official star data
    
    tgeStarDatGammaOS->SetMarkerStyle(star);
    tgeStarDatGammaOS->SetMarkerColor(neonGreen);
    tgeStarDatGammaOS->SetLineColor(neonGreen);

    tgeStarDatGammaSS->SetMarkerStyle(cross);
    tgeStarDatGammaSS->SetMarkerColor(magenta);
    tgeStarDatGammaSS->SetLineColor(magenta);
    
    /////////////////////

    tmgv22->Add(tgeULv22vsCent);
    tmgv22->Add(tgeLSv22vsCent);

    tmgv2->Add(tgeULv2vsCent);
    tmgv2->Add(tgeLSv2vsCent);

    // official star data
    //tmgv2->Add(tgeStarDatGammaOS);
    //tmgv2->Add(tgeStarDatGammaSS);
    /////////////////////

    ldgv22->AddEntry(tgeULv22vsCent,"Unlike Sign");
    ldgv22->AddEntry(tgeLSv22vsCent,"Like Sign");

    ldgv2->AddEntry(tgeULv2vsCent,"Unlike Sign");
    ldgv2->AddEntry(tgeLSv2vsCent,"Like Sign");

    // official star data
    //ldgv2->AddEntry(tgeStarDatGammaOS,"OS #gamma star data");
    //ldgv2->AddEntry(tgeStarDatGammaSS,"SS #gamma star data");
    /////////////////////

    TCanvas *cdgv22 = new TCanvas("cdgv22");
    tmgv22->Draw("apz");
    ldgv22->Draw("same");
    centLine->Draw("same");
    // tgeULv22vsCent->Draw("apz");
    // tgeLSv22vsCent->Draw("apz same");

    TCanvas *cdgv2 = new TCanvas("cdgv2");
    tmgv2->Draw("apz");
    ldgv2->Draw("same");
    centLine->Draw("same");

    TCanvas *crefv22 = new TCanvas("crefv22");
    profv22RefvsCent->SetTitle("Charged particle (reference) V_{2} vs centrality");
    profv22RefvsCent->Draw();

    // Calculating delta gamma vs Ach

    TProfile *profULCorrVsAch[numCentralities];
    TProfile *profLSCorrVsAch[numCentralities];
    TProfile *profRefV22vsAch[numCentralities];

    char varName[256];

    for(int i = 0; i < numCentralities; i++)
    {
        // sprintf(varName,"profdgULvsAchC%i",i+1);
        sprintf(varName,"profULvsAchnolrC%i",i+1);
        profULCorrVsAch[i] = (TProfile*) file->Get(varName);

        // sprintf(varName,"profdgLSvsAchC%i",i+1);
        sprintf(varName,"profLSvsAchnolrC%i",i+1);
        profLSCorrVsAch[i] = (TProfile*) file->Get(varName);

        sprintf(varName,"profcRefv22vsAchC%i",i+1);
        profRefV22vsAch[i] = (TProfile*) file->Get(varName);

        if(rebin)
        {
            profULCorrVsAch[i]->RebinX(rebinAmount);
            profLSCorrVsAch[i]->RebinX(rebinAmount);
            profRefV22vsAch[i]->RebinX(rebinAmount);
        }
    }

    // extracting the bin values 

    int numAchBins = profULCorrVsAch[0]->GetNbinsX();

    double ULCorrVsAchVals[numCentralities][numAchBins];
    double ULCorrVsAchValsXval[numCentralities][numAchBins];
    double ULCorrVsAchValsErr[numCentralities][numAchBins];
    double ULCorrVsAchValsXvalErr[numCentralities][numAchBins];
    
    double LSCorrVsAchVals[numCentralities][numAchBins];
    double LSCorrVsAchValsXval[numCentralities][numAchBins];
    double LSCorrVsAchValsErr[numCentralities][numAchBins];
    double LSCorrVsAchValsXvalErr[numCentralities][numAchBins];
    
    double V22VsAchVals[numCentralities][numAchBins];
    double V22VsAchValsXval[numCentralities][numAchBins];
    double V22VsAchValsErr[numCentralities][numAchBins];
    double V22VsAchValsXvalErr[numCentralities][numAchBins];

    vector< vector<double> > dgULvsAchVals;
    vector< vector<double> > dgULvsAchValsErr;
    vector< vector<double> > dgLSvsAchVals;
    vector< vector<double> > dgLSvsAchValsErr;

    vector< vector<double> > AchVals;
    vector< vector<double> > AchValsWidth;

    vector< vector<double> > DeltaGamVals;
    vector< vector<double> > DeltaGamValsErr;

    vector<double> pushDouble;

    double intV2val;
    double intV2valErr;

    double intv2val;
    double intv2valErr;

    double intULcorr;
    double intULcorrErr;
    double intLScorr;
    double intLScorrErr;

    double intULdg;
    double intLSdg;
    double intULdgErr;
    double intLSdgErr;

    double intDelGam;
    double intDelGamErr;

    // storing values in the arrays
    for(int i = 0; i < numCentralities; i++)
    {
        dgULvsAchVals.push_back(pushDouble);
        dgULvsAchValsErr.push_back(pushDouble);
        dgLSvsAchVals.push_back(pushDouble);
        dgLSvsAchValsErr.push_back(pushDouble);

        AchVals.push_back(pushDouble);
        AchValsWidth.push_back(pushDouble);

        DeltaGamVals.push_back(pushDouble);
        DeltaGamValsErr.push_back(pushDouble);

        for(int j = 0; j < numAchBins; j++)
        {
            // I don't think storing these values is very necessary
            ULCorrVsAchVals[i][j] = profULCorrVsAch[i]->GetBinContent(j);
            ULCorrVsAchValsErr[i][j] = profULCorrVsAch[i]->GetBinError(j);
            ULCorrVsAchValsXval[i][j] = profULCorrVsAch[i]->GetBinCenter(j);
            ULCorrVsAchValsXvalErr[i][j] = profULCorrVsAch[i]->GetBinWidth(j)/2.;

            LSCorrVsAchVals[i][j] = profLSCorrVsAch[i]->GetBinContent(j);
            LSCorrVsAchValsErr[i][j] = profLSCorrVsAch[i]->GetBinError(j);
            LSCorrVsAchValsXval[i][j] = profLSCorrVsAch[i]->GetBinCenter(j);
            LSCorrVsAchValsXvalErr[i][j] = profLSCorrVsAch[i]->GetBinWidth(j)/2.;

            V22VsAchVals[i][j] = profRefV22vsAch[i]->GetBinContent(j);
            V22VsAchValsErr[i][j] = profRefV22vsAch[i]->GetBinError(j);
            V22VsAchValsXval[i][j] = profRefV22vsAch[i]->GetBinCenter(j);
            V22VsAchValsXvalErr[i][j] = profRefV22vsAch[i]->GetBinWidth(j)/2.; 

            if(ULCorrVsAchValsXval[i][j] != V22VsAchValsXval[i][j])
            {
                cerr << "mismatch of binning for division" << endl;
            }

            // storing the values in the vectors 

            intULcorr = profULCorrVsAch[i]->GetBinContent(j);
            intULcorrErr = profULCorrVsAch[i]->GetBinError(j);

            intLScorr = profLSCorrVsAch[i]->GetBinContent(j);
            intLScorrErr = profLSCorrVsAch[i]->GetBinError(j);

            intV2val = profRefV22vsAch[i]->GetBinContent(j);
            intV2valErr = profRefV22vsAch[i]->GetBinError(j);

            if(intV2val <= 0) continue;

            intv2val = TMath::Sqrt(intV2val);
            intv2valErr = 0.5*intv2val*TMath::Sqrt(intV2valErr/intV2val);

            // can use the errorProp function here if I decide to edit it
            intULdg = intULcorr/intv2val;
            intULdgErr = intULdg*TMath::Sqrt( (intULcorrErr/intULcorr)*(intULcorrErr/intULcorr) + (intv2valErr/intv2val)*(intv2valErr/intv2val)  ); 

            intLSdg = intLScorr/intv2val;
            intLSdgErr = intLSdg*TMath::Sqrt( (intLScorrErr/intLScorr)*(intLScorrErr/intLScorr) + (intv2valErr/intv2val)*(intv2valErr/intv2val)  ); 

            intDelGam = intULdg - intLSdg;
            intDelGamErr = TMath::Sqrt(intULdgErr*intULdgErr + intLSdgErr*intLSdgErr);

            //if(i==5 && j>170 && j<230)
            //{
            //    printf("ULErr = %.5f\n",intULdgErr);
            //}

            if(isnan(intULdg) || isnan(intLSdg) )
            {
                cout << "continue failed" << endl;
                continue;
            }

            dgULvsAchVals[i].push_back(intULdg);
            dgULvsAchValsErr[i].push_back(intULdgErr);

            dgLSvsAchVals[i].push_back(intLSdg);
            dgLSvsAchValsErr[i].push_back(intLSdgErr);

            AchVals[i].push_back(ULCorrVsAchValsXval[i][j]);
            AchValsWidth[i].push_back(V22VsAchValsXvalErr[i][j]);

            DeltaGamVals[i].push_back(intDelGam);
            DeltaGamValsErr[i].push_back(intDelGamErr);
        }
    }
    // end of storing c++ std::vector
   
    // making graphs now

    TCanvas *cGammaCorr[numCentralities];
    TMultiGraph *tmgGammaCorr[numCentralities];

    TGraphErrors *tgeGammaUL[numCentralities];
    TGraphErrors *tgeGammaLS[numCentralities];

    TCanvas *cDelGam[numCentralities];
    TGraphErrors *tgeDelGam[numCentralities];

    // initialize TGraphErrors

    TLegend *lGamma; // only need the one right now

    int numPoints = 0;

    char graphTitle[256];
    char graphNames[256];
    char canvNames[256];

    for(int i = 0; i < numCentralities; i++)
    {
        numPoints = dgULvsAchVals[i].size();

        tgeGammaUL[i] = new TGraphErrors(numPoints,&AchVals[i][0],&dgULvsAchVals[i][0],&AchValsWidth[i][0],&dgULvsAchValsErr[i][0]);
        tgeGammaLS[i] = new TGraphErrors(numPoints,&AchVals[i][0],&dgLSvsAchVals[i][0],&AchValsWidth[i][0],&dgLSvsAchValsErr[i][0]);

        tgeDelGam[i] = new TGraphErrors(numPoints,&AchVals[i][0],&DeltaGamVals[i][0],&AchValsWidth[i][0],&DeltaGamValsErr[i][0]);

        tgeGammaUL[i]->SetMarkerColor(blue);
        tgeGammaUL[i]->SetLineColor(blue);
        tgeGammaUL[i]->SetMarkerStyle(openCircle);

        tgeGammaLS[i]->SetMarkerColor(red);
        tgeGammaLS[i]->SetLineColor(red);
        tgeGammaLS[i]->SetMarkerStyle(openCircle);

        if(i==0)
        {
            lGamma = new TLegend(0.7,0.65,1.0,0.8);
            lGamma->AddEntry(tgeGammaUL[i],"OS");
            lGamma->AddEntry(tgeGammaLS[i],"SS");
        }

        sprintf(canvNames,"cGamC%i",i+1);
        sprintf(graphTitle,"#gamma vs A_{ch} for centrality = %s ",centralities[i]);
        sprintf(graphNames,"tmgGamC%i",i+1);
        cGammaCorr[i] = new TCanvas(canvNames);

        tmgGammaCorr[i] = new TMultiGraph(graphNames,graphTitle);

        tmgGammaCorr[i]->Add(tgeGammaUL[i]);
        tmgGammaCorr[i]->Add(tgeGammaLS[i]);

        tmgGammaCorr[i]->Draw("apz");

        lGamma->Draw("same");

        // cGammaCorr[i]->Close();

        // delta gamma plotting
        sprintf(canvNames,"cDelGamC%i",i+1);
        sprintf(graphTitle,"#Delta #gamma vs A_{ch} for centrality = %s",centralities[i]);

        cDelGam[i] = new TCanvas(canvNames);

        tgeDelGam[i]->SetTitle(graphTitle);
        tgeDelGam[i]->Draw("apz");
        AchLine->Draw("same");

        // cDelGam[i]->Close();

    }


    return;
} 

double errorProp(double val1, double val1err, double val2, double val2err)
{
    // simple function for a part of the error propagation for multiplying values
    
    double a = val1err/val1;
    double b = val2err/val2;

    double error = TMath::Sqrt(a*a + b*b); 

    return error;
}



