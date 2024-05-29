#include <iostream>
#include <TFolder.h>
#include <TROOT.h>
#include "TLoopManager.h"
#include "TModuleDecoderFactory.h"
#include "TModuleDecoderFixed.h"
#include "TModuleDecoderV7XX.h"
#include "TModuleDecoderV767.h"
#include "TModuleDecoderV1190.h"
#include "TModuleDecoderV1290.h"
#include "TModuleDecoderSIS3820.h"
#include "TModuleDecoderSIS3610.h"
#include "TModuleDecoderMXDC32.h"
#include "TModuleDecoderSkip.h"
#include "TModuleDecoderA3100FreeRunTSI.h"
#include "TModuleDecoderV1740_mod.h"

int main(int argc, char **argv)
{
    std::string filename = argv[1];
    art::TLoopManager *man = art::TLoopManager::Instance();
    std::map<std::string, std::string> replace;
    if (argc == 4)
    {
        replace["NAME"] = argv[2];
        replace["NUM"] = argv[3];
    }
    art::TModuleDecoderFactory *df = art::TModuleDecoderFactory::Instance();
    // mod ID 0 : Fixed16
    const Int_t digits0 = 16;
    df->Register(new art::TModuleDecoderFixed<unsigned short>(0, digits0));
    // mod ID 1 : Fixed24
    const Int_t digits1 = 24;
    df->Register(new art::TModuleDecoderFixed<unsigned int>(1, digits1));
    // mod ID 21 : V7XX
    df->Register(new art::TModuleDecoderV7XX);
    // mod ID 23 : V767
    df->Register(new art::TModuleDecoderV767);
    // mod ID 24 : V1190
    // mod ID 25 : V1290
    // mod ID 26 : V1190C
    art::TModuleDecoder *v1190 = new art::TModuleDecoderV1190;
    art::TModuleDecoder *v1290 = new art::TModuleDecoderV1290(25);
    art::TModuleDecoder *v1190c = new art::TModuleDecoderV1190(26);
    v1190->SetVerboseLevel(kError);
    v1290->SetVerboseLevel(kError);
    v1190c->SetVerboseLevel(kError);
    df->Register(v1190);
    df->Register(v1290);
    df->Register(v1190c);
    // mod ID 36 : SIS3820
    df->Register(new art::TModuleDecoderSIS3820);
    df->Register(new art::TModuleDecoderSIS3610);
    df->Register(new art::TModuleDecoderMXDC32);

    df->Register(new art::TModuleDecoderSkip(42));

    df->Register(new art::TModuleDecoderSkip(8));
    // mod ID 59 : AMTTDC
    //    gInterpreter->ProcessLine("art::TModuleDecoderFactory::Instance()->Register(new art::TModuleDecoderAMTTDC);");
    //    df->Register(new art::TModuleDecoderAMTTDC);

    df->Register(new art::TModuleDecoderA3100FreeRunTSI);
    df->Register(new art::TModuleDecoderV1740_mod);

    // Skip for r3_2021
    df->Register(new art::TModuleDecoderSkip(9));
    df->Register(new art::TModuleDecoderSkip(30));
    df->Register(new art::TModuleDecoderSkip(33));
    df->Register(new art::TModuleDecoderSkip(30));

    // Preparation of folder for artemis
    TFolder *top = gROOT->GetRootFolder()->AddFolder("artemis", "artemis top level folders");
    gROOT->GetListOfBrowsables()->Add(top);

    man->Add(filename.c_str(), &replace);
    man->Resume();
    do
    {
        sleep(1);
    } while (man->GetLoop()->IsRunning());
    man->Suspend();
    man->Terminate();
    return 0;
}