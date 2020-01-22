#include "rootheader.h"

void v2MixedPlanes()
{
    
    const bool addHists = true;
    // const bool addHists = false;

    const bool rebin = true;
    // const bool rebin = false;
    const int rebinAmount = 8;

    const int numCentralities = 9;

    const int color1 = 11;
    const int color2 = 4;
    const int blkcolor = 1;
    const int redcolor = 2;
    const int bluecolor = 4;
    const int greycolor = 11;

    // for plotting select centralities
    const int startCent = 0;
    const int endCent = 9;

    ofstream fdebug("debug.txt",std::ofstream::out);

    char centralities[numCentralities][256]={
        {"70 - 80%"},
        {"60 - 70%"},
        {"50 - 60%"},
        {"40 - 50%"},
        {"30 - 40%"},
        {"20 - 30%"},
        {"10 - 20%"},
        {"5 - 10%"},
        {"0 - 5%"}
    };

    const double centralityVals[numCentralities] = {75,65,55,45,35,25,15,7.5,2.5};
    const double centralityValsErrs[numCentralities] = {0,0,0,0,0,0,0,0,0};

    char fileName[512];
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run11_200GeV/treeHists_Jan_11_2019/femtoAnalysis200.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run11_200GeV/treeHist_Jan25_2019/femto200_Run11.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run11_200GeV/treeHist_Feb5_2019/femtoTree200.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_Feb18_2019/femtoDst200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_Mar8_2019/femtoDstHist200_Run16.root");
    sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_Mar9_2019/femtoDstHist200_Run16.root");
    // sprintf(fileName,"/Users/terrenceedmonds/Documents/Purdue/Research/work/femtoDst/Data/Results/Run16_200GeV/treeHist_Mar19_2019/femtoDstHist200_Run16.root");// larger eta gap
    
    TFile *file = new TFile(fileName);

    TLine *Ach_line = new TLine(-0.5,0,0.5,0);
    Ach_line->SetLineColor(blkcolor);

    TLine *centLine = new TLine(0,0,100,0);
    centLine->SetLineColor(redcolor);

    TH2D *hv22PlusRefPi[numCentralities];
    TH2D *hv22MinusRefPi[numCentralities];
    TH2D *hv22PlusRefAll[numCentralities];
    TH2D *hv22MinusRefAll[numCentralities];
    TH2D *hv22PlusRefPOI[numCentralities];
    TH2D *hv22MinusRefPOI[numCentralities];

    TH2D *hv22PlusAllPOI[numCentralities];
    TH2D *hv22MinusAllPOI[numCentralities];
    TH2D *hv22PlusPiPOI[numCentralities];
    TH2D *hv22MinusPiPOI[numCentralities];
    TH2D *hv22PlusPOIAll[numCentralities];
    TH2D *hv22MinusPOIAll[numCentralities];
    TH2D *hv22PlusPOIPi[numCentralities];
    TH2D *hv22MinusPOIPi[numCentralities];

    TH2D *hv22RefAll[numCentralities];
    TH2D *hv22RefAllPOIPlus[numCentralities];
    TH2D *hv22RefAllPOIMinus[numCentralities];
    TH2D *hv22POIRefAllPlus[numCentralities];
    TH2D *hv22POIRefAllMinus[numCentralities];

    // the unweighted histograms
    TH2D *hv22PlusRefPiUnw[numCentralities];
    TH2D *hv22MinusRefPiUnw[numCentralities];
    TH2D *hv22PlusRefAllUnw[numCentralities];
    TH2D *hv22MinusRefAllUnw[numCentralities];
    TH2D *hv22PlusRefPOIUnw[numCentralities];
    TH2D *hv22MinusRefPOIUnw[numCentralities];

    TH2D *hv22PlusAllPOIUnw[numCentralities];
    TH2D *hv22MinusAllPOIUnw[numCentralities];
    TH2D *hv22PlusPiPOIUnw[numCentralities];
    TH2D *hv22MinusPiPOIUnw[numCentralities];
    TH2D *hv22PlusPOIAllUnw[numCentralities];
    TH2D *hv22MinusPOIAllUnw[numCentralities];
    TH2D *hv22PlusPOIPiUnw[numCentralities];
    TH2D *hv22MinusPOIPiUnw[numCentralities];

    TH2D *hv22RefAllUnw[numCentralities];
    TH2D *hv22RefAllPOIPlusUnw[numCentralities];
    TH2D *hv22RefAllPOIMinusUnw[numCentralities];
    TH2D *hv22POIRefAllPlusUnw[numCentralities];
    TH2D *hv22POIRefAllMinusUnw[numCentralities];


    // profiles for the v22 
    TProfile *hv22PlusRefPipfx[numCentralities];
    TProfile *hv22MinusRefPipfx[numCentralities];
    TProfile *hv22PlusRefAllpfx[numCentralities];
    TProfile *hv22MinusRefAllpfx[numCentralities];
    TProfile *hv22PlusRefPOIpfx[numCentralities];
    TProfile *hv22MinusRefPOIpfx[numCentralities];

    TProfile *hv22PlusAllPOIpfx[numCentralities];
    TProfile *hv22MinusAllPOIpfx[numCentralities];
    TProfile *hv22PlusPiPOIpfx[numCentralities];
    TProfile *hv22MinusPiPOIpfx[numCentralities];
    TProfile *hv22PlusPOIAllpfx[numCentralities];
    TProfile *hv22MinusPOIAllpfx[numCentralities];
    TProfile *hv22PlusPOIPipfx[numCentralities];
    TProfile *hv22MinusPOIPipfx[numCentralities];

    TProfile *hv22RefAllpfx[numCentralities];
    TProfile *hv22RefAllPOIPluspfx[numCentralities];
    TProfile *hv22RefAllPOIMinuspfx[numCentralities];
    TProfile *hv22POIRefAllPluspfx[numCentralities];
    TProfile *hv22POIRefAllMinuspfx[numCentralities];


    // the unweighted profiles
    TProfile *hv22PlusRefPiUnwpfx[numCentralities];
    TProfile *hv22MinusRefPiUnwpfx[numCentralities];
    TProfile *hv22PlusRefAllUnwpfx[numCentralities];
    TProfile *hv22MinusRefAllUnwpfx[numCentralities];
    TProfile *hv22PlusRefPOIUnwpfx[numCentralities];
    TProfile *hv22MinusRefPOIUnwpfx[numCentralities];

    TProfile *hv22PlusAllPOIUnwpfx[numCentralities];
    TProfile *hv22MinusAllPOIUnwpfx[numCentralities];
    TProfile *hv22PlusPiPOIUnwpfx[numCentralities];
    TProfile *hv22MinusPiPOIUnwpfx[numCentralities];
    TProfile *hv22PlusPOIAllUnwpfx[numCentralities];
    TProfile *hv22MinusPOIAllUnwpfx[numCentralities];
    TProfile *hv22PlusPOIPiUnwpfx[numCentralities];
    TProfile *hv22MinusPOIPiUnwpfx[numCentralities];

    TProfile *hv22RefAllUnwpfx[numCentralities];
    TProfile *hv22RefAllPOIPlusUnwpfx[numCentralities];
    TProfile *hv22RefAllPOIMinusUnwpfx[numCentralities];
    TProfile *hv22POIRefAllPlusUnwpfx[numCentralities];
    TProfile *hv22POIRefAllMinusUnwpfx[numCentralities];

    char pname[256];
    char mname[256];

    // getting the v22 histograms from the data file 
    for(int i = 0; i < numCentralities; i++)
    {
        sprintf(pname,"hv22RefAllPC%i",i+1);
        sprintf(mname,"hv22RefAllMC%i",i+1);

        hv22PlusRefAll[i] = (TH2D*) file->Get(pname);
        hv22MinusRefAll[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22RefPiPC%i",i+1);
        sprintf(mname,"hv22RefPiMC%i",i+1);

        hv22PlusRefPi[i] = (TH2D*) file->Get(pname);
        hv22MinusRefPi[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22POIPC%i",i+1);
        sprintf(mname,"hv22POIMC%i",i+1);

        hv22PlusRefPOI[i] = (TH2D*) file->Get(pname);
        hv22MinusRefPOI[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22AllPOIPC%i",i+1);
        sprintf(mname,"hv22AllPOIMC%i",i+1);

        hv22PlusAllPOI[i] = (TH2D*) file->Get(pname);
        hv22MinusAllPOI[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22PiPOIPC%i",i+1);
        sprintf(mname,"hv22PiPOIMC%i",i+1);

        hv22PlusPiPOI[i] = (TH2D*) file->Get(pname);
        hv22MinusPiPOI[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22POIAllPC%i",i+1);
        sprintf(mname,"hv22POIAllMC%i",i+1);

        hv22PlusPOIAll[i] = (TH2D*) file->Get(pname);
        hv22MinusPOIAll[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22POIPiPC%i",i+1);
        sprintf(mname,"hv22POIPiMC%i",i+1);

        hv22PlusPOIPi[i] = (TH2D*) file->Get(pname);
        hv22MinusPOIPi[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22refAllC%i",i+1);
        hv22RefAll[i] = (TH2D*) file->Get(pname);
   
        sprintf(pname,"hv22refallpoiPC%i",i+1);
        sprintf(mname,"hv22refallpoiMC%i",i+1);
        hv22RefAllPOIPlus[i] = (TH2D*) file->Get(pname);
        hv22RefAllPOIMinus[i] = (TH2D*) file->Get(mname);
    
        sprintf(pname,"hv22poirefallPC%i",i+1);
        sprintf(mname,"hv22poirefallMC%i",i+1);
        hv22POIRefAllPlus[i] = (TH2D*) file->Get(pname);
        hv22POIRefAllMinus[i] = (TH2D*) file->Get(mname);


        // unweighted histograms
        sprintf(pname,"hv22RefAllPC%iu",i+1);
        sprintf(mname,"hv22RefAllMC%iu",i+1);

        hv22PlusRefAllUnw[i] = (TH2D*) file->Get(pname);
        hv22MinusRefAllUnw[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22RefPiPC%iu",i+1);
        sprintf(mname,"hv22RefPiMC%iu",i+1);

        hv22PlusRefPiUnw[i] = (TH2D*) file->Get(pname);
        hv22MinusRefPiUnw[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22POIPC%iu",i+1);
        sprintf(mname,"hv22POIMC%iu",i+1);

        hv22PlusRefPOIUnw[i] = (TH2D*) file->Get(pname);
        hv22MinusRefPOIUnw[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22AllPOIPC%iu",i+1);
        sprintf(mname,"hv22AllPOIMC%iu",i+1);

        hv22PlusAllPOIUnw[i] = (TH2D*) file->Get(pname);
        hv22MinusAllPOIUnw[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22PiPOIPC%iu",i+1);
        sprintf(mname,"hv22PiPOIMC%iu",i+1);

        hv22PlusPiPOIUnw[i] = (TH2D*) file->Get(pname);
        hv22MinusPiPOIUnw[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22POIAllPC%iu",i+1);
        sprintf(mname,"hv22POIAllMC%iu",i+1);

        hv22PlusPOIAllUnw[i] = (TH2D*) file->Get(pname);
        hv22MinusPOIAllUnw[i] = (TH2D*) file->Get(mname);

        sprintf(pname,"hv22POIPiPC%iu",i+1);
        sprintf(mname,"hv22POIPiMC%iu",i+1);

        hv22PlusPOIPiUnw[i] = (TH2D*) file->Get(pname);
        hv22MinusPOIPiUnw[i] = (TH2D*) file->Get(mname);

        // adding relevant histograms together

    
        if(rebin)
        {
            hv22PlusRefAll[i] -> RebinX(rebinAmount);
            hv22MinusRefAll[i]-> RebinX(rebinAmount);
            hv22PlusRefPi[i]  -> RebinX(rebinAmount);
            hv22MinusRefPi[i] -> RebinX(rebinAmount);
            hv22PlusRefPOI[i] -> RebinX(rebinAmount);
            hv22MinusRefPOI[i]-> RebinX(rebinAmount);

            hv22PlusAllPOI[i] -> RebinX(rebinAmount);
            hv22MinusAllPOI[i]-> RebinX(rebinAmount);
            hv22PlusPiPOI[i]  -> RebinX(rebinAmount);
            hv22MinusPiPOI[i] -> RebinX(rebinAmount);

            hv22PlusPOIAll[i] -> RebinX(rebinAmount);
            hv22MinusPOIAll[i]-> RebinX(rebinAmount);
            hv22PlusPOIPi[i]  -> RebinX(rebinAmount);
            hv22MinusPOIPi[i] -> RebinX(rebinAmount);

            hv22RefAll[i] -> RebinX(rebinAmount);

            hv22RefAllPOIPlus[i]  ->RebinX(rebinAmount);
            hv22RefAllPOIMinus[i] ->RebinX(rebinAmount);
            hv22POIRefAllPlus[i]  ->RebinX(rebinAmount);
            hv22POIRefAllMinus[i] ->RebinX(rebinAmount);
        }

        if(addHists) // variable at top of function
        {
            hv22PlusAllPOI[i]->Add(hv22PlusPOIAll[i],1);
            hv22MinusAllPOI[i]->Add(hv22MinusPOIAll[i],1);
            hv22PlusPiPOI[i]->Add(hv22PlusPOIPi[i],1);
            hv22MinusPiPOI[i]->Add(hv22MinusPOIPi[i],1);
 
            hv22PlusAllPOIUnw[i]->Add(hv22PlusPOIAllUnw[i],1);
            hv22MinusAllPOIUnw[i]->Add(hv22MinusPOIAllUnw[i],1);
            hv22PlusPiPOIUnw[i]->Add(hv22PlusPOIPiUnw[i],1);
            hv22MinusPiPOIUnw[i]->Add(hv22MinusPOIPiUnw[i],1);
           
            hv22RefAllPOIPlus[i]->Add(hv22POIRefAllPlus[i],1);
            hv22RefAllPOIMinus[i]->Add(hv22POIRefAllMinus[i],1); 
        }



        // now to make the profiles

        hv22PlusRefAllpfx[i] = hv22PlusRefAll[i]->ProfileX();
        hv22MinusRefAllpfx[i] = hv22MinusRefAll[i]->ProfileX();
        hv22PlusRefPipfx[i] = hv22PlusRefPi[i]->ProfileX();
        hv22MinusRefPipfx[i] = hv22MinusRefPi[i]->ProfileX();
        hv22PlusRefPOIpfx[i] = hv22PlusRefPOI[i]->ProfileX();
        hv22MinusRefPOIpfx[i] = hv22MinusRefPOI[i]->ProfileX();
        
        hv22PlusAllPOIpfx[i] = hv22PlusAllPOI[i]->ProfileX();
        hv22MinusAllPOIpfx[i] = hv22MinusAllPOI[i]->ProfileX();
        hv22PlusPiPOIpfx[i] = hv22PlusPiPOI[i]->ProfileX();
        hv22MinusPiPOIpfx[i] = hv22MinusPiPOI[i]->ProfileX();

        // commented out profiles are unnecessary because they are added
        // prior

        //hv22PlusPOIAllpfx[i] = hv22PlusPOIAll[i]->ProfileX();
        //hv22MinusPOIAllpfx[i] = hv22MinusPOIAll[i]->ProfileX();
        //hv22PlusPOIPipfx[i] = hv22PlusPOIPi[i]->ProfileX();
        //hv22MinusPOIPipfx[i] = hv22MinusPOIPi[i]->ProfileX();

        // unweighted profiles
        hv22PlusRefAllUnwpfx[i] = hv22PlusRefAll[i]->ProfileX();
        hv22MinusRefAllUnwpfx[i] = hv22MinusRefAll[i]->ProfileX();
        hv22PlusRefPiUnwpfx[i] = hv22PlusRefPi[i]->ProfileX();
        hv22MinusRefPiUnwpfx[i] = hv22MinusRefPi[i]->ProfileX();
        hv22PlusRefPOIUnwpfx[i] = hv22PlusRefPOI[i]->ProfileX();
        hv22MinusRefPOIUnwpfx[i] = hv22MinusRefPOI[i]->ProfileX();
        
        hv22PlusAllPOIUnwpfx[i] = hv22PlusAllPOI[i]->ProfileX();
        hv22MinusAllPOIUnwpfx[i] = hv22MinusAllPOI[i]->ProfileX();
        hv22PlusPiPOIUnwpfx[i] = hv22PlusPiPOI[i]->ProfileX();
        hv22MinusPiPOIUnwpfx[i] = hv22MinusPiPOI[i]->ProfileX();

        //hv22PlusPOIAllUnwpfx[i] = hv22PlusPOIAll[i]->ProfileX();
        //hv22MinusPOIAllUnwpfx[i] = hv22MinusPOIAll[i]->ProfileX();
        //hv22PlusPOIPiUnwpfx[i] = hv22PlusPOIPi[i]->ProfileX();
        //hv22MinusPOIPiUnwpfx[i] = hv22MinusPOIPi[i]->ProfileX();

        hv22RefAllpfx[i] = hv22RefAll[i]->ProfileX();
        hv22RefAllPOIPluspfx[i] = hv22RefAllPOIPlus[i]->ProfileX();
        hv22RefAllPOIMinuspfx[i] = hv22RefAllPOIMinus[i]->ProfileX();

    }


    int numXbins = hv22PlusAllPOIpfx[0]->GetNbinsX();

    // drawing the v22 profiles
   
    TCanvas *cv22RefAllP[numCentralities];
    TCanvas *cv22RefAllM[numCentralities];
    TCanvas *cv22RefPiP[numCentralities];
    TCanvas *cv22RefPiM[numCentralities];

    TCanvas *cv22AllPOIP[numCentralities];
    TCanvas *cv22AllPOIM[numCentralities];
    TCanvas *cv22POIAllP[numCentralities];
    TCanvas *cv22POIAllM[numCentralities];
    TCanvas *cv22PiPOIP[numCentralities];
    TCanvas *cv22PiPOIM[numCentralities];
    TCanvas *cv22POIPiP[numCentralities];
    TCanvas *cv22POIPiM[numCentralities];

    TCanvas *cv22AddAllPOIP[numCentralities];
    TCanvas *cv22AddAllPOIM[numCentralities];
    TCanvas *cv22AddPiPOIP[numCentralities];
    TCanvas *cv22AddPiPOIM[numCentralities];

    TCanvas *cv22RefAllPUnw[numCentralities];
    TCanvas *cv22RefAllMUnw[numCentralities];
    TCanvas *cv22RefPiPUnw[numCentralities];
    TCanvas *cv22RefPiMUnw[numCentralities];

    TCanvas *cv22AllPOIPUnw[numCentralities];
    TCanvas *cv22AllPOIMUnw[numCentralities];
    TCanvas *cv22POIAllPUnw[numCentralities];
    TCanvas *cv22POIAllMUnw[numCentralities];
    TCanvas *cv22PiPOIPUnw[numCentralities];
    TCanvas *cv22PiPOIMUnw[numCentralities];
    TCanvas *cv22POIPiPUnw[numCentralities];
    TCanvas *cv22POIPiMUnw[numCentralities];

    TCanvas *cv22AddAllPOIPUnw[numCentralities];
    TCanvas *cv22AddAllPOIMUnw[numCentralities];
    TCanvas *cv22AddPiPOIPUnw[numCentralities];
    TCanvas *cv22AddPiPOIMUnw[numCentralities];

    TCanvas *cv22RefAll[numCentralities];
    TCanvas *cv22RefAllpoi[numCentralities];

    TLegend *lgv22RefAll[numCentralities];
    TLegend *lgv22RefPi[numCentralities];
    TLegend *lgv22poipi[numCentralities];
    TLegend *lgv22poiall[numCentralities];

    TLegend *lgv22RefAllpoi[numCentralities];
    // TLegend *lgv22

    // TCanvas *cTest = new TCanvas("ctest");
    // hv22PlusAllPOIpfx[0]->Draw();

    char canName[256];
    char profTitle[256];
    char savName[256];

    // plotting v22 values
    for(int i = startCent; i < endCent; i++)
    {
        sprintf(canName,"cv22RefAllPlusC%i",i+1);
        cv22RefAllP[i] = new TCanvas(canName);
        sprintf(profTitle,"Reference v^{2}_{+/-}{2} for all particles centrality = %s",centralities[i]);

        hv22PlusRefAllpfx[i]->SetTitle(profTitle);

        hv22PlusRefAllpfx[i]->Draw();
        hv22PlusRefAllpfx[i]->SetMarkerStyle(4);
        hv22PlusRefAllpfx[i]->SetMarkerColor(redcolor);
        hv22PlusRefAllpfx[i]->SetLineColor(redcolor);
        hv22MinusRefAllpfx[i]->Draw("same");
        hv22MinusRefAllpfx[i]->SetMarkerStyle(5);
        hv22MinusRefAllpfx[i]->SetMarkerColor(color2);
        hv22MinusRefAllpfx[i]->SetLineColor(color2);
        Ach_line->Draw("same");

        hv22PlusRefAllpfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        hv22MinusRefAllpfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);

        lgv22RefAll[i] = new TLegend(0.7,0.65,1.0,0.8);
        lgv22RefAll[i]->AddEntry(hv22PlusRefAllpfx[i],"v^{2}{2}_{+}");
        lgv22RefAll[i]->AddEntry(hv22MinusRefAllpfx[i],"v^{2}{2}_{-}");
        lgv22RefAll[i]->Draw("same");

        sprintf(savName,"Plots/mixedPlane/v22RefAllC%i.pdf",i+1);
        cv22RefAllP[i]->SaveAs(savName);
        cv22RefAllP[i]->Close();

        sprintf(canName,"cv22RefPiPlusC%i",i+1);
        cv22RefPiP[i] = new TCanvas(canName);
        sprintf(profTitle,"Reference Pion v^{2}_{+/-}{2} for centrality = %s",centralities[i]);

        hv22PlusRefPipfx[i]->SetTitle(profTitle);

        hv22PlusRefPipfx[i]->Draw();
        hv22PlusRefPipfx[i]->SetMarkerStyle(4);
        hv22PlusRefPipfx[i]->SetMarkerColor(redcolor);
        hv22PlusRefPipfx[i]->SetLineColor(redcolor);
        hv22MinusRefPipfx[i]->Draw("same");
        hv22MinusRefPipfx[i]->SetMarkerStyle(5);
        hv22MinusRefPipfx[i]->SetMarkerColor(color2);
        hv22MinusRefPipfx[i]->SetLineColor(color2);

        if(i == 8)
        {
            hv22PlusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.09,0.09);
            hv22PlusRefPipfx[i]->GetYaxis()->SetRangeUser(0.0015,0.0019);
            
            hv22MinusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.09,0.09);
            hv22MinusRefPipfx[i]->GetYaxis()->SetRangeUser(0.0015,0.0019);
        }
        if(i == 7)
        {
            hv22PlusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.09,0.09);
            hv22PlusRefPipfx[i]->GetYaxis()->SetRangeUser(0.0019,0.00225);

            hv22MinusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.09,0.09);
            hv22MinusRefPipfx[i]->GetYaxis()->SetRangeUser(0.0019,0.00225);
        }
        if(i == 6)
        {
            hv22PlusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22PlusRefPipfx[i]->GetYaxis()->SetRangeUser(0.00290,0.0032);

            hv22MinusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22MinusRefPipfx[i]->GetYaxis()->SetRangeUser(0.00290,0.0032);
        }
        if(i == 5)
        {
            hv22PlusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22PlusRefPipfx[i]->GetYaxis()->SetRangeUser(0.00420,0.0044);

            hv22MinusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22MinusRefPipfx[i]->GetYaxis()->SetRangeUser(0.00420,0.0044);
        }
        if(i == 4)
        {
            hv22PlusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22PlusRefPipfx[i]->GetYaxis()->SetRangeUser(0.00506,0.00530);

            hv22MinusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22MinusRefPipfx[i]->GetYaxis()->SetRangeUser(0.00506,0.00530);
        }
        if(i == 3)
        {
            hv22PlusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22PlusRefPipfx[i]->GetYaxis()->SetRangeUser(0.00520,0.00551);

            hv22MinusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22MinusRefPipfx[i]->GetYaxis()->SetRangeUser(0.00520,0.00551);
        }
        if(i == 2)
        {
            hv22PlusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22PlusRefPipfx[i]->GetYaxis()->SetRangeUser(0.00475,0.0051);

            hv22MinusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22MinusRefPipfx[i]->GetYaxis()->SetRangeUser(0.00475,0.0051);
        }
        if(i == 1)
        {
            hv22PlusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22PlusRefPipfx[i]->GetYaxis()->SetRangeUser(0.0039,0.0042);

            hv22MinusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22MinusRefPipfx[i]->GetYaxis()->SetRangeUser(0.0039,0.0042);
        }
        if(i == 0)
        {
            hv22PlusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22PlusRefPipfx[i]->GetYaxis()->SetRangeUser(0.0030,0.0042);

            hv22MinusRefPipfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22MinusRefPipfx[i]->GetYaxis()->SetRangeUser(0.0030,0.0042);
        }

        lgv22RefPi[i] = new TLegend(0.7,0.65,1.0,0.8);
        lgv22RefPi[i]->AddEntry(hv22PlusRefPipfx[i],"v^{2}{2}_{+}");
        lgv22RefPi[i]->AddEntry(hv22MinusRefPipfx[i],"v^{2}{2}_{-}");
        lgv22RefPi[i]->Draw("same");

        Ach_line->Draw("same");
        sprintf(savName,"Plots/mixedPlane/v22RefPiC%i.pdf",i+1);
        cv22RefPiP[i]->SaveAs(savName);
        cv22RefPiP[i]->Close();
        
         
        sprintf(canName,"cv22POIPiC%i",i+1);
        cv22POIPiP[i] = new TCanvas(canName);
        sprintf(profTitle,"POI-Ref(pions) v^{2}_{+/-}{2} centrality = %s",centralities[i]);
        hv22PlusPiPOIpfx[i]->SetTitle(profTitle);
        hv22PlusPiPOIpfx[i]->Draw();
        hv22PlusPiPOIpfx[i]->SetMarkerStyle(4);
        hv22PlusPiPOIpfx[i]->SetMarkerColor(redcolor);
        hv22PlusPiPOIpfx[i]->SetLineColor(redcolor);
        hv22MinusPiPOIpfx[i]->Draw("same");
        hv22MinusPiPOIpfx[i]->SetMarkerStyle(5);
        hv22MinusPiPOIpfx[i]->SetMarkerColor(color2);
        hv22MinusPiPOIpfx[i]->SetLineColor(color2);
        Ach_line->Draw("same");

        lgv22poipi[i] = new TLegend(0.7,0.65,1.0,0.8);
        lgv22poipi[i]->AddEntry(hv22PlusPiPOIpfx[i],"v22 +");
        lgv22poipi[i]->AddEntry(hv22MinusPiPOIpfx[i],"v22 -");
        lgv22poipi[i]->Draw("same");
        cv22POIPiP[i]->Close();

        sprintf(canName,"cv22POIAllC%i",i+1);
        cv22AllPOIP[i] = new TCanvas(canName);
        sprintf(profTitle,"POI-Ref(all) v^{2}_{+/-}{2} centrality = %s",centralities[i]);
        hv22PlusAllPOIpfx[i]->SetTitle(profTitle);
        hv22PlusAllPOIpfx[i]->Draw();
        hv22PlusAllPOIpfx[i]->SetMarkerStyle(4);
        hv22PlusAllPOIpfx[i]->SetMarkerColor(redcolor);
        hv22PlusAllPOIpfx[i]->SetLineColor(redcolor);
        hv22MinusAllPOIpfx[i]->Draw("same");
        hv22MinusAllPOIpfx[i]->SetMarkerStyle(5);
        hv22MinusAllPOIpfx[i]->SetMarkerColor(color2);
        hv22MinusAllPOIpfx[i]->SetLineColor(color2);
        Ach_line->Draw("same");

        hv22PlusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        hv22MinusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1); 

        if(i == 8)
        {
            hv22PlusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22PlusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.001,0.0019);

            hv22MinusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22MinusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.001,0.0019);
        }
        if(i == 7)
        {
            hv22PlusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22PlusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.0011,0.0022);

            hv22MinusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22MinusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.0011,0.0022);
        }
        if(i == 6)
        {
            hv22PlusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22PlusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.0017,0.0022);

            hv22MinusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22MinusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.0017,0.0022);
        }
        if(i == 5)
        {
            hv22PlusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22PlusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.0023,0.0027);

            hv22MinusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22MinusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.0023,0.0027);
        }
        if(i == 4)
        {
            hv22PlusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22PlusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.0027,0.00315);

            hv22MinusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22MinusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.0027,0.00315);
        }
        if(i == 3)
        {
            hv22PlusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22PlusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.00285,0.00325);

            hv22MinusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22MinusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.00285,0.00325);
        }
        if(i == 2)
        {
            hv22PlusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22PlusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.00260,0.00305);

            hv22MinusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            hv22MinusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.00260,0.00305);
        }
        if(i == 1)
        {
            hv22PlusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22PlusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.0018,0.0028);

            hv22MinusAllPOIpfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            hv22MinusAllPOIpfx[i]->GetYaxis()->SetRangeUser(0.0018,0.0028);
        }

        lgv22poiall[i] = new TLegend(0.7,0.65,1.0,0.8);
        lgv22poiall[i]->AddEntry(hv22PlusAllPOIpfx[i],"v22 +");
        lgv22poiall[i]->AddEntry(hv22MinusAllPOIpfx[i],"v22 -");
        lgv22poiall[i]->Draw("same");
        sprintf(savName,"Plots/mixedPlane/v22allpoiPandM%i.pdf",i+1);
        cv22AllPOIP[i]->SaveAs(savName);
        cv22AllPOIP[i]->Close();

        // creating ref all and ref all-poi

        sprintf(canName,"cv22refall%i",i);
        cv22RefAll[i] = new TCanvas(canName);
        sprintf(profTitle,"v^{2}_{All}{2} for all reference particles at centrality = %s",centralities[i]);
        hv22RefAllpfx[i]->SetTitle(profTitle);
        hv22RefAllpfx[i]->Draw();
        hv22RefAllpfx[i]->SetMarkerStyle(4);
        hv22RefAllpfx[i]->SetMarkerColor(redcolor);
        hv22RefAllpfx[i]->SetLineColor(redcolor);
        Ach_line->Draw("same");

        hv22RefAllpfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        sprintf(savName,"Plots/mixedPlane/v22refall%i.pdf",i+1);
        cv22RefAll[i]->SaveAs(savName);
        //cv22RefAll[i]->Close();
        
        
        sprintf(canName,"cv22refallpoiC%i",i);
        cv22RefAllpoi[i] = new TCanvas(canName);
        sprintf(profTitle,"v^{2}_{ref all poi}{2} of all reference particles and POI at centrality = %s",centralities[i]);
        hv22RefAllPOIPluspfx[i]->SetTitle(profTitle);
        hv22RefAllPOIPluspfx[i]->Draw();
        hv22RefAllPOIPluspfx[i]->SetMarkerStyle(4);
        hv22RefAllPOIPluspfx[i]->SetMarkerColor(redcolor);
        hv22RefAllPOIPluspfx[i]->SetLineColor(redcolor);
        hv22RefAllPOIMinuspfx[i]->Draw("same");
        hv22RefAllPOIMinuspfx[i]->SetMarkerStyle(5);
        hv22RefAllPOIMinuspfx[i]->SetMarkerColor(bluecolor);
        hv22RefAllPOIMinuspfx[i]->SetLineColor(bluecolor);
        Ach_line->Draw("same");

        lgv22RefAllpoi[i] = new TLegend(0.7,0.65,1.0,0.8);
        lgv22RefAllpoi[i]->AddEntry(hv22RefAllPOIPluspfx[i],"v22 +");
        lgv22RefAllpoi[i]->AddEntry(hv22RefAllPOIMinuspfx[i],"v22 -");
        lgv22RefAllpoi[i]->Draw("same");
 
        // hv22RefAllPOIPluspfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        // hv22RefAllPOIMinuspfx[i]->GetXaxis()->SetRangeUser(-0.1,0.1); 
        sprintf(savName,"Plots/mixedPlane/v22refallpoi%i.pdf",i);
        cv22RefAllpoi[i]->SaveAs(savName);
        // cv22RefAllpoi[i]->Close();
    }    


    // creating the v2 plots

    double xBinPlusValsAllPOI[numCentralities][numXbins];
    double xBinPlusValsAllPOIErr[numCentralities][numXbins];
    double v2poiPlusValsAllPOI[numCentralities][numXbins];
    double v2poiPlusValsAllPOIErr[numCentralities][numXbins];    
    
    double xBinPlusValsPiPOI[numCentralities][numXbins];
    double xBinPlusValsPiPOIErr[numCentralities][numXbins];
    double v2poiPlusValsPiPOI[numCentralities][numXbins];
    double v2poiPlusValsPiPOIErr[numCentralities][numXbins];   

    double v22PlusRefAllVals[numCentralities][numXbins];
    double v22PlusRefAllValsErr[numCentralities][numXbins];
    double v22PlusRefPiVals[numCentralities][numXbins];
    double v22PlusRefPiValsErr[numCentralities][numXbins]; 
 
    double v2PlusRefAllVals[numCentralities][numXbins];
    double v2PlusRefAllValsErr[numCentralities][numXbins];
    double v2PlusRefPiVals[numCentralities][numXbins];
    double v2PlusRefPiValsErr[numCentralities][numXbins]; 
 
    double xBinMinusValsAllPOI[numCentralities][numXbins];
    double xBinMinusValsAllPOIErr[numCentralities][numXbins];
    double v2poiMinusValsAllPOI[numCentralities][numXbins];
    double v2poiMinusValsAllPOIErr[numCentralities][numXbins];    
    
    double xBinMinusValsPiPOI[numCentralities][numXbins];
    double xBinMinusValsPiPOIErr[numCentralities][numXbins];
    double v2poiMinusValsPiPOI[numCentralities][numXbins];
    double v2poiMinusValsPiPOIErr[numCentralities][numXbins];   

    double v22MinusRefAllVals[numCentralities][numXbins];
    double v22MinusRefAllValsErr[numCentralities][numXbins];
    double v22MinusRefPiVals[numCentralities][numXbins];
    double v22MinusRefPiValsErr[numCentralities][numXbins]; 
 
    double v2MinusRefAllVals[numCentralities][numXbins];
    double v2MinusRefAllValsErr[numCentralities][numXbins];
    double v2MinusRefPiVals[numCentralities][numXbins];
    double v2MinusRefPiValsErr[numCentralities][numXbins]; 

    // v22 and v2 values for true ref all

    double v22RefAll[numCentralities][numXbins];
    double v22RefAllErr[numCentralities][numXbins];
    double v2RefAll[numCentralities][numXbins];
    double v2RefAllErr[numCentralities][numXbins];

    double v22refallpoiPlus[numCentralities][numXbins];
    double v22refallpoiPlusErr[numCentralities][numXbins];
    double v22refallpoiMinus[numCentralities][numXbins];
    double v22refallpoiMinusErr[numCentralities][numXbins];

    double v2refallpoiPlus[numCentralities][numXbins];
    double v2refallpoiPlusErr[numCentralities][numXbins];
    double v2refallpoiMinus[numCentralities][numXbins];
    double v2refallpoiMinusErr[numCentralities][numXbins];

    // initializing values
    for(int i = 0; i < numCentralities; i++)
    {
        for(int j = 0; j < numXbins; j++)
        {
            xBinPlusValsAllPOI[i][j] = 0;
            xBinPlusValsAllPOIErr[i][j] = 0;
            v2poiPlusValsAllPOI[i][j] = 0;
            v2poiPlusValsAllPOIErr[i][j] = 0;

            xBinPlusValsPiPOI[i][j] = 0;
            xBinPlusValsPiPOIErr[i][j] = 0;
            v2poiPlusValsPiPOI[i][j] = 0;
            v2poiPlusValsPiPOIErr[i][j] = 0;

            v22PlusRefAllVals[i][j] = 0;
            v22PlusRefAllValsErr[i][j] = 0;
            v22PlusRefPiVals[i][j] = 0;
            v22PlusRefPiValsErr[i][j] = 0;

            v2PlusRefAllVals[i][j] = 0;
            v2PlusRefAllValsErr[i][j] = 0;
            v2PlusRefPiVals[i][j] = 0;
            v2PlusRefPiValsErr[i][j] = 0;

            xBinMinusValsAllPOI[i][j] = 0;
            xBinMinusValsAllPOIErr[i][j] = 0;
            v2poiMinusValsAllPOI[i][j] = 0;
            v2poiMinusValsAllPOIErr[i][j] = 0;

            xBinMinusValsPiPOI[i][j] = 0;
            xBinMinusValsPiPOIErr[i][j] = 0;
            v2poiMinusValsPiPOI[i][j] = 0;
            v2poiMinusValsPiPOIErr[i][j] = 0;

            v22MinusRefAllVals[i][j] = 0;
            v22MinusRefAllValsErr[i][j] = 0;
            v22MinusRefPiVals[i][j] = 0;
            v22MinusRefPiValsErr[i][j] = 0;
 
            v2MinusRefAllVals[i][j] = 0;
            v2MinusRefAllValsErr[i][j] = 0;
            v2MinusRefPiVals[i][j] = 0;
            v2MinusRefPiValsErr[i][j] = 0;

            v22RefAll[i][j] = 0;
            v22RefAllErr[i][j] = 0;
            v2RefAll[i][j] = 0;
            v2RefAllErr[i][j] = 0;

            v22refallpoiPlus[i][j] = 0;
            v22refallpoiPlusErr[i][j] = 0;
            v22refallpoiMinus[i][j] = 0;
            v22refallpoiMinusErr[i][j] = 0;

            v2refallpoiPlus[i][j] = 0;
            v2refallpoiPlusErr[i][j] = 0;
            v2refallpoiMinus[i][j] = 0;
            v2refallpoiMinusErr[i][j] = 0;
        }

    }

    // some intermediate variables
    
    double interv22Pallpoi;
    double interv22Mallpoi;
    double interv22Ppipoi;
    double interv22Mpipoi;

    double interv22Pallpoierr;
    double interv22Mallpoierr;
    double interv22Ppipoierr;
    double interv22Mpipoierr;

    double interv22refallpoiPlus;
    double interv22refallpoiPlusErr;
    double interv22refallpoiMinus;
    double interv22refallpoiMinusErr;

    // storing values
    for(int i = startCent; i < endCent; i++)
    {
        for(int j = 0; j < numXbins; j++)
        {
            xBinPlusValsAllPOI[i][j] = hv22PlusAllPOIpfx[i]->GetBinCenter(j+1);
            xBinPlusValsAllPOIErr[i][j] = 0.5*hv22PlusAllPOIpfx[i]->GetBinWidth(j+1);

            interv22Pallpoi = hv22PlusAllPOIpfx[i]->GetBinContent(j+1); // all singly charged particles
            interv22Pallpoierr = hv22PlusAllPOIpfx[i]->GetBinError(j+1);

            interv22Mallpoi = hv22MinusAllPOIpfx[i]->GetBinContent(j+1);
            interv22Mallpoierr = hv22MinusAllPOIpfx[i]->GetBinError(j+1);

            interv22Ppipoi = hv22PlusPiPOIpfx[i]->GetBinContent(j+1);
            interv22Ppipoierr =  hv22PlusPiPOIpfx[i]->GetBinError(j+1);

            interv22Mpipoi = hv22MinusPiPOIpfx[i]->GetBinContent(j+1);
            interv22Mpipoierr = hv22MinusPiPOIpfx[i]->GetBinError(j+1);

            interv22refallpoiPlus = hv22RefAllPOIPluspfx[i]->GetBinContent(j+1); // ref all particles and poi
            interv22refallpoiPlusErr = hv22RefAllPOIPluspfx[i]->GetBinError(j+1);

            interv22refallpoiMinus = hv22RefAllPOIMinuspfx[i]->GetBinContent(j+1); // 
            interv22refallpoiMinusErr = hv22RefAllPOIMinuspfx[i]->GetBinError(j+1);

            v22PlusRefAllVals[i][j] = hv22PlusRefAllpfx[i]->GetBinContent(j+1);
            v22PlusRefAllValsErr[i][j] = hv22PlusRefAllpfx[i]->GetBinError(j+1);

            v22MinusRefAllVals[i][j] = hv22MinusRefAllpfx[i]->GetBinContent(j+1);
            v22MinusRefAllValsErr[i][j] = hv22MinusRefAllpfx[i]->GetBinError(j+1);
 
            v22PlusRefPiVals[i][j] = hv22PlusRefPipfx[i]->GetBinContent(j+1);
            v22PlusRefPiValsErr[i][j] = hv22PlusRefPipfx[i]->GetBinError(j+1);

            v22MinusRefPiVals[i][j] = hv22MinusRefPipfx[i]->GetBinContent(j+1);
            v22MinusRefPiValsErr[i][j] = hv22MinusRefPipfx[i]->GetBinError(j+1);

            v22RefAll[i][j] = hv22RefAllpfx[i]->GetBinContent(j+1);
            v22RefAllErr[i][j] = hv22RefAllpfx[i]->GetBinError(j+1);

            // propagate errors here

            if(v22PlusRefAllVals[i][j] < 0 ) 
            {
                v22PlusRefAllVals[i][j] = 0;
                v2poiPlusValsAllPOI[i][j] = 0;
                v2poiPlusValsAllPOIErr[i][j] = 0;
            }

            if(v22MinusRefAllVals[i][j] < 0 ) 
            {
                v22PlusRefAllVals[i][j] = 0;
                v2poiMinusValsAllPOI[i][j] = 0;
                v2poiMinusValsAllPOIErr[i][j] = 0;
            }

            if(v22PlusRefPiVals[i][j] < 0 ) 
            {
                v22PlusRefPiVals[i][j] = 0;
                v2poiPlusValsPiPOI[i][j] = 0;
                v2poiPlusValsPiPOIErr[i][j] = 0;
            }

            if(v22MinusRefPiVals[i][j] < 0 ) 
            {
                v22MinusRefPiVals[i][j] = 0;
                v2poiMinusValsPiPOI[i][j] = 0;
                v2poiMinusValsPiPOIErr[i][j] = 0;
            }
            if(v22RefAll[i][j] < 0)
            {
                v22RefAll[i][j] = 0;
                v2RefAll[i][j] = 0;
                v2RefAllErr[i][j] = 0;
                v2refallpoiMinus[i][j] = 0;
                v2refallpoiPlus[i][j] = 0;
                v2refallpoiMinusErr[i][j] = 0;
                v2refallpoiPlusErr[i][j] = 0;
            }


            // CHECK ERROR PROPAGATION AS WELL

            if(v22PlusRefAllVals[i][j] != 0) v2PlusRefAllVals[i][j] = TMath::Sqrt(v22PlusRefAllVals[i][j]);
            if(v22PlusRefAllVals[i][j] != 0) v2PlusRefAllValsErr[i][j] = 0.5*fabs(v2PlusRefAllVals[i][j])*(v22PlusRefAllValsErr[i][j]/v22PlusRefAllVals[i][j]);

            if(v22PlusRefPiVals[i][j] != 0) v2PlusRefPiVals[i][j] = TMath::Sqrt(v22PlusRefPiVals[i][j]);
            if(v22PlusRefPiVals[i][j] != 0) v2PlusRefPiValsErr[i][j] = 0.5*fabs(v2PlusRefPiVals[i][j])*(v22PlusRefPiValsErr[i][j]/v22PlusRefPiVals[i][j]);
 
            if(v22MinusRefAllVals[i][j] != 0) v2MinusRefAllVals[i][j] = TMath::Sqrt(v22MinusRefAllVals[i][j]);
            if(v22MinusRefAllVals[i][j] != 0) v2MinusRefAllValsErr[i][j] = 0.5*fabs(v2MinusRefAllVals[i][j])*(v22MinusRefAllValsErr[i][j]/v22MinusRefAllVals[i][j]);

            if(v22MinusRefPiVals[i][j] != 0) v2MinusRefPiVals[i][j] = TMath::Sqrt(v22MinusRefPiVals[i][j]);
            if(v22MinusRefPiVals[i][j] != 0) v2MinusRefPiValsErr[i][j] = 0.5*fabs(v2MinusRefPiVals[i][j])*(v22MinusRefPiValsErr[i][j]/v22MinusRefPiVals[i][j]);

            if(v22PlusRefAllVals[i][j] != 0) v2poiPlusValsAllPOI[i][j] = interv22Pallpoi/v2PlusRefAllVals[i][j];
            if(v22PlusRefPiVals[i][j] != 0) v2poiPlusValsPiPOI[i][j] = interv22Ppipoi/v2PlusRefPiVals[i][j];

            if(v22MinusRefAllVals[i][j] != 0) v2poiMinusValsAllPOI[i][j] = interv22Mallpoi/v2MinusRefAllVals[i][j];
            if(v22MinusRefPiVals[i][j] != 0) v2poiMinusValsPiPOI[i][j] = interv22Mpipoi/v2MinusRefPiVals[i][j];

            if(v22PlusRefAllVals[i][j] != 0) v2poiPlusValsAllPOIErr[i][j] = fabs(v2poiPlusValsAllPOI[i][j])*TMath::Sqrt( TMath::Power( (interv22Pallpoierr/interv22Pallpoi),2) 
                    + TMath::Power( (v2PlusRefAllValsErr[i][j]/v2PlusRefAllVals[i][j]),2) );

            if(v22PlusRefPiVals[i][j] != 0) v2poiPlusValsPiPOIErr[i][j] = fabs(v2poiPlusValsPiPOI[i][j])*TMath::Sqrt( TMath::Power( (interv22Ppipoierr/interv22Ppipoi),2) 
                    + TMath::Power( (v2PlusRefPiValsErr[i][j]/v2PlusRefPiVals[i][j]),2) );

            if(v22MinusRefAllVals[i][j] != 0) v2poiMinusValsAllPOIErr[i][j] = fabs(v2poiMinusValsAllPOI[i][j])*TMath::Sqrt( TMath::Power( (interv22Mallpoierr/interv22Mallpoi),2) 
                    + TMath::Power( (v2MinusRefAllValsErr[i][j]/v2MinusRefAllVals[i][j]),2) );

            if(v22MinusRefPiVals[i][j] != 0) v2poiMinusValsPiPOIErr[i][j] = fabs(v2poiMinusValsPiPOI[i][j])*TMath::Sqrt( TMath::Power( (interv22Mpipoierr/interv22Mpipoi),2) 
                    + TMath::Power( (v2MinusRefPiValsErr[i][j]/v2MinusRefPiVals[i][j]),2) );

           // true ref all below this comment
           
            if( v22RefAll[i][j] != 0 ) 
            {
                v2RefAll[i][j] = TMath::Sqrt(v22RefAll[i][j]);
                v2RefAllErr[i][j] = 0.5*fabs(v2RefAll[i][j])*(v22RefAllErr[i][j]/v22RefAll[i][j]);

                v2refallpoiPlus[i][j] = interv22refallpoiPlus/v2RefAll[i][j];
                v2refallpoiMinus[i][j] = interv22refallpoiMinus/v2RefAll[i][j];

                v2refallpoiPlusErr[i][j] = fabs(v2refallpoiPlus[i][j])*TMath::Sqrt( TMath::Power(interv22refallpoiPlusErr/interv22refallpoiPlus,2) 
                        + TMath::Power(v2RefAllErr[i][j]/v2RefAll[i][j],2) );
                v2refallpoiMinusErr[i][j] = fabs(v2refallpoiMinus[i][j])*TMath::Sqrt( TMath::Power(interv22refallpoiMinusErr/interv22refallpoiMinus,2) 
                        + TMath::Power(v2RefAllErr[i][j]/v2RefAll[i][j],2) );
            }
            
        }
    }
  
    // safety loop 
   
    for(int i = 0; i < numCentralities; i++)
    {
        for(int j = 0; j < numXbins; j++)
        {
            if( isnan(v2poiPlusValsPiPOI[i][j]) ) v2poiPlusValsPiPOI[i][j] = 0;
            if( isnan(v2poiMinusValsPiPOI[i][j]) ) v2poiMinusValsPiPOI[i][j] = 0;
            if( isnan(v2poiPlusValsAllPOI[i][j]) ) v2poiPlusValsAllPOI[i][j] = 0;
            if( isnan(v2poiMinusValsAllPOI[i][j]) ) v2poiMinusValsAllPOI[i][j] = 0;

            if( isnan(v2poiPlusValsPiPOIErr[i][j]) ) v2poiPlusValsPiPOIErr[i][j] = 0;
            if( isnan(v2poiMinusValsPiPOIErr[i][j]) ) v2poiMinusValsPiPOIErr[i][j] = 0;
            if( isnan(v2poiPlusValsAllPOIErr[i][j]) ) v2poiPlusValsAllPOIErr[i][j] = 0;
            if( isnan(v2poiMinusValsAllPOIErr[i][j]) ) v2poiMinusValsAllPOIErr[i][j] = 0;

            if( isnan(v2refallpoiPlus[i][j] ) )
            {
                v2refallpoiPlus[i][j] = 0;
                v2refallpoiPlusErr[i][j] = 0;
            }
            if( isnan(v2refallpoiMinus[i][j]) )
            {
                v2refallpoiMinus[i][j] = 0;
                v2refallpoiMinusErr[i][j] = 0;
            }
        }
    } 

    // drawing and fitting the v2 plots

    TCanvas *cv2PiPoi[numCentralities];
    TCanvas *cv2AllPoi[numCentralities];

    TCanvas *cv2refallpoi[numCentralities];

    TGraphErrors *tgv2PlusPiPOI[numCentralities]; 
    TGraphErrors *tgv2MinusPiPOI[numCentralities];
    TGraphErrors *tgv2PlusAllPOI[numCentralities];
    TGraphErrors *tgv2MinusAllPOI[numCentralities];
    
    TGraphErrors *tgv2refallpoiPlus[numCentralities];
    TGraphErrors *tgv2refallpoiMinus[numCentralities];

    TMultiGraph *tmgv2Allpoi[numCentralities];
    TMultiGraph *tmgv2Pipoi[numCentralities];

    TMultiGraph *tmgv2refallpoi[numCentralities];

    char tmgName[256];

    TLegend *lgv2AllPoi[numCentralities];
    TLegend *lgv2PiPoi[numCentralities];

    TLegend *lgv2refallpoi[numCentralities];

    for(int i = startCent; i < endCent; i++)
    {
        tgv2PlusPiPOI[i] = new TGraphErrors(numXbins,xBinPlusValsAllPOI[i],v2poiPlusValsPiPOI[i],xBinPlusValsAllPOIErr[i],v2poiPlusValsPiPOIErr[i]);
        tgv2MinusPiPOI[i] = new TGraphErrors(numXbins,xBinPlusValsAllPOI[i],v2poiMinusValsPiPOI[i],xBinPlusValsAllPOIErr[i],v2poiMinusValsPiPOIErr[i]);
        tgv2PlusAllPOI[i] = new TGraphErrors(numXbins,xBinPlusValsAllPOI[i],v2poiPlusValsAllPOI[i],xBinPlusValsAllPOIErr[i],v2poiPlusValsAllPOIErr[i]);
        tgv2MinusAllPOI[i] = new TGraphErrors(numXbins,xBinPlusValsAllPOI[i],v2poiMinusValsAllPOI[i],xBinPlusValsAllPOIErr[i],v2poiMinusValsAllPOIErr[i]);

        tgv2refallpoiPlus[i] = new TGraphErrors(numXbins,xBinPlusValsAllPOI[i],v2refallpoiPlus[i],xBinPlusValsAllPOIErr[i],v2refallpoiPlusErr[i]);
        tgv2refallpoiMinus[i] = new TGraphErrors(numXbins,xBinPlusValsAllPOI[i],v2refallpoiMinus[i],xBinPlusValsAllPOIErr[i],v2refallpoiMinusErr[i]);
    }

    //TCanvas *ctest = new TCanvas();
    //tgv2PlusPiPOI[3]->Draw("apz");
    //Ach_line->Draw("same");
  
    for(int i = startCent; i < endCent; i++)
    {
        sprintf(canName,"cv2refallpoiC%i",i+1);
        sprintf(profTitle,"v{2}_{+} and v{2}_{-} with all particles for reference, centrality = %s",centralities[i]);
        sprintf(savName,"v2refallpoi%i.pdf",i+1);
        sprintf(tmgName,"tmgv2refallpoiC%i",i+1);

        cv2refallpoi[i] = new TCanvas(canName);
        tmgv2refallpoi[i] = new TMultiGraph(tmgName,profTitle);

        tgv2refallpoiPlus[i]->SetMarkerStyle(3);
        tgv2refallpoiPlus[i]->SetMarkerColor(redcolor);
        tgv2refallpoiPlus[i]->SetLineColor(redcolor);

        tgv2refallpoiMinus[i]->SetMarkerStyle(4);
        tgv2refallpoiMinus[i]->SetMarkerColor(bluecolor);
        tgv2refallpoiMinus[i]->SetLineColor(bluecolor);

        tmgv2refallpoi[i]->Add(tgv2refallpoiPlus[i]);
        tmgv2refallpoi[i]->Add(tgv2refallpoiMinus[i]);

        lgv2refallpoi[i] = new TLegend(0.7,0.65,1.0,0.8);
        lgv2refallpoi[i]->AddEntry(tgv2refallpoiPlus[i],"v{2}_{+}");
        lgv2refallpoi[i]->AddEntry(tgv2refallpoiMinus[i],"v{2}_{-}");

        tmgv2refallpoi[i]->Draw("apz");
        Ach_line->Draw("same");
        lgv2refallpoi[i]->Draw("same");

        // making specific dimensions

        sprintf(savName,"Plots/mixedPlane/v2refallpminmC%i.pdf",i+1);
        cv2refallpoi[i]->SaveAs(savName);
        // cv2refallpoi[i]->Close();
    }

    for(int i = startCent; i < endCent; i++)
    {
        sprintf(canName,"cv2allpoiC%i",i+1);
        sprintf(profTitle,"v{2}_{+} and v{2}_{-} with all singly charged particles for reference, centrality = %s",centralities[i]);
        sprintf(savName,"v2allpoi%i.pdf",i+1);
        sprintf(tmgName,"tmgv2allpoiC%i",i+1);

        cv2AllPoi[i] = new TCanvas(canName);
        tmgv2Allpoi[i] = new TMultiGraph(tmgName,profTitle);

        tgv2PlusAllPOI[i]->SetMarkerStyle(3);
        tgv2PlusAllPOI[i]->SetMarkerColor(redcolor);
        tgv2PlusAllPOI[i]->SetLineColor(redcolor);

        tgv2MinusAllPOI[i]->SetMarkerStyle(4);
        tgv2MinusAllPOI[i]->SetMarkerColor(color2);
        tgv2MinusAllPOI[i]->SetLineColor(color2);
        
        tmgv2Allpoi[i]->Add(tgv2PlusAllPOI[i]);
        tmgv2Allpoi[i]->Add(tgv2MinusAllPOI[i]);

        lgv2AllPoi[i] = new TLegend(0.7,0.65,1.0,0.8);
        lgv2AllPoi[i]->AddEntry(tgv2PlusAllPOI[i],"v{2}_{+}");
        lgv2AllPoi[i]->AddEntry(tgv2MinusAllPOI[i],"v{2}_{-}");

        tmgv2Allpoi[i]->Draw("apz");
        Ach_line->Draw("same");
        lgv2AllPoi[i]->Draw("same");

        if(i == 8)
        {
            tmgv2Allpoi[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            tmgv2Allpoi[i]->GetYaxis()->SetRangeUser(0.025,0.045);
        }
        if(i == 7)
        {
            tmgv2Allpoi[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            tmgv2Allpoi[i]->GetYaxis()->SetRangeUser(0.025,0.045);
        }
        if(i == 6)
        {
            tmgv2Allpoi[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            tmgv2Allpoi[i]->GetYaxis()->SetRangeUser(0.031,0.04);
        }
        if(i == 5)
        {
            tmgv2Allpoi[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
            tmgv2Allpoi[i]->GetYaxis()->SetRangeUser(0.0356,0.0415);
        }
        if(i == 4)
        {
            tmgv2Allpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tmgv2Allpoi[i]->GetYaxis()->SetRangeUser(0.0376,0.0438);
        }
        if(i == 3)
        {
            tmgv2Allpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tmgv2Allpoi[i]->GetYaxis()->SetRangeUser(0.0372,0.0446);
        }
        if(i == 2)
        {
            tmgv2Allpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tmgv2Allpoi[i]->GetYaxis()->SetRangeUser(0.0375,0.0444);
        }
        if(i == 1)
        {
            tmgv2Allpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tmgv2Allpoi[i]->GetYaxis()->SetRangeUser(0.0294,0.0443);
        }
        if(i == 0)
        {
            tmgv2Allpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tmgv2Allpoi[i]->GetYaxis()->SetRangeUser(0.005,0.057);
        }

        sprintf(savName,"Plots/mixedPlane/v2pandmAllC%i.pdf",i+1);
        cv2AllPoi[i]->SaveAs(savName);

        cv2AllPoi[i]->Close();

    }

    for(int i = startCent; i < endCent; i++)
    {
        // if(i != 4) continue;
        sprintf(canName,"cv2pipoiC%i",i+1);
        sprintf(profTitle,"v{2}_{+} and v{2}_{-} with pions for reference, centrality = %s",centralities[i]);
        sprintf(savName,"v2pipoi%i.pdf",i+1);
        sprintf(tmgName,"tmgv2pipoiC%i",i+1);

        cv2PiPoi[i] = new TCanvas(canName);
        tmgv2Pipoi[i] = new TMultiGraph(tmgName,profTitle);

        tgv2PlusPiPOI[i]->SetMarkerStyle(3);
        tgv2PlusPiPOI[i]->SetMarkerColor(redcolor);
        tgv2PlusPiPOI[i]->SetLineColor(redcolor);

        tgv2MinusPiPOI[i]->SetMarkerStyle(4);
        tgv2MinusPiPOI[i]->SetMarkerColor(color2);
        tgv2MinusPiPOI[i]->SetLineColor(color2);
        
        tmgv2Pipoi[i]->Add(tgv2PlusPiPOI[i]);
        tmgv2Pipoi[i]->Add(tgv2MinusPiPOI[i]);

        lgv2PiPoi[i] = new TLegend(0.7,0.65,1.0,0.8);
        lgv2PiPoi[i]->AddEntry(tgv2PlusPiPOI[i],"v{2}_{+}");
        lgv2PiPoi[i]->AddEntry(tgv2MinusPiPOI[i],"v{2}_{-}");

        tmgv2Pipoi[i]->Draw("apz");
        Ach_line->Draw("same");
        lgv2PiPoi[i]->Draw("same");

        if(i == 0)
        {
            // 70 - 80% centrality
            tmgv2Pipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        }
        if(i == 1)
        {
            // 60 - 70% centrality
            tmgv2Pipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        }
        if(i == 2) 
        {
            // 50 - 60% centrality
            tmgv2Pipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        }
        if(i == 3)
        {
            // 40 - 50% centrality
            tmgv2Pipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        }
        if(i == 4)
        {
            // 30 - 40% centrality
            tmgv2Pipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        }
        if(i == 5)
        {
            // 20 - 30% centrality
            tmgv2Pipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        }
        if(i == 6)
        {
            // 10 - 20% centrality
            tmgv2Pipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        }
        if(i == 7)
        {
            // 5-10% centrality
            tmgv2Pipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        }
        if(i == 8)
        {
            // 0-5% centrality
            tmgv2Pipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
        }

        sprintf(savName,"Plots/mixedPlane/v2pandmPiC%i.pdf",i+1);
        cv2PiPoi[i]->SaveAs(savName);

        cv2PiPoi[i]->Close();

    }

    // debug loop
    /*
    for(int i = 0; i < numCentralities; i++)
    {
        printf("v2poiPlusValsAllPOI[%i] = \n",i);
        for(int j = 0; j < numXbins; j++)
        {
            printf("%.4f \t",v2poiMinusValsAllPOIErr[i][j]);
        }
        printf("\n");
    }
    */
    // end of debug loop

    // v2(-) - v2(+) and fitting 

    vector < double > pushDouble;

    vector < vector < double > > v2pmpipoi;
    vector < vector < double > > v2pmallpoi;
    vector < vector < double > > xv2pivals;
    vector < vector < double > > xv2allvals; 

    vector < vector < double > > v2pmpipoierr;
    vector < vector < double > > v2pmallpoierr;
    vector < vector < double > > xv2pivalserr;
    vector < vector < double > > xv2allvalserr; 

    vector < vector < double > > v2refallpoipm;
    vector < vector < double > > v2refallpoipmerr;
    vector < vector < double > > xv2refall;
    vector < vector < double > > xv2refallerr;

    double v2Hold;
    double v2HoldErr;

    for(int i = startCent; i < endCent; i++)
    {
        v2pmpipoi.push_back(pushDouble);
        v2pmallpoi.push_back(pushDouble);
        xv2pivals.push_back(pushDouble);
        xv2allvals.push_back(pushDouble);

        v2pmpipoierr.push_back(pushDouble);
        v2pmallpoierr.push_back(pushDouble);
        xv2pivalserr.push_back(pushDouble);
        xv2allvalserr.push_back(pushDouble);

        v2refallpoipm.push_back(pushDouble);
        v2refallpoipmerr.push_back(pushDouble);
        xv2refall.push_back(pushDouble);
        xv2refallerr.push_back(pushDouble);

        for(int j = 0; j < numXbins; j++)
        {
            if(v2poiMinusValsAllPOI[i][j] != 0 && v2poiPlusValsAllPOI[i][j] != 0)
            {
                v2Hold = v2poiMinusValsAllPOI[i][j] - v2poiPlusValsAllPOI[i][j];
                v2HoldErr = TMath::Sqrt( TMath::Power(v2poiMinusValsAllPOIErr[i][j],2) + TMath::Power(v2poiPlusValsAllPOIErr[i][j],2) );

                v2pmallpoi[i].push_back(v2Hold);
                v2pmallpoierr[i].push_back(v2HoldErr);
                xv2allvals[i].push_back(xBinPlusValsAllPOI[i][j]);
                xv2allvalserr[i].push_back(xBinPlusValsAllPOIErr[i][j]);
            }
            if(v2poiMinusValsPiPOI[i][j] != 0 && v2poiPlusValsPiPOI[i][j] != 0)
            {
                v2Hold = v2poiMinusValsPiPOI[i][j] - v2poiPlusValsPiPOI[i][j];
                v2HoldErr = TMath::Sqrt( TMath::Power(v2poiMinusValsPiPOIErr[i][j],2) + TMath::Power(v2poiPlusValsPiPOIErr[i][j],2) );

                v2pmpipoi[i].push_back(v2Hold);
                v2pmpipoierr[i].push_back(v2HoldErr);
                xv2pivals[i].push_back(xBinPlusValsAllPOI[i][j]);
                xv2pivalserr[i].push_back(xBinPlusValsAllPOIErr[i][j]);
            }
            // ref all for all particles
            if(v2refallpoiPlus[i][j] != 0 && v2refallpoiMinus[i][j] != 0)
            {
                v2Hold = v2refallpoiMinus[i][j] - v2refallpoiPlus[i][j];
                v2HoldErr = TMath::Sqrt( TMath::Power(v2refallpoiMinusErr[i][j],2) + TMath::Power(v2refallpoiPlusErr[i][j],2) );

                v2refallpoipm[i].push_back(v2Hold);
                v2refallpoipmerr[i].push_back(v2HoldErr);
                xv2refall[i].push_back(xBinPlusValsAllPOI[i][j]);
                xv2refallerr[i].push_back(xBinPlusValsAllPOIErr[i][j]);
            } 

        }

    }

    // debugging loop
    /*
    for(int i = 0; i < numCentralities; i++)
    {
        printf("v2[%i]=\n",i);
        for(int j = 0; j < v2pmallpoi[i].size(); j++)
        {
            printf("%.4f \t",v2pmallpoi[i][j]);   
        }
        printf("\n");
    }
    */
    // end of debugging loop

    TCanvas *cv2diffpipoi[numCentralities];
    TCanvas *cv2diffallpoi[numCentralities];
    TCanvas *cv2diffrefallpoi[numCentralities];

    TGraphErrors *tgv2diffpipoi[numCentralities];
    TGraphErrors *tgv2diffallpoi[numCentralities];
    TGraphErrors *tgv2diffrefallpoi[numCentralities];

    TGraphErrors *tgv2diffpipoiAch[numCentralities]; // previous plots are observed Ach, this will be Ach

    TF1 *rFitall[numCentralities];
    TF1 *rFitpi[numCentralities];
    TF1 *rFitrefall[numCentralities];

    double rFitValsAll[numCentralities];
    double rFitValsAllErr[numCentralities];

    double rFitValsPi[numCentralities];
    double rFitValsPiErr[numCentralities];

    double rFitrefallval[numCentralities];
    double rFitrefallvalerr[numCentralities];

    char fitName[256];

    // ALL CHARGED PARTICLES
    for(int i = startCent; i < endCent; i++)
    {
        sprintf(canName,"cv2diffrefallC%i",i+1);
        sprintf(profTitle,"v{2}_{-} - v{2}_{+} all particles as reference, centrality = %s",centralities[i]);

        cv2diffrefallpoi[i] = new TCanvas(canName);
        tgv2diffrefallpoi[i] = new TGraphErrors(v2refallpoipm[i].size(),&(xv2refall[i][0]),&(v2refallpoipm[i][0]),&(xv2refallerr[i][0]),&(v2refallpoipmerr[i][0]));
        tgv2diffrefallpoi[i]->SetTitle(profTitle);
        tgv2diffrefallpoi[i]->SetMarkerColor(bluecolor);
        tgv2diffrefallpoi[i]->SetLineColor(bluecolor);
        tgv2diffrefallpoi[i]->SetMarkerStyle(3);

        sprintf(fitName,"fitsrefall%i",i);
       
        if( i == 8 ) // 0 - 5 %
        { 
            rFitrefall[i] = new TF1(fitName,"pol1",-0.1,0.1);
            tgv2diffrefallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            // tgv2diffrefallpoi[i]->GetYaxis()->SetRangeUser(-0.056,0.025);
        }
        if( i == 7 ) // 5 - 10 %
        { 
            rFitrefall[i] = new TF1(fitName,"pol1",-0.1,0.1);
            tgv2diffrefallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tgv2diffrefallpoi[i]->GetYaxis()->SetRangeUser(-0.14,0.13);
        }
        if( i == 6 ) // 10 - 20 %
        { 
            rFitrefall[i] = new TF1(fitName,"pol1",-0.1,0.1);
            tgv2diffrefallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tgv2diffrefallpoi[i]->GetYaxis()->SetRangeUser(-0.022,0.027);
        }
        if( i == 5 ) // 20 - 30 %
        { 
            rFitrefall[i] = new TF1(fitName,"pol1",-0.1,0.1);
            tgv2diffrefallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tgv2diffrefallpoi[i]->GetYaxis()->SetRangeUser(-0.006,0.014);
        }
        if( i == 4 ) // 30 - 40 %
        { 
            rFitrefall[i] = new TF1(fitName,"pol1",-0.1,0.1);
            // rFitrefall[i]->SetParLimits(1,0,0.005);
            tgv2diffrefallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tgv2diffrefallpoi[i]->GetYaxis()->SetRangeUser(-0.01,0.01);
            // tgv2diffrefallpoi[i]->SetName("tryfit");
        }
        if( i == 3 ) // 40 - 50 %
        { 
            rFitrefall[i] = new TF1(fitName,"pol1",-0.1,0.1);
            tgv2diffrefallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tgv2diffrefallpoi[i]->GetYaxis()->SetRangeUser(-0.015,0.01);
        }
        if( i == 2 ) // 50 - 60 %
        { 
            rFitrefall[i] = new TF1(fitName,"pol1",-0.1,0.1);
            tgv2diffrefallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tgv2diffrefallpoi[i]->GetYaxis()->SetRangeUser(-0.015,0.012);
        }
        if( i == 1 ) // 60 - 70 %
        { 
            rFitrefall[i] = new TF1(fitName,"pol1",-0.1,0.1);
            tgv2diffrefallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tgv2diffrefallpoi[i]->GetYaxis()->SetRangeUser(-0.015,0.012);
        }
        if( i == 0 ) // 70 - 80 %
        { 
            rFitrefall[i] = new TF1(fitName,"pol1",-0.1,0.1);
            tgv2diffrefallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
            tgv2diffrefallpoi[i]->GetYaxis()->SetRangeUser(-0.025,0.02);
        }


        tgv2diffrefallpoi[i]->Draw("apz");
        Ach_line->Draw("same");

        tgv2diffrefallpoi[i]->Fit(rFitrefall[i],"R");
        rFitrefallval[i] = rFitrefall[i]->GetParameter(1);
        rFitrefallvalerr[i] = rFitrefall[i]->GetParError(1);

        sprintf(savName,"Plots/mixedPlane/v2diffrefallC%i.pdf",i+1);
        cv2diffrefallpoi[i]->SaveAs(savName);

        // cv2diffrefallpoi[i]->Close();


    }

    // SINGLY CHARGED ALL PARTICLES
    //for(int i = startCent; i < endCent; i++)
    //{
    //    sprintf(canName,"cv2diffallC%i",i+1);
    //    sprintf(profTitle,"v{2}_{-} - v{2}_{+} all singly charged particles as reference, centrality = %s",centralities[i]);

    //    cv2diffallpoi[i] = new TCanvas(canName);
    //    tgv2diffallpoi[i] = new TGraphErrors(v2pmallpoi[i].size(),&(xv2allvals[i][0]),&(v2pmallpoi[i][0]),&(xv2allvalserr[i][0]),&(v2pmallpoierr[i][0]));
    //    tgv2diffallpoi[i]->SetTitle(profTitle);
    //    tgv2diffallpoi[i]->SetMarkerColor(bluecolor);
    //    tgv2diffallpoi[i]->SetLineColor(bluecolor);
    //    tgv2diffallpoi[i]->SetMarkerStyle(3);

    //    sprintf(fitName,"fitsall%i",i);

    //    // fit range wil have to be specified for each histogram

    //    if(i == 8) // 0 - 5%
    //    {
    //        rFitall[i] = new TF1(fitName,"[0] + [1]*x",-0.07,0.07);
    //        // rFitall[i]->SetParLimits(1,-5,5);
    //        tgv2diffallpoi[i]->GetXaxis()->SetRangeUser(-0.08,0.08);
    //        tgv2diffallpoi[i]->GetYaxis()->SetRangeUser(-0.001,0.02);
    //    }
    //    if(i == 7) // 5 - 10%
    //    {
    //        rFitall[i] = new TF1(fitName,"[0] + [1]*x",-0.1,0.1);
    //        // rFitall[i]->SetParLimits(1,-5,5);
    //        tgv2diffallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
    //        tgv2diffallpoi[i]->GetYaxis()->SetRangeUser(-0.008,0.031);
    //    }
    //    if(i == 6) // 10 - 20%
    //    {
    //        rFitall[i] = new TF1(fitName,"[0] + [1]*x",-0.1,0.1);
    //        // rFitall[i]->SetParLimits(1,-5,5);
    //        tgv2diffallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
    //        tgv2diffallpoi[i]->GetYaxis()->SetRangeUser(-0.002,0.012);
    //    }
    //    if(i == 5) // 20 - 30%
    //    {
    //        rFitall[i] = new TF1(fitName,"[0] + [1]*x",-0.05,0.05);
    //        // rFitall[i]->SetParLimits(1,-5,5);
    //        tgv2diffallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
    //        tgv2diffallpoi[i]->GetYaxis()->SetRangeUser(0.001,0.006);
    //    }
    //    if(i == 4)
    //    {
    //        rFitall[i] = new TF1(fitName,"[0] + [1]*x",-0.1,0.1);
    //        // rFitall[i]->SetParLimits(1,-5,5);
    //        tgv2diffallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
    //        tgv2diffallpoi[i]->GetYaxis()->SetRangeUser(0.0002,0.005);
    //    }
    //    if(i == 3) // 
    //    {
    //        rFitall[i] = new TF1(fitName,"[0] + [1]*x",-0.05,0.05);
    //        // rFitall[i]->SetParLimits(1,-5,5);
    //        tgv2diffallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
    //        tgv2diffallpoi[i]->GetYaxis()->SetRangeUser(0.0005,0.005);
    //    }
    //    if(i == 2) // 
    //    {
    //        rFitall[i] = new TF1(fitName,"[0] + [1]*x",-0.1,0.1);
    //        // rFitall[i]->SetParLimits(1,-5,5);
    //        tgv2diffallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
    //        tgv2diffallpoi[i]->GetYaxis()->SetRangeUser(-0.0026,0.004);
    //    }
    //    if(i == 1) // 
    //    {
    //        rFitall[i] = new TF1(fitName,"[0] + [1]*x",-0.1,0.1);
    //        // rFitall[i]->SetParLimits(1,-5,5);
    //        tgv2diffallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
    //        tgv2diffallpoi[i]->GetYaxis()->SetRangeUser(-0.009,0.012);
    //    }
    //    if(i == 0) 
    //    {
    //        rFitall[i] = new TF1(fitName,"[0] + [1]*x",-0.1,0.1);
    //        // rFitall[i]->SetParLimits(1,-5,5);
    //        tgv2diffallpoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
    //        tgv2diffallpoi[i]->GetYaxis()->SetRangeUser(-0.02,0.036);
    //    }
    //    

    //    tgv2diffallpoi[i]->Draw("apz");
    //    Ach_line->Draw("same");

    //    tgv2diffallpoi[i]->Fit(rFitall[i],"R");
    //    rFitValsAll[i] = rFitall[i]->GetParameter(1);
    //    rFitValsAllErr[i] = rFitall[i]->GetParError(1);

    //    sprintf(savName,"Plots/mixedPlane/v2diffallC%i.pdf",i+1);
    //    cv2diffallpoi[i]->SaveAs(savName);

    //    cv2diffallpoi[i]->Close();

    //}

    //// REFERENCE PIONS
    //for(int i = startCent; i < endCent; i++)
    //{
    //    sprintf(canName,"cv2diffpiC%i",i+1);
    //    sprintf(profTitle,"v{2}_{-} - v{2}_{+} pions as reference, centrality = %s",centralities[i]);

    //    cv2diffpipoi[i] = new TCanvas(canName);
    //    tgv2diffpipoi[i] = new TGraphErrors(v2pmpipoi[i].size(),&(xv2pivals[i][0]),&(v2pmpipoi[i][0]),&(xv2pivalserr[i][0]),&(v2pmpipoierr[i][0]));
    //    tgv2diffpipoi[i]->SetTitle(profTitle);
    //    tgv2diffpipoi[i]->SetMarkerColor(bluecolor);
    //    tgv2diffpipoi[i]->SetLineColor(bluecolor);
    //    tgv2diffpipoi[i]->SetMarkerStyle(3);
    //    tgv2diffpipoi[i]->GetXaxis()->SetTitle("Obs A_{ch}");
    //    tgv2diffpipoi[i]->GetYaxis()->SetTitle("v_{2}(#pi^{-}) - v_{2}(#pi^{+})");
    //    tgv2diffpipoi[i]->Draw("apz");
    //    Ach_line->Draw("same");

    //    sprintf(fitName,"fitspi%i",i);

    //    // fit range wil have to be specified for each histogram
    //    if(i==0) // 70 - 80%
    //    {
    //        rFitpi[i] = new TF1(fitName,"[0] + [1]*x",-0.1,0.1); 
    //        rFitpi[i]->SetParLimits(1,-5,5);
    //        tgv2diffpipoi[i]->GetXaxis()->SetRangeUser(-0.2,0.2);
    //        tgv2diffpipoi[i]->GetYaxis()->SetRangeUser(-0.2,0.2);
    //    }
    //    if(i==1) // 60 - 70%
    //    {
    //        rFitpi[i] = new TF1(fitName,"[0] + [1]*x",-0.1,0.1); 
    //        rFitpi[i]->SetParLimits(1,-5,5);
    //        tgv2diffpipoi[i]->GetXaxis()->SetRangeUser(-0.15,0.15);
    //        tgv2diffpipoi[i]->GetYaxis()->SetRangeUser(-0.15,0.15);
    //    }
    //    if(i==2) // 50 - 60% 
    //    {
    //        rFitpi[i] = new TF1(fitName,"[0] + [1]*x",-0.11,0.13); 
    //        rFitpi[i]->SetParLimits(1,-5,5);
    //        tgv2diffpipoi[i]->GetXaxis()->SetRangeUser(-0.15,0.15);
    //        tgv2diffpipoi[i]->GetYaxis()->SetRangeUser(-0.15,0.15);
    //    }
    //    if(i==3) // 40 - 50%
    //    {
    //        rFitpi[i] = new TF1(fitName,"[0] + [1]*x",-0.07,0.11);
    //        rFitpi[i]->SetParLimits(1,-5,5); 
    //        tgv2diffpipoi[i]->GetXaxis()->SetRangeUser(-0.11,0.11);
    //        tgv2diffpipoi[i]->GetYaxis()->SetRangeUser(-0.1,0.1);
    //    }
    //    if(i==4) // 30 - 40% 
    //    {
    //        rFitpi[i] = new TF1(fitName,"[0] + [1]*x",-0.11,0.11);
    //        tgv2diffpipoi[i]->GetXaxis()->SetRangeUser(-0.12,0.12);
    //        tgv2diffpipoi[i]->GetYaxis()->SetRangeUser(-0.06,0.09); 
    //    }
    //    if(i==5) // 20 - 30% 
    //    {
    //        rFitpi[i] = new TF1(fitName,"[0] + [1]*x",-0.03,0.03);
    //        // rFitpi[i]->SetParRange
    //        tgv2diffpipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.11);
    //        tgv2diffpipoi[i]->GetYaxis()->SetRangeUser(-0.1,0.1);
    //    } 
    //    if(i==6) // 10 - 20%
    //    {
    //        rFitpi[i] = new TF1(fitName,"[0] + [1]*x",-0.05,0.05);
    //        rFitpi[i]->SetParLimits(1,-5,5); 
    //        tgv2diffpipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
    //        tgv2diffpipoi[i]->GetYaxis()->SetRangeUser(-0.07,0.06);
    //    }
    //    if(i==7) // 5-10%
    //    {
    //        rFitpi[i] = new TF1(fitName,"[0] + [1]*x",-0.05,0.05);
    //        tgv2diffpipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1); 
    //        tgv2diffpipoi[i]->GetYaxis()->SetRangeUser(-0.1,0.1); 
    //    }
    //    if(i==8) // 0-5% 
    //    {
    //        rFitpi[i] = new TF1(fitName,"[0] + [1]*x",-0.05,0.05);
    //        rFitpi[i]->SetParLimits(1,-5,5);
    //        tgv2diffpipoi[i]->GetXaxis()->SetRangeUser(-0.1,0.1);
    //        tgv2diffpipoi[i]->GetYaxis()->SetRangeUser(-0.1,0.1); 
    //    }

    //    tgv2diffpipoi[i]->Fit(rFitpi[i],"R");
    //    rFitValsPi[i] = rFitpi[i]->GetParameter(1);
    //    rFitValsPiErr[i] = rFitpi[i]->GetParError(1);

    //    sprintf(savName,"Plots/mixedPlane/v2diffpiC%i.pdf",i+1);
    //    cv2diffpipoi[i]->SaveAs(savName);

    //    cv2diffpipoi[i]->Close();

    //}


    // creating and drawing the r-slop plots
    TCanvas *crFitrefall = new TCanvas("rfitrefall");
    TGraphErrors *tgeRfitrefall = new TGraphErrors(numCentralities,centralityVals,rFitrefallval,centralityValsErrs,rFitrefallvalerr);
    tgeRfitrefall->SetTitle("r-slope vs Centrality with all particle reference");
    tgeRfitrefall->SetMarkerStyle(4);
    tgeRfitrefall->SetMarkerColor(color2);
    tgeRfitrefall->SetLineColor(color2);
    tgeRfitrefall->GetXaxis()->SetTitle("centrality %");
    tgeRfitrefall->GetYaxis()->SetTitle("r-slope");
    tgeRfitrefall->Draw("apz");
    centLine->Draw("same");

    crFitrefall->SaveAs("Plots/mixedPlane/rFitrefall.pdf");
    // crFitrefall->Close();

    // charged all particles
    //TCanvas *crFitAll = new TCanvas("rfitall");
    //TGraphErrors *tgeRfitAll = new TGraphErrors(numCentralities,centralityVals,rFitValsAll,centralityValsErrs,rFitValsAllErr);
    //tgeRfitAll->SetTitle("r-slope vs Centrality with all singly charged particles reference");
    //tgeRfitAll->SetMarkerStyle(4);
    //tgeRfitAll->SetMarkerColor(color2);
    //tgeRfitAll->SetLineColor(color2);
    //tgeRfitAll->GetXaxis()->SetTitle("centrality %");
    //tgeRfitAll->GetYaxis()->SetTitle("r-slope");
    //tgeRfitAll->Draw("apz");
    //centLine->Draw("same");

    //crFitAll->SaveAs("Plots/mixedPlane/rFitall.pdf");
    //crFitAll->Close();

    // reference pions
    //TCanvas *crFitPi = new TCanvas("rfitpi");
    //TGraphErrors *tgeRfitPi = new TGraphErrors(numCentralities,centralityVals,rFitValsPi,centralityValsErrs,rFitValsPiErr);
    //tgeRfitPi->SetTitle("r-slope vs Centrality for pion reference");
    //tgeRfitPi->SetMarkerStyle(4);
    //tgeRfitPi->SetMarkerColor(color2);
    //tgeRfitPi->SetLineColor(color2);
    //tgeRfitPi->GetXaxis()->SetTitle("centrality %");
    //tgeRfitPi->GetYaxis()->SetTitle("r-slope");
    //tgeRfitPi->Draw("apz");
    //centLine->Draw("same");

    //crFitPi->SaveAs("Plots/mixedPlane/rFitpi.pdf");
    //crFitPi->Close();

    // debug loops
/*    
    for(int i = 0; i < numCentralities; i++)
    {
        fdebug << i <<"\tv22poiref vals(+) = " << endl;

        for(int j = 0; j < numXbins; j++)
        {
            if(j%10 == 0) fdebug << endl;

            fdebug << hv22PlusPiPOIpfx[i]->GetBinContent(j+1) <<"\t" ;
        }

        fdebug << endl;

        fdebug << i <<"\tv22refpi vals (+) = " << endl;

        for(int j = 0; j < numXbins; j++)
        {
            if(j%10 == 0) fdebug << endl;
            fdebug << v22PlusRefPiVals[i][j] <<"\t" ;
        }

        fdebug << endl;

        fdebug<< i<< "\tv2refpi vals (+) = " << endl;

        for(int j = 0; j < numXbins; j++)
        {
            if(j%10 == 0) fdebug << endl;
            fdebug << v2PlusRefPiVals[i][j] <<"\t" ;
        }

        fdebug << endl;


        fdebug<< i << "\tv2poi vals (+) = " << endl;

        for(int j = 0; j < numXbins; j++)
        {
            if(j%10 == 0) fdebug << endl;
            fdebug << v2poiPlusValsPiPOI[i][j] <<"\t" ;
        }

        fdebug << endl;

        fdebug<< i << "\tv22poiref vals (-) = " << endl;

        for(int j = 0; j < numXbins; j++)
        {
            if(j%10 == 0) fdebug << endl;
            fdebug << hv22MinusPiPOIpfx[i]->GetBinContent(j+1) <<"\t" ;
        }

        fdebug << endl;

        fdebug<< i << "\tv22refpi vals (-) = " << endl;

        for(int j = 0; j < numXbins; j++)
        {
            if(j%10 == 0) fdebug << endl;
            fdebug << v22MinusRefPiVals[i][j] <<"\t" ;
        }

        fdebug << endl;

        fdebug<< i << "\tv2refpi vals (-) = " << endl;

        for(int j = 0; j < numXbins; j++)
        {
            if(j%10 == 0) fdebug << endl;
            fdebug << v2MinusRefPiVals[i][j] <<"\t" ;
        }

        fdebug << endl;


        fdebug<< i << "\tv2poi vals (-) = " << endl;

        for(int j = 0; j < numXbins; j++)
        {
            if(j%10 == 0) fdebug << endl;
            fdebug << v2poiMinusValsPiPOI[i][j] <<"\t" ;
        }

        fdebug << endl;
    }
*/


    // end of debug loops



    return;
}











