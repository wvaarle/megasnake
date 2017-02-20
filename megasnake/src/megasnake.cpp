#include "stdafx.h"

#include "Image.h"
#include "View.h"
#include "Volume.h"
#include "VolumeLoader.h"

using namespace megasnake;

int main()
{
	auto loader = std::make_unique<VolumeLoader>();
	auto volume = loader->load("D:/work/data/OMI fusion data/japan - mouse/CT");

	auto view = std::make_shared<View>(volume);
	view->setSliceDirection(SliceDirection::Z);
	view->setSliceNumber(50);
	auto image = view->getImage();
	image->writeToFile("D:/personal/projects/megasnake/test.tiff");

    return 0;
}

