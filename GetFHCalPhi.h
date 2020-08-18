float GetFHCalPhi(int iModule)
{
  const int Nmodules = 45;
  int xAxisSwitch = (iModule < Nmodules) ? 1 : -1;
  int module = (iModule < Nmodules) ? iModule : iModule - Nmodules;
  float x, y, phi = -999.;
  if (module >= 0 && module <= 4)
    {
      y = 45.;
      x = (module - 2) * 15.;
      phi = TMath::ATan2(y, x * xAxisSwitch);
    }
  else if ((module >= 5) && (module <= 39))
    {
      y = (3 - (module + 2) / 7) * 15.;
      x = (3 - (module + 2) % 7) * 15.;
      phi = TMath::ATan2(y, x * xAxisSwitch);
    }
  else if ((module >= 40) && (module <= 44))
    {
      y = -45.;
      x = (module - 42) * 15.;
      phi = TMath::ATan2(y, x * xAxisSwitch);
    }
  return phi;
}
