#include "KGVTKDistanceTesterBuilder.hh"
#include "KVTKWindow.h"

using namespace KGeoBag;
namespace katrin
{

    static const int sKGVTKDistanceTesterStructure =
        KGVTKDistanceTesterBuilder::Attribute< string >( "name" ) +
        KGVTKDistanceTesterBuilder::Attribute< string >( "surfaces" ) +
        KGVTKDistanceTesterBuilder::Attribute< string >( "spaces" ) +
        KGVTKDistanceTesterBuilder::Attribute< KThreeVector >( "sample_disk_origin" ) +
        KGVTKDistanceTesterBuilder::Attribute< KThreeVector >( "sample_disk_normal" ) +
        KGVTKDistanceTesterBuilder::Attribute< double >( "sample_disk_radius" ) +
        KGVTKDistanceTesterBuilder::Attribute< unsigned int >( "sample_count" ) +
        KGVTKDistanceTesterBuilder::Attribute< double >( "vertex_size" );

    static const int sKGVTKDistanceTesterWindow =
        KVTKWindowBuilder::ComplexElement< KGVTKDistanceTester >( "vtk_distance_tester" );

}