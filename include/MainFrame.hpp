// MainFrame.hpp --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 2月  2 22:08:49 2019 (+0800)
// Last-Updated: 六 2月  2 22:09:06 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 1
// URL: http://wuhongyi.cn 


/// @file MainFrame.hpp
/// @brief
/// @author S. V. Paulauskas
/// @date June 02, 2018
/// @copyright Copyright (c) 2018 S. V. Paulauskas. 
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License

#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_

#include <TGFrame.h>
#include <TGMenu.h>
#include <TGApplication.h>
#include <TApplication.h>
#include <TGClient.h>
#include <TGTab.h>
#include <TGButton.h>
#include <TGNumberEntry.h>
#include <TGLabel.h>
#include <TGTextEntry.h>
#include <TRootEmbeddedCanvas.h>
#include <TH1S.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TF1.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TGFileDialog.h>
#include <TCanvas.h>
#include <TGListBox.h>
#include <TList.h>
#include <TApplication.h>
#include <TFile.h>
#include <TKey.h>
#include <TH2D.h>
#include <TH3D.h>
#include "TString.h"

#include <string>

///@brief
class MainFrame : public TGMainFrame {
public:
    /// Default Constructor
    MainFrame();

    /// Default Destructor
    ~MainFrame();

    MainFrame(const TGWindow *p, TApplication *a);

    void Exit();
    void PlotSelected();
    void OpenFile();
private:
    void Initialize(TApplication *app);
    void UpdateHistogramList();
    void AddHistogramListToFrame();
    void SetupControlButtons();

    TGListBox *fListBox;
    TList *fSelected;
    TApplication *app_;
    TFile *file_;
    TCanvas *canvas_;

    TH1 *hist;

    std::map<int, std::tuple<bool, TAxis, TAxis, TAxis,TString> > axisMap_;

    bool isFirstPlotCall_;

    static constexpr unsigned int frameWidth_ = 350;
    static constexpr unsigned int histogramListHeight_ = 200;
    static constexpr auto frameName_ = "Histogram Viewer";

ClassDef(MainFrame, 1)
};

#endif /* _MAINFRAME_H_ */

// 
// MainFrame.hpp ends here
