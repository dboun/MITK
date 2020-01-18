#if !defined(CaPTkLatticeRoisForMask_H__INCLUDED)
#define CaPTkLatticeRoisForMask_H__INCLUDED

#include "mitkLabelSetImage.h"

#include <vector>

namespace captk
{
class RADIOMICS_EXPORT LatticeRoisForMask
{
public:
    LatticeRoisForMask();
    ~LatticeRoisForMask();

    std::vector<mitk::LabelSetImage::Pointer> Generate(
        mitk::LabelSetImage::Pointer mask,
        int radius = 1, int neighborhood = 27, int type = 2
    );
};
}

#endif // !defined(CaPTkLatticeRoisForMask_H__INCLUDED)
