#include "KGCutConeSpaceBuilder.hh"
#include "KGInterfaceBuilder.hh"

namespace katrin
{

    static const int sKGCutConeSpaceBuilder =
        KGInterfaceBuilder::ComplexElement< KGCutConeSpace >( "cut_cone_space" );

    static const int sKGCutConeSpaceBuilderStructure =
        KGCutConeSpaceBuilder::Attribute< string >( "name" ) +
        KGCutConeSpaceBuilder::Attribute< double >( "z1" ) +
        KGCutConeSpaceBuilder::Attribute< double >( "z2" ) +
        KGCutConeSpaceBuilder::Attribute< double >( "r1" ) +
        KGCutConeSpaceBuilder::Attribute< double >( "r2" ) +
        KGCutConeSpaceBuilder::Attribute< unsigned int >( "longitudinal_mesh_count" ) +
        KGCutConeSpaceBuilder::Attribute< double >( "longitudinal_mesh_power" ) +
        KGCutConeSpaceBuilder::Attribute< unsigned int >( "radial_mesh_count" ) +
        KGCutConeSpaceBuilder::Attribute< double >( "radial_mesh_power" ) +
        KGCutConeSpaceBuilder::Attribute< unsigned int >( "axial_mesh_count" );
}