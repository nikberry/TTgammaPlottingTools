void feynman()
{
   //Draw Feynman diagrams
   //Author: Nik Berry 
  
  TString diagramName;
//  diagramName = "ttbardilepton";
  diagramName = "ttgammadilepton";
//  diagramName = "ttgammadileptonsinglephoton"; 

   TCanvas *c1 = new TCanvas("c1", "A canvas", 10,10, 600, 300);
   c1->Range(0, -40, 140, 100);
   Int_t linsav = gStyle->GetLineWidth();
   gStyle->SetLineWidth(3);
   TLatex t;
   t.SetTextAlign(22);
   t.SetTextSize(0.1);

   TCurlyLine *g;
   g = new TCurlyLine(10, 10, 30, 30); g->Draw(); 
   g = new TCurlyLine(10, 50, 30, 30); g->Draw();
   t.DrawLatex(7,10,"g");
   t.DrawLatex(7,50,"g");

   g  = new TCurlyLine(30, 30, 55, 30); g->Draw(); 
   t.DrawLatex(42.5, 39,"g");    
    
   TLine *l; 
   l = new TLine(55, 30, 75, 10); l->Draw();
   l = new TLine(55, 30, 75, 50); l->Draw();
   t.DrawLatex(65,14,"#bar{t}");
   t.DrawLatex(65,46,"t");

   TCurlyLine *W;
   W = new TCurlyLine(75,50,95,75); W->SetWavy(); W->Draw();
   t.DrawLatex(85,75,"W^{+}");
   
   l = new TLine(75,50,115,40); l->Draw();
   t.DrawLatex(85,40,"b");

   l = new TLine(95,75,115,65); l->Draw();
   l = new TLine(95,75,115,85); l->Draw();
   t.DrawLatex(120,65,"#nu_{e,#mu}");
   t.DrawLatex(120,85,"e^{+}#mu^{+}"); 

   W = new TCurlyLine(75,10,95,-15); W->SetWavy(); W->Draw();
   t.DrawLatex(85,-18,"W^{-}");
    
   l = new TLine(75,10,115,20); l->Draw(); 
   t.DrawLatex(85,22,"#bar{b}"); 
    
   l = new TLine(95,-15,115,-25); l->Draw();
   l = new TLine(95,-15,115,-10); l->Draw();
   t.DrawLatex(120,-25,"#bar{#nu}_{e,#mu}");
   t.DrawLatex(120,-10,"e^{-}#mu^{-}");

if(diagramName == "ttgammadileptonsinglephoton"){
   TCurlyLine* gamma;
   gamma = new TCurlyLine(65,40,80,95); gamma->SetWavy(); gamma->Draw();
   t.DrawLatex(69,75,"#gamma");
}

if(diagramName == "ttgammadilepton"){
   TCurlyLine* gamma;
   gamma = new TCurlyLine(65,40,80,95); gamma->SetWavy(); gamma->Draw(); //top
   gamma = new TCurlyLine(90,47,110,60); gamma->SetWavy(); gamma->Draw(); //b
   gamma = new TCurlyLine(85,0,105,7); gamma->SetWavy(); gamma->Draw(); //W
   gamma = new TCurlyLine(108,-11,125,15); gamma->SetWavy(); gamma->Draw();
   t.DrawLatex(69,75,"#gamma");
   t.DrawLatex(112,55,"#gamma");
   t.DrawLatex(108,6,"#gamma");
   t.DrawLatex(127,15,"#gamma");
}

//   TLine * l;
//   l = new TLine(10, 10, 30, 30); l->Draw();
//   l = new TLine(10, 50, 30, 30); l->Draw();
//   TCurlyArc *ginit = new TCurlyArc(30, 30, 12.5*sqrt(2), 135, 225);
//   ginit->SetWavy();
//   ginit->Draw();
//   t.DrawLatex(7,6,"e^{-}");
//   t.DrawLatex(7,55,"e^{+}");
//   t.DrawLatex(7,30,"#gamma");

//   TCurlyLine *gamma = new TCurlyLine(30, 30, 55, 30);
//   gamma->SetWavy();
//   gamma->Draw();
//   t.DrawLatex(42.5,37.7,"#gamma");

//   TArc *a = new TArc(70, 30, 15);
//   a->Draw();
//   t.DrawLatex(55, 45,"#bar{q}");
//   t.DrawLatex(85, 15,"q");
//   TCurlyLine *gluon = new TCurlyLine(70, 45, 70, 15);
//   gluon->Draw();
//   t.DrawLatex(77.5,30,"g");

//    TCurlyLine *z0 = new TCurlyLine(85, 30, 110, 30);
//    z0->SetWavy();
//    z0->Draw();
//    t.DrawLatex(100, 37.5,"Z^{0}");
   
//   l = new TLine(110, 30, 130, 10); l->Draw();
//   l = new TLine(110, 30, 130, 50); l->Draw();

//   TCurlyArc *gluon1 = new TCurlyArc(110, 30, 12.5*sqrt(2), 315, 45);
//   gluon1->Draw();

//   t.DrawLatex(135,6,"#bar{q}");
//   t.DrawLatex(135,55,"q");
//   t.DrawLatex(135,30,"g");
   c1->Update();
   gStyle->SetLineWidth(linsav);
   c1->SaveAs("Plots/FeynmanDiagrams/" + diagramName + ".pdf");
   c1->SaveAs("Plots/FeynmanDiagrams/" + diagramName + ".png");
   c1->SaveAs("Plots/FeynmanDiagrams/" + diagramName + ".eps");
}
