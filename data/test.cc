// test.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 2月  2 19:14:32 2019 (+0800)
// Last-Updated: 六 2月  2 21:18:32 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 6
// URL: http://wuhongyi.cn 

void test()
{
  TH1I *h1 = new TH1I("h","",100,0,1);
  TH2D *h2 = new TH2D("h","",100,0,1,100,0,1);

  h1->Fill(0.2);
  h2->Fill(0.8,0.8);
}

// 
// test.cc ends here

















