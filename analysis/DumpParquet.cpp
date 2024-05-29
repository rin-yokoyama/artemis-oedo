/**
 * @file DumpParquet.cpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief Dump artemis output objects to a parquet file
 * @version 0.1
 * @date 2024-01-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include "TROOT.h"
#include "ROOT/RDataFrame.hxx"
#include "TClonesArray.h"
#include "TEventHeader.h"
#include "TTimingChargeData.h"
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <arrow/pretty_print.h>
#include <arrow/record_batch.h>
#include <arrow/type.h>
#include <parquet/arrow/writer.h>
#include <vector>
#include <functional>
#include <TSystem.h>
#include "TParquetFileWriter.hpp"
#include "TTimingChargeDataBuilder.hpp"
#include "TSRPPACPlaneDataBuilder.hpp"

/** prints usage **/
void usage(char *argv0)
{
    std::cout << "[DumpParquet]: Usage: "
              << argv0 << "-i [input_file] -n [n_workers] -o [output_file]"
              << std::endl;
}

// Main function
int main(int argc, char **argv)
{
    // TString dypath = gSystem->GetDynamicPath();
    // TString incpath = gSystem->GetIncludePath();
    // incpath.Append(gSystem->GetFromPipe("artemis-config --cflags"));
    // dypath.Append(gSystem->GetFromPipe("artemis-config --dypaths"));
    // dypath.Append(":/home/sh12s24/art_analysis/user/yokoyama/install/lib");
    // incpath.Append(" -I/home/sh12s24/art_analysis/user/yokoyama/install/include");

    // dypath.Append(":/opt/GETDecoder/lib");
    // incpath.Append(" -I/opt/GETDecoder/include");

    // gSystem->SetDynamicPath(dypath);
    // gSystem->SetIncludePath(incpath);
    //  gSystem->Load("libGETDecoder");
    //  gSystem->Load("libMinuit");
    //  gSystem->Load("libGenetic");
    // gSystem->Load("libartshare");
    // gSystem->Load("libCAT");
    gSystem->Load("liboedo");
    // gSystem->Load("libartget_sh12");

    std::string input_file_name;
    std::string output_file_name = "output.parquet";
    Int_t n_workers = 1;

    /** parsing commandline arguments **/
    int opt = 0;
    while ((opt = getopt(argc, argv, "o:n:i:")) != -1)
    {
        switch (opt)
        {
        case 'o':
            output_file_name = optarg;
            break;
        case 'n':
            n_workers = std::stoi(optarg);
            break;
        case 'i':
            input_file_name = optarg;
            break;
        default:
            usage(argv[0]);
            return 1;
            break;
        }
    }

    if (input_file_name.empty())
    {
        usage(argv[0]);
        return 1;
    }

    // Enable multithreading
    // ROOT::EnableImplicitMT(n_workers);

    // Create RDataFrame from a tree.
    auto rd = std::make_shared<ROOT::RDataFrame>("tree", input_file_name);

    art::TParquetFileWriter writer(rd);

    // Define builder objects
    writer.AddBuilder(std::make_shared<art::TTimingChargeDataBuilder>("src1_x_raw"));
    writer.AddBuilder(std::make_shared<art::TTimingChargeDataBuilder>("src1_y_raw"));
    writer.AddBuilder(std::make_shared<art::TTimingChargeDataBuilder>("src2_x_raw"));
    writer.AddBuilder(std::make_shared<art::TTimingChargeDataBuilder>("src2_y_raw"));
    writer.AddBuilder(std::make_shared<art::TSRPPACPlaneDataBuilder>("src1_x"));
    writer.AddBuilder(std::make_shared<art::TSRPPACPlaneDataBuilder>("src1_y"));
    writer.AddBuilder(std::make_shared<art::TSRPPACPlaneDataBuilder>("src2_x"));
    writer.AddBuilder(std::make_shared<art::TSRPPACPlaneDataBuilder>("src2_y"));
    writer.AddBuilder(std::make_shared<art::TTimingChargeDataBuilder>("activeslit"));

    writer.Fill();
    writer.Write(output_file_name);
    return 0;
}