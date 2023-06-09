/*
 * @file   TSRPPACPlaneStripDqdxProcessor.h
 * @brief  divide SRPPAC TimingChargeData into collection for each plane
 */

#ifndef TSRPPACPLANESTRIPDQDXPROCESSOR_H
#define TSRPPACPLANESTRIPDQDXPROCESSOR_H

#include <TProcessor.h>
#include "TSRPPACPlaneProcessor.h"

#include <vector>

namespace art {
   class TSRPPACPlaneStripDqdxProcessor;
   class TConverterBase;
}

class TClonesArray;

class art::TSRPPACPlaneStripDqdxProcessor : public TSRPPACPlaneProcessor {
public:
   // Default constructor
   TSRPPACPlaneStripDqdxProcessor();
   virtual ~TSRPPACPlaneStripDqdxProcessor();

   virtual void Process();

protected:
   TConverterBase** fConverter; // converter
   TString	         fConverterName;    // name of dq-to-length converter
   TConverterBase** fConverter01;
   TString	         fConverterName01;
   TConverterBase** fConverter10;
   TString	         fConverterName10;
   TConverterBase** fConverter12;
   TString	         fConverterName12;
   TConverterBase** fConverter21;
   TString	         fConverterName21;
   TConverterBase** fConverter23;
   TString	         fConverterName23;
   TConverterBase** fConverter32;
   TString	         fConverterName32;
   TConverterBase** fConverter34;
   TString	         fConverterName34;
   TConverterBase** fConverter43;
   TString	         fConverterName43;
   TConverterBase** fConverter45;
   TString	         fConverterName45;
   TConverterBase** fConverter54;
   TString	         fConverterName54;
   TConverterBase** fConverter56;
   TString	         fConverterName56;
   TConverterBase** fConverter65;
   TString	         fConverterName65;
   TConverterBase** fConverter67;
   TString	         fConverterName67;
   TConverterBase** fConverter76;
   TString	         fConverterName76;
   TConverterBase** fConverter78;
   TString	         fConverterName78;
   TConverterBase** fConverter87;
   TString	         fConverterName87;
   TConverterBase** fConverter89;
   TString	         fConverterName89;
   TConverterBase** fConverter98;
   TString	         fConverterName98;
   TConverterBase** fConverter910;
   TString	         fConverterName910;
   TConverterBase** fConverter109;
   TString	         fConverterName109;
   TConverterBase** fConverter1011;
   TString	         fConverterName1011;
   TConverterBase** fConverter1110;
   TString	         fConverterName1110;
   TConverterBase** fConverter1112;
   TString	         fConverterName1112;
   TConverterBase** fConverter1211;
   TString	         fConverterName1211;
   TConverterBase** fConverter1213;
   TString	         fConverterName1213;
   TConverterBase** fConverter1312;
   TString	         fConverterName1312;
   TConverterBase** fConverter1314;
   TString	         fConverterName1314;
   TConverterBase** fConverter1413;
   TString	         fConverterName1413;
   TConverterBase** fConverter1415;
   TString	         fConverterName1415;
   TConverterBase** fConverter1514;
   TString	         fConverterName1514;
   TConverterBase** fConverter1516;
   TString	         fConverterName1516;
   TConverterBase** fConverter1615;
   TString	         fConverterName1615;
   TConverterBase** fConverter1617;
   TString	         fConverterName1617;
   TConverterBase** fConverter1716;
   TString	         fConverterName1716;
   TConverterBase** fConverter1718;
   TString	         fConverterName1718;
   TConverterBase** fConverter1817;
   TString	         fConverterName1817;
   TConverterBase** fConverter1819;
   TString	         fConverterName1819;
   TConverterBase** fConverter1918;
   TString	         fConverterName1918;
   TConverterBase** fConverter1920;
   TString	         fConverterName1920;
   TConverterBase** fConverter2019;
   TString	         fConverterName2019;
   TConverterBase** fConverter2021;
   TString	         fConverterName2021;
   TConverterBase** fConverter2120;
   TString	         fConverterName2120;
   TConverterBase** fConverter2122;
   TString	         fConverterName2122;
   TConverterBase** fConverter2221;
   TString	         fConverterName2221;
   TConverterBase** fConverter2223;
   TString	         fConverterName2223;
   TConverterBase** fConverter2322;
   TString	         fConverterName2322;
   TConverterBase** fConverter2324;
   TString	         fConverterName2324;
   TConverterBase** fConverter2423;
   TString	         fConverterName2423;
   TConverterBase** fConverter2425;
   TString	         fConverterName2425;
   TConverterBase** fConverter2524;
   TString	         fConverterName2524;
   TConverterBase** fConverter2526;
   TString	         fConverterName2526;
   TConverterBase** fConverter2625;
   TString	         fConverterName2625;
   TConverterBase** fConverter2627;
   TString	         fConverterName2627;
   TConverterBase** fConverter2726;
   TString	         fConverterName2726;
   TConverterBase** fConverter2728;
   TString	         fConverterName2728;
   TConverterBase** fConverter2827;
   TString	         fConverterName2827;
   TConverterBase** fConverter2829;
   TString	         fConverterName2829;
   TConverterBase** fConverter2928;
   TString	         fConverterName2928;
   TConverterBase** fConverter2930;
   TString	         fConverterName2930;
   TConverterBase** fConverter3029;
   TString	         fConverterName3029;
   TConverterBase** fConverter3031;
   TString	         fConverterName3031;
   TConverterBase** fConverter3130;
   TString	         fConverterName3130;
   TConverterBase** fConverter3132;
   TString	         fConverterName3132;
   TConverterBase** fConverter3231;
   TString	         fConverterName3231;
   TConverterBase** fConverter3233;
   TString	         fConverterName3233;
   TConverterBase** fConverter3332;
   TString	         fConverterName3332;
   TConverterBase** fConverter3334;
   TString	         fConverterName3334;
   TConverterBase** fConverter3433;
   TString	         fConverterName3433;
   TConverterBase** fConverter3435;
   TString	         fConverterName3435;
   TConverterBase** fConverter3534;
   TString	         fConverterName3534;
   TConverterBase** fConverter3536;
   TString	         fConverterName3536;
   TConverterBase** fConverter3635;
   TString	         fConverterName3635;
   TConverterBase** fConverter3637;
   TString	         fConverterName3637;
   TConverterBase** fConverter3736;
   TString	         fConverterName3736;
   TConverterBase** fConverter3738;
   TString	         fConverterName3738;
   TConverterBase** fConverter3837;
   TString	         fConverterName3837;
   TConverterBase** fConverter3839;
   TString	         fConverterName3839;
   TConverterBase** fConverter3938;
   TString	         fConverterName3938;
   TConverterBase** fConverter3940;
   TString	         fConverterName3940;
   TConverterBase** fConverter4039;
   TString	         fConverterName4039;
   TConverterBase** fConverter4041;
   TString	         fConverterName4041;
   TConverterBase** fConverter4140;
   TString	         fConverterName4140;
   TConverterBase** fConverter4142;
   TString	         fConverterName4142;
   TConverterBase** fConverter4241;
   TString	         fConverterName4241;
   TConverterBase** fConverter4243;
   TString	         fConverterName4243;
   TConverterBase** fConverter4342;
   TString	         fConverterName4342;
   TConverterBase** fConverter4344;
   TString	         fConverterName4344;
   TConverterBase** fConverter4443;
   TString	         fConverterName4443;
   TConverterBase** fConverter4445;
   TString	         fConverterName4445;
   TConverterBase** fConverter4544;
   TString	         fConverterName4544;
   TConverterBase** fConverter4546;
   TString	         fConverterName4546;
   TConverterBase** fConverter4645;
   TString	         fConverterName4645;
   TConverterBase** fConverter4647;
   TString	         fConverterName4647;
   TConverterBase** fConverter4746;
   TString	         fConverterName4746;
   TConverterBase** fConverter4748;
   TString	         fConverterName4748;
   TConverterBase** fConverter4847;
   TString	         fConverterName4847;
   TConverterBase** fConverter4849;
   TString	         fConverterName4849;
   TConverterBase** fConverter4948;
   TString	         fConverterName4948;
   TConverterBase** fConverter4950;
   TString	         fConverterName4950;
   TConverterBase** fConverter5049;
   TString	         fConverterName5049;
   TConverterBase** fConverter5051;
   TString	         fConverterName5051;
   TConverterBase** fConverter5150;
   TString	         fConverterName5150;
   TConverterBase** fConverter5152;
   TString	         fConverterName5152;
   TConverterBase** fConverter5251;
   TString	         fConverterName5251;
   TConverterBase** fConverter5253;
   TString	         fConverterName5253;
   TConverterBase** fConverter5352;
   TString	         fConverterName5352;
   TConverterBase** fConverter5354;
   TString	         fConverterName5354;
   TConverterBase** fConverter5453;
   TString	         fConverterName5453;
   TConverterBase** fConverter5455;
   TString	         fConverterName5455;
   TConverterBase** fConverter5554;
   TString	         fConverterName5554;
   TConverterBase** fConverter5556;
   TString	         fConverterName5556;
   TConverterBase** fConverter5655;
   TString	         fConverterName5655;
   TConverterBase** fConverter5657;
   TString	         fConverterName5657;
   TConverterBase** fConverter5756;
   TString	         fConverterName5756;
   TConverterBase** fConverter5758;
   TString	         fConverterName5758;
   TConverterBase** fConverter5857;
   TString	         fConverterName5857;
   TConverterBase** fConverter5859;
   TString	         fConverterName5859;
   TConverterBase** fConverter5958;
   TString	         fConverterName5958;
   TConverterBase** fConverter5960;
   TString	         fConverterName5960;
   TConverterBase** fConverter6059;
   TString	         fConverterName6059;
   TConverterBase** fConverter6061;
   TString	         fConverterName6061;
   TConverterBase** fConverter6160;
   TString	         fConverterName6160;
   TConverterBase** fConverter6162;
   TString	         fConverterName6162;
   TConverterBase** fConverter6261;
   TString	         fConverterName6261;
   TConverterBase** fConverter6263;
   TString	         fConverterName6263;
   TConverterBase** fConverter6362;
   TString	         fConverterName6362;
   TConverterBase** fConverter6364;
   TString	         fConverterName6364;
   TConverterBase** fConverter6463;
   TString	         fConverterName6463;
   TConverterBase** fConverter6465;
   TString	         fConverterName6465;
   TConverterBase** fConverter6564;
   TString	         fConverterName6564;
   TConverterBase** fConverter6566;
   TString	         fConverterName6566;
   TConverterBase** fConverter6665;
   TString	         fConverterName6665;
   TConverterBase** fConverter6667;
   TString	         fConverterName6667;
   TConverterBase** fConverter6766;
   TString	         fConverterName6766;
   TConverterBase** fConverter6768;
   TString	         fConverterName6768;
   TConverterBase** fConverter6867;
   TString	         fConverterName6867;
   TConverterBase** fConverter6869;
   TString	         fConverterName6869;
   TConverterBase** fConverter6968;
   TString	         fConverterName6968;
   TConverterBase** fConverter6970;
   TString	         fConverterName6970;
   TConverterBase** fConverter7069;
   TString	         fConverterName7069;
   TConverterBase** fConverter7071;
   TString	         fConverterName7071;
   TConverterBase** fConverter7170;
   TString	         fConverterName7170;
   TConverterBase** fConverter7172;
   TString	         fConverterName7172;
   TConverterBase** fConverter7271;
   TString	         fConverterName7271;
   TConverterBase** fConverter7273;
   TString	         fConverterName7273;
   TConverterBase** fConverter7372;
   TString	         fConverterName7372;
   TConverterBase** fConverter7374;
   TString	         fConverterName7374;
   TConverterBase** fConverter7473;
   TString	         fConverterName7473;
   TConverterBase** fConverter7475;
   TString	         fConverterName7475;
   TConverterBase** fConverter7574;
   TString	         fConverterName7574;
   TConverterBase** fConverter7576;
   TString	         fConverterName7576;
   TConverterBase** fConverter7675;
   TString	         fConverterName7675;
   TConverterBase** fConverter7677;
   TString	         fConverterName7677;
   TConverterBase** fConverter7776;
   TString	         fConverterName7776;
   TConverterBase** fConverter7778;
   TString	         fConverterName7778;
   TConverterBase** fConverter7877;
   TString	         fConverterName7877;
   TConverterBase** fConverter7879;
   TString	         fConverterName7879;
   TConverterBase** fConverter7978;
   TString	         fConverterName7978;
   TConverterBase** fConverter7980;
   TString	         fConverterName7980;
   TConverterBase** fConverter8079;
   TString	         fConverterName8079;
   TConverterBase** fConverter8081;
   TString	         fConverterName8081;
   TConverterBase** fConverter8180;
   TString	         fConverterName8180;
   TConverterBase** fConverter8182;
   TString	         fConverterName8182;
   TConverterBase** fConverter8281;
   TString	         fConverterName8281;
   TConverterBase** fConverter8283;
   TString	         fConverterName8283;
   TConverterBase** fConverter8382;
   TString	         fConverterName8382;
   TConverterBase** fConverter8384;
   TString	         fConverterName8384;
   TConverterBase** fConverter8483;
   TString	         fConverterName8483;
   TConverterBase** fConverter8485;
   TString	         fConverterName8485;
   TConverterBase** fConverter8584;
   TString	         fConverterName8584;
   TConverterBase** fConverter8586;
   TString	         fConverterName8586;
   TConverterBase** fConverter8685;
   TString	         fConverterName8685;
   TConverterBase** fConverter8687;
   TString	         fConverterName8687;
   TConverterBase** fConverter8786;
   TString	         fConverterName8786;
   TConverterBase** fConverter8788;
   TString	         fConverterName8788;
   TConverterBase** fConverter8887;
   TString	         fConverterName8887;
   TConverterBase** fConverter8889;
   TString	         fConverterName8889;
   TConverterBase** fConverter8988;
   TString	         fConverterName8988;
   TConverterBase** fConverter8990;
   TString	         fConverterName8990;
   TConverterBase** fConverter9089;
   TString	         fConverterName9089;
   TConverterBase** fConverter9091;
   TString	         fConverterName9091;
   TConverterBase** fConverter9190;
   TString	         fConverterName9190;
   TConverterBase** fConverter9192;
   TString	         fConverterName9192;
   TConverterBase** fConverter9291;
   TString	         fConverterName9291;
   TConverterBase** fConverter9293;
   TString	         fConverterName9293;
   TConverterBase** fConverter9392;
   TString	         fConverterName9392;
   TConverterBase** fgainConverter; // converter
   TString	         fgainConverterName;    // name of dq-to-length converter
   Int_t fCombination;

   ClassDef(TSRPPACPlaneStripDqdxProcessor,0) // processor for SRPPAC plane division
};

#endif // TSRPPACPLANSTRIPDQDXEPROCESSOR_H
