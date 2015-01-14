#include "KSTermMaxRBuilder.h"
#include "KSRootBuilder.h"

using namespace Kassiopeia;
namespace katrin
{

    template< >
    KSTermMaxRBuilder::~KComplexElement()
    {
    }

    static int sKSTermMaxRStructure =
        KSTermMaxRBuilder::Attribute< string >( "name" ) +
        KSTermMaxRBuilder::Attribute< double >( "r" );

    static int sKSTermMaxR =
        KSRootBuilder::ComplexElement< KSTermMaxR >( "ksterm_max_r" );

}