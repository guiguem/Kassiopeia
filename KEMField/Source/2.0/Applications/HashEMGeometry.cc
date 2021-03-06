#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <sys/stat.h>

#include "KTypelist.hh"
#include "KSurfaceContainer.hh"

#include "KEMFileInterface.hh"
#include "KSADataStreamer.hh"
#include "KBinaryDataStreamer.hh"

#include "KMD5HashGenerator.hh"

using namespace KEMField;

template <class Typelist>
struct OmitAttributeInTypelist
{
  OmitAttributeInTypelist(KMD5HashGenerator& hashGenerator, std::string attributeName)
  {
    typedef typename Typelist::Head Head;
    typedef typename Typelist::Tail Tail;

    if (Head::Name() == attributeName)
      hashGenerator.Omit(Type2Type<Head>());
    else
      OmitAttributeInTypelist<Tail>(hashGenerator,attributeName);
  }
};

template <>
struct OmitAttributeInTypelist<KNullType>
{
  OmitAttributeInTypelist(KMD5HashGenerator&, std::string) {}
};

template <class Typelist>
struct AppendNames
{
  AppendNames(std::string prefix,std::string suffix,std::string& usage)
  {
    typedef typename Typelist::Head Head;
    typedef typename Typelist::Tail Tail;

    usage.append(prefix);
    usage.append(Head::Name());
    usage.append(suffix);
    AppendNames<Tail>(prefix,suffix,usage);
  }
};

template <>
struct AppendNames<KNullType>
{
  AppendNames(std::string,std::string,std::string&) {}
};

int main(int argc, char* argv[])
{
  std::string usage =
    "\n"
    "Usage: HashEMGeometry <GeometryFile>\n"
    "\n"
    "This program takes a KEMField geometry file and generates a unique hash from it.\n"
    "\n"
    "\tAvailable options:\n"
    "\t -h, --help               (shows this message and exits)\n"
    "\t -n, --name               (name of surface container)\n"
    "\t -o, --omit_attribute     (omits data for a surface attribute)\n"
    "\t -m, --masked_bits        (masks the least significant n bits)\n"
    "\n"
    "\tOmittable attributes:\n";

  std::string prefix = "\t\t";
  std::string suffix = ",\n";

  AppendNames<KBasisTypes>(prefix,suffix,usage);
  AppendNames<KBoundaryTypes>(prefix,suffix,usage);
  AppendNames<KShapeTypes>(prefix,suffix,usage);

  usage = usage.substr(0,usage.find_last_of(suffix)-(suffix.size()-1));
  usage.append("\n\n");

  if (argc == 1)
  {
    std::cout<<usage;
    return 0;
  }

  static struct option longOptions[] = {
    {"help", no_argument, 0, 'h'},
    {"name", required_argument, 0, 'n'},
    {"masked_bits", required_argument, 0, 'm'},
    {"omit_attribute", required_argument, 0, 'o'},
  };

  static const char *optString = "hn:m:o:";

  KMD5HashGenerator hashGenerator;
  KSurfaceContainer surfaceContainer;
  std::string name = KSurfaceContainer::Name();

  while(1) {
    char optId = getopt_long(argc, argv,optString, longOptions, NULL);
    if(optId == -1) break;
    switch(optId) {
    case('h'): // help
      std::cout<<usage<<std::endl;
      return 0;
    case('n'):
      name = optarg;
      break;
    case('m'):
      hashGenerator.MaskedBits(atoi(optarg));
      break;
    case('o'):
      OmitAttributeInTypelist<KBasisTypes>(hashGenerator,optarg);
      OmitAttributeInTypelist<KBoundaryTypes>(hashGenerator,optarg);
      OmitAttributeInTypelist<KShapeTypes>(hashGenerator,optarg);
      break;
    default: // unrecognized option
      std::cout<<usage<<std::endl;
      return 1;
    }
  }

  std::string inFileName = argv[optind];
  std::string fileSuffix = inFileName.substr(inFileName.find_last_of("."),std::string::npos);

  struct stat fileInfo;
  bool exists;
  int fileStat;

  // Attempt to get the file attributes
  fileStat = stat(inFileName.c_str(),&fileInfo);
  if(fileStat == 0)
    exists = true;
  else
    exists = false;

  if (!exists)
  {
    std::cout<<"Error: file \""<<inFileName<<"\" cannot be read."<<std::endl;
    return 1;
  }

  KBinaryDataStreamer binaryDataStreamer;

  if (fileSuffix.compare(binaryDataStreamer.GetFileSuffix()) != 0)
  {
    std::cout<<"Error: unkown file extension \""<<suffix<<"\""<<std::endl;
    return 1;
  }

  KEMFileInterface::GetInstance()->Read(inFileName,surfaceContainer,name);

  std::cout<<hashGenerator.GenerateHash(surfaceContainer)<<std::endl;

  return 0;
}
