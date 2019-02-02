// MainFrame.cpp --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 2月  2 22:09:14 2019 (+0800)
// Last-Updated: 六 2月  2 22:09:26 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 1
// URL: http://wuhongyi.cn 


/// @file MainFrame.cpp
/// @brief
/// @author S. V. Paulauskas
/// @date June 02, 2018
/// @copyright Copyright (c) 2018 S. V. Paulauskas. 
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License

#include "MainFrame.hpp"

ClassImp(MainFrame)

MainFrame::MainFrame() = default;

MainFrame::~MainFrame()
{
  // Clean up main frame...
  Cleanup();
  if (fSelected)
    {
      fSelected->Delete();
      delete fSelected;
    }
}

void MainFrame::Initialize(TApplication *app)
{
  app_ = app;
  file_ = nullptr;
  canvas_ = new TCanvas("canvas", "");
  hist = nullptr;
  // hist2d = nullptr;
  // hist3d = nullptr;

  canvas_->ToggleEditor();
  canvas_->ToggleEventStatus();
  canvas_->ToggleToolBar();

  fListBox = new TGListBox(this, 89);
  fSelected = new TList;

  isFirstPlotCall_ = true;

  // axies1d_ = std::make_pair(TAxis(), TAxis());

  SetCleanup(kDeepCleanup);
}

void MainFrame::UpdateHistogramList()
{
  fListBox->RemoveAll();
  axisMap_.clear();
    
  int id = 0;
  for (auto &&keyAsTObj : *(file_->GetListOfKeys()))
    {
      auto key = (TKey *) keyAsTObj;

      if (key->IsFolder()) //TTrees are registered as folders, we want to skip those.
	continue;

      auto obj = key->ReadObj();
      fListBox->AddEntry(TString::Format("%s ; %s",obj->GetName(),obj->GetTitle()).Data(), id);
      axisMap_.emplace(std::make_pair(id, std::make_tuple(true, TAxis(), TAxis(), TAxis(),obj->GetName())));
      id++;
    }
  gClient->NeedRedraw(fListBox->GetContainer());
  Layout();
}

void MainFrame::AddHistogramListToFrame()
{
  fListBox->Resize(frameWidth_, histogramListHeight_);
  AddFrame(fListBox, new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY, 5, 5, 5, 5));
}

void MainFrame::SetupControlButtons()
{
  // Create a horizontal frame containing button(s)
  auto *hframe = new TGHorizontalFrame(this, frameWidth_, 20, kFixedWidth);

  auto *open = new TGTextButton(hframe, "&Open");
  open->SetToolTipText("Click here to open a file");
  open->Connect("Pressed()", "MainFrame", this, "OpenFile()");
  hframe->AddFrame(open, new TGLayoutHints(kLHintsExpandX, 5, 5, 3, 4));

  auto *show = new TGTextButton(hframe, "&Show");
  show->SetToolTipText("Click here to plot the selected histogram");
  show->Connect("Pressed()", "MainFrame", this, "PlotSelected()");
  hframe->AddFrame(show, new TGLayoutHints(kLHintsExpandX, 5, 5, 3, 4));

  auto *exit = new TGTextButton(hframe, "&Exit ");
  exit->Connect("Pressed()", "MainFrame", this, "Exit()");
  hframe->AddFrame(exit, new TGLayoutHints(kLHintsExpandX, 5, 5, 3, 4));

  AddFrame(hframe, new TGLayoutHints(kLHintsExpandX, 2, 2, 5, 1)); //Expands the buttons to fill the width
  AddFrame(hframe, new TGLayoutHints(kLHintsBottom | kLHintsRight, 2, 2, 5, 1)); // positions buttons bottom right
}

void MainFrame::OpenFile()
{
  const char *filetypes[] = {"ROOT files", "*.root", nullptr, nullptr};
  TGFileInfo fi;
  fi.fFileTypes = filetypes;
  new TGFileDialog(gClient->GetRoot(), this, kFDOpen, &fi);
  if (fi.fFilename)
    {
      file_ = new TFile(fi.fFilename);
      UpdateHistogramList();
    }
}

MainFrame::MainFrame(const TGWindow *p, TApplication *app) : TGMainFrame(p)
{
  Initialize(app);
  SetupControlButtons();
  OpenFile();

  if (file_)
    AddHistogramListToFrame();

  SetWindowName(frameName_);
  MapSubwindows();
  Resize(GetDefaultSize());
  MapWindow();
}

void MainFrame::Exit()
{
  app_->Terminate(0);
}

void MainFrame::PlotSelected()
{
  fSelected->Clear();

  auto id = fListBox->GetSelected();
  auto isFirstTimePlotting = std::get<0>(axisMap_.find(id)->second);

  file_ = TFile::Open(file_->GetName());


  // if (hist)
  //   {
  //     auto histogramID = std::stoi(std::string(hist3d->GetName(), 1, std::string::npos));
  //     bool isSameId = hist->GetName() == std::get<4>(axisMap_.find(id)->second);

  //     if (!isFirstTimePlotting && isSameId)
  // 	{
  //         hist2d->GetXaxis()->Copy(std::get<1>(axisMap_.find(id)->second));
  //         hist2d->GetYaxis()->Copy(std::get<2>(axisMap_.find(id)->second));
  //         hist2d->GetZaxis()->Copy(std::get<3>(axisMap_.find(id)->second));
  // 	}
  //     else
  // 	{
  //         hist2d->GetXaxis()->Copy(std::get<1>(axisMap_.find(histogramID)->second));
  //         hist2d->GetYaxis()->Copy(std::get<2>(axisMap_.find(histogramID)->second));
  //         hist2d->GetZaxis()->Copy(std::get<3>(axisMap_.find(id)->second));
  // 	}
  //   }

  // std::cout<<std::get<4>(axisMap_.find(id)->second)<<std::endl;
  canvas_->cd();
  file_->GetObject(std::get<4>(axisMap_.find(id)->second), hist);

  if (hist)
    {
      if (!isFirstTimePlotting)
	{
	  hist->GetXaxis()->operator=(std::get<1>(axisMap_.find(id)->second));
	  hist->GetYaxis()->operator=(std::get<2>(axisMap_.find(id)->second));
	  hist->GetZaxis()->operator=(std::get<3>(axisMap_.find(id)->second));
	}
      else
	{
	  std::get<0>(axisMap_.find(id)->second) = false;
	  hist->GetXaxis()->Copy(std::get<1>(axisMap_.find(id)->second));
	  hist->GetYaxis()->Copy(std::get<2>(axisMap_.find(id)->second));
	  hist->GetZaxis()->Copy(std::get<3>(axisMap_.find(id)->second));
	}
      hist->Draw("COLZ");
    }
  else
    std::cout << "Couldn't figure out how to draw histogram with ID " << std::get<4>(axisMap_.find(id)->second) << std::endl;

  canvas_->Update();
}

// 
// MainFrame.cpp ends here
